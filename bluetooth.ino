
// #define RELAY_CONTROL_PIN 2
#define MAX_NUM_OF_USERS 3
#define DEBUG

int pinFromApp = 0;

struct User {
  // TODO: Add RFID identity here??
    int id;
    int pin;
    char name[5];
} users[MAX_NUM_OF_USERS] = {
  // Id,  Pin, "Name"
    { 1, 1111, "Jani" },
    { 2, 2222, "Joni" },
    { 3, 3333, "Satu" }
  }; 

  bool bluetoothAuth(){
    /*
     * Serial.available()
     * 
     * Get the number of bytes (characters) available for reading from the serial port.
     * This is data that's already arrived and stored in the serial receive buffer (which holds 64 bytes).
     * Reference: https://www.arduino.cc/en/Serial/Available
    */
    if(Serial.available() > 0){
      /*
       * Serial.parseInt()
       * 
       * Returns the first valid (long) integer number from the serial buffer. Characters that are not integers (or the minus sign) are skipped.
       * Reference: https://www.arduino.cc/en/Reference/ParseInt
      */
      pinFromApp = Serial.parseInt();
      // Loop through the users array
      for(int i = 0; i < MAX_NUM_OF_USERS; i++) {
        // Check if: pin code sent by the user through the mobile app is same as one of the hardcoded pin's at the users array
        if(pinFromApp == users[i].pin){
            #ifdef DEBUG
              // Debug code...
              Serial.print("ID: ");
              Serial.println(users[i].id);
              Serial.print("Nimi: ");
              Serial.println(users[i].name);
            #endif
            return true;
          }
          /*
           * TODO:
           * else {
           * // Authentication failed
           * }
          */
      }
      }
      return false;
    }

// Opens the solenoid lock
void relayControl(int operatingTime){
  PORTD &= ~_BV(PB2);  // Write port D Bit 2 value to LOW (BV = Bit Value)
  delay(operatingTime);
  PORTD |= _BV(PB2);  // Write port D Bit 2 value to HIGH
  }

void setup() {
  
  Serial.begin(9600);
  DDRD = _BV(PD2);
  // Pin 2 state is defined to HIGH for the relay control (NO, Normally Open)
  PORTD |= _BV(PB2);  // Write port D Bit 2 value to HIGH
}

void loop() {
  
  if(bluetoothAuth() == true){
      // TODO: Write authentication data to MicroSD
    #ifdef DEBUG
      // Debug code...
      Serial.println("RELE NAPS, LUKKO AUKI");
    #endif
    // Opens the solenoid lock for 500ms (short operating time is only for development purpose)
    relayControl(500);
    }
    /*
     * else {
     * // Authentication failed
     * // TODO: Write authentication data to MicroSD
     * }
    */
}
