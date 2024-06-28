#include <RH_RF95.h>

#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(9600);
  while (!Serial);

  if (!rf95.init()) {
    Serial.println("LoRa initialization failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully");
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == '1') {
      sendMessage("elephant");
    } else if (receivedChar == '2') {
      sendMessage("cow");
    } else {
      sendMessage("other");
    }
  }
}

void sendMessage(const char* message) {
  Serial.print("Sending message: ");
  Serial.println(message);
  rf95.send((uint8_t *)message, strlen(message));
  rf95.waitPacketSent();
  Serial.println("Message sent successfully");
}
