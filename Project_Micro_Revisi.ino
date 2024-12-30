#define BLYNK_TEMPLATE_ID "TMPL6Nu24SeDE"
#define BLYNK_TEMPLATE_NAME "HelloWorld"
//#define BLYNK_AUTH_TOKEN "KfWgaNJngdLvDjS6QtvAmHmjRtH321Dy"

#include <WiFiClient.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>//install
#include <ezButton.h>//install
#include <Button.h>
//#include <DHT.h>

#define LED_PIN 4
#define LED_PIN1 32
#define TRIG_PIN  23  // ESP32 pin GPIO23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN  22  // ESP32 pin GPIO22 connected to Ultrasonic Sensor's ECHO pin
#define TRIG_PIN1 25  // ESP32 pin GPIO23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN1 26  // ESP32 pin GPIO22 connected to Ultrasonic Sensor's ECHO pin
#define SERVO_PIN 21  // ESP32 pin GPIO26 connected to Servo Motor's pin
#define SERVO_PIN1 19  // ESP32 pin GPIO26 connected to Servo Motor's pin
#define DISTANCE_THRESHOLD  5 // centimeters
BlynkTimer timer;

char auth[] = "KfWgaNJngdLvDjS6QtvAmHmjRtH321Dy"; // from BLYNK_AUTH_TOKEN
char ssid[] = "OPPO Reno8 Z 5G";  // Activate your personal hotspot at mobile phone
char pass[] = "k629pbsb";    // Password to access the personal hotspot

//double humidity, temp;
float duration_us, distance_cm, duration_us1, distance_cm1;
// int led_state = LOW;    // the current state of LED
// int button_state;       // the current state of button
// int last_button_state;  // the previous state of button

// int LEDPin = 14;              // LED connected at pin GPIO D5

//unsigned long previousMillis = 0;
//const long interval = 15000;
Servo servo;
Servo servo1;
//ezButton button(BUTTON_PIN);

void maincode(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  
  digitalWrite(TRIG_PIN, HIGH);
  // digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // digitalWrite(TRIG_PIN1, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;
  Blynk.virtualWrite(V0,distance_cm);

  if (distance_cm  < DISTANCE_THRESHOLD){
    servo.write(90); 
    //digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  } else {
    servo.write(0);
    digitalWrite(LED_PIN, LOW);
  }

  digitalWrite(TRIG_PIN1, LOW);
  delayMicroseconds(5);

  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);

  // last_button_state = button_state;      // save the last state
  // button_state = digitalRead(BUTTON_PIN); // read new state

  // duration_us = pulseIn(ECHO_PIN, HIGH);
  duration_us1 = pulseIn(ECHO_PIN1, HIGH);
  // calculate the distance
  // distance_cm = 0.017 * duration_us;
  distance_cm1 = 0.017 * duration_us1;
  Blynk.virtualWrite(V1,distance_cm1);

  if (distance_cm1 < DISTANCE_THRESHOLD){
    servo1.write(90);
    digitalWrite(LED_PIN1, HIGH);
  } else {
    servo1.write(0);
    digitalWrite(LED_PIN1, LOW);
  }
    
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  // pinMode(BUTTON_PIN, INPUT_PULLUP);
  //button.setDebounceTime(50);
  pinMode(TRIG_PIN, OUTPUT); // set ESP32 pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set ESP32 pin to input mode
  pinMode(TRIG_PIN1, OUTPUT); // set ESP32 pin to output mode
  pinMode(ECHO_PIN1, INPUT);  // set ESP32 pin to input mode
  //pinMode(BUZZER_PIN, OUTPUT);
  servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo1.attach(SERVO_PIN1);
  servo.write(0);
  servo1.write(0);
  Serial.begin(115200);      // Serial speed between Computer to ESP32
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);      
  WiFi.begin(ssid, pass);    // Try to login to WiFi(s)

  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);              // Delay switching between WiFi hotspots
    Serial.print(".");
  }
  Serial.println("WiFi connected!");
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  //dht.begin();
  timer.setInterval(1000L, maincode);
}

bool isFirstConnect = true;
BLYNK_CONNECTED(){
  if (isFirstConnect)
  {
    Blynk.syncAll();
    isFirstConnect =false;
  }
}

// BLYNK_WRITE(V1) {
//   int LEDSwitch = param.asInt();   // Connection between physical and virtual pin)
//   digitalWrite(LEDPin, LEDSwitch); // Let the LEDpin equal to LEDSwitch@HelloWord Device 
// }


void loop() {
  Blynk.run();
  timer.run();
}
