#ifndef HW5_CAMERA_H
#define HW5_CAMERA_H

/*----------視窗的寬跟高----------*/
extern int windowWidth, windowHeight;
/*----------眼睛座標的平移旋轉----------*/
extern float eyePosition[3];
extern float eyeRadius;
extern float windowMove[2];
extern int XY[2];

// function
void mouseMove(int x, int y);
void mouseWheel(int wheel, int direction, int x, int y);

#endif // !HW5_CAMERA_H