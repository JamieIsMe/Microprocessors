#include <stm32f031x6.h>
#include "display.h"
#include "serial.h"
#include "prbs.h"
#include "sound.h"
void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);
int leftPressed(void);
int rightPressed(void);
int upPressed(void);
void death(void);
void InitialiseGame(int);
void lvl1(void);
void lvl2(void);
void lvl3(void);
void completed(void);

volatile uint32_t milliseconds;
uint16_t count = 0;

/*
int song[] = {587, 587, 587,  440, 783, 783, 698,587, 698, 783, 523, 523, 587,  440, 783, 783, 698, 587, 698, 783, 493, 493, 587,  440, 783, 783, 698, 587, 698, 783,  440,  440, 587};

void loop(){
	while (1){
		for (int i = 0; i<33; i++){
			playNote(song[i]);
		}
	}
};
*/
const uint16_t heart[]=
{
	0,40224,40224,0,0,0,0,40224,40224,0,40224,40224,40224,40224,0,0,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,40224,0,40224,40224,40224,40224,40224,40224,40224,40224,0,0,0,40224,40224,40224,40224,40224,40224,0,0,0,0,0,40224,40224,40224,40224,0,0,0,
};

const uint16_t flowey[]=
{
	65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,65535,65535,65535,65535,0,0,0,65535,65535,0,0,65535,65535,65535,65535,65535,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,0,0,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,0,0,0,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,0,0,0,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,0,0,65535,65535,0,0,0,0,0,0,0,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,0,0,0,0,0,0,0,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,0,0,0,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,0,0,65535,65535,65535,65535,65535,65535,0,0,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,65535,65535,0,0,0,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,0,0,0,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,0,0,0,65535,65535,65535,65535,0,0,0,0,0,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,65535,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65535,65535,0,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,0,0,0,0,0,0,0,0,0,65535,65535,0,0,0,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,0,65535,65535,65535,65535,0,0,0,0,0,65535,65535,65535,65535,65535,0,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,65535,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,65535,65535,0,65535,65535,65535,0,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,65535,65535,0,65535,65535,65535,0,65535,65535,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,65535,
};

void InitialiseGame(levelCount){
	fillRectangle(0,0,128,159,RGBToWord(255,255,255));
	printText("Press Left", 30,30,RGBToWord(0,0,0),RGBToWord(255,255,255));
	printText(" To Start", 30,45,RGBToWord(0,0,0),RGBToWord(255,255,255));
	uint32_t seed = 0;
	while (!leftPressed() || seed == 0){
		seed++;
	}
	count = 0;
	//Sets Background To Black
	fillRectangle(0,0,128,159,RGBToWord(0,0,0));
	putImage(45,20,41,42,flowey,0,0);
	initprbs(seed);
	printDecimal(prbs());
	//Section Below For Testing Collisions
	//Sets Barrier to Dimgrey
	fillRectangle(0,0,128,65,RGBToWord(255,255,255));
	if (levelCount == 1){
		lvl1();
	}
	else if (levelCount == 2){
		lvl2();
	}
	else if (levelCount == 3){
		lvl3();
	}
};

void lvl1()
{
	printText("Oh... a", 60,20,RGBToWord(0,255,0),RGBToWord(255,255,255));
	printText("fresh soul", 60,30,RGBToWord(0,255,0),RGBToWord(255,255,255));
	putImage(10,20,41,42,flowey,0,0);
}

void lvl2(){
	printText("Ouch..", 60,20,RGBToWord(255,165,0),RGBToWord(255,255,255));
	printText("that hurts", 60,30,RGBToWord(255,165,0),RGBToWord(255,255,255));
}

void lvl3(){
	printText("Thats it.", 60,20,RGBToWord(255,0,0),RGBToWord(255,255,255));
	printText("DIE!", 60,30,RGBToWord(255,0,0),RGBToWord(255,255,255));
}

void death()
{
	fillRectangle(0,0,128,159,RGBToWord(255,255,255));
	printText("You Died...", 30,30,RGBToWord(255,0,0),RGBToWord(255,255,255));
	delay(2000);	
}

void completed()
{
	fillRectangle(0,0,128,159,RGBToWord(255,255,255));
	printText("You Beat The Level!", 30,30,RGBToWord(255,0,0),RGBToWord(255,255,255));
	delay(2000);	
}

int main()
{
	int hinverted = 0;
	int vinverted = 0;
	int toggle = 0;
	int hmoved = 0;
	int vmoved = 0;
	uint16_t x = 64;
	uint16_t y = 105;

	// Two Bottom Spawning Enemies
	uint16_t oldenemyx;
	uint16_t oldenemyy;
	uint16_t oldenemy2x;
	uint16_t oldenemy2y;
	uint16_t enemyx = 0;
	uint16_t enemyy = 150;
	uint16_t enemy2x = 64;
	uint16_t enemy2y = 150;
	// Two Top Spawning Enemies
	uint16_t enemy3x = 0;
	uint16_t enemy3y = 65;
	uint16_t enemy4x = 64;
	uint16_t enemy4y = 65;
	uint16_t oldenemy3x;
	uint16_t oldenemy3y;
	uint16_t oldenemy4x;
	uint16_t oldenemy4y;
	// Two Side Spawning Enemies
	uint16_t enemy5x = 0;
	uint16_t enemy5y = random(65, 154);
	uint16_t enemy6x = 108;
	uint16_t enemy6y = random(65, 154);
	uint16_t oldenemy5x;
	uint16_t oldenemy5y;
	uint16_t oldenemy6x;
	uint16_t oldenemy6y;


	uint16_t oldx = x;
	uint16_t oldy = y;
	uint16_t hitboxx = random(0,100);
	uint16_t hitboxy = random(65,140);
	int levelCount = 1;
	initSerial();
	initClock();
	initSysTick();
	setupIO();
	initSerial();
	eputs("Starting the game");
	fillRectangle(0,0,128,159,RGBToWord(255,255,255));
	printText("Press Left", 30,30,RGBToWord(0,0,0),RGBToWord(255,255,255));
	printText(" To Start", 30,45,RGBToWord(0,0,0),RGBToWord(255,255,255));
	uint32_t seed = 0;
	while (!leftPressed() || seed == 0){
		seed++;
	}
	//Sets Background To Black
	fillRectangle(0,0,128,159,RGBToWord(0,0,0));
	//Sets Barrier to White
	fillRectangle(0,0,128,65,RGBToWord(255,255,255));
	initprbs(seed);
	printDecimal(prbs());
	lvl1();
	while(1)
	{
		if (enemyy > 65)
		{
			oldenemyx = enemyx;
			oldenemyy = enemyy;
			enemyy--;
			fillRectangle(oldenemyx,oldenemyy,20,5,RGBToWord(0,0,0));
			fillRectangle(enemyx,enemyy,20,5,RGBToWord(255,255,255));
		}
		else
		{
			fillRectangle(enemyx,enemyy,20,5,RGBToWord(0,0,0));
			enemyx = random(0,44);
			enemyy = 150;
			fillRectangle(enemyx,enemyy,20,5,RGBToWord(255,255,255));
			if (count != 5){
				count += 1;
			}
		}
		//New Enemy Spawns From Top For Level 2
		if (levelCount >= 2){
			if (enemy3y < 159){
				oldenemy3x = enemy3x;
				oldenemy3y = enemy3y;
				enemy3y++;
				fillRectangle(oldenemy3x,oldenemy3y,20,5,RGBToWord(0,0,0));
				fillRectangle(enemy3x,enemy3y,20,5,RGBToWord(255,255,255));
			}
			else {
			fillRectangle(enemy3x,enemy3y,20,5,RGBToWord(0,0,0));
			enemy3x = random(0,44);
			enemy3y = 65;
			fillRectangle(enemy3x,enemy3y,20,5,RGBToWord(255,255,255));
			}
		}
		if (levelCount >= 3){
			if (enemy5x < 108){
				oldenemy5x = enemy5x;
				oldenemy5y = enemy5y;
				enemy5x++;
				fillRectangle(oldenemy5x,oldenemy5y,20,5,RGBToWord(0,0,0));
				fillRectangle(enemy5x,enemy5y,20,5,RGBToWord(255,255,255));
			}
			else {
			fillRectangle(enemy5x,enemy5y,20,5,RGBToWord(0,0,0));
			enemy5x = 0;
			enemy5y = random(65, 154);
			fillRectangle(enemy5x,enemy5y,20,5,RGBToWord(255,255,255));
			}
		}
		if (enemy2y > 65)
		{
			oldenemy2x = enemy2x;
			oldenemy2y = enemy2y;
			enemy2y--;
			fillRectangle(oldenemy2x,oldenemy2y,20,5,RGBToWord(0,0,0));
			fillRectangle(enemy2x,enemy2y,20,5,RGBToWord(255,255,255));
			if (count == 5)
			{
				fillRectangle(hitboxx,hitboxy,10,10,RGBToWord(255,255,0));
			}
		}
		else
		{
			fillRectangle(enemy2x,enemy2y,20,5,RGBToWord(0,0,0));
			enemy2x = random(64,108);
			enemy2y = 150;
			fillRectangle(enemy2x,enemy2y,20,5,RGBToWord(255,255,255));
		}
		if (levelCount >= 2){
			if (enemy4y < 159){
				oldenemy4x = enemy4x;
				oldenemy4y = enemy4y;
				enemy4y++;
				fillRectangle(oldenemy4x,oldenemy4y,20,5,RGBToWord(0,0,0));
				fillRectangle(enemy4x,enemy4y,20,5,RGBToWord(255,255,255));
			}
			else{
			fillRectangle(enemy4x,enemy4y,20,5,RGBToWord(0,0,0));
			enemy4x = random(64,108);
			enemy4y = 65;
			fillRectangle(enemy4x,enemy4y,20,5,RGBToWord(255,255,255));
			}
		}
		if (levelCount >= 3){
			if (enemy6x > 0){
				oldenemy6x = enemy6x;
				oldenemy6y = enemy6y;
				enemy6x--;
				fillRectangle(oldenemy6x,oldenemy6y,20,5,RGBToWord(0,0,0));
				fillRectangle(enemy6x,enemy6y,20,5,RGBToWord(255,255,255));
			}
			else {
			fillRectangle(enemy6x,enemy6y,20,5,RGBToWord(0,0,0));
			enemy6x = 108;
			enemy6y = random(65, 154);
			fillRectangle(enemy6x,enemy6y,20,5,RGBToWord(255,255,255));
			}
		}
		hmoved = vmoved = 0;
		hinverted = vinverted = 0;
		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			if (x < 118)
			{
				x = x + 1;
				hmoved = 1;
				hinverted=0;
			}						
		}
		if ((GPIOB->IDR & (1 << 5))==0) // left pressed
		{			
			
			if (x > 0)
			{
				x = x - 1;
				hmoved = 1;
				hinverted=1;
			}			
		}
		if ( (GPIOA->IDR & (1 << 11)) == 0) // down pressed
		{
			if (y < 150)
			{
				y = y + 1;			
				vmoved = 1;
				vinverted = 0;
			}
		}
		if (y > 65)
		{
			if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
			{			
				if (y > 16)
				{
					y = y - 1;
					vmoved = 1;
					vinverted = 1;
				}
			}
		}
		if ((vmoved) || (hmoved))
		{
			// only redraw if there has been some movement (reduces flicker)
			fillRectangle(oldx,oldy,10,9,0);
			oldx = x;
			oldy = y;					
			if (hmoved)
			{
				if (toggle)
				{
					putImage(x,y,10,9,heart,0,0);
					putImage(10,20,41,42,flowey,0,0);
				}
				else
				{
					putImage(x,y,10,9,heart,0,0);
					putImage(10,20,41,42,flowey,0,0);
				}

				toggle = toggle ^ 1;
			}
			else
			{
				putImage(x,y,10,9,heart,0,0);
			}
		}		
		//Checks If User Is Inside The Enemy	
		if (isInside(enemyx,enemyy,20,5,x,y) || isInside(enemyx,enemyy,20,5,x+10,y) || isInside(enemyx,enemyy,20,5,x,y+9) || isInside(enemyx,enemyy,20,5,x+10,y+9)){
			//Sets The Character Coords Back To Default
			x = 64;
			y = 105;
			enemyx = 0;
			enemyy = 150;
			enemy2x = 64;
			enemy2y = 150;
			enemy3x = 0;
			enemy3y = 65;
			enemy4x = 64;
			enemy4y = 65;
			enemy5x = 0;
			enemy5y = random(65, 154);
			enemy6x = 108;
			enemy6y = random(65, 154);
			count = 0;
			death();
			InitialiseGame(levelCount);
		}
		else if (isInside(enemy2x,enemy2y,20,5,x,y) || isInside(enemy2x,enemy2y,20,5,x+10,y) || isInside(enemy2x,enemy2y,20,5,x,y+9) || isInside(enemy2x,enemy2y,20,5,x+10,y+9)){
			//Sets The Character Coords Back To Default
			x = 64;
			y = 105;
			enemyx = 0;
			enemyy = 150;
			enemy2x = 64;
			enemy2y = 150;
			enemy3x = 0;
			enemy3y = 65;
			enemy4x = 64;
			enemy4y = 65;
			enemy5x = 0;
			enemy5y = random(65, 154);
			enemy6x = 108;
			enemy6y = random(65, 154);
			count = 0;
			death();
			InitialiseGame(levelCount);
		}
		if (levelCount >= 2){
			if (isInside(enemy3x,enemy3y,20,5,x,y) || isInside(enemy3x,enemy3y,20,5,x+10,y) || isInside(enemy3x,enemy3y,20,5,x,y+9) || isInside(enemy3x,enemy3y,20,5,x+10,y+9)){
				//Sets The Character Coords Back To Default
				x = 64;
				y = 105;
				enemyx = 0;
				enemyy = 150;
				enemy2x = 64;
				enemy2y = 150;
				enemy3x = 0;
				enemy3y = 65;
				enemy4x = 64;
				enemy4y = 65;
				enemy5x = 0;
				enemy5y = random(65, 154);
				enemy6x = 108;
				enemy6y = random(65, 154);
				count = 0;
				death();
				InitialiseGame(levelCount);
			}
			else if (isInside(enemy4x,enemy4y,20,5,x,y) || isInside(enemy4x,enemy4y,20,5,x+10,y) || isInside(enemy4x,enemy4y,20,5,x,y+9) || isInside(enemy4x,enemy4y,20,5,x+10,y+9)){
				//Sets The Character Coords Back To Default
				x = 64;
				y = 105;
				enemyx = 0;
				enemyy = 150;
				enemy2x = 64;
				enemy2y = 150;
				enemy3x = 0;
				enemy3y = 65;
				enemy4x = 64;
				enemy4y = 65;
				enemy5x = 0;
				enemy5y = random(65, 154);
				enemy6x = 108;
				enemy6y = random(65, 154);
				count = 0;
				death();
				InitialiseGame(levelCount);
			}
		}
		delay(50);
		if (isInside(hitboxx,hitboxy,20,5,x,y) || isInside(hitboxx,hitboxy,20,5,x+10,y) || isInside(hitboxx,hitboxy,20,5,x,y+9) || isInside(hitboxx,hitboxy,20,5,x+10,y+9)){
			// Checks if user is inside the yellow square
			if (count >= 5){
				levelCount += 1;
				x = 64;
				y = 105;
				enemyx = 0;
				enemyy = 150;
				enemy2x = 64;
				enemy2y = 150;
				enemy3x = 0;
				enemy3y = 65;
				enemy4x = 64;
				enemy4y = 65;
				hitboxx = random(0,100);
				hitboxy = random(65,140);
				completed();
				InitialiseGame(levelCount);
			}
		}
		if (levelCount >= 3){
			if (isInside(enemy5x,enemy5y,20,5,x,y) || isInside(enemy5x,enemy5y,20,5,x+10,y) || isInside(enemy5x,enemy5y,20,5,x,y+9) || isInside(enemy5x,enemy5y,20,5,x+10,y+9)){
				//Sets The Character Coords Back To Default
				x = 64;
				y = 105;
				enemyx = 0;
				enemyy = 150;
				enemy2x = 64;
				enemy2y = 150;
				enemy3x = 0;
				enemy3y = 65;
				enemy4x = 64;
				enemy4y = 65;
				enemy5x = 0;
				enemy5y = random(65, 154);
				enemy6x = 108;
				enemy6y = random(65, 154);
				count = 0;
				death();
				InitialiseGame(levelCount);
			}
			else if (isInside(enemy6x,enemy6y,20,5,x,y) || isInside(enemy6x,enemy6y,20,5,x+10,y) || isInside(enemy6x,enemy6y,20,5,x,y+9) || isInside(enemy6x,enemy6y,20,5,x+10,y+9)){
				//Sets The Character Coords Back To Default
				x = 64;
				y = 105;
				enemyx = 0;
				enemyy = 150;
				enemy2x = 64;
				enemy2y = 150;
				enemy3x = 0;
				enemy3y = 65;
				enemy4x = 64;
				enemy4y = 65;
				enemy5x = 0;
				enemy5y = random(65, 154);
				enemy6x = 108;
				enemy6y = random(65, 154);
				count = 0;
				death();
				InitialiseGame(levelCount);
			}
		}
		delay(50);
		if (isInside(hitboxx,hitboxy,20,5,x,y) || isInside(hitboxx,hitboxy,20,5,x+10,y) || isInside(hitboxx,hitboxy,20,5,x,y+9) || isInside(hitboxx,hitboxy,20,5,x+10,y+9)){
			// Checks if user is inside the yellow square
			if (count >= 5){
				levelCount += 1;
				x = 64;
				y = 105;
				enemyx = 0;
				enemyy = 150;
				enemy2x = 64;
				enemy2y = 150;
				enemy3x = 0;
				enemy3y = 65;
				enemy4x = 64;
				enemy4y = 65;
				hitboxx = random(0,100);
				hitboxy = random(65,140);
				completed();
				InitialiseGame(levelCount);
			}
		}
	}
	return 0;
}
void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}
void SysTick_Handler(void)
{
	milliseconds++;
}
void initClock(void)
{
// This is potentially a dangerous function as it could
// result in a system with an invalid clock signal - result: a stuck system
        // Set the PLL up
        // First ensure PLL is disabled
        RCC->CR &= ~(1u<<24);
        while( (RCC->CR & (1 <<25))); // wait for PLL ready to be cleared
        
// Warning here: if system clock is greater than 24MHz then wait-state(s) need to be
// inserted into Flash memory interface
				
        FLASH->ACR |= (1 << 0);
        FLASH->ACR &=~((1u << 2) | (1u<<1));
        // Turn on FLASH prefetch buffer
        FLASH->ACR |= (1 << 4);
        // set PLL multiplier to 12 (yielding 48MHz)
        RCC->CFGR &= ~((1u<<21) | (1u<<20) | (1u<<19) | (1u<<18));
        RCC->CFGR |= ((1<<21) | (1<<19) ); 

        // Need to limit ADC clock to below 14MHz so will change ADC prescaler to 4
        RCC->CFGR |= (1<<14);

        // and turn the PLL back on again
        RCC->CR |= (1<<24);        
        // set PLL as system clock source 
        RCC->CFGR |= (1<<1);
}
void delay(volatile uint32_t dly)
{
	uint32_t end_time = dly + milliseconds;
	while(milliseconds != end_time)
		__asm(" wfi "); // sleep
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2); // clear pull-up resistor bits
	Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	/*
	*/
	uint32_t mode_value = Port->MODER;
	Mode = Mode << (2 * BitNumber);
	mode_value = mode_value & ~(3u << (BitNumber * 2));
	mode_value = mode_value | Mode;
	Port->MODER = mode_value;
}
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py)
{
	// checks to see if point px,py is within the rectange defined by x,y,w,h
	uint16_t x2,y2;
	x2 = x1+w;
	y2 = y1+h;
	int rvalue = 0;
	if ( (px >= x1) && (px <= x2))
	{
		// ok, x constraint met
		if ( (py >= y1) && (py <= y2))
			rvalue = 1;
	}
	return rvalue;
}

void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
	display_begin();
	pinMode(GPIOB,4,0);
	pinMode(GPIOB,5,0);
	pinMode(GPIOA,8,0);
	pinMode(GPIOA,11,0);
	enablePullUp(GPIOB,4);
	enablePullUp(GPIOB,5);
	enablePullUp(GPIOA,11);
	enablePullUp(GPIOA,8);
}

int leftPressed(){
	if ((GPIOB->IDR & (1 << 5))==0){
		return 1;
	} else {
		return 0;
	}
}

int rightPressed(){
	if ((GPIOB->IDR & (1 << 4))==0) {
		return 1;
	} else {
		return 0;
	}
}