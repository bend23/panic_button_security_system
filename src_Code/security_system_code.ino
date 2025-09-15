#include <Servo.h>
#include <ezButton.h>

#define TRIG_PIN 2
#define ECHO_PIN 4
#define BUZZER_PIN 13
#define DISTANCE_ 10 //centimeters

float duration, distance_cm;

const int BUTTON_PIN = 3; 
const int dezactivation_PIN = 12;
const int SERVO_PIN = 9;

ezButton button(BUTTON_PIN);
ezButton dezactivationButton(dezactivation_PIN);
Servo servo;

int angle = 0;
bool sensorActive = false;

void setup() {
  //Serial.begin(9600);
  button.setDebounceTime(50);
  dezactivationButton.setDebounceTime(50);
  servo.attach(SERVO_PIN);

  servo.write(angle);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {

  button.loop();
  dezactivationButton.loop();

  if(button.isPressed()){

    if(sensorActive == false && angle == 0){
      sensorActive = !sensorActive;
      angle = 220;
    }
  }
    
  if(dezactivationButton.isPressed()) {
    if(sensorActive){
      sensorActive = false;
      angle = 0;
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  //delay(500);

  servo.write(angle);

  if(sensorActive){
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance_cm = 0.017 * duration;

    if(distance_cm < DISTANCE_){
      digitalWrite(BUZZER_PIN, HIGH);
    }else{
      digitalWrite(BUZZER_PIN, LOW);
    }

    delay(100);
  }
}
