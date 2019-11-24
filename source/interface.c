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
	if(state){
		printStrSt7735S("   ",25,30,bgColor,textColor);
		printStrSt7735S("ON ",29,30,bgColor,textColor);
	}else{
		printStrSt7735S("OFF",25,30,bgColor,textColor);
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
	sprintf(buf,"%2.1f",temp);
	printStrSt7735S(buf,94,30,bgColor,textColor);
	setFontst7735S(SmallFont);
	printStrSt7735S("AKTUALNA",94,17,bgColor,textColor);
}
void updateSetpointTemp(float temp){
	setFontst7735S(BigFont);
	char buf[10];
	sprintf(buf,"%2.1f",temp);
	printStrSt7735S(buf,94,63,bgColor,textColor);
	setFontst7735S(SmallFont);
	printStrSt7735S("ZADANA",104,51,bgColor,textColor);
}
