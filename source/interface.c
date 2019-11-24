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
	lcdst_drawHLine(0,15,159,frameColor.r,frameColor.g,frameColor.b);
	lcdst_drawVLine(100,15,60,frameColor.r,frameColor.g,frameColor.b);	
	lcdst_drawHLine(0,60,100,frameColor.r,frameColor.g,frameColor.b);
	lcdst_drawHLine(100,50,60,frameColor.r,frameColor.g,frameColor.b);
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
