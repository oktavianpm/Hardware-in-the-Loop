#include <SoftwareSerial.h>
#include <TimerOne.h>

SoftwareSerial mySerial(5, 6);

float input = 0;

String words;

float Kp = 20;
float Kd = 0;
float Ki = 0;
float T = 0.02;
float a = 2 / T;

float currentErr = 0;
float prev1Err = 0;
float prev2Err = 0;

float currentCtrl = 0;
float prev1Ctrl = 0;
float prev2Ctrl = 0;

float prev1Output = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  Timer1.initialize(50000);
  Timer1.attachInterrupt(controller);
}

void loop() {
  if (Serial.available() > 0) {
    words = Serial.readString();
    if (words.indexOf('S') != -1) {
      input = words.toFloat();
    } else if (words.indexOf('P') != -1) {
      Kp = words.toFloat();
    } else if (words.indexOf('I') != -1) {
      Ki = words.toFloat();
    } else if (words.indexOf('D') != -1) {
      Kd = words.toFloat();
    }
  }
  if (mySerial.available() > 0) {
    prev1Output = mySerial.parseFloat(SKIP_ALL, '\n');
    currentErr = input - prev1Output;
  }
}

void controller() {
  //Parameter pengendali P
  if ((Kp != 0) && (Kd == 0) && (Ki == 0)) {
    currentCtrl = Kp * currentErr;
  }
  //Parameter pengendali PI
  else if ((Kp != 0) && (Kd == 0) && (Ki != 0)) {
    currentCtrl = prev1Ctrl + (Kp + Ki / a) * currentErr + (-Kp + Ki / a) * prev1Err;
  }
  //Parameter pengendali PD
  else if ((Kp != 0) && (Kd != 0) && (Ki == 0)) {
    currentCtrl = -1 * prev1Ctrl + (Kp + a * Kd) * currentErr + (Kp - a * Kd) * prev1Err;
  }
  //Parameter pengendali PID
  else if ((Kp != 0) && (Kd != 0) && (Ki != 0)) {
    currentCtrl = ((a * Kp + Ki + pow(a, 2) * Kd) * currentErr + (2 * Ki - 2 * pow(a, 2) * Kd) * prev1Err + (pow(a, 2) * Kd - a * Kp + Ki) * prev2Err + a * prev2Ctrl) / a ;
  }
  
  Serial.println(input);
  mySerial.println(currentCtrl, 5);

  prev2Err = prev1Err;
  prev1Err = currentErr;

  prev2Ctrl = prev1Ctrl;
  prev1Ctrl = currentCtrl;
}
