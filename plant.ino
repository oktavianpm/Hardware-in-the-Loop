#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);

float T = 0.02;
float a = 2/T;

float currentCtrl = 0;
float prev1Ctrl = 0;
float prev2Ctrl = 0;

float currentOutput = 0;
float prev1Output = 0;
float prev2Output = 0;

float sp = 0;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (mySerial.available() > 0) {
    currentCtrl = mySerial.parseFloat(SKIP_ALL, '\n');

    //Persamaan Plant Motor untuk Kendali Posisi
    currentOutput = (2*pow(a,2)-20)/(pow(a,2)+7*a+10)*prev1Output - (pow(a,2)-7*a+10)/(pow(a,2)+7*a+10)*prev2Output + 0.75/(pow(a,2)+7*a+10)*currentCtrl + 1.5/(pow(a,2)+7*a+10)*prev1Ctrl + 0.75/(pow(a,2)+7*a+10)*prev2Ctrl;
    
    mySerial.println(currentOutput, 5);
    Serial.println(currentOutput, 5);
    
    prev2Ctrl = prev1Ctrl;
    prev1Ctrl = currentCtrl;
    
    prev2Output = prev1Output;
    prev1Output = currentOutput;
  }
}#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);

float T = 0.02;
float a = 2/T;

float currentCtrl = 0;
float prev1Ctrl = 0;
float prev2Ctrl = 0;

float currentOutput = 0;
float prev1Output = 0;
float prev2Output = 0;

float sp = 0;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (mySerial.available() > 0) {
    currentCtrl = mySerial.parseFloat(SKIP_ALL, '\n');

    //Persamaan Plant Motor untuk Kendali Posisi
    currentOutput = (2*pow(a,2)-20)/(pow(a,2)+7*a+10)*prev1Output - (pow(a,2)-7*a+10)/(pow(a,2)+7*a+10)*prev2Output + 0.75/(pow(a,2)+7*a+10)*currentCtrl + 1.5/(pow(a,2)+7*a+10)*prev1Ctrl + 0.75/(pow(a,2)+7*a+10)*prev2Ctrl;
    
    mySerial.println(currentOutput, 5);
    Serial.println(currentOutput, 5);
    
    prev2Ctrl = prev1Ctrl;
    prev1Ctrl = currentCtrl;
    
    prev2Output = prev1Output;
    prev1Output = currentOutput;
  }
}
