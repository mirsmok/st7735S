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
using namespace std;
struct temperatureSensorData {
	int RSSI;
	string devType;
	float batVoltage;
	float actualTemperature;
	string id;
} roomSensor;

string findTag(string input, string tag){
	string startTag = "<"+tag+">";
	string endTag = "</"+tag+">";
	string missing = "";

	if(input.find(startTag)>=0 && input.find(endTag)>=0 ){
		int startIndex= input.find(startTag)+startTag.length();
		int stopIndex = input.find(endTag);
		string value=input.substr(startIndex,stopIndex-startIndex);
		return value;
	}  
	else{
		return missing;
	}	    
}

void parseRoomSensorData(char * buf){
	string data=buf;
	roomSensor.RSSI=stof(findTag(data,"RSSI"));
	roomSensor.devType=findTag(data,"dev_type");
	roomSensor.batVoltage=stof(findTag(data,"supplayVoltage"));
	roomSensor.actualTemperature=stof(findTag(data,"sensorTemperature"));
	roomSensor.id=stof(findTag(data,"id"));
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
dataToSend+=String("<sensorTemperature>")+ String(actualTemperature)+ String("</sensorTemperature></content>");
 */
struct outputModuleData {
	int RSSI;
	string devType;
	string state;
	float actualTemperature;
	string id;
} outputModule;


void parseOutputModuleData(char * buf){
	string data=buf;
	outputModule.RSSI=stof(findTag(data,"RSSI"));
	outputModule.devType=findTag(data,"dev_type");
	outputModule.state=findTag(data,"outputState");
	outputModule.actualTemperature=stof(findTag(data,"sensorTemperature"));
	outputModule.id=stof(findTag(data,"id"));
}
