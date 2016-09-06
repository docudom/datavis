#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//button mappings

int button1Pin = 7;
int button2Pin = 8;
int button3Pin = 9;
int button4Pin = 10;
int button5Pin = 11;
int button6Pin = 12;
int button7Pin = 13;

int ledPin = 5;

//                servos - 0...1...2...3...4...5...6...7...8...9...10..11..12..13..14..15
int button1MaxHeights[] = {100,200,200,300,100,300,200,200,200,200,100,200,200,200,200,200};

//                servos - 0...1...2...3...4...5...6...7...8...9...10..11..12..13..14..15
int button2MaxHeights[] = {200,300,100,200,200,200,100,300,300,100,200,200,200,200,200,300};

//                servos - 0...1...2...3...4...5...6...7...8...9...10..11..12..13..14..15
int button3MaxHeights[] = {300,100,100,100,300,100,200,200,200,200,300,200,200,100,200,200};

//                servos - 0...1...2...3...4...5...6...7...8...9...10..11..12..13..14..15
int button4MaxHeights[] = {200,300,100,300,200,300,200,300,300,100,200,200,300,200,100,200};

//                servos - 0...1...2...3...4...5...6...7...8...9...10..11..12..13..14..15
int button5MaxHeights[] = {200,100,100,100,200,200,200,200,200,200,200,200,100,200,200,200};

//                servos - 0...1...2...3...4...5...6...7...8...9...10..11..12..13..14..15
int button6MaxHeights[] = {200,200,300,200,200,200,200,100,100,200,200,200,200,200,100,300};

//                servos - 0...1...2...3...4...5...6...7...8...9...10..11..12..13..14..15
int button7MaxHeights[] = {200,200,200,200,200,200,200,100,100,200,200,200,200,300,100,100};

//used to track what's currently active (the last thing pressed)
int activeButtonNumber = -1;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  200 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  700 // this is the 'maximum' pulse length count (out of 4096)

void setup() 
{
  Serial.begin(9600);  
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pinMode(ledPin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(button5Pin, INPUT_PULLUP);
  pinMode(button6Pin, INPUT_PULLUP);
  pinMode(button7Pin, INPUT_PULLUP);

  for (uint16_t servNum = 0; servNum < 16; servNum++) {

    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(servNum, 0, pulselen);
    }

    delay(100);
  }
}


void loop() {
  //track which button was pressed and which servos to move
  int pressedButton = 0;
  
  //arrays to store the servos that should move for each button
  int button1Servos[] = {0,1,2,3,4,5,10,12};
  int button2Servos[] = {1,2,6,7,8,9,13,14};
  int button3Servos[] = {0,1,2,3,4,5,10,12};
  int button4Servos[] = {1,2,3,5,7,8,9,12,13};
  int button5Servos[] = {0,1,2,3,4,5,10,12};
  int button6Servos[] = {2,3,5,6,7,8,9,13,14,15};
  int button7Servos[] = {6,7,8,9,13,14,15};

  if(digitalRead(button1Pin) == LOW) // Button 1 pressed 
  { 
    digitalWrite(ledPin, HIGH);
    Serial.println("Button 1 pressed");
    pressedButton =  1;
  }
  
  if (digitalRead(button2Pin) == LOW) // Button 2 pressed 
  { 
    digitalWrite(ledPin, LOW);
    Serial.println("Button 2 pressed");
    pressedButton =  2;
  }

  if(digitalRead(button3Pin) == LOW) // Button 1 pressed 
  { 
    digitalWrite(ledPin, HIGH);
    Serial.println("Button 3 pressed");
    pressedButton =  3;
  }
  
  if (digitalRead(button4Pin) == LOW) // Button 2 pressed 
  { 
    digitalWrite(ledPin, LOW);
    Serial.println("Button 4 pressed");
    pressedButton =  4;
  }

  if(digitalRead(button5Pin) == LOW) // Button 1 pressed 
  { 
    digitalWrite(ledPin, HIGH);
    Serial.println("Button 5 pressed");
    pressedButton =  5;
  }
  
  if (digitalRead(button6Pin) == LOW) // Button 2 pressed 
  { 
    digitalWrite(ledPin, LOW);
    Serial.println("Button 6 pressed");
    pressedButton =  6;
  }

  if (digitalRead(button7Pin) == LOW) // Button 2 pressed 
  { 
    digitalWrite(ledPin, LOW);
    Serial.println("Button 7 pressed");
    pressedButton =  7;
  }
  
  if(pressedButton == 0){
    Serial.println("press a button you twat ");
  }
  
  if(pressedButton > 0){
    if(activeButtonNumber != pressedButton){
  
      if(activeButtonNumber == 1){
        MoveServoSetDown(button1Servos, sizeof(button1Servos)/ sizeof(int));
      }
  
      if(activeButtonNumber == 2){
        MoveServoSetDown(button2Servos, sizeof(button2Servos)/ sizeof(int));
      }

      if(activeButtonNumber == 3){
        MoveServoSetDown(button3Servos, sizeof(button3Servos)/ sizeof(int));
      }
  
      if(activeButtonNumber == 4){
        MoveServoSetDown(button4Servos, sizeof(button4Servos)/ sizeof(int));
      }

       if(activeButtonNumber == 5){
        MoveServoSetDown(button5Servos, sizeof(button5Servos)/ sizeof(int));
      }
  
      if(activeButtonNumber == 6){
        MoveServoSetDown(button6Servos, sizeof(button6Servos)/ sizeof(int));
      }
      
      if(activeButtonNumber == 7){
        MoveServoSetDown(button7Servos, sizeof(button7Servos)/ sizeof(int));
      }
    }
  
    if(activeButtonNumber != pressedButton){
  
      if(pressedButton == 1){
        MoveServoSetUp(button1Servos, sizeof(button1Servos)/ sizeof(int),button1MaxHeights);
      }
  
      if(pressedButton == 2){
        MoveServoSetUp(button2Servos, sizeof(button2Servos)/ sizeof(int),button2MaxHeights);
      }

      if(pressedButton == 3){
        MoveServoSetUp(button3Servos, sizeof(button3Servos)/ sizeof(int),button3MaxHeights);
      }
  
      if(pressedButton == 4){
        MoveServoSetUp(button4Servos, sizeof(button4Servos)/ sizeof(int),button4MaxHeights);
      }

      if(pressedButton == 5){
        MoveServoSetUp(button5Servos, sizeof(button5Servos)/ sizeof(int),button5MaxHeights);
      }
  
      if(pressedButton == 6){
        MoveServoSetUp(button6Servos, sizeof(button6Servos)/ sizeof(int),button6MaxHeights);
      }
      
      if(pressedButton == 7){
        MoveServoSetUp(button7Servos, sizeof(button7Servos)/ sizeof(int),button7MaxHeights);
      }
    }

    activeButtonNumber = pressedButton;
  }
}

//function to move a set of servos up
void MoveServoSetUp(int servos[], int length,int maxHeights[]){
  Serial.println("Moving servos up");
  int i;
  //loop through the servos and move them
  for (i = 0; i < length; i++){
    uint8_t servoNumber = servos[i];
    //Serial.println("Moving servos up loop - " + servoNumber);
    Serial.println(servoNumber);
    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > maxHeights[servoNumber]; pulselen--) {
      pwm.setPWM(servos[i], 0, pulselen);
    }
  }
}

//function to move a set of servos down
void MoveServoSetDown(int servos[], int length){
  Serial.println("Moving servos down");
  int i;
  //loop through the servos and move them
  for (i = 0; i < length; i++){
    uint8_t servoNumber = servos[i];
   // Serial.println("Moving servos down loop - " + servoNumber);
    Serial.println(servoNumber);
    delay(500);
    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(servos[i], 0, pulselen);
    }
  }
  
}


//function to move a set of servos up
void MoveServoUp(int servo){
  Serial.println("Moving servos up");
  int i;
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servo, 0, pulselen);
  }
}

//function to move a set of servos down
void MoveServoDown(int servo){
  Serial.println("Moving servos down");
  int i;
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servo, 0, pulselen);
  }
}



