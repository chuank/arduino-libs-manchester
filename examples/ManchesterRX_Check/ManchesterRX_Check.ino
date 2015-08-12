
#include <Manchester.h>

/*

  Manchester Receiver example

  In this example receiver will receive two bytes of payload and 8 bit sender id per transmission
  message also contains an 8-bit checksum and receiver can check if the data has been transmitted correctly

  try different speeds using this constants, your maximum possible speed will
  depend on various factors like transmitter type, distance, microcontroller speed, ...

  MAN_300 0
  MAN_600 1
  MAN_1200 2
  MAN_2400 3
  MAN_4800 4
  MAN_9600 5
  MAN_19200 6
  MAN_38400 7


*/

#define RX_PIN 4
#define LED_PIN 13

#define BUFFER_SIZE 4           // 4 bytes required for buffer
uint8_t buffer[BUFFER_SIZE];    // buffer to store data for processing

uint8_t moo = 1;
uint16_t data;
uint8_t id;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, moo);
  man.setupReceive(RX_PIN, MAN_1200);
  man.beginReceive();
}

void loop() {
  if (man.receiveComplete()) { //received something

    if (man.decodeMessage(buffer, id, data)) { //extract id and data from message, check if checksum is correct
      // id now contains ID of sender, receiver or any other arbitrary 8-bit data
      // data now contains two bytes of data received from sender
      // both id and data are BELIEVED (not guaranteed) to be transmitted correctly
      moo = ++moo % 2;
      digitalWrite(LED_PIN, moo);

      man.beginReceiveArray(BUFFER_SIZE, buffer);   // get ready for new incoming data
    }
  }
}
