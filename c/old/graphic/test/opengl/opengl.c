
#include <GL/glut.h>

void reshape(int w, int h){
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(0, 0);
	glColor3f(0.0, 0.0, 0.1);
	glVertex2i(0, 500);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(500, 500);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(500, 0);

	glEnd();


	glutSwapBuffers();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); /* Double bufferisation. */

	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL test");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutMainLoop();

	return 0 ;
}

