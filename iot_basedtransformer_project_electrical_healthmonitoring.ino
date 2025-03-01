#define BLYNK_TEMPLATE_ID "TMPL3BgRZDXri"
#define BLYNK_TEMPLATE_NAME "iot based transformer health monitoring"
#define BLYNK_AUTH_TOKEN "sfqroow6k5Xm00uoLdWtoB47CJVB_5KK"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <ESP8266_Lib.h>

// LCD I2C Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ESP-01 (CM05) Software Serial
#define ESP_TX 2  // Connect ESP-01 TX to Arduino Pin 2 (RX)
#define ESP_RX 3  // Connect ESP-01 RX to Arduino Pin 3 (TX, via voltage divider)
SoftwareSerial espSerial(ESP_TX, ESP_RX);

// Blynk Credentials
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";
char auth[] = "YourBlynkAuthToken";

// ESP-01 Setup
ESP8266 wifi(&espSerial);

// Pin Definitions
#define RELAY_PIN 7
#define BUZZER_PIN 8
#define TEMP_SENSOR A1
#define CURRENT_SENSOR A0
#define MOTOR_IN1 5
#define MOTOR_IN2 6
#define MOTOR_PWM 9

// Threshold Values
float tempThreshold1 = 70.0; // Fan at 50% speed
float tempThreshold2 = 80.0; // Fan at 100% speed, Buzzer ON
float maxCurrent = 1.0;      // Load Cut-off at 1.0A

void setup() {
    Serial.begin(115200);
    espSerial.begin(115200); // Communication with ESP-01
    Blynk.begin(auth, wifi, ssid, pass);

    // Initialize LCD
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("System Initializing");
    delay(2000);
    lcd.clear();

    // Pin Modes
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
    pinMode(MOTOR_PWM, OUTPUT);
    
    digitalWrite(RELAY_PIN, HIGH); // Load ON initially
    digitalWrite(BUZZER_PIN, LOW); // Buzzer OFF initially
}

void loop() {
    Blynk.run();
    
    float temp = getTemperature();
    float current = getCurrent();

    // Send Data to Blynk App
    Blynk.virtualWrite(V1, temp);
    Blynk.virtualWrite(V2, current);

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print(current);
    lcd.print(" A");

    // Cooling System Logic
    if (temp >= tempThreshold1 && temp < tempThreshold2) {
        setFanSpeed(50); // 50% Speed
        digitalWrite(BUZZER_PIN, LOW);
    } else if (temp >= tempThreshold2) {
        setFanSpeed(100); // 100% Speed
        digitalWrite(BUZZER_PIN, HIGH);
        Blynk.logEvent("high_temperature", " High Temperature Alert! Cooling at Full Speed!");
    } else {
        stopCooling();
        digitalWrite(BUZZER_PIN, LOW);
    }

    // **Load Cut-Off Logic**
    if (temp >= tempThreshold2 || current > maxCurrent) {
        digitalWrite(RELAY_PIN, LOW); // Turn Off Load
        digitalWrite(BUZZER_PIN, HIGH);
        Blynk.logEvent("load_disconnected", " Load Disconnected! Overcurrent or Overheat Detected!");
    } else {
        digitalWrite(RELAY_PIN, HIGH); // Keep Load On
    }

    delay(1000); // 1-second delay for stable readings
}

// Function to Get Temperature
float getTemperature() {
    int rawValue = analogRead(TEMP_SENSOR);
    return (rawValue * 5.0 / 1024.0) * 100.0; // Convert to °C
}

// Function to Get Load Current
float getCurrent() {
    int rawValue = analogRead(CURRENT_SENSOR);
    float voltage = (rawValue / 1024.0) * 5.0; // Convert to voltage
    float current = (voltage - 2.5) / 0.185;   // ACS712 sensitivity is 185 mV/A
    return current;
}
// Function to Control Cooling System
void setFanSpeed(int speedPercentage) {
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    int speed = map(speedPercentage, 0, 100, 0, 255);
    analogWrite(MOTOR_PWM, speed);
}

// Function to Stop Cooling System
void stopCooling() {
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_PWM, 0);
}
