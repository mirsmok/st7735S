#define btnBack 2
#define btnForward 3
#define btnUp 4
#define btnDown 5
#define btnEnter 1
void setBgColor(unsigned char r,unsigned char g, unsigned char b){
	bgColor.r=r;
	bgColor.g=g;
	bgColor.b=b;
}
void setFgColor(unsigned char r,unsigned char g, unsigned char b){
	fgColor.r=r;
	fgColor.g=g;
	fgColor.b=b;
}
void setFrameColor(unsigned char r,unsigned char g, unsigned char b){
	frameColor.r=r;
	frameColor.g=g;
	frameColor.b=b;
}
void setTextColor(unsigned char r,unsigned char g, unsigned char b){
	textColor.r=r;
	textColor.g=g;
	textColor.b=b;
}
void drawFrames(void){
	int verticalSplit=92;
	lcdst_drawHLine(0,15,159,frameColor.r,frameColor.g,frameColor.b);
	lcdst_drawVLine(verticalSplit,15,65,frameColor.r,frameColor.g,frameColor.b);	
	lcdst_drawHLine(0,60,verticalSplit,frameColor.r,frameColor.g,frameColor.b);
	lcdst_drawHLine(verticalSplit,49,160-verticalSplit,frameColor.r,frameColor.g,frameColor.b);
}
void updateStatus(char * message){
	setFontst7735S(SmallFont);
	printStrSt7735S(message,10,1,bgColor,textColor);
}
void updateHeatingState(unsigned char state){
	setFontst7735S(BigFont);
	char on[]="ON ";
	char off[]="OFF";
	if(state){
		printStrSt7735S(on,25,30,bgColor,textColor);
	}else{
		printStrSt7735S(off,25,30,bgColor,textColor);
	}
}
void updateHeatingTemp(float temp){
	setFontst7735S(SmallFont);
	char buf[12];
	sprintf(buf,"WODA:%2.1f",temp);
	printStrSt7735S(buf,8,65,bgColor,textColor);
}
void updateActualTemp(float temp){
	setFontst7735S(BigFont);
	char buf[10];
	char aktualna[]="AKTUALNA";
	sprintf(buf,"%2.1f",temp);
	printStrSt7735S(buf,94,30,bgColor,textColor);
	setFontst7735S(SmallFont);
	printStrSt7735S(aktualna,94,17,bgColor,textColor);
}
void updateSetpointTemp(float temp){
	setFontst7735S(BigFont);
	char buf[10];
	char zadana[]="ZADANA";
	sprintf(buf,"%2.1f",temp);
	printStrSt7735S(buf,94,63,bgColor,textColor);
	setFontst7735S(SmallFont);
	printStrSt7735S(zadana,104,51,bgColor,textColor);
}
//*********** GPIO config for keyboard ****************
// CON 	| wiring GPIO   | function
// 13  	|	2	| Back		
// 15	|	3	| Forward
// 16	|	4	| Up
// 18	|	5	| Down
// 12	|	11	| Enter/Long push = power down
//*****************************************************

void configKeyboard(void){
	pinMode(btnBack,INPUT);
	pullUpDnControl(btnBack,PUD_UP);
	pinMode(btnForward,INPUT);
	pullUpDnControl(btnForward,PUD_UP);
	pinMode(btnUp,INPUT);
	pullUpDnControl(btnUp,PUD_UP);
	pinMode(btnDown,INPUT);
	pullUpDnControl(btnDown,PUD_UP);
	pinMode(btnEnter,INPUT);
	pullUpDnControl(btnEnter,PUD_UP);
}
struct defKeyboard{
	bool upPressed;
	bool downPressed;
	bool backPressed;
	bool forwardPressed;
	bool enterPressed;
	bool upLongPressed;
	bool downLongPressed;
	bool backLongPressed;
	bool forwardLongPressed;
	bool enterLongPressed;
	int upCounter;
	int downCounter;
	int backCounter;
	int forwardCounter;
	int enterCounter;
} keyboard;
void checkKeyboard(void){
	//button back
	if(!digitalRead(btnBack)){
		delay(10);
		if(!digitalRead(btnBack)){
			updateStatus("<<<<<<<<<<");
			keyboard.backPressed=true;
			keyboard.backCounter++;
			if(keyboard.backCounter > 10){
				keyboard.backLongPressed=true;
				updateStatus(":LONG <<<<<<<<<<<");
			}
		}			
	}
	else{
		keyboard.backPressed=false;
		keyboard.backLongPressed=false;
		keyboard.backCounter=0;
	}
	//button foreard
	if(!digitalRead(btnForward)){
		delay(10);
		if(!digitalRead(btnForward)){
			updateStatus(">>>>>>>>>>");
			keyboard.forwardPressed=true;
			keyboard.forwardCounter++;
			if(keyboard.forwardCounter > 10){
				keyboard.forwardLongPressed=true;
				updateStatus(":LONG >>>>>>>>");
			}
		}			
	}
	else{
		keyboard.forwardPressed=false;
		keyboard.forwardLongPressed=false;
		keyboard.forwardCounter=0;
	}
	//button up
	if(!digitalRead(btnUp)){
		delay(10);
		if(!digitalRead(btnUp)){
			updateStatus("/\\ /\\ /\\");
			keyboard.upPressed=true;
			keyboard.upCounter++;
			if(keyboard.upCounter > 10){
				keyboard.upLongPressed=true;
				updateStatus(":LONG /\\ /\\ /\\");
			}
		}			
	}
	else{
		keyboard.upPressed=false;
		keyboard.upLongPressed=false;
		keyboard.upCounter=0;
	}
	//button down
	if(!digitalRead(btnDown)){
		delay(10);
		if(!digitalRead(btnDown)){
			updateStatus("\\/ \\/ \\/");
			keyboard.downPressed=true;
			keyboard.downCounter++;
			if(keyboard.downCounter > 10){
				keyboard.downLongPressed=true;
				updateStatus(":LONG \\/ \\/ \\/");
			}
		}			
	}
	else{
		keyboard.downPressed=false;
		keyboard.downLongPressed=false;
		keyboard.downCounter=0;
	}
	//button enter
	if(!digitalRead(btnEnter)){
		delay(10);
		if(!digitalRead(btnEnter)){
			updateStatus("_| _| _|");
			keyboard.enterPressed=true;
			keyboard.enterCounter++;
			if(keyboard.enterCounter > 10){
				keyboard.enterLongPressed=true;
				updateStatus(":LONG _| _| _|");
			}
		}			
	}
	else{
		keyboard.enterPressed=false;
		keyboard.enterLongPressed=false;
		keyboard.enterCounter=0;
	}
//******************** actions *********************
	if(keyboard.enterLongPressed){
		updateStatus("!!! Shutdown now !!!");
		system("sudo shutdown now");
	}
	if(keyboard.upPressed){
		settings.heatingSetpoint+=0.1;
	}
	if(keyboard.downPressed){
		settings.heatingSetpoint-=0.1;
	}
}
