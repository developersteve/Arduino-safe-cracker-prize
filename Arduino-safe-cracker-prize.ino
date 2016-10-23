/*
Safe cracker prize with random number generation

Uses the following hardware, on top of the basic wires and breadboard...

1 Arduino Uno - just about any Arduino will do
2 leds - Green, for when the combination to the safe is selected
1 Servo - for activating a door to get a prize once the combo is found
1 Analogue turner - to dial the combination in 

 */

#include <Servo.h> 

Servo myservo;

int ledPin1 = 7;      // select the pin for the LED1
int ledPin2 = 8;      // select the pin for the LED2
int servPin1 = 10;      // select the pin for the servo
int sensorPin = A0;    // analogue pin for the tuner 

int sensorValue = 0;  //sensorValue

//variance in the combo, otherwise it gets too fiddly trying to get the exact number
int Varin = 40;

//combination, randomly generated
int sVal1 = random(21,500);
int sVal2 = random(500,1000);

//combodone
int yVal1 = 0;
int yVal2 = 0;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
  myservo.attach(servPin1);
}

void loop() {

  if(yVal1 == 0) digitalWrite(ledPin1, HIGH);
  if(yVal2 == 0) digitalWrite(ledPin2, HIGH);
    
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  //see if the value of the turner matches 
  if(yVal1 == 0 && sensorValue >= (sVal1-Varin) && sensorValue <= (sVal1+Varin)){
    digitalWrite(ledPin1, LOW);
    yVal1 = 1;
    Serial.println("yes");    
  }
  else if(yVal2 == 0 && sensorValue >= (sVal2-Varin) && sensorValue <= (sVal2+Varin)){
    yVal2 = ActivLed(ledPin2);      
  }

  // when it matches then run the "you won script"
  if(yVal1 == 1 && yVal2 == 1){
    myservo.write(0);
    delay(15);
    myservo.write(180);
    delay(15);
    myservo.write(0);
    delay(20);

    //blink LEDs
    BlinkLights(250,5);
        
    //reset
    yVal1 = 0;
    yVal2 = 0;

    //reseed
    sVal1 = random(21,500);
    sVal2 = random(500,1000);
  }

  //todo add reset button
  //  if(sensorValue==0){
  //    yVal1 = 0;
  //    yVal2 = 0;
  //  }
  
  delay(2000);
}

int ActivLed(char led){

  digitalWrite(led, LOW);
  Serial.println(led + "yes");  
  return 1;
  
}

int BlinkLights(int paws, int loo){
    
    while(loo>0){
      
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      delay(paws);
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
      delay(paws);
    
      loo = loo -1;
    }
    
}

