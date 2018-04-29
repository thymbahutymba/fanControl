#include <wiringPi.h>
#include <fstream>
#include <iostream>
#include <csignal>
#include <stdlib.h>
using namespace std;

extern "C" void sendMessage(string);

#define u2s 1000000
#define m2s 1000
#define MAX_TEMP 60
#define NORMAL_TEMP 40
#define pin 1

void handler(int SIG){
	digitalWrite(pin, LOW);
	cout << "Exit from fan control, signal " << SIG << " received." << endl;
	sendMessage("fanControl stopped.");
	exit(0);
}

int main(){

	const int c = 1000;

	int temp;
	ifstream file;

	signal(SIGTERM, handler);
	signal(SIGHUP, handler);
	signal(SIGINT, handler);

	wiringPiSetup();
	pinMode(pin, OUTPUT);
	sendMessage("fanControl started.");
	for(;;){

		//read the temperature from the file
		file.open("/sys/class/thermal/thermal_zone0/temp", ios_base::in);
		file >> temp;
		file.close();

		//calculate temperature as integer
		temp /= c;
		if(temp>MAX_TEMP && !digitalRead(pin)){
			digitalWrite(pin, HIGH);
			cout << "Fan on, current temp is: " << temp << "°C." << endl;
			//sendMessage("Fan on.");
		};
		if(temp<NORMAL_TEMP && digitalRead(pin)){
			digitalWrite(pin, LOW);
			cout << "Fan off, current temp is: " << temp << "°C." << endl;
			//sendMessage("Fan off.");
		};
		delay(5*m2s);
	};
	return 0;
}
