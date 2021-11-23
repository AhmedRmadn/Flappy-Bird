#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mmsystem.h>
#include <glut.h>



void drawBarriers(float x, float y,bool color);
void drawSet(float y1, float y2, float y3, float start,bool color);
void drawPowerup(float y1, float start);
void drawMap();
void drawPlayer();
void drawQuad(float x, float y, float w, float h);
void Anim(void);

void control();
void drawCircle(float x, float y, float r, float R, float G, float B);
void drawTriangle();
void Display();
void Timer(int val);
void Keyboard(unsigned char key, int x, int y);

void detectCol();
void printScore();
void printGameOver();
void drawStart();
void printStart();
void print(int x, int y, char* string);
void playerMove();

int windowWidth = 1000;
int windowHight = 600;
int dashboard = 50;
int windowHightAll = windowHight + dashboard;

int d = 200;
int PW = 80;
int gap = 300;

float xPlayer = 150;
float yPlayer = 400;
int dPlayer = 50;
float playerSpeed = 2;
float grav = 0.03;
int freez = 3;
float bounce = 0.7;
bool move = true;
int col = 0;
int powerUpD = 20;

int yPTarget = 0;
int inPowerUp = -1;
int Score = 0;
int tries = 3;
bool powered = false;
bool gameOver = false;

const int numOfBarriers = 3;
const int numOfSets = 4;
const int sizeOfXPos = numOfSets;
const int numOfParPower = 4;
bool speedUp = false;
float head = 30;
float addHead = 2;


const int sets[numOfSets][numOfBarriers] = { {300,250,120},{200,300,250},{150,200,150} ,{150,200,300} };

float xPos[sizeOfXPos];
int yHight[sizeOfXPos][numOfBarriers];
int powerUp[sizeOfXPos];

float xstart = windowWidth;
float spead = 4;
int freezing = 20;
float r = (dPlayer / 2);
boolean GameStart = false;
template<typename T, size_t n>
void print_array(T const(&arr)[n])
{
	for (size_t i = 0; i < n; i++) {
		std::cout << arr[i] << ' ';
	}
	std::cout << "\n";
}


void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(windowWidth, windowHightAll);
	glutInitWindowPosition(150, 150);

	xPos[0] = windowWidth;

	for (int i = 1; i < sizeOfXPos; i++) {
		xPos[i] = xPos[i - 1] + (3 * PW) + (3 * gap);
	}
	srand(time(NULL));
	for (int i = 0; i < sizeOfXPos; i++) {
		int randSet = rand() % numOfSets;
		int randPower = rand() % numOfParPower;
		//std::cout << "\n" ;
		//std::cout << "You entered " << randPower;
		powerUp[i] = -1;
		if (randPower == 0) {
			powerUp[i] = i;
		}
		for (int j = 0; j < numOfBarriers; j++) {
			yHight[i][j] = sets[randSet][j];
		}
	}



	glutCreateWindow("Flappy Robot");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);      // sets the Keyboard handler function; called when a key is pressed // sets the KeyboardUp handler function; called when a key is released
	//glutMouseFunc(Mouse);       // sets the Mouse handler function; called when a mouse button is clicked
	glutTimerFunc(0, Timer, 0); // sets the Timer handler function; which runs every `Threshold` milliseconds (1st argument)
	//glutIdleFunc(Anim);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.04706f, 0.048823f, 0.20784f, 0);
	gluOrtho2D(0, windowWidth, 0, windowHightAll);

	glutMainLoop();
}

void drawBarriers(float x, float y,bool color) {
	
	/*glBegin(GL_LINE_LOOP); // GL_LINE_STRIP, GL_LINE_LOOP
	glVertex2f(x, 0);
	glVertex2f(x, y);
	glVertex2f(x - 2, y);
	glVertex2f(x - 2, y + 30);
	glVertex2f(x + PW + 2.5, y + 30);
	glVertex2f(x + PW + 2.5, y);
	glVertex2f(x + PW+0.5, y);
	glVertex2f(x + PW+0.5, 0);
	glEnd();*/




	//glColor3f(98.0/255.0, 107.0/255.0, 222.0/255.0);
	//glColor3f(0.2, 0.4, 0);
	if(!color)
	   glColor3f(98.0/255.0, 107.0/255.0, 222.0/255.0);
	else
		glColor3f(98.0 / 255.0, 0.4, 0);

	glBegin(GL_QUADS);

	glVertex2f(x, 0);
	glVertex2f(x, y - head);
	glVertex2f(x + PW, y - head);
	glVertex2f(x + PW, 0);


	glVertex2f(x - addHead, y - head);
	glVertex2f(x - addHead, y);
	glVertex2f(x + PW + addHead, y);
	glVertex2f(x + PW + addHead, y - head);

	glVertex2f(x, windowHight);
	glVertex2f(x, y + d + head);
	glVertex2f(x + PW, y + d + head);
	glVertex2f(x + PW, windowHight);

	glVertex2f(x - addHead, y + d + head);
	glVertex2f(x - addHead, y + d);
	glVertex2f(x + PW + addHead, y + d);
	glVertex2f(x + PW + addHead, y + d + head);


	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP); // GL_LINE_STRIP, GL_LINE_LOOP
	glVertex2f(x, 0);
	glVertex2f(x, y - head);
	glVertex2f(x + PW, y - head);
	glVertex2f(x + PW, 0);
	glEnd();

	glBegin(GL_LINE_STRIP); // GL_LINE_STRIP, GL_LINE_LOOP
	glVertex2f(x, y - head);
	glVertex2f(x - addHead, y - head);
	glVertex2f(x - addHead, y);
	glVertex2f(x + PW + addHead, y);
	glVertex2f(x + PW + addHead, y - head);
	glVertex2f(x + PW, y - head);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(x, windowHight);
	glVertex2f(x, y + d + head);
	glVertex2f(x + PW, y + d + head);
	glVertex2f(x + PW, windowHight);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(x, y + d + head);
	glVertex2f(x - addHead, y + d + head);
	glVertex2f(x - addHead, y + d);
	glVertex2f(x + PW + addHead, y + d);
	glVertex2f(x + PW + addHead, y + d + head);
	glVertex2f(x + PW, y + d + head);
	glEnd();



}
void drawSet(float y1, float y2, float y3, float start,bool color) {
	//yPTarget = -1;
	drawBarriers(start, y1,color);
	start = start + PW + gap;
	drawBarriers(start, y2,color);
	start = start + PW + gap;
	drawBarriers(start, y3,color);

}
void drawPowerup(float y1, float start) {

	float x = start + PW / 2 - (powerUpD / 2);
	float y = y1 + (d / 4) - (powerUpD / 2);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x, y + powerUpD);
	glVertex2f(x + powerUpD, y + powerUpD);
	glVertex2f(x + powerUpD, y);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);

	glVertex3f(x, y + (powerUpD / 2), 0);
	glVertex3f(x, y + powerUpD, 0);
	glVertex3f(x + (powerUpD / 2), y + powerUpD, 0.0f);

	glVertex3f(x, y, 0);
	glVertex3f(x, y + (powerUpD / 2), 0);
	glVertex3f(x + (powerUpD / 2), y, 0.0f);

	glVertex3f(x + (powerUpD / 2), y, 0.0f);
	glVertex3f(x + powerUpD, y, 0);
	glVertex3f(x + powerUpD, y + (powerUpD / 2), 0);


	glVertex3f(x + powerUpD, y + (powerUpD / 2), 0);
	glVertex3f(x + powerUpD, y + powerUpD, 0.0f);
	glVertex3f(x + (powerUpD / 2), y + powerUpD, 0.0f);



	glEnd();
}
void drawMap() {
	for (int i = 0; i < sizeOfXPos; i++) {
		drawSet(yHight[i][0], yHight[i][1], yHight[i][2], xPos[i], i ==0&&powered);
		if (powerUp[i] >-1) {
			drawPowerup(yHight[i][0], xPos[i]);
		}
	}
}

/*void drawPlayer() {
	if(col>0)
		drawCircle(xPlayer - (dPlayer / 2), yPlayer - dPlayer / 2, r, 1, 0, 0);
	else
		drawCircle(xPlayer - (dPlayer / 2), yPlayer - dPlayer / 2, r, 1, 1, 0);
	drawTriangle();
	drawCircle(xPlayer - (dPlayer / 2) + (r / 4), yPlayer - dPlayer / 2 + (r / 2), r * 0.25, 0, 0, 0);
	drawCircle(xPlayer - (dPlayer / 2) + (r / 4), yPlayer - dPlayer / 2 - (r / 2), r * 0.25, 0, 0, 0);
	glBegin(GL_LINE_LOOP); // GL_LINE_STRIP, GL_LINE_LOOP
	glColor3f(0, 0, 0);
	glVertex3f(xPlayer - (dPlayer / 2) - 10, yPlayer - dPlayer / 2 + 6, 0);
	glVertex3f(xPlayer - (dPlayer / 2) - 10, yPlayer - dPlayer / 2 - 6, 0);
	glEnd();

}*/
void drawPlayer() {

	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(xPlayer, yPlayer);
	glVertex2f(xPlayer, yPlayer - dPlayer);
	glVertex2f(xPlayer - dPlayer, yPlayer - dPlayer);
	glVertex2f(xPlayer - dPlayer, yPlayer);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xPlayer, yPlayer);
	glVertex2f(xPlayer, yPlayer - dPlayer);
	glVertex2f(xPlayer - dPlayer, yPlayer - dPlayer);
	glVertex2f(xPlayer - dPlayer, yPlayer);
	glEnd();

	glColor3f(0.66666666f, 0.66666666f, 0.73333333f);
	glBegin(GL_POLYGON);
	glVertex2f(xPlayer- (0.1 * dPlayer), yPlayer- (0.1 * dPlayer));
	glVertex2f(xPlayer- (0.1 * dPlayer), yPlayer - dPlayer + (0.1 * dPlayer));
	glVertex2f(xPlayer - dPlayer+ (0.1 * dPlayer), yPlayer - dPlayer+ (0.1 * dPlayer));
	glVertex2f(xPlayer - dPlayer+ (0.1 * dPlayer), yPlayer- (0.1 * dPlayer));
	glEnd();
	
	drawCircle((xPlayer - (0.1 * dPlayer))-( dPlayer/4) , (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer/6, 0, 0, 0);
	drawCircle((xPlayer - dPlayer + (0.1 * dPlayer))+(dPlayer / 4), (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer / 6, 0, 0, 0);
	if (col <= 0) {
		drawCircle((xPlayer - (0.1 * dPlayer)) - (dPlayer / 4), (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer / 7, 1, 0.53333f, 0.46666f);
		drawCircle((xPlayer - dPlayer + (0.1 * dPlayer)) + (dPlayer / 4), (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer / 7, 1, 0.53333f, 0.46666f);
	}
	else {
		drawCircle((xPlayer - (0.1 * dPlayer)) - (dPlayer / 4), (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer / 7, 1, 0, 0);
		drawCircle((xPlayer - dPlayer + (0.1 * dPlayer)) + (dPlayer / 4), (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer / 7, 1, 0, 0);
	}

	drawCircle((xPlayer - (0.1 * dPlayer)) - (dPlayer / 4), (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer / 15, 0, 0, 0);
	drawCircle((xPlayer - dPlayer + (0.1 * dPlayer)) + (dPlayer / 4), (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer / 15, 0, 0, 0);

	drawCircle((xPlayer - (0.1 * dPlayer)) - (dPlayer / 4), (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer / 50, 1, 0.53333f, 0.46666f);
	drawCircle((xPlayer - dPlayer + (0.1 * dPlayer)) + (dPlayer / 4), (yPlayer - (0.1 * dPlayer)) - (dPlayer / 4), dPlayer / 50, 1, 0.53333f, 0.46666f);

	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f((xPlayer - (0.1 * dPlayer))-(0.1*dPlayer), (yPlayer - (0.1 * dPlayer))-(0.5 * dPlayer));
	glVertex2f((xPlayer - (0.1 * dPlayer)) - (0.1 * dPlayer), (yPlayer - (0.1 * dPlayer)) - (0.7 * dPlayer));
	glVertex2f((xPlayer - dPlayer + (0.1 * dPlayer))+(0.1 * dPlayer), (yPlayer - (0.1 * dPlayer)) - (0.7 * dPlayer));
	glVertex2f((xPlayer - dPlayer + (0.1 * dPlayer)) + (0.1 * dPlayer), (yPlayer - (0.1 * dPlayer)) - (0.5 * dPlayer));
	glEnd();
	float xtemp0 = (xPlayer - (0.1 * dPlayer)) - (0.1 * dPlayer);
	float xtemp1 = (xPlayer - dPlayer + (0.1 * dPlayer)) + (0.1 * dPlayer);
	float ytemp0 = (yPlayer - (0.1 * dPlayer)) - (0.5 * dPlayer);
	float ytemp1 = (yPlayer - (0.1 * dPlayer)) - (0.7 * dPlayer);
	float width = xtemp0 - xtemp1;
	float height = ytemp0 - ytemp1;
	///std::cout << "You entered " << inPowerUp << "\n";
	xtemp0 = xtemp0 - (width * 0.09);
	xtemp1 = xtemp1 + (width * 0.09);
	ytemp0 = ytemp0 - (width * 0.09);
	ytemp1 = ytemp1 + (width * 0.09);
	width = xtemp0 - xtemp1;
	height = ytemp0 - ytemp1;
	float tw = (3 / 19) * width;
	float gw = (1 / 3) * tw;
	float th = (4 / 9) * height;
	float gh = (1 / 4) * th;
	float xT = xtemp0;
	float yT = ytemp0;
	drawQuad(xtemp0, ytemp0, width*((yPlayer-dPlayer / 2)/windowHight)+1, height);





}
void drawQuad(float x , float y ,  float w , float h) {
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x-w, y);
	glVertex2f(x-w, y-h);
	glVertex2f(x, y-h);
	glEnd();

}
void drawCircle(float x, float y, float r, float R, float G, float B) {

	glPushMatrix();
	glColor3f(R, G, B);
	glTranslatef(x, y, 0);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
	glEnd();
}
void drawTriangle() {
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex3f(xPlayer - (dPlayer / 2) - 7, yPlayer - dPlayer / 2 + 6, 0);
	glVertex3f(xPlayer - (dPlayer / 2) - 7, yPlayer - dPlayer / 2 - 6, 0);
	glVertex3f(xPlayer - (dPlayer / 2) + (r / 2) - 5, yPlayer - dPlayer / 2, 0.0f);
	glEnd();
}
void drawDashboard() {
	glColor3f(199.0/255, 171.0/255, 183.0/255);
	glBegin(GL_QUADS);
	glVertex2f(0, windowHight);
	glVertex2f(0, windowHightAll);
	glVertex2f(windowWidth, windowHightAll);
	glVertex2f(windowWidth, windowHight);
	glEnd();
	printScore();
	for (int i = 0; i < tries; i++) {
		//glColor3f(98.0 / 255.0, 107.0 / 255.0, 222.0 / 255.0);
		drawCircle(windowWidth / 2 - 40 + (i * 25), windowHightAll - 25, 10, 98.0 / 255.0, 07.0 / 255.0, 222.0 / 255.0);
	}

}


void Anim() {

	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	control();
}
void control() {
	//std::cout << "You entered " << spead;
	for (int i = 0; i < sizeOfXPos; i++) {
		xPos[i] -= spead;
		int start = xPos[i];
		if (start <= xPlayer && start + PW >= xPlayer - dPlayer) {
			yPTarget = yHight[i][0];
			float x = start + PW / 2 + -(powerUpD / 2);
			if (x <= xPlayer && x + powerUpD >= xPlayer - dPlayer && powerUp[i] != -1) {
				inPowerUp = powerUp[i];
			}
		}
		if ((int)(start + PW - xPlayer + dPlayer) == 0) {
			Score++;
			PlaySound(TEXT("res/coins.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
		start = start + PW + gap;
		if (start <= xPlayer && start + PW >= xPlayer - dPlayer) {
			yPTarget = yHight[i][1];
		}
		if ((int)(start + PW - xPlayer + dPlayer) == 0) {
			Score++;
			PlaySound(TEXT("res/coins.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
		start = start + PW + gap;
		if (start <= xPlayer && start + PW >= xPlayer - dPlayer) {
			yPTarget = yHight[i][2];
		}
		if ((int)(start + PW - xPlayer + dPlayer) == 0) {
			Score++;
			PlaySound(TEXT("res/coins.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
	}
	if (xPos[1] - gap <= 0) {
		//std::cout << "You entered \n";
		powered = false;
		for (int i = 0; i < sizeOfXPos - 1; i++) {
			xPos[i] = xPos[i + 1];
		}
		xPos[sizeOfXPos - 1] = xPos[sizeOfXPos - 2] + (3 * PW) + (3 * gap);
		srand(time(NULL));
		int randSet = rand() % numOfSets;
		int randpowerUp = rand() % numOfParPower;

		for (int i = 0; i < sizeOfXPos - 1; i++) {
			powerUp[i] = powerUp[i + 1];
			if (powerUp[i] > -1) {
				powerUp[i]--;
			}
			for (int j = 0; j < numOfBarriers; j++) {
				yHight[i][j] = yHight[i + 1][j];
			}
		}

		powerUp[sizeOfXPos - 1] = -1;
		if (randpowerUp == 0) {
			powerUp[sizeOfXPos - 1] = sizeOfXPos - 1;
		}


		if (inPowerUp > -1) {
			inPowerUp--;
		}
		if (randpowerUp == 0) {
			powerUp[sizeOfXPos - 1] = sizeOfXPos - 1;
		}
		for (int j = 0; j < numOfBarriers; j++) {
			yHight[sizeOfXPos - 1][j] = sets[randSet][j];
		}
		//	std::cout << "*********************** \n";
			//std::cout << "You entered " << randSet << "\n";
			//std::cout << "You entered " << yHight[randSet][0] << "\n";
		//	print_array(yHight[0]);
			//print_array(yHight[1]);
			//print_array(yHight[2]);

	}
	if (move && col == 0) {
		yPlayer -= playerSpeed;
	}
	else if (col > 0) {
		col -= 1;;
	}


}


void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	//drawSet(200, 50, 100, 100);
	if (gameOver) {
		printGameOver();
	}
	else if(GameStart) {
		drawMap();
		drawPlayer();
		drawDashboard();
	}
	else if (!GameStart) {
		drawStart();
	}







	glFlush();
}




void Timer(int value) {
	//std::cout << "You entered " << gameOver << "\n";
	if (!gameOver&&GameStart) {
		detectCol();
		control();
		playerMove();

	}
	else if (!GameStart) {
		drawStart();
	}
	glutPostRedisplay();



	glutTimerFunc(1000 / 120, Timer, 0);
}
void playerMove() {
	if (col <= 0) {
		yPlayer -= playerSpeed;
		playerSpeed += grav;
	}
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w' &&GameStart &&col<=0)
	{
		playerSpeed -= (playerSpeed + playerSpeed*0.25+1);
		PlaySound(TEXT("res/jump.wav"), NULL, SND_ASYNC | SND_FILENAME);

	}
	if (key == ' ' && !GameStart) {
		GameStart = true;
		xPlayer = 150;
		yPlayer = 400;
		dPlayer = 50;
	}
}


void detectCol() {
	if (yPlayer >= windowHight) {
		tries = 0;
	}
	if (yPlayer - dPlayer <= 0) {
		tries = 0;
	}
	if (yPTarget > 0 && yPlayer - dPlayer - 5 <= yPTarget && !powered) {
		yPlayer = yPTarget + (d / 2) + (dPlayer / 2) + 10;
		col = freezing;
		if (!powered) {
			tries--;
			PlaySound(TEXT("res/crash.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
	}
	if (yPTarget > 0 && yPlayer >= yPTarget + d && !powered) {
		yPlayer = yPTarget + (d / 2) + (dPlayer / 2) + 10;
		col = freezing;
		if (!powered) {
			tries--;
			PlaySound(TEXT("res/crash.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
	}
	if (yPTarget > 0 && inPowerUp != -1 && yPlayer - dPlayer - 5 <= (yPTarget + (d / 4) - (powerUpD / 2) + powerUpD)) {
		/*std::cout << "You entered " << inPowerUp << "\n";
		std::cout << "You entered " << powerUp[inPowerUp] << "\n";
		print_array(powerUp);*/
		powered = true;
		powerUp[inPowerUp] = -1;
		PlaySound(TEXT("res/power.wav"), NULL, SND_ASYNC | SND_FILENAME);

	}
	yPTarget = 0;
	inPowerUp = -1;
	if (tries == 0) {
		PlaySound(TEXT("res/gameOver.wav"), NULL, SND_ASYNC | SND_FILENAME);
		gameOver = true;
	}

}
void printScore() {
	glColor3f(0, 0, 0);
	char* p0s[20];
	sprintf((char*)p0s, "Score: %d", Score);
	print(35, windowHightAll - 35, (char*)p0s);
}
void printGameOver() {
	dPlayer = 200;
	xPlayer = (windowWidth / 2) - (dPlayer / 2);
	yPlayer = (windowHight / 2) + (dPlayer / 2);
	col = freezing;
	drawPlayer();
	glColor3f(1, 1, 1);
	char* p0s[20];
	sprintf((char*)p0s, "YOUR SCORE : %d", Score);
	print(windowWidth / 2 - 70, windowHightAll / 2 - 50, (char*)p0s);
	sprintf((char*)p0s, "GAME OVER !!!!!");
	print(windowWidth / 2 - 70, windowHightAll / 2, (char*)p0s);
}

void drawStart() {

	dPlayer = 200;
	xPlayer = (windowWidth / 2)-(dPlayer/2);
	yPlayer = (windowHight / 2) + (dPlayer / 2);
	drawPlayer();
	printStart();

}
void printStart() {
	glColor3f(1, 1, 1);
	char* p0s[20];
	sprintf((char*)p0s, "PRESS SPACE TO START THE GAME");
	print(windowWidth / 2 - 70, windowHightAll / 2 - 50, (char*)p0s);
	sprintf((char*)p0s, "FLAPPY ROBOT");
	print(windowWidth / 2 - 70, windowHightAll / 2, (char*)p0s);
}

void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character

	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}


/*
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	char* p0s[20];
	sprintf((char*)p0s, "Score: %d", 50);
	print(500, 300, (char*)p0s);


	glFlush();
}*/

