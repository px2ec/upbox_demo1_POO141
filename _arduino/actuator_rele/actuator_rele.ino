// Control de ventosas para robot ZBOT
// Version 2.0 by Pedro Espinoza

// cantidad de ventosas por defecto
#define C_SUCKS       4

// Tipo de instrucciones
#define ENABLE_INTR   48
#define DISABLE_INTR  56
//--
#define ENABLE_ALL    44
#define DISABLE_ALL   52


typedef struct minipkt {
  int size; // bytes of parameters
  int gcount; // counter rx parameters
  int param[99]; // array of parameters
  int intr ; // instruction
  int ready; // packet status
  }packet;

int suckpines[C_SUCKS] = {9, 8, 7, 6}; // pins of suction-cups
int enflag = 0; // enable flag from recieving packet

// working packet
packet lepacket;

void setup()
{
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the Pines as an output:
  for (int i = 0; i < C_SUCKS; i++) {
    pinMode(suckpines[i], OUTPUT);
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
    case ENABLE_INTR: // activar de forma selectiva
      // se trabajan las ventosas
      for(int i = 0; i < n_sucks; i++){
          aux1 = tmppacket.param[i];
          digitalWrite(suckpines[aux1 - 1], 1);
      }

      break;
    case DISABLE_INTR: // desactivar de forma selectiva
      // se trabajan las ventosas
      for(int i = 0; i < n_sucks; i++){
          aux1 = tmppacket.param[i];
          digitalWrite(suckpines[aux1 - 1], 0);
      }

      break;
    case ENABLE_ALL: // activar todos
      // se trabajan las ventosas
      for(int i = 0; i < C_SUCKS; i++){
          digitalWrite(suckpines[i], 1);
      }

      break;
    case DISABLE_ALL: // desactivar todos
      // se trabajan las ventosas
      for(int i = 0; i < C_SUCKS; i++){
          digitalWrite(suckpines[i], 0);
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

    Serial.println(input);
  }
}