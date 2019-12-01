#include <string>
using namespace std;
struct temperatureSensorData {
	int RSSI;
	string devType;
	float batVoltage;
	float actualTemperature;
	string id;
	bool error;
	int timeoutTimer;
	int maxTimeout;
} roomSensor;

struct outputModuleData {
	int RSSI;
	string devType;
	string state;
	float actualTemperature;
	float setpointTemperature;
	string id;
	bool error;
	int timeoutTimer;
	int maxTimeout;
} outputModule;

struct systemSettings{
	float heatingSetpoint;
	float heatingHist;
}settings;

struct systemStatus{
	bool heatingState;
	bool error;
}status;

