#ifdef _WIN64
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif
#include "Hw5Man.h"

#define PI 3.14159265358979323846f

//GLUquadricObj *sphere;
/*---------- cube的參數 ----------*/
float cubeVertex[][3] = { { -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, -0.5f }, { -0.5f, 0.5f, -0.5f }, { -0.5f, -0.5f, 0.5f }, { 0.5f, -0.5f, 0.5f }, { 0.5f, 0.5f, 0.5f }, { -0.5f, 0.5f, 0.5f } };
int cubeFace[][4] = { { 0, 3, 2, 1 }, { 0, 1, 5, 4 }, { 1, 2, 6, 5 }, { 4, 5, 6, 7 }, { 2, 3, 7, 6 }, { 0, 4, 7, 3 } };
float cubeNormal[][3] = { { 0, 0, -1 }, { 0, -1, 0 }, { 1, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { -1, 0, 0 } };

void drawCube() {
	for (int i = 0; i < 6; i++) {
		// 畫長方體的面
		glNormal3fv(cubeNormal[i]);
		glBegin(GL_QUADS);
			glVertex3fv(cubeVertex[cubeFace[i][0]]);
			glVertex3fv(cubeVertex[cubeFace[i][1]]);
			glVertex3fv(cubeVertex[cubeFace[i][2]]);
			glVertex3fv(cubeVertex[cubeFace[i][3]]);
		glEnd();
	}
}

void manView(Man *man) {
	if (man->manType == 1)	// 敵人視野範圍
		man->viewFar = 60;
	else if (man->manType == 2)	// 目標視野範圍
		man->viewFar = 40;
	// 算最遠的平面
	int angle = man->bodyAngle + man->headAngle[1] + 90;
	// 人眼高度
	float y = man->position[1] + man->headHeight*3.5f;
	// 右
	float x1 = -cosf((angle-60)/180.f * PI) * 2*man->viewFar;
	float z1 = sinf((angle-60)/180.f * PI) * 2*man->viewFar;
	// 左
	float x2 = -cosf((angle+60)/180.f * PI) * 2*man->viewFar;
	float z2 = sinf((angle+60)/180.f * PI) * 2*man->viewFar;
	// 上
	float y1 = man->position[1] + man->headHeight*3.5f + 20;
	// 下
	float y2 = man->position[1] + man->headHeight*3.5f-20;

	glBegin(GL_TRIANGLES);
		glVertex3f(man->position[0], y, man->position[2]);
		glVertex3f(man->position[0] + x1, y1, man->position[2] + z1);
		glVertex3f(man->position[0] + x2, y1, man->position[2] + z2);

		glVertex3f(man->position[0], y, man->position[2]);
		glVertex3f(man->position[0] + x1, y2, man->position[2] + z1);
		glVertex3f(man->position[0] + x2, y2, man->position[2] + z2);
	glEnd();
	//float plane[4];
}


void drawMan(Man man) {
	glPushMatrix();
		manView(&man);
		// 移動
		glTranslatef(man.position[0], man.position[1], man.position[2]);
		// 把人抬高
		glTranslatef(0, 2.25f*man.headHeight, 0);
		// 角度
		glRotatef(man.bodyAngle, 0, 1, 0);
		// 身體
		glPushMatrix();
			glScalef(man.headHeight, 1.5f*man.headHeight, .5f*man.headHeight);
			drawCube();
		glPopMatrix();
		// 頭
		glTranslatef(0, .75f*man.headHeight, 0);
		glPushMatrix();
			// 節點
			glRotatef(man.headAngle[0], 1, 0, 0);	//-45~45
			glRotatef(man.headAngle[1], 0, 1, 0);	//-90~90
			glTranslatef(0, .5f*man.headHeight, 0);
			glScalef(man.headHeight, man.headHeight, man.headHeight);
			drawCube();
		glPopMatrix();
		// 左手
		glPushMatrix();
			glTranslatef(.5f*man.headHeight, 0, 0);
			// 節點
			glRotatef(man.leftHandAngle[0], -1, 0, 0);	//-90~90
			glRotatef(man.leftHandAngle[1], 0, 0, 1);	//0~90
			glTranslatef(.2f*man.headHeight, -.75f*man.headHeight, 0);
			glScalef(.4f*man.headHeight, 1.5f*man.headHeight, .4f*man.headHeight);
			drawCube();
		glPopMatrix();
		// 右手
		glPushMatrix();
			glTranslatef(-.5f*man.headHeight, 0, 0);
			// 節點
			glRotatef(man.rightHandAngle[0], -1, 0, 0);	//-90~90
			glRotatef(man.rightHandAngle[1], 0, 0, -1);	//0~90
			glTranslatef(-.2f*man.headHeight, -.75f*man.headHeight, 0);
			glPushMatrix();
				glScalef(.4f*man.headHeight, 1.5f*man.headHeight, .4f*man.headHeight);
				drawCube();
			glPopMatrix();
			// 武器
			glTranslatef(0, -.75f*man.headHeight, 0);
			if (man.weaponType == 1) {
				glRotatef(man.weaponAngle, 0, 1, 0);
				glTranslatef(0, 0, 5);
				glScalef(0.2f, 1, 10);
				drawCube();
			}
		glPopMatrix();
		glTranslatef(0, -1.5f*man.headHeight, 0);
		// 左腳
		glPushMatrix();
			// 節點
			glRotatef(man.leftFeetAngle, 1, 0, 0);	//-60~90
			glTranslatef(.25f*man.headHeight, -.75f*man.headHeight, 0);
			glScalef(.5f*man.headHeight, 1.5f*man.headHeight, .5f*man.headHeight);
			drawCube();
		glPopMatrix();
		// 右腳
		glPushMatrix();
			// 節點
			glRotatef(man.rightFeetAngle, 1, 0, 0);	//-60~90
			glTranslatef(-.25f*man.headHeight, -.75f*man.headHeight, 0);
			glScalef(.5f*man.headHeight, 1.5f*man.headHeight, .5f*man.headHeight);
			drawCube();
		glPopMatrix();
	glPopMatrix();
}

void manWalk(Man *man) {
	if (man->manType == 2){
		if (man->faceLeft) {
			man->headAngle[1] += 2;
			if (man->headAngle[1] > 60)
				man->faceLeft = false;
		}
		else if (man->manType == 1) {
			man->headAngle[1] -= 2;
			if (man->headAngle[1] < -60)
				man->faceLeft = true;
		}
	}

	if (man->bodyAngle > 360)
		man->bodyAngle -= 360;
	if (man->bodyAngle < 0)
		man->bodyAngle += 360;
	if (man->isLefthFeet) {
		man->leftFeetAngle += 4;
		man->rightFeetAngle -= 4;
		man->leftHandAngle[0]--;
		man->rightHandAngle[0]++;
		if (man->leftFeetAngle == 44)
			man->isLefthFeet = false;
	}
	else {
		man->leftFeetAngle -= 4;
		man->rightFeetAngle += 4;
		man->leftHandAngle[0]++;
		man->rightHandAngle[0]--;
		if (man->rightFeetAngle == 44)
			man->isLefthFeet = true;
	}
}

void manStand(Man *man) {
	//if (man->headAngle[0] > 0)
	//	man->headAngle[0]--;
	//else if (man->headAngle[0] < 0)
	//	man->headAngle[0]++;

	if (man->leftFeetAngle > 0)
		man->leftFeetAngle -= 4;
	else if (man->leftFeetAngle < 0)
		man->leftFeetAngle += 4;

	if (man->rightFeetAngle > 0)
		man->rightFeetAngle -= 4;
	else if (man->rightFeetAngle < 0)
		man->rightFeetAngle += 4;

	if (man->leftHandAngle[0] > 0)
		man->leftHandAngle[0]--;
	else if (man->leftHandAngle[0] < 0)
		man->leftHandAngle[0]++;

	if (man->rightHandAngle[0] > 0)
		man->rightHandAngle[0]--;
	else if (man->rightHandAngle[0] < 0)
		man->rightHandAngle[0]++;
}

void manJump(Man *man, unsigned int time) {
	// S = vt - g/2*t*t
	man->position[1] += man->jumpSpeed*time/100  - 0.5f*10*time*time/10000;
	// v = v0 -gt
	man->jumpSpeed -= 10.f*time/100;
}

void manAttack(Man *man) {
	if (man->weaponType == 1){	// 刀
		if (man->hitCombo == 1) {
			man->rightHandAngle[0] += 20;
			if (man->rightHandAngle[0] >= 180)
				man->hitCombo = 0;
		}
		else {
			if (man->rightHandAngle[0] >= 20) {
				man->rightHandAngle[0] -= 20;
				//man->rightHandAngle[1] -= 5;
				//man->weaponAngle += 5;
			}
			else {
				man->rightHandAngle[0] -= 4;	// 20/5
				//man->rightHandAngle[1] += 16;	// 5 * 160/20 / 20/5
				//man->weaponAngle -= 8;
				if (man->weaponAngle <= 0) {
					man->isAttack = false;
					man->hitCombo = 1;
					//man->rightHandAngle[1] = 0;
					//man->weaponAngle = 0;
				}
			}
		}
	}
	else if (man->weaponType == 2){	// 弓
	}
	else if (man->weaponType == 3){	// 重武器
	}
}

void enemyAutomatic(Man *man) {
	// 隨便亂走
	srand(time(NULL));
	int randomNumber = (rand() % 5) - 1;
	
	if (randomNumber == -1)
		man->bodyAngle--;
	else if (randomNumber == 1)
		man->bodyAngle++;
	if (randomNumber > 1)
		manStand(man);
	else {
		manWalk(man);
		if (man->position[0] >= 1000) {
			if (man->bodyAngle < 180)
				man->position[0] += sinf(man->bodyAngle / 180.f * PI);
			else
				man->position[0] -= sinf(man->bodyAngle / 180.f * PI);
		}
		else if (man->position[0] <= -1000) {
			if (man->bodyAngle<180)
				man->position[0] -= sinf(man->bodyAngle / 180.f * PI);
			else
				man->position[0] += sinf(man->bodyAngle / 180.f * PI);

		}
		else
			man->position[0] += sinf(man->bodyAngle / 180.f * PI);

		if (man->position[2] >= 1000) {
			if (man->bodyAngle>90 && man->bodyAngle<270)
				man->position[0] += cosf(man->bodyAngle / 180.f * PI);
			else
				man->position[0] -= cosf(man->bodyAngle / 180.f * PI);
		}
		else if (man->position[2] <= -1000) {
			if (man->bodyAngle>90 && man->bodyAngle < 270)
				man->position[0] -= cosf(man->bodyAngle / 180.f * PI);
			else
				man->position[0] += cosf(man->bodyAngle / 180.f * PI);
		}
		else
			man->position[2] += cosf(man->bodyAngle / 180.f * PI);
	}
	// 發現主角
	manAttack(man);
}

void targetAutomatic(Man *man) {
	// 隨便亂走
	int randomNumber = (rand() % 5) - 1;
	
	if (randomNumber == -1)
		man->bodyAngle--;
	else if (randomNumber == 1)
		man->bodyAngle++;
	if (randomNumber > 1)
		manStand(man);
	else {
		manWalk(man);
		if (man->position[0] >= 1000) {
			if (man->bodyAngle < 180)
				man->position[0] += sinf(man->bodyAngle / 180.f * PI);
			else
				man->position[0] -= sinf(man->bodyAngle / 180.f * PI);
		}
		else if (man->position[0] <= -1000) {
			if (man->bodyAngle<180)
				man->position[0] -= sinf(man->bodyAngle / 180.f * PI);
			else
				man->position[0] += sinf(man->bodyAngle / 180.f * PI);

		}
		else
			man->position[0] += sinf(man->bodyAngle / 180.f * PI);

		if (man->position[2] >= 1000) {
			if (man->bodyAngle>90 && man->bodyAngle<270)
				man->position[0] += cosf(man->bodyAngle / 180.f * PI);
			else
				man->position[0] -= cosf(man->bodyAngle / 180.f * PI);
		}
		else if (man->position[2] <= -1000) {
			if (man->bodyAngle>90 && man->bodyAngle < 270)
				man->position[0] -= cosf(man->bodyAngle / 180.f * PI);
			else
				man->position[0] += cosf(man->bodyAngle / 180.f * PI);
		}
		else
			man->position[2] += cosf(man->bodyAngle / 180.f * PI);
	}
	// 發現主角
	// 逃離主角
}