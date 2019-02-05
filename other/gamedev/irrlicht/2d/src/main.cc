/** Example 006 2D Graphics

This Tutorial shows how to do 2d graphics with the Irrlicht Engine.
It shows how to draw images, keycolor based sprites,
transparent rectangles, and different fonts. You may consider
this useful if you want to make a 2d game with the engine, or if
you want to draw a cool interface or head up display for your 3d game.

As always, I include the header files, use the irr namespace,
and tell the linker to link with the .lib file.
*/
#include <irrlicht.h>
#include <iostream>
#include <vector>
#include <new>
#include "driverChoice.h" // Choosing driver.

using namespace irr;

typedef core::position2d<s32> sposition2d ;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

class MapObjectsHandler;

/*
At first, we let the user select the driver type, then start up the engine, set
a caption, and get a pointer to the video driver.
*/

// Example event receiver.
class MyEventReceiver : public IEventReceiver {
	public:
		// This is the one method that we have to implement
		virtual bool OnEvent(const SEvent& event)
		{
			// Remember whether each key is down or up
			if (event.EventType == irr::EET_KEY_INPUT_EVENT)
				KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

			/*
			Always return false by default. If you return true you tell the engine
			that you handled this event completely and the Irrlicht should not
			process it any further. So for example if you return true for all 
			EET_KEY_INPUT_EVENT events then Irrlicht would not pass on key-events
			to it's GUI system.
			*/
			return false;
		}

		// This is used to check whether a key is being held down
		virtual bool IsKeyDown(EKEY_CODE keyCode) const
		{
			return KeyIsDown[keyCode];
		}
		
		MyEventReceiver()
		{
			for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
				KeyIsDown[i] = false;
		}
	private:
		// We use this array to store the current state of each key
		bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

class ICamera {
	public:
		ICamera(sposition2d position=sposition2d()){
			this->position = position ;
		}
		virtual void setPosition(sposition2d position){
			this->position = position ;
		}
		virtual sposition2d getPosition(void){
			return this->position ;
		}
		virtual void move(sposition2d vector){
			this->position ;
		}
	protected:
	private:	
		sposition2d position;
};

class IObject {// Class for all objects.
	public: 
		IObject(MapObjectsHandler *handler, sposition2d position=sposition2d()){
			this->handler  = handler  ;
			this->position = position ;
			this->onStart();
		}

		// This function will be called every frame.
		virtual void onFrame(const f32 frame_delta_time) = 0;

		/*{
			std::cout<<"You have to override 'onFrame' method right now."<<std::endl;
		}*/

		// This function will be called when one time when object created.
		virtual void onStart(void){};
		virtual void Draw(void) = 0 ;
		
		/*{
			std::cout<<"You have to override 'onStart' method right now."<<std::endl;
		}*/

		// Position.
		virtual void setPosition(sposition2d position){ this->position = position ; }
		sposition2d getPosition(void){	return position ; }
	protected:
		// Object position in 2D area.
		sposition2d position;
		MapObjectsHandler *handler;

	private:
};

class IMapObject : public IObject {
	// Change position with camera position.
	public:
		// Move by vector.
		virtual void move(sposition2d vector){
			this->setPosition(this->getPosition()+vector) ;
		}
		virtual void onFrame(const f32 frame_delta_time){
			//std::cout<<"You have to override 'onFrame' method right now."<<std::endl;
		}
		virtual void onStart(void){}
		virtual void moveCameraDepends(void){
			this->position -= this->handler->camera->getPosition() ;
		}
	protected:
	private:
};

class IAnimatedObject : IMapObject{
	public:
		// Objects with animation interface.
		void onFrame(const s32 frame_delta_time){	
		}

		// This function gets to draw animation.
		virtual void Animate(const f32 frame_delta_time) = 0 ;
		virtual void AnimateRealisation();
	protected:
	private:
};

class IMobObject : IAnimatedObject {
	public:	
		// Change position of object.
	protected:
		// All characteristics mobs have.
		s32 health_points;
		s32 movement_speed;
	private:
};

class ImpObject : IMobObject {	
	public:
	protected:
	private:
};

class IBuildingObject : IMapObject {
	public:
	protected:
	private:
};

class MapObjectsHandler {
	/*
	 * This is class to handle everything in loop.
	 * It's main handler of engine, it calls onFrame
	 * of all objects we can see right now.
	 */
	public:
		MapObjectsHandler(IrrlichtDevice *device, IEventReceiver *event_receiver){
			this->device         = device ;
			this->event_receiver = event_receiver ;
			this->camera         = new ICamera() ;
			this->driver         = device->getVideoDriver() ;
		};

		void mainLoopCycle(void){	
			while(this->device->run() && this->driver){

				u32 then = this->device->getTimer()->getTime() ;
				// This loops does function onFrame of every existing object.
				for( auto object : this->map_objects ){
					// Getting difference between frames.
					const u32 now = this->device->getTimer()->getTime() ;
					const f32 frame_delta_time = (f32)(now-then)/1000.f ;

					// Calling function you should realize for every object.
					object->onFrame(frame_delta_time);
					object->moveCameraDepends();
					object->Draw();
					driver->endScene();
				}
			}
		};

		void addMapObject(IMapObject *object){
			// Adding new object to handle on the map.
			this->map_objects.push_back(object);
		}
		std::vector<IMapObject *> map_objects;

		IEventReceiver      *event_receiver;
		ICamera             *camera;
		IrrlichtDevice      *device;
		video::IVideoDriver *driver;
	protected:
	private:
};

int main(){
	// Ask user for driver.
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;

	// Create device.
	//
	MyEventReceiver receiver;
	IrrlichtDevice *device = createDevice(driverType,
		core::dimension2d<u32>(512, 384), 16,
		false, false, false, &receiver);

	if (device == 0)
		return 1; // Could not create selected driver.

	

	device->setWindowCaption(L"Irrlicht Engine - 2D Graphics Demo");

	video::IVideoDriver* driver = device->getVideoDriver();

	/*
	All 2d graphics in this example are put together into one texture,
	2ddemo.png. Because we want to draw colorkey based sprites, we need to
	load this texture and tell the engine, which part of it should be
	transparent based on a colorkey.

	In this example, we don't tell it the color directly, we just say "Hey
	Irrlicht Engine, you'll find the color I want at position (0,0) on the
	texture.". Instead, it would be also possible to call
	driver->makeColorKeyTexture(images, video::SColor(0,0,0,0)), to make
	e.g. all black pixels transparent. Please note that
	makeColorKeyTexture just creates an alpha channel based on the color.
	*/
	video::ITexture* images = driver->getTexture("../../media/graphics/2ddemo.png");
	driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));

	/*
	To be able to draw some text with two different fonts, we first load
	them. Ok, we load just one. As the first font we just use the default
	font which is built into the engine. Also, we define two rectangles
	which specify the position of the images of the red imps (little flying
	creatures) in the texture.
	*/
	gui::IGUIFont* font = device->getGUIEnvironment()->getBuiltInFont();
	gui::IGUIFont* font2 =
		device->getGUIEnvironment()->getFont("../../media/fonthaettenschweiler.bmp");

	core::rect<s32> imp1(348,14,385,78);
	core::rect<s32> imp2(387,15,423,78);

	/*
	Prepare a nicely filtering 2d render mode for special cases.
	*/
	driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
	driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;

	/*
	Everything is prepared, now we can draw everything in the draw loop,
	between the begin scene and end scene calls. In this example, we are
	just doing 2d graphics, but it would be no problem to mix them with 3d
	graphics. Just try it out, and draw some 3d vertices or set up a scene
	with the scene manager and draw it.
	*/
	core::position2d<s32> camera_position(0, 0);
	while(device->run() && driver) {
		if( device->isWindowActive() ){
			u32 time = device->getTimer()->getTime();

			driver->beginScene(true, true, video::SColor(255,120,102,136));

			if(       receiver.IsKeyDown(irr::KEY_KEY_S) ){
				camera_position.Y += 2 ;
			}if( receiver.IsKeyDown(irr::KEY_KEY_W) ){
				camera_position.Y -= 2 ;
			}if( receiver.IsKeyDown(irr::KEY_KEY_D) ){
				camera_position.X += 2 ;
			}if( receiver.IsKeyDown(irr::KEY_KEY_A)){
				camera_position.X -= 2 ;
			}
			/*
			First, we draw 3 sprites, using the alpha channel we
			created with makeColorKeyTexture. The last parameter
			specifies that the drawing method should use this alpha
			channel. The last-but-one parameter specifies a
			color, with which the sprite should be colored.
			(255,255,255,255) is full white, so the sprite will
			look like the original. The third sprite is drawn
			with the red channel modulated based on the time.
			*/

			// Draw fire & dragons background world.
			driver->draw2DImage(images, core::position2d<s32>(50,50)-camera_position,
				core::rect<s32>(0,0,342,224), 0,
				video::SColor(255,255,255,255), true);

			// Draw flying imp.
			driver->draw2DImage(
			   images,
			   core::position2d<s32>(164,125)-camera_position,
			   (time/500 % 2) ? imp1 : imp2,
			   0,
			   video::SColor(255,255,255,255),
			   true
			);

			// Draw second flying imp with colorcylce
			driver->draw2DImage(images, core::position2d<s32>(20,105)-camera_position,
				(time/500 % 2) ? imp1 : imp2, 0,
				video::SColor(255,(time) % 255,255,255), true);

			/*
			Drawing text is really simple. The code should be self
			explanatory.
			*/

			// draw some text
			/*if (font)
				font->draw(L"This demo shows that Irrlicht is also capable of drawing 2D graphics.",
					core::rect<s32>(130,10,300,50),
					video::SColor(255,255,255,255));*/

			// draw some other text
			/*if (font2)
				font2->draw(L"Also mixing with 3d graphics is possible.",
					core::rect<s32>(130,20,300,60),
					video::SColor(255,time % 255,time % 255,255));*/

			
			/*Next, we draw the Irrlicht Engine logo (without
			using a color or an alpha channel). Since we slightly scale
			the image we use the prepared filter mode.
			*/
			/*driver->enableMaterial2D();
			driver->draw2DImage(images, core::rect<s32>(10,10,108,48),
				core::rect<s32>(354,87,442,118));
			driver->enableMaterial2D(false);
			*/

			/*
			Finally draw a half-transparent rect under the mouse cursor.
			*/
			/*core::position2d<s32> m = device->getCursorControl()->getPosition() ;
			driver->draw2DRectangle(video::SColor(100,255,255,255),
				core::rect<s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));
				*/

			//driver->endScene();
		}
	}

	device->drop();

	return 0;
}
