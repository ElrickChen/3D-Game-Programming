#include <math.h>
#ifdef _WIN64
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif
#include "Hw5Camera.h"

#define PI 3.14159265358979323846f

/*----------Culling----------*/
float plane[6 * 4];	// 上下左右近遠		Ax + By + Cz + D = 0

void mouseMove(int x, int y) {
	windowMove[0] += (x - XY[0]) / 3.f;
	float temp = (y - XY[1]) / 3.f;
	if (!(windowMove[1] > 87 && temp > 0) && !(windowMove[1] < -87 && temp < 0))
		windowMove[1] += temp;

	eyePosition[0] = eyeRadius * sinf(windowMove[0] / 180 * PI);
	eyePosition[1] = eyeRadius * sinf(windowMove[1] / 180 * PI);
	eyePosition[2] = eyeRadius * cosf(windowMove[0] / 180 * PI);

	XY[0] = x;
	XY[1] = y;
}

void mouseWheel(int wheel, int direction, int x, int y) {
	if (direction == 1)		// 向前
		eyeRadius--;
	else if (direction == -1)	// 向後
		eyeRadius++;
	eyePosition[0] = eyeRadius * sinf(windowMove[0] / 180 * PI);
	eyePosition[1] = eyeRadius * sinf(windowMove[1] / 180 * PI);
	eyePosition[2] = eyeRadius * cosf(windowMove[0] / 180 * PI);
}

//void crossProduct(float vector1[3], float vector2[3], float product[3]) {
//	float i = vector1[1] * vector2[2] - vector1[2] * vector2[1];
//	float j = vector1[2] * vector2[0] - vector1[0] * vector2[2];
//	float k = vector1[0] * vector2[1] - vector1[1] * vector2[0];
//	product[0] = i;
//	product[1] = j;
//	product[2] = k;
//	//printf("(%f, %f, %f)*(%f, %f, %f)\n", vector1[0], vector1[1], vector1[2], vector2[0], vector2[1], vector2[2]);
//	//printf("%fi + %fj + %fk\n", product[0], product[1], product[2]);
//}
//void setPlaneEquation(float point1[3], float point2[3], float point3[3], float *planeEquation) {
//	float vector1[3];
//	for (int i = 0; i < 3; i++)
//		vector1[i] = point1[i] - point2[i];
//	float vector2[3];
//	for (int i = 0; i < 3; i++)
//		vector2[i] = point3[i] - point2[i];
//
//	float normal[3];
//	crossProduct(vector1, vector2, normal);
//	// 正規化
//	float length = 0;
//	for (int i = 0; i < 3; i++)
//		length += normal[i] * normal[i];
//	length = sqrtf(length);
//	for (int i = 0; i < 3; i++)
//		normal[i] = normal[i] / length;
//	// d = -ax-by-cz
//	float distance = 0;
//	for (int i = 0; i < 3; i++)
//		distance -= normal[i] * point1[i];
//
//	planeEquation[0] = normal[0];
//	planeEquation[1] = normal[1];
//	planeEquation[2] = normal[2];
//	planeEquation[3] = distance;
//}
//void computeViewVolumePlane(float fovy, float aspect, float zNear, float zFar) {
//	// compute the Z axis of camera
//	float cameraZ[3];
//	float length = 0;
//	for (int i = 0; i < 3; i++)
//		length += eyePosition[i] * eyePosition[i];
//	length = sqrtf(length);
//	for (int i = 0; i < 3; i++)
//		cameraZ[i] = eyePosition[i] / length;
//	//printf_s("cZ: (%f, %f, %f)\n", cameraZ[0], cameraZ[1], cameraZ[2]);
//	// X axis of camera with given "up" vector and Z axis
//	float up[] = { 0, 1, 0 };
//	float cameraX[3];
//	//printf_s("cX: (%f, %f, %f)\n", cameraX[0], cameraX[1], cameraX[2]);
//	crossProduct(up, cameraZ, cameraX);
//	// the real "up" vector is the cross product of Z and X
//	float cameraY[3];
//	crossProduct(cameraZ, cameraX, cameraY);
//
//	float tanTheta = (float)tan(fovy / 2 * PI / 180);
//	float nearHeight = zNear*tanTheta;
//	float nearWidth = nearHeight*aspect;
//	float farHeight = zFar*tanTheta;
//	float farWidth = farHeight*aspect;
//
//	// compute the centers of the near and far planes
//	float nearCenter[3];
//	for (int i = 0; i < 3; i++)
//		nearCenter[i] = eyePosition[i] + cameraZ[i] * zNear;
//	float farCenter[3];
//	for (int i = 0; i < 3; i++)
//		farCenter[i] = eyePosition[i] + cameraZ[i] * zFar;
//
//	// compute the 4 corners of the frustum on the near plane
//	float nearTopLeft[3];
//	for (int i = 0; i < 3; i++)
//		nearTopLeft[i] = nearCenter[i] + cameraY[i] * nearHeight - cameraX[i] * nearWidth;
//	float nearTopRight[3];
//	for (int i = 0; i < 3; i++)
//		nearTopRight[i] = nearCenter[i] + cameraY[i] * nearHeight + cameraX[i] * nearWidth;
//	float nearButtomLeft[3];
//	for (int i = 0; i < 3; i++)
//		nearButtomLeft[i] = nearCenter[i] - cameraY[i] * nearHeight - cameraX[i] * nearWidth;
//	float nearButtomRight[3];
//	for (int i = 0; i < 3; i++)
//		nearButtomRight[i] = nearCenter[i] - cameraY[i] * nearHeight + cameraX[i] * nearWidth;
//
//	// compute the 4 corners of the frustum on the far plane
//	float farTopLeft[3];
//	for (int i = 0; i < 3; i++)
//		farTopLeft[i] = farCenter[i] + cameraY[i] * farHeight - cameraX[i] * farWidth;
//	float farTopRight[3];
//	for (int i = 0; i < 3; i++)
//		farTopRight[i] = farCenter[i] + cameraY[i] * farHeight + cameraX[i] * farWidth;
//	float farButtomLeft[3];
//	for (int i = 0; i < 3; i++)
//		farButtomLeft[i] = farCenter[i] - cameraY[i] * farHeight - cameraX[i] * farWidth;
//	float farButtomRight[3];
//	for (int i = 0; i < 3; i++)
//		farButtomRight[i] = farCenter[i] - cameraY[i] * farHeight + cameraX[i] * farWidth;
//
//	// compute the six planes
//	// 都順時針給點
//	setPlaneEquation(nearTopRight, nearTopLeft, farTopLeft, plane + 0 * 4);
//	setPlaneEquation(nearButtomLeft, nearButtomRight, farButtomRight, plane + 1 * 4);
//	setPlaneEquation(nearTopLeft, nearButtomLeft, farButtomLeft, plane + 2 * 4);
//	setPlaneEquation(nearButtomRight, nearTopRight, farButtomRight, plane + 3 * 4);
//	setPlaneEquation(nearTopLeft, nearTopRight, nearButtomRight, plane + 4 * 4);
//	setPlaneEquation(farTopRight, farTopLeft, farButtomLeft, plane + 5 * 4);
//}
//int isInFrustum(MyShape shape) {
//	float distance = 0;
//	int result = 1;	// inside
//
//	if (shape.type == 0) {	// 球體
//		float radius = sqrtf(shape.WidthHeightLong[0] * shape.WidthHeightLong[0] * 3);
//		for (int i = 0; i < 6; i++) {
//			//	distance = pl[i].distance(p);
//			for (int j = 0; j < 3; j++)
//				distance += plane[i * 4 + j] * shape.position[j];
//			distance += plane[i * 4 + 3];
//			if (distance < -radius)
//				return -1;	// outside
//			else if (distance < radius)
//				result = 0;	// intersect
//		}
//	}
//	else {
//		// 每個頂點都要判斷
//		float vertex[8][3];
//		for (int i = 0; i < 8; i++) {
//			int x = i / 4;
//			int y = i / 2;
//			int z = i / 1;
//			x = (x % 2 == 0) ? 1 : -1;
//			y = (y % 2 == 0) ? 1 : -1;
//			z = (z % 2 == 0) ? 1 : -1;
//
//			vertex[i][0] = shape.position[0] + x*shape.WidthHeightLong[0] / 2;
//			vertex[i][1] = shape.position[1] + y*shape.WidthHeightLong[1] / 2;
//			vertex[i][2] = shape.position[2] + z*shape.WidthHeightLong[2] / 2;
//		}
//
//		// 判斷是否有頂點在裡面
//		int in, out;
//		for (int i = 0; i < 6; i++) {
//			in = 0;	out = 0;
//			for (int j = 0; j < 8 && (in == 0 || out == 0); j++) {
//				// the corner is outside or inside
//				for (int k = 0; j < 3; j++)
//					distance += plane[i * 4 + k] * vertex[j][k];
//				distance += plane[i * 4 + 3];
//				if (distance < 0)
//					out++;
//				else
//					in++;
//			}
//			//if all corners are out
//			if (!in)
//				return -1;	// outside
//			// if some corners are out and others are in
//			else if (out)
//				result = 0;	// intersect
//		}
//	}
//	return result;
//}