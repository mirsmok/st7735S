//data exchange module
/*
data structure from temperature sensor 
String dataToSend = "<content><RSSI>"+String(WiFi.RSSI())+"</RSSI>";
dataToSend+="<dev_type>temperatureSensor</dev_type>";
dataToSend+="<supplayVoltage>"+String(supplayVoltage)+"</supplayVoltage>";
dataToSend+="<sensorTemperature>"+String(temperature)+"</sensorTemperature>";
dataToSend+="<id>2001</id></content>";

*/
#include <string>
#include "dataExchange.h"
using namespace std;

void heating(void){
	if(roomSensor.actualTemperature < (settings.heatingSetpoint-settings.heatingHist))
		status.heatingState=true;
	if(roomSensor.actualTemperature > (settings.heatingSetpoint-settings.heatingHist)) 
		status.heatingState=false;
}

string findTag(string input, string tag){
	string startTag = "<"+tag+">";
	string endTag = "</"+tag+">";
	string missing = "";
	size_t pos1=input.find(startTag.c_str());
	size_t pos2=input.find(endTag.c_str());
	if(pos1!=string::npos && pos2!=string::npos){
		int startIndex= input.find(startTag.c_str())+startTag.length();
		int stopIndex = input.find(endTag.c_str());
		string value=input.substr(startIndex,stopIndex-startIndex);
		return value;
	}  
	else{
		return missing;
	}	    
}

void parseData(char * buf){
//	printf("\notrzymano dane");
	string data(buf,strlen(buf));
	string returnValue="";
//	printf("\ndane: %s",data.c_str());
	string devType=findTag(data,"dev_type");
	if(devType=="temperatureSensor"){
		if(findTag(data,"dev_type")!="")
			roomSensor.devType=findTag(data,"dev_type");
		if(findTag(data,"RSSI")!="")
			roomSensor.RSSI=stoi(findTag(data,"RSSI"));
		if(findTag(data,"supplayVoltage")!="")
			roomSensor.batVoltage=stof(findTag(data,"supplayVoltage"));
		if(findTag(data,"sensorTemperature")!="")
			roomSensor.actualTemperature=stof(findTag(data,"sensorTemperature"));
		if(findTag(data,"id")!="")
			roomSensor.id=findTag(data,"id");
		strcpy(buf, returnValue.c_str());
		roomSensor.error=false;
		roomSensor.timeoutTimer=0;
	}
	if(devType=="outputModule"){
		if(findTag(data,"RSSI")!="")
			outputModule.RSSI=stoi(findTag(data,"RSSI"));
		if(findTag(data,"dev_type")!="")
			outputModule.devType=findTag(data,"dev_type");
		if(findTag(data,"outputState")!="")
			outputModule.state=findTag(data,"outputState");
		if(findTag(data,"sensorTemperature")!="")
			outputModule.actualTemperature=stof(findTag(data,"sensorTemperature"));
		if(findTag(data,"id")!="")
			outputModule.id=findTag(data,"id");
		//prepere output
		returnValue+="<content><setpointTemperature>";
		char ans[10];
		snprintf(ans,10,"%2.1f",settings.heatingSetpoint);
		returnValue+=ans;
		returnValue+="</setpointTemperature><roomTemperature>";
		snprintf(ans,10,"%2.1f",roomSensor.actualTemperature);
		returnValue+=ans;
		if(status.heatingState)
			returnValue+="</roomTemperature><outputState>ON</outputState></content>";
		else
			returnValue+="</roomTemperature><outputState>OFF</outputState></content>";
		strcpy(buf,returnValue.c_str());
		outputModule.error=false;
		outputModule.timeoutTimer=0;
	}
	if(devType=="remoteConsole"){
		if(findTag(data,"setpoint")!=""){
			string tag=findTag(data,"setpoint");
			settings.heatingSetpoint=atof(tag.c_str());
		}
	}
//	return buf;
}

/*parse data on output module
if (!findTag(line,"setpointTemperature").equals(""))
	setpointTemperature=findTag(line,"setpointTemperature");
if(!findTag(line,"roomTemperature").equals(""))
	roomTemperature=findTag(line,"roomTemperature");
value=findTag(line,"outputState");
if(!value.equals("") ){
	if (value.equals("ON")){
		outputState=true;
	}
	if (value.equals("OFF")){
		outputState=false;
	}
}
/////////////////////////////////////////////////////
//send data to server from outputModule
////////////////////////////////////////////////////
String dataToSend="<content><RSSI>"+String(WiFi.RSSI())+"</RSSI>";
dataToSend+="<dev_type>outputModule</dev_type>";
dataToSend+="<id>1002</id>";
dataToSend+=String("<outputState>")+ String(outputState ? "ON" : "OFF")+ String("</outputState>");
dataToSend+=String("<sensorTemperature>")+ String(actualTemperature)+ String("</sensorTemperature></content>");*/

