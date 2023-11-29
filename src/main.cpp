#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

const int xshut0 = 4;
const int xshut1 = 5;
Adafruit_VL53L0X lox0 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (! Serial) {
    delay(1);
  }

  pinMode(xshut0, OUTPUT);
  pinMode(xshut1, OUTPUT);
  digitalWrite(xshut0, LOW);
  digitalWrite(xshut1, LOW);
  delay(10);
  digitalWrite(xshut0, HIGH);
  digitalWrite(xshut1, HIGH);
  delay(10);

  // SET SENSOR#0
  digitalWrite(xshut1, LOW);
  Serial.println("SET VL53L0X#0 ADDRESS: 0x30");
  if (!lox0.begin(0x30)) {
    Serial.println(F("Failed to boot VL53L0X#0 at 0x30"));
    while(1);
  }

  // SET SENSOR#1
  digitalWrite(xshut1, HIGH);
  Serial.println("SET VL53L0X#1 ADDRESS: 0x31");
  if (!lox1.begin(0x31)) {
    Serial.println(F("Failed to boot VL53L0X#1 at 0x31"));
    while(1);
  }

  // start continuous ranging
  lox0.startRangeContinuous();
  lox1.startRangeContinuous();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (lox0.isRangeComplete() && lox1.isRangeComplete()) {
    Serial.print("Sensor#0: ");
    Serial.print(lox0.readRange());
    Serial.print(", Sensor#1: ");
    Serial.println(lox1.readRange());
  }
  delay(300);
}