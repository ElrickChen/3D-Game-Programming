#include <GL/glut.h>
#include"Hw5Scene.h"
/*----場地大小----*/
int Halfboundary=1000;
/*---------材質------------*/
int  width, height;
unsigned int text_name[8];
unsigned char * stone;
unsigned char * SkyBox_Top;
unsigned char * SkyBox_Left;
unsigned char * SkyBox_Front;
unsigned char * SkyBox_Right;
unsigned char * SkyBox_Back;


void drawXYZ() {
	glBegin(GL_LINES);    /* Draw a line */
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(300.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);    /* Draw a line */
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);
	glVertex3f(0.0,0.0,0.0);
	glEnd();

	glBegin(GL_LINES);    /* Draw a line */
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 300.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();


}
void draw_floor()
{
	glBegin(GL_POLYGON);
	float normal[3] = { 0.0 ,1.0,0.0 };
	float range = 1.0;
	glNormal3fv(normal);
	glColor3f(0.9, 0.9, 0.9);
	glTexCoord2f(0.0, 0.0);     	glVertex3f(-Halfboundary, 0, -Halfboundary);
	glTexCoord2f(0.0, range);		glVertex3f(-Halfboundary, 0, Halfboundary);
	glTexCoord2f(range, range);		glVertex3f(Halfboundary, 0, Halfboundary);
	glTexCoord2f(range, 0.0);		glVertex3f(Halfboundary, 0, -Halfboundary);
	glEnd();
}
void draw_SkyBox() {
	drawXYZ();
	glPushMatrix();
		glTranslatef(0.0,-Halfboundary*0.45,0.0);
		float range = 1.0;
		//----Top
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, text_name[1]);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		float normal_Top[3] = { 0.0 ,-1.0,0.0 };
		glBegin(GL_POLYGON);
		glNormal3fv(normal_Top);
		glColor3f(0.9, 0.9, 0.9);
		glTexCoord2f(0.0, 0.0); 	glVertex3f(-Halfboundary, Halfboundary+9, -Halfboundary);
		glTexCoord2f(0.0, range);	glVertex3f(-Halfboundary, Halfboundary + 9, Halfboundary);
		glTexCoord2f(range, range); glVertex3f(Halfboundary, Halfboundary + 9 , Halfboundary);
		glTexCoord2f(range, 0.0);	glVertex3f(Halfboundary, Halfboundary + 9, -Halfboundary);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//----Left
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, text_name[2]);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		float normal_Left[3] = { -1.0 ,0.0,0.0 };
		glBegin(GL_POLYGON);
		glNormal3fv(normal_Left);
		glColor3f(0.9, 0.9, 0.9);
		glTexCoord2f(0.0, 0.0);	    glVertex3f(Halfboundary, -9.0, -Halfboundary);
		glTexCoord2f(0.0, range);   glVertex3f(Halfboundary, Halfboundary + 9, -Halfboundary);
		glTexCoord2f(range, range); glVertex3f(Halfboundary, Halfboundary + 9, Halfboundary);
		glTexCoord2f(range, 0.0);   glVertex3f(Halfboundary, -9.0, Halfboundary);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//----Front
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, text_name[3]);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		float normal_Front[3] = { 0.0 ,0.0,-1.0 };
		glBegin(GL_POLYGON);
		glNormal3fv(normal_Front);
		glColor3f(0.9, 0.9, 0.9);
		glTexCoord2f(0.0, 0.0);		 glVertex3f(Halfboundary, -9.0, Halfboundary);
		glTexCoord2f(0.0, range);	 glVertex3f(Halfboundary, Halfboundary + 9, Halfboundary);
		glTexCoord2f(range, range);  glVertex3f(-Halfboundary, Halfboundary + 9, Halfboundary);
		glTexCoord2f(range, 0.0);	 glVertex3f(-Halfboundary, -9.0, Halfboundary);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//----Right
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, text_name[4]);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		float normal_Right[3] = { 1.0 ,0.0,0.0 };
		glBegin(GL_POLYGON);
		glNormal3fv(normal_Right);
		glColor3f(0.9, 0.9, 0.9);
		glTexCoord2f(0.0, 0.0);		glVertex3f(-Halfboundary, -9.0, Halfboundary);
		glTexCoord2f(0.0, range);	glVertex3f(-Halfboundary, Halfboundary + 9, Halfboundary);
		glTexCoord2f(range, range); glVertex3f(-Halfboundary, Halfboundary + 9, -Halfboundary);
		glTexCoord2f(range, 0.0);	glVertex3f(-Halfboundary, -9.0, -Halfboundary);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//----Back
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, text_name[5]);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		float normal_Back[3] = { 0.0 ,1.0,0.0 };
		glBegin(GL_POLYGON);
		glNormal3fv(normal_Back);
		glColor3f(0.9, 0.9, 0.9);
		glTexCoord2f(0.0, 0.0);		glVertex3f(Halfboundary, -9.0, -Halfboundary);
		glTexCoord2f(0.0, range);	glVertex3f(Halfboundary, Halfboundary + 9, -Halfboundary);
		glTexCoord2f(range, range); glVertex3f(-Halfboundary, Halfboundary+9, -Halfboundary);
		glTexCoord2f(range, 0.0);	glVertex3f(-Halfboundary, -9.0, -Halfboundary);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void drawScene() {
	//畫世界座標三軸
	//drawXYZ();
	//畫地板
	glPushMatrix();
	//glTranslatef(0.0, -6.5, 0.0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, text_name[0]);		
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	draw_floor();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//畫SkyBox
	draw_SkyBox();
}
//prepare texture
void create_texture() {
	//---------
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(6, text_name);

	//---------地板材質
	glBindTexture(GL_TEXTURE_2D, text_name[0]);
	int result = readBMPfile("../../../Object/brick2.bmp", &width, &height, &stone);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, stone);
	//---------SkyBox Top
	result = readBMPfile("../../../Object/Top.bmp", &width, &height, &SkyBox_Top);
	glBindTexture(GL_TEXTURE_2D, text_name[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, SkyBox_Top);
	//---------SkyBox Ground
	//---------SkyBox Left
	result = readBMPfile("../../../Object/Left.bmp", &width, &height, &SkyBox_Left);
	glBindTexture(GL_TEXTURE_2D, text_name[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, SkyBox_Left);
	//---------SkyBox Front
	result = readBMPfile("../../../Object/Front.bmp", &width, &height, &SkyBox_Front);
	glBindTexture(GL_TEXTURE_2D, text_name[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, SkyBox_Front);
	//---------SkyBox Right
	result = readBMPfile("../../../Object/Right.bmp", &width, &height, &SkyBox_Right);
	glBindTexture(GL_TEXTURE_2D, text_name[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, SkyBox_Right);
	//---------SkyBox Back
	result = readBMPfile("../../../Object/Back.bmp", &width, &height, &SkyBox_Back);
	glBindTexture(GL_TEXTURE_2D, text_name[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, SkyBox_Back);
}