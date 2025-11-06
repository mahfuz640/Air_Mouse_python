#include <ESP8266WiFi.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const char* ssid = "abcde";          // your Wi-Fi SSID
const char* password = "123456789";  // your Wi-Fi password
const char* serverIP = "10.94.151.52";  // your PC IP address
const int serverPort = 5000;

WiFiClient client;

#define BTN_LEFT_PIN D5
#define BTN_RIGHT_PIN D6

float gx_offset = 0, gy_offset = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);
  mpu.initialize();

  pinMode(BTN_LEFT_PIN, INPUT_PULLUP);
  pinMode(BTN_RIGHT_PIN, INPUT_PULLUP);

  Serial.println("\nConnecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Calibrate gyro
  Serial.println("Calibrating Gyroscope... Keep the sensor still!");
  long gx_sum = 0, gy_sum = 0;
  for (int i = 0; i < 200; i++) {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    gx_sum += gx;
    gy_sum += gy;
    delay(5);
  }
  gx_offset = gx_sum / 200.0;
  gy_offset = gy_sum / 200.0;
  Serial.printf("✅ Calibration done. gx_offset=%.2f gy_offset=%.2f\n", gx_offset, gy_offset);
}

void loop() {
  if (!client.connected()) {
    Serial.println("Connecting to PC...");
    if (client.connect(serverIP, serverPort)) {
      Serial.println("✅ Connected to PC!");
    } else {
      Serial.println("❌ Connection failed. Retrying...");
      delay(1000);
      return;
    }
  }

  int16_t ax, ay, az, gx_raw, gy_raw, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx_raw, &gy_raw, &gz);

  float gx = (gx_raw - gx_offset) / 131.0;
  float gy = (gy_raw - gy_offset) / 131.0;

  int dx = (int)(gx * 2.0);
  int dy = (int)(-gy * 2.0);

  if (abs(dx) < 1) dx = 0;
  if (abs(dy) < 1) dy = 0;

  bool leftPressed = !digitalRead(BTN_LEFT_PIN);
  bool rightPressed = !digitalRead(BTN_RIGHT_PIN);

  String data = String(dx) + "," + String(dy) + "," + String(leftPressed) + "," + String(rightPressed);
  client.println(data);

  delay(20);
}
