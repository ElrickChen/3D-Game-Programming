#ifndef HW5_MAN_H
#define HW5_MAN_H
struct Man {
	char manType;	// 0主角	1敵人	2目標	3平民
	float position[3];
	float headHeight;	// 身長 4 個頭
	short bodyAngle;	// y

	short headAngle[2];	//x:-45~45	//y:-90~90
	short rightHandAngle[2];	//-x:-90~90	//-z:0~90
	short leftHandAngle[2];	//-x:-90~90	//z:0~90
	short rightFeetAngle;	//x:-60~90
	short leftFeetAngle;	//x:-60~90

	//char state = 's';	// s:stand	w:walk	r:run	f:fight
	bool isWalk;
	bool isLefthFeet;
	bool faceLeft;

	int jumpHigh;
	float jumpSpeed;

	bool isAttack;
	char weaponType;	// 0:none	1:sword
	char hitCombo;	// 0: 收	1: 
	//float weaponPosition[3];
	short weaponAngle;

	short viewFar;	// far target:20 enemy:30	view angle :120 
};

extern Man protagonist;

void drawCube();
void drawMan(Man man);
void manWalk(Man *man);
void manStand(Man *man);
void manFight(Man *man);
void manJump(Man *man, unsigned int time);
void manAttack(Man *man);
void enemyAutomatic(Man *man);
void targetAutomatic(Man *man);

#endif