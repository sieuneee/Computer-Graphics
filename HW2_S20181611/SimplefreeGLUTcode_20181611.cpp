#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

int rightbuttonpressed = 0;
float r_line = 1.0f, g_line = 1.0f, b_line = 1.0f;
//float r = 0.0f, g = 0.0f, b = 0.0f; // Backgroud color = Black
float r = 250.0f / 255.0f, g = 128.0f / 255.0f, b = 114.0f / 255.0f; // Background color = Salmon
//float leftbutton = 0.1;
//float rightbutton = 0.1;
float x1=-1.0f, x2=0.0f;


void display(void) {
	glClearColor(r, g, b, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(r_line, g_line, b_line);
	glBegin(GL_LINES);
	glVertex2f(x1, 0.0f); glVertex2f(x2, 0.0f);
	glEnd();
	glFlush();
}


void display_toggle(void) {
	glClearColor(r_line, g_line, b_line, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(r, g, b);
	glBegin(GL_LINES);
	glVertex2f(x1, 0.0f); glVertex2f(x2, 0.0f);
	glEnd();
	glFlush();
}


void display_c(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(255.0, 255.0, 255.0);

	glVertex3f(0.0, -0.25, 0.0);
	glVertex3f(0.25, -0.4, 0.0);
	glVertex3f(0.15, -0.15, 0.0);
	glVertex3f(0.35, 0.05, 0.0);
	glVertex3f(0.1, 0.05, 0.0);
	glVertex3f(0.0, 0.35, 0.0);
	glVertex3f(-0.1, 0.05, 0.0);
	glVertex3f(-0.35, 0.05, 0.0);
	glVertex3f(-0.15, -0.15, 0.0);
	glVertex3f(-0.25, -0.4, 0.0);

	glEnd();
	glFlush();
}

void display_rightmouse(void) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(r_line, g_line, b_line);
	glBegin(GL_LINES);
	x1 = x1 + 0.1;
	x2 = x2 + 0.1;
	glVertex2f(x1, 0.0f); glVertex2f(x2, 0.0f);
	glEnd();
	glFlush();
}

void display_leftmouse(void) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(r_line, g_line, b_line);
	glBegin(GL_LINES);
	x1 = x1 - 0.1;
	x2 = x2 - 0.1;
	glVertex2f(x1, 0.0f); glVertex2f(x2, 0.0f);
	glEnd();
	glFlush();
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		r = 1.0f; g = b = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 'g':
		g = 1.0f; r = b = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 'b':
		b = 1.0f; r = g = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 's':
		glutDisplayFunc(display);
		r = 250.0f / 255.0f, g = 128.0f / 255.0f, b = 114.0f / 255.0f;
		r_line = 1.0f, g_line = 1.0f, b_line = 1.0f;
		x1 = -1.0f, x2 = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 'c':
		glutDisplayFunc(display_c);
		glutPostRedisplay();
		break;
	case 'x':
		glutDisplayFunc(display);
		glutPostRedisplay();
		break;
	case 'q':
		glutLeaveMainLoop(); 
		break;
	}
}

void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		r -= 0.1f;
		if (r < 0.0f) r = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		r += 0.1f;
		if (r > 1.0f) r = 1.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		g -= 0.1f;
		if (g < 0.0f) g = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		g += 0.1f;
		if (g > 1.0f) g = 1.0f;  
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	}
}

void mousepress(int button, int state, int x, int y) {
	int key;
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		key = glutGetModifiers();
		if (key == GLUT_ACTIVE_SHIFT) {
			glutDisplayFunc(display_toggle);
			glutPostRedisplay();
		}
		else {
			glutDisplayFunc(display_leftmouse);
			fprintf(stdout, "*** The left mouse button was pressed at (%d, %d).\n", x, y);
		}
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		key = glutGetModifiers();
		if (key == GLUT_ACTIVE_SHIFT) {
			glutDisplayFunc(display);
			glutPostRedisplay();
		}
	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		glutDisplayFunc(display_rightmouse);
		rightbuttonpressed = 1;
	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP))
		rightbuttonpressed = 0;
}

void mousemove(int x, int y) {
	if (rightbuttonpressed) 
		fprintf(stdout, "$$$ The right mouse button is now at (%d, %d).\n", x, y);
}
	
void reshape(int width, int height) {
	fprintf(stdout, "### The new window size is %dx%d.\n", width, height);
}

void close(void) {
	fprintf(stdout, "\n^^^ The control is at the close callback function now.\n\n");
}

void register_callbacks(void) {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mousepress);
	glutMotionFunc(mousemove);
	glutReshapeFunc(reshape);
 	glutCloseFunc(close);
}

void initialize_renderer(void) {
	register_callbacks();
}

void initialize_glew(void) {
	GLenum error;

	glewExperimental = TRUE;
	error = glewInit();
	if (error != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		exit(-1);
	}
	fprintf(stdout, "*********************************************************\n");
	fprintf(stdout, " - GLEW version supported: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, " - OpenGL renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, " - OpenGL version supported: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "*********************************************************\n\n");
}

void greetings(char *program_name, char messages[][256], int n_message_lines) {
	fprintf(stdout, "**************************************************************\n\n");
	fprintf(stdout, "  PROGRAM NAME: %s\n\n", program_name);
	fprintf(stdout, "    This program was coded for CSE4170 students\n");
	fprintf(stdout, "      of Dept. of Comp. Sci. & Eng., Sogang University.\n\n");

	for (int i = 0; i < n_message_lines; i++)
		fprintf(stdout, "%s\n", messages[i]);
	fprintf(stdout, "\n**************************************************************\n\n");

	initialize_glew();
}

#define N_MESSAGE_LINES 4
void main(int argc, char *argv[]) {
	char program_name[64] = "Sogang CSE4170 SimplefreeGLUTcode";
	char messages[N_MESSAGE_LINES][256] = {
		"    - Keys used: 'r', 'g', 'b', 's', 'c', 'x', 'q'",
		"    - Special keys used: LEFT, RIGHT, UP, DOWN",
		"    - Mouse used: L-click, R-click and move",
		"    - Other operations: window size change, shift key +left mouse click"
	};

	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // <-- Be sure to use this profile for this example code!
 //	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 200);
	glutCreateWindow(program_name);

	greetings(program_name, messages, N_MESSAGE_LINES);
	initialize_renderer();

 //   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_EXIT); // default
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutMainLoop();
	fprintf(stdout, "^^^ The control is at the end of main function now.\n\n");
}