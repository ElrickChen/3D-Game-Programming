#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#ifdef _WIN64
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif
//#include "Polyhedron.h"
#include "Hw5Man.h"
#include "Hw5Scene.h"
#include "Hw5Audio.h"
#include "Hw5Camera.h"

#define PI 3.14159265358979323846f

/*----------視窗的寬跟高----------*/
int windowWidth = 1280, windowHeight = 720;
/*----------眼睛座標的平移旋轉----------*/
float eyePosition[] = { 0, 0, -70 };
float eyeRadius = 70;
float windowMove[] = { 0, 0 };
int XY[] = { 0, 0 };
/*----------平行光的參數----------*/
float light_position[4] = { 1, 1, 1, 0 };
float light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
float mat_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
float theta, phi;
bool keyBuffer[256];

//polyhedron *scene;
Man protagonist, enemy, target;
unsigned int time = 20;	// 1000/20 >> fps = 50

void prepare_lighting() {
	//theta = fmodf(theta, 2 * PI);
	//phi = fmodf(phi, 2 * PI);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
}

void initial() {
	GLenum err = glewInit();
	if (GLEW_OK != err)printf("Error: %s\n", glewGetErrorString(err));

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, windowWidth, windowHeight);

	//theta = PI / 2;
	//phi = -PI / 2;

	glEnable(GL_LIGHTING);
	prepare_lighting();

	create_texture();

	// 主角
	protagonist.manType = 0;
	protagonist.headHeight = 4;
	protagonist.jumpHigh = 20;
	protagonist.jumpSpeed = -20;
	protagonist.weaponType = 1;
	// 敵人
	enemy.manType = 1;
	enemy.headHeight = 8;
	enemy.weaponType = 1;
	enemy.position[0] = 10;
	enemy.position[2] = 10;
	// 目標
	target.manType = 2;
	target.headHeight = 5;
	target.weaponType = 0;
	target.position[0] = -10;
	target.position[2] = -10;

	windowMove[0] = 180;
	//if (scene == NULL) {
	//	scene = obj_create("../../../Object/Loli/loli.obj");
	//}
	glEnable(GL_COLOR_MATERIAL);
}

void makeProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// viewVolume 鏡頭角度/2, 寬高比, 近平面距離, 遠平面距離
	gluPerspective(45, (double)windowWidth / windowHeight, 0.5, 3000);
}
void makeView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyePosition[0] + protagonist.position[0], eyePosition[1], eyePosition[2] + +protagonist.position[2],
		protagonist.position[0], protagonist.position[1], protagonist.position[2], 0, 1, 0);
	//gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2], 0, 0, 0, 0, 1, 0);

}
void displayFunction() {
	// 清除前一個畫面的顏色及深度
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 第三人稱
	makeProjection();
	makeView();

	drawScene();
	drawMan(protagonist);
	drawMan(enemy);
	drawMan(target);
	//if (scene) {
	//	glEnable(GL_TEXTURE_2D);
	//	draw_polyhedron(scene);
	//	glDisable(GL_TEXTURE_2D);
	//}
	// 將後台緩衝區交換到前端
	glutSwapBuffers();
}

void mousePress(int button, int state, int x, int y) {
	//XY[0] = x;
	//XY[1] = y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	if (!protagonist.isAttack) {
		protagonist.isAttack = true;
		protagonist.hitCombo = 1;
		alSourcePlay(Sources[SOURCE1]);
	}
}


void keyboardDown(unsigned char key, int x, int y) {
	keyBuffer[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
	keyBuffer[key] = false;
	if (key == 'w' || key == 's')
		protagonist.isWalk = false;

	// 修正左右轉會重製聲音的 bug
	if (key == 'a' || key == 'd') {
		if (keyBuffer['w'] || keyBuffer['s'])
			protagonist.isWalk = true;
		else
			protagonist.isWalk = false;
	}
}

void keyOperations() {
	if (keyBuffer[0x1B])	exit(0);
	if (keyBuffer['r']) {
		eyePosition[0] = 0;
		eyePosition[1] = 0;
		eyePosition[2] = 50;
		eyeRadius = 50;
		windowMove[0] = 0;
		windowMove[1] = 0;
		XY[0] = 0;
		XY[1] = 0;
	}
	//switch (key) {
	//case 'p':
	//	theta -= .05f;
	//	prepare_lighting();
	//	break;

	//case 'P':
	//	theta += .05f;
	//	prepare_lighting();
	//	break;

	//case 'o':
	//	phi -= .05f;
	//	prepare_lighting();
	//	break;

	//case 'O':
	//	phi += .05f;
	//	prepare_lighting();
	//	break;
	//};

	if (keyBuffer['+'])
		mouseWheel(1, 1, 0, 0);
	else if (keyBuffer['-'])
		mouseWheel(1, -1, 0, 0);

	// 角色前進
	if (keyBuffer['w'] || keyBuffer['s'] || keyBuffer['a'] || keyBuffer['d']){
		protagonist.isWalk = true;
		if (keyBuffer['w']) {
			protagonist.position[0] += 2 * sinf(protagonist.bodyAngle / 180.f * PI);
			protagonist.position[2] += 2 * cosf(protagonist.bodyAngle / 180.f * PI);
		}
		else if (keyBuffer['s']) {
			protagonist.position[0] -= sinf(protagonist.bodyAngle / 180.f * PI);
			protagonist.position[2] -= cosf(protagonist.bodyAngle / 180.f * PI);
		}
		if (keyBuffer['a']) {
			protagonist.bodyAngle += 4;
		}
		else if (keyBuffer['d']) {
			protagonist.bodyAngle -= 4;
		}
	}
	// 角色跳躍
	if (keyBuffer[' '])
		if (protagonist.jumpSpeed <= -protagonist.jumpHigh) {
			protagonist.jumpSpeed = (float)protagonist.jumpHigh;
			alSourcePlay(Sources[SOURCE2]);
		}
}

void timerFunction(int value) {
	playWalkSound(protagonist.isWalk);
	//playWalkSound(enemy.isWalk);
	//playWalkSound(target.isWalk);
	if (protagonist.isWalk) {
		manWalk(&protagonist);
	}
	if (!protagonist.isWalk) {
		manStand(&protagonist);
	}
	if (protagonist.jumpSpeed > -protagonist.jumpHigh) {
		manJump(&protagonist, time);
		//printf("speed:%f\tpos:%f\n", man.jump, man.position[1]);
	}
	if (protagonist.isAttack) {
		manAttack(&protagonist);
	}
	keyOperations();

	enemyAutomatic(&enemy);
	targetAutomatic(&target);

	// 再次顯現場景
	glutPostRedisplay();
	// 需要在函數中再調用一次，才能保證循環
	glutTimerFunc(time, timerFunction, value);
}

void main(int argc, char **argv) {
	/******************************** OPENAL init ********************************/
	// Initialize OpenAL and clear the error bit.
	ALCdevice *device;
	ALCcontext *context;
	device = alcOpenDevice(NULL); // select the "preferred device"
	if (device) {
		context = alcCreateContext(device, NULL);
		alcMakeContextCurrent(context);
	}
	//alutInit(NULL, 0);

	// Generate Buffers
	alGetError();

	// Load the wav data.
	if (LoadALData() == AL_FALSE)
	{
		printf("Error loading data.");
		system("Pause");
		exit(0);
	}
	SetListenerValues();
	// Setup an exit procedure.
	atexit(KillALData);

	/******************************** OPENGL init ********************************/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 10);
	glutCreateWindow("3D Game Programming Final Project");

	initial();
	glutDisplayFunc(displayFunction);
	glutMouseFunc(mousePress);
	//glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);
#ifdef _WIN64
	glutMouseWheelFunc(mouseWheel);
#endif
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutTimerFunc(time, timerFunction, 0);

	glutMainLoop();
}