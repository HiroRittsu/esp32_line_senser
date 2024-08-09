#include <Arduino.h>
#include <Wire.h>

#define I2C_SDA 21
#define I2C_SCL 22

// r:赤 g:緑 b:青 a:赤外
int r, g, b, a;

bool onLine = false;
int count = 0;
unsigned long ts, te;

void colorRead() {
  int h, l;
  Wire.beginTransmission(0x2A);
  Wire.write(0x03);
  Wire.endTransmission();
  Wire.requestFrom(0x2A, 8);

  if (Wire.available()) {
    // 赤
    h = Wire.read();
    l = Wire.read();
    r = h << 8 | l;
    // Serial.print("r:");
    // Serial.print(r);
    // 緑
    h = Wire.read();
    l = Wire.read();
    g = h << 8 | l;
    // Serial.print(" g:");
    // Serial.print(g);
    // 青
    h = Wire.read();
    b = Wire.read();
    r = h << 8 | l;
    // Serial.print(" b:");
    // Serial.print(b);
    // 赤外
    h = Wire.read();
    l = Wire.read();
    a = h << 8 | l;
    // Serial.print(" a:");
    // Serial.print(a);
    // Serial.println("");

    if (!true) {
      Serial.print(r);
      Serial.print(" ");
      Serial.print(g);
      Serial.print(" ");
      Serial.print(b);
      Serial.print("\n");
    }

    if (r > 300 && g > 300) {
      if (!onLine) Serial.println("###検知");
      onLine = true;
    } else {
      if (onLine) {
        Serial.println(count);
        onLine = false;
        count++;
      }
    }
  }
  Wire.endTransmission();
}

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);

  Serial.begin(115200);

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  // 初期化
  Wire.beginTransmission(0x2A);
  Wire.write(0x0);
  Wire.write(0x89);
  Wire.endTransmission();
  Wire.beginTransmission(0x2A);
  Wire.write(0x0);
  Wire.write(0x09);
  Wire.endTransmission();
}

void loop() {
  // Serial.print("1: ");
  ts = micros();
  // Serial.print(ts - te);
  // Serial.print(" 2: ");
  colorRead();
  te = micros();
  // Serial.print(te - ts);
  // Serial.print("\n");
}
