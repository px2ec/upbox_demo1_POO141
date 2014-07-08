// Control de Reles upBox
// Version 1.0 by Pedro Espinoza

// cantidad de ventosas por defecto
#define ACTUATORS		4

// Tipo de instrucciones
#define ENABLE_INTR		48
#define DISABLE_INTR	56
//--
#define ENABLE_ALL		44
#define DISABLE_ALL		52

#define CHECK_DEV		16


typedef struct minipkt {
	int size; // bytes of parameters
	int gcount; // counter rx parameters
	int param[99]; // array of parameters
	int intr ; // instruction
	int ready; // packet status
	}packet;

int act_arr[ACTUATORS] = {9, 8, 7, 6}; // pins of suction-cups
int enflag = 0; // enable flag from recieving packet

// working packet
packet lepacket;

void printDeviceDescription() {
	Serial.write(0xFF);
	Serial.write(CHECK_DEV);
	Serial.write(8);
	Serial.write("ACT_RELE");
}

void setup() {
	// initialize the serial communication:
	Serial.begin(9600);
	// initialize the Pines as an output:
	for (int i = 0; i < ACTUATORS; i++) {
		pinMode(act_arr[i], OUTPUT);
	}
	
	lepacket.ready = 0;
	lepacket.intr = 0;
	lepacket.size = 0;
	lepacket.gcount = 0;

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
		case CHECK_DEV:
			if (tmppacket.param[0] == CHECK_DEV)
				printDeviceDescription();
			break; 
		case ENABLE_INTR: // activar de forma selectiva
			for(int i = 0; i < n_sucks; i++){
					aux1 = tmppacket.param[i];
					digitalWrite(act_arr[aux1 - 1], 1);
			}

			break;
		case DISABLE_INTR: // desactivar de forma selectiva
			for(int i = 0; i < n_sucks; i++){
					aux1 = tmppacket.param[i];
					digitalWrite(act_arr[aux1 - 1], 0);
			}

			break;
		case ENABLE_ALL: // activar todos
			for(int i = 0; i < ACTUATORS; i++){
					digitalWrite(act_arr[i], 1);
			}

			break;
		case DISABLE_ALL: // desactivar todos
			for(int i = 0; i < ACTUATORS; i++){
					digitalWrite(act_arr[i], 0);
			}

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