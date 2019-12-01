/*
 * MIT License
 * Copyright (c) 2018, Michal Kozakiewicz, github.com/michal037
 *
 * Version: 2.0.0
 * Standard: GCC-C11
 */

bool firstLoop =true;
#include <stdio.h>
#include <wiringPi.h>
#include "st7735s.h"
#include "interface.h"
#include "DefaultFonts.cpp"
//#include "interface.cpp"
#include "server.cpp"
#include "dataExchange.cpp"
#include "interface.cpp"
#include <string>
#include "cloud.cpp"
//#include <signal.h>
#include "cyclicInterrupt.cpp"
using namespace std;

int main(int argc, char *argv[])
{
	//setup cyclic interrupt in interval 1000us
//	signal(SIGALRM, cyclicInterrupt);   
//	ualarm(100000, 100000);
	//server socket for temp external device
	sockServ server;
	server.setRcvCB(parseData);
	//init server max_clients=30 port 1500
	server.init(1500,30);
	

	lcdst_t *myDisplay = NULL;
	
	/* Initialize the Wiring Pi library */
	wiringPiSetup();
	
	/* Initialize the display and receive pointer */
	myDisplay = lcdst_init(30000000, 0, 9, 8);
	
	/* Print received pointer */
	printf("myDisplay: %p\n", myDisplay);
	//system configuration	
	configKeyboard();
	lcdst_setInversion(1);
	setBgColor(50,50,50);
    	setFgColor(0,255,0);
	setFrameColor(255,0,255);
	setTextColor(50,255,50);
	setErrorColor(255,0,0);
	//draw whole screen in background color
	lcdst_drawFRect(0, 0, 161, 80, bgColor.r,bgColor.g,bgColor.b);
	drawFrames();
	unsigned int loopCounter=0;
	settings.heatingSetpoint=21.5;
	roomSensor.actualTemperature=21.6;
	roomSensor.maxTimeout=800;
	outputModule.maxTimeout=60;
	while(1){
		if((loopCounter%2)==0)
			cyclicInterrupt();
		if((loopCounter%10)==0){
			//check if some new data arrive
			server.check();
			//check heating conditions
			heating();
			updateHeatingState(status.heatingState);
			updateHeatingTemp(outputModule.actualTemperature);
			updateActualTemp(roomSensor.actualTemperature);
		}
		if((loopCounter%250)==0)
			putThingspeakData();
		updateStatus();
		updateSetpointTemp(settings.heatingSetpoint);
		checkKeyboard();
		delay(100);
		loopCounter++;
		firstLoop=false;
	}	
	return 0;
} /* main */
