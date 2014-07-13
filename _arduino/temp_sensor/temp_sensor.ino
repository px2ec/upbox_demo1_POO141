// Control de Reles upBox
// Version 1.0 by Pedro Espinoza

// cantidad de ventosas por defecto

// Tipo de instrucciones
#define RQST_TEMP		15
//--
#define CHECK_DEV		16
#define INIT_DEV		9

#define CHECK_STATE		42

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 9
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

typedef struct minipkt {
	int size; // bytes of parameters
	int gcount; // counter rx parameters
	int param[99]; // array of parameters
	int intr ; // instruction
	int ready; // packet status
	}packet;

int act_state = 0;
int enflag = 0; // enable flag from recieving packet

// working packet
packet lepacket;

void printDeviceDescription() {
	Serial.write(0xFF);
	Serial.write(CHECK_DEV);
	Serial.write(8);
	Serial.write("TMP_SENS");
}

void sendState() {
	Serial.write(0xFF);
	Serial.write(CHECK_STATE);
	Serial.write(1);
	Serial.write((int)act_state);
}

void sendTemp() {
	sensors.requestTemperatures(); // Send the command to get temperatures

	Serial.write(0xFF);
	Serial.write(RQST_TEMP);
	Serial.write(1);
	Serial.write((int)sensors.getTempCByIndex(0));
}

void setup() {
	// initialize the serial communication:
	Serial.begin(9600);

	lepacket.ready = 0;
	lepacket.intr = 0;
	lepacket.size = 0;
	lepacket.gcount = 0;

	sensors.begin();
}

void loop() {

	if ((enflag != 1) || !(lepacket.ready)) return;

	packet tmppacket = lepacket;
	int aux1 = 0;

	enflag = 0;
	lepacket.ready = 0;
	lepacket.intr = 0;
	lepacket.size = 0;
	lepacket.gcount = 0;

	int n_sucks = tmppacket.size;

	switch(tmppacket.intr){
		case INIT_DEV:
			//Serial.write(0);
			break;
		case CHECK_DEV:
			if (tmppacket.param[0] == CHECK_DEV)
				printDeviceDescription();
			break; 
		case RQST_TEMP:
			if (tmppacket.param[0] == RQST_TEMP)
				sendTemp();
			break; 
		}
}

void serialEvent() {
	int input = 0; // temporally variable for serial cache
	while (Serial.available()) {
		input = (int)Serial.read();

		// while recieving bytes, keeps in packet's structure
		if ((input == 255) && (enflag == 0)) {
			enflag = 1;
		} else if ((enflag == 1) && (lepacket.intr == 0)) {
			lepacket.intr = input;
		} else if ((enflag == 1) && (lepacket.size == 0)) {
			lepacket.size = input;
		} else if ((enflag == 1) && (lepacket.size > 0) && (lepacket.size != lepacket.gcount)) {
			lepacket.param[lepacket.gcount++] = input;
			if(lepacket.size == lepacket.gcount){
				lepacket.ready = 1;
			}
		}

		//Serial.println(input);
	}
}