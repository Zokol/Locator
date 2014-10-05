/*
  Arduino Transponder
  Author: Heikki Juva - OH1EMX, heikki@juva.lu
  Version: 0.5 - 03.10.2014
  
  This is an small program that uses simple ASK-transmitter to broadcast an identifier and payload. 
  As an example, the payload can contain altitude and location data, or similar information to ease finding the transmitter.
  
  I wrote this program to help locating my FPV Quadcopter in case of crashing it.
 */
 
char ID[] = "OH1EMX";
int TX_pin = 13;
int BIT_DELAY = 100;
int CHAR_DELAY = 0;
int MSG_DELAY = 10000;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(TX_pin, OUTPUT);
  digitalWrite(TX_pin, LOW);    // ensure that the TX is off 
  delay(MSG_DELAY);
}

// the loop routine runs over and over again forever:
void loop() {
  for (int i = 0; i < 6; i++){
    tx_char(ID[i]);
    digitalWrite(TX_pin, LOW);    // Send 0
    delay(CHAR_DELAY);
  }
  delay(MSG_DELAY);
}

// Converts the character into bitstream and transmits it.
void tx_char(char c) {
  // This will 'output' the binary representation of 'inputChar' as 8 characters of '1's and '0's, MSB first.
  for ( uint8_t bitMask = 128; bitMask != 0; bitMask = bitMask >> 1 ) {
    if ( c & bitMask ) {
      digitalWrite(TX_pin, HIGH);   // Send 1
      Serial.write("1");
    } else {
      digitalWrite(TX_pin, LOW);    // Send 0
      Serial.write("0");
    }
    delay(BIT_DELAY);  // wait between bits
    //digitalWrite(TX_pin, LOW);    // Send 0
  }
}
