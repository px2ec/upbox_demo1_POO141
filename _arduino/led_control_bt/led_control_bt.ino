
char NOMBRE[10]  = "MODDEVBT_";    
char BPS         = '4';           // 1=1200 , 2=2400, 3=4800, 4=9600, 5=19200, 6=38400, 7=57600, 8=115200
char PASS[10]    = "0000";        
 
// Control de LedControl over bluetooth upBox
// Version 1.0 by Pedro Espinoza

// 
//#define ACTUATORS     4

// Tipo de instrucciones
#define ENABLE_INTR     48
#define DISABLE_INTR    56
//--
#define ENABLE_ALL      44
#define DISABLE_ALL     52

#define CHECK_DEV       16
#define INIT_DEV        9

#define CHECK_STATE     42
#define SET_BRIGHTNESS  12


typedef struct minipkt {
    int size; // bytes of parameters
    int gcount; // counter rx parameters
    int param[99]; // array of parameters
    int intr ; // instruction
    int ready; // packet status
    }packet;

const int led_pin = 9; // pins of suction-cups
int enflag = 0; // enable flag from recieving packet
bool led_state = 0;

// working packet
packet lepacket;

void printDeviceDescription() {
    Serial.write(0xFF);
    Serial.write(CHECK_DEV);
    Serial.write(8);
    Serial.write("LED_CTRL");
}

void sendState() {
    Serial.write(0xFF);
    Serial.write(CHECK_STATE);
    Serial.write(1);
    Serial.write((int)led_state);
}

void setup() {
    // initialize the serial communication bt:
    Serial.begin(9600);
    pinMode(13,OUTPUT);
    digitalWrite(13,HIGH);
    delay(10000);
    digitalWrite(13,LOW);
    
    Serial.print("AT"); 
    delay(1000);
 
    Serial.print("AT+NAME"); 
    Serial.print(NOMBRE);
    delay(1000);
 
    Serial.print("AT+BAUD"); 
    Serial.print(BPS); 
    delay(1000);
 
    Serial.print("AT+PIN");
    Serial.print(PASS); 
    delay(1000);   
    // initialize the Pines as an output:
    pinMode(led_pin, OUTPUT);
    
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
        case INIT_DEV:
            //Serial.write(0);
            break;
        case CHECK_DEV:
            if (tmppacket.param[0] == CHECK_DEV)
                printDeviceDescription();
            break; 
        case ENABLE_INTR: // activar de forma selectiva
            led_state = 1;
            digitalWrite(led_pin, 1);

            break;
        case DISABLE_INTR: // desactivar de forma selectiva
            led_state = 0;
            digitalWrite(led_pin, 0);

            break;
        case CHECK_STATE: // desactivar de forma selectiva
            if (tmppacket.param[0] == CHECK_STATE)
                led_state = 0;
            digitalWrite(led_pin, 0);

            break;
        case SET_BRIGHTNESS: // desactivar de forma selectiva
            
            analogWrite(led_pin, (int)(tmppacket.param[0]));

            break;
//      case ENABLE_ALL: // activar todos
//          for(int i = 0; i < ACTUATORS; i++){
//                  digitalWrite(act_arr[i], 1);
//          }
//
//          break;
//      case DISABLE_ALL: // desactivar todos
//          for(int i = 0; i < ACTUATORS; i++){
//                  digitalWrite(act_arr[i], 0);
//          }
//
//          break; 
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