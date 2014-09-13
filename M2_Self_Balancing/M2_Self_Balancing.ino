#include <TextFinder.h>

TextFinder  finder(Serial1);  
const int NUMBER_OF_FIELDS = 3; // how many comma seperated fields we expect                                           
float values[NUMBER_OF_FIELDS];   // array holding values for all the fields
//values[0] = roll
//values[1] = pitch
//values[2] = yaw



void motor_right_direction(int forward_is_0_back_is_1){
  if(forward_is_0_back_is_1 == 0){
     digitalWrite(2, HIGH);
     digitalWrite(3, LOW);
  } else if ( forward_is_0_back_is_1 == 1) {
     digitalWrite(2, LOW);
     digitalWrite(3, HIGH);
  }
}

void motor_left_direction(int forward_is_0_back_is_1){
  if(forward_is_0_back_is_1 == 0){
     digitalWrite(4, LOW);
     digitalWrite(5, HIGH);
  } else if ( forward_is_0_back_is_1 == 1) {
     digitalWrite(4, HIGH);
     digitalWrite(5, LOW);
  }
}

void setup() 
{ 
  Serial.begin(57600); // Initialize serial port to send and receive at 9600 baud
  
  Serial1.begin(57600);  //Serial1 used to received readings from the CJMCU IMU
  
  pinMode(2, OUTPUT);  //Motor2  IN1
  pinMode(3, OUTPUT);  //Motor2  IN2
  pinMode(4, OUTPUT);  //Motor1  IN1
  pinMode(5, OUTPUT);  //Motor1  IN2
  pinMode(6, OUTPUT);  //Motor2  EN2
  pinMode(7, OUTPUT);  //Motor1  EN1
  
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  
  //http://sobisource.com/arduino-mega-pwm-pin-and-frequency-timer-control/
  TCCR4B = (TCCR4B & 0xF8) | 0x02 ; //Pin6,7,8 PWM Hz change to 3.921Hz
} 

void loop()
{
  int fieldIndex = 0;            // the current field being received
  finder.find("#YPR");   
  while(fieldIndex < NUMBER_OF_FIELDS){
    values[fieldIndex++] = finder.getFloat();
  }    
  
  //values[1] = abs( values[1] );
  if(values[1] >= 0) {
    motor_right_direction(0);
    motor_left_direction(0);
  } else {
    motor_right_direction(1);
    motor_left_direction(1);
  }
  
  values[1] = abs(values[1]);
  //analogWrite(4, 130);
  //analogWrite(7, 130);
  analogWrite(6, constrain( map(values[1], 0, 90, 0, 255), 0, 255 ));
  analogWrite(7, constrain( map(values[1], 0, 90, 0, 255), 0, 255 ));
  
  //Serial.println(values[1]);
}


