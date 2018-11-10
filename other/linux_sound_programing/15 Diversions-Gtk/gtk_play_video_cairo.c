
#include <gtk/gtk.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#define OVERLAY_IMAGE "jan-small.png"

GtkWidget *image;
GtkWidget *window;
int width, height;

/* FFMpeg vbls */
AVFormatContext *pFormatCtx = NULL;
AVCodecContext *pCodecCtx = NULL;
int videoStream;
struct SwsContext *sws_ctx = NULL;
AVCodec *pCodec = NULL;

static void pixmap_destroy_notify(guchar *pixels,
				  gpointer data) {
    printf("Destroy pixmap - not sure how\n");
}

static gboolean draw_image(gpointer user_data) {
    GdkPixbuf *pixbuf = (GdkPixbuf *) user_data;

    gtk_image_set_from_pixbuf((GtkImage *) image, pixbuf);
    gtk_widget_queue_draw(image);
    g_object_unref(pixbuf);
    
    return G_SOURCE_REMOVE;
}

static void *play_background(void *args) {

    int i;
    AVPacket packet;
    int frameFinished;
    AVFrame *pFrame = NULL;

    int bytesDecoded;
    GdkPixbuf *pixbuf;
    GdkPixbuf *overlay_pixbuf;
    AVFrame *picture_RGB;
    char *buffer;

    GError *error = NULL;
    overlay_pixbuf = gdk_pixbuf_new_from_file(OVERLAY_IMAGE, &error);
    if (!overlay_pixbuf) {
	fprintf(stderr, "%s\n", error->message);
	g_error_free(error);
	exit(1);
    }

    // add an alpha layer for a white background
    overlay_pixbuf = gdk_pixbuf_add_alpha(overlay_pixbuf, TRUE, 255, 255, 255);

    int overlay_width = gdk_pixbuf_get_width(overlay_pixbuf);
    int overlay_height =  gdk_pixbuf_get_height(overlay_pixbuf);

    pFrame=av_frame_alloc();

    i=0;
    picture_RGB = av_frame_alloc();
    buffer = malloc (avpicture_get_size(PIX_FMT_RGB24, width, height));
    avpicture_fill((AVPicture *)picture_RGB, buffer, PIX_FMT_RGB24, width, height);

    while(av_read_frame(pFormatCtx, &packet)>=0) {
	if(packet.stream_index==videoStream) {
	    usleep(33670);  // 29.7 frames per second
	    // Decode video frame
	    avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished,
				  &packet);

	    int width = pCodecCtx->width;
	    int height = pCodecCtx->height;
	    
	    sws_ctx = sws_getContext(width, height, pCodecCtx->pix_fmt, width, height, 
				     PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

	    if (frameFinished) {
		printf("Frame %d\n", i++);
		
		sws_scale(sws_ctx,  (uint8_t const * const *) pFrame->data, pFrame->linesize, 0, height, picture_RGB->data, picture_RGB->linesize);
		
		printf("old width %d new width %d\n",  pCodecCtx->width, picture_RGB->width);
		pixbuf = gdk_pixbuf_new_from_data(picture_RGB->data[0], GDK_COLORSPACE_RGB,
						  0, 8, width, height, 
						  picture_RGB->linesize[0], pixmap_destroy_notify,
						  NULL);

		// Create the destination surface
		cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 
								       width, height);
		cairo_t *cr = cairo_create(surface);

		// draw the background image
		gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
		cairo_paint (cr);

		// overlay an image on top
		// alpha blending will be done by Cairo
		gdk_cairo_set_source_pixbuf(cr, overlay_pixbuf, 300, 200);
		cairo_paint (cr);

		// draw some white text on top
		cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
		// this is a standard font for Cairo
		cairo_select_font_face (cr, "cairo:serif",
					CAIRO_FONT_SLANT_NORMAL, 
					CAIRO_FONT_WEIGHT_BOLD);
		cairo_set_font_size (cr, 20);
		cairo_move_to(cr, 10.0, 50.0);
		cairo_show_text (cr, "hello");



		pixbuf = gdk_pixbuf_get_from_surface(surface,
						     0,
						     0,
						     width,
						     height);
		gdk_threads_add_idle(draw_image, pixbuf);		

		/* reclaim memory */
		sws_freeContext(sws_ctx);
		cairo_surface_destroy(surface);
		cairo_destroy(cr);
	    }
	}
	av_free_packet(&packet);
    }

    printf("Video over!\n");
    exit(0);
}

/* Called when the windows are realized
 */
static void realize_cb (GtkWidget *widget, gpointer data) {
    /* start the video playing in its own thread */
    pthread_t tid;
    pthread_create(&tid, NULL, play_background, NULL);
}

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */
    return TRUE;
}

/* Another callback */
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

int main(int argc, char** argv)
{
    int i;


    /* FFMpeg stuff */

    AVFrame *pFrame = NULL;
    AVPacket packet;

    AVDictionary *optionsDict = NULL;

    av_register_all();

    if(avformat_open_input(&pFormatCtx, "short.mpg", NULL, NULL)!=0)
	return -1; // Couldn't open file
  
    // Retrieve stream information
    if(avformat_find_stream_info(pFormatCtx, NULL)<0)
	return -1; // Couldn't find stream information
  
    // Dump information about file onto standard error
    av_dump_format(pFormatCtx, 0, argv[1], 0);
  
    // Find the first video stream
    videoStream=-1;
    for(i=0; i<pFormatCtx->nb_streams; i++)
	if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
	    videoStream=i;
	    break;
	}
    if(videoStream==-1)
	return -1; // Didn't find a video stream

    for(i=0; i<pFormatCtx->nb_streams; i++)
	if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO) {
	    printf("Found an audio stream too\n");
	    break;
	}

  
    // Get a pointer to the codec context for the video stream
    pCodecCtx=pFormatCtx->streams[videoStream]->codec;
  
    // Find the decoder for the video stream
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec==NULL) {
	fprintf(stderr, "Unsupported codec!\n");
	return -1; // Codec not found
    }
  
    // Open codec
    if(avcodec_open2(pCodecCtx, pCodec, &optionsDict)<0)
	return -1; // Could not open codec

    width =  pCodecCtx->width;
    height =  pCodecCtx->height;

    sws_ctx =
	sws_getContext
	(
	 pCodecCtx->width,
	 pCodecCtx->height,
	 pCodecCtx->pix_fmt,
	 pCodecCtx->width,
	 pCodecCtx->height,
	 PIX_FMT_YUV420P,
	 SWS_BILINEAR,
	 NULL,
	 NULL,
	 NULL
	 );

    /* GTK stuff now */
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);
    g_signal_connect (window, "destroy",
		      G_CALLBACK (destroy), NULL);
    g_signal_connect (window, "realize", G_CALLBACK (realize_cb), NULL);
    

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    image = gtk_image_new();
    gtk_widget_show (image);

    gtk_container_add (GTK_CONTAINER (window), image);
    gtk_widget_show (window);
    
    gtk_main ();
    
    return 0;
}

