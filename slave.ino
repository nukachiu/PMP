#include <Wire.h>
#include <Servo.h>
// Pinii motor 1 stanga
#define mpin00 5
#define mpin01 6
// Pinii motor 2 dreapta
#define mpin10 3
#define mpin11 11
Servo srv;
int x = 0;

void setup() {
 Wire.begin(9);
 Serial.begin(9600);
 Wire.onReceive(receiveEvent);

 // configurarea pinilor motor ca iesire, initial valoare 0
 digitalWrite(mpin00, 0);
 digitalWrite(mpin01, 0);
 digitalWrite(mpin10, 0);
 digitalWrite(mpin11, 0);
 pinMode (mpin00, OUTPUT);
 pinMode (mpin01, OUTPUT);
 pinMode (mpin10, OUTPUT);
 pinMode (mpin11, OUTPUT);
 // pin LED
 pinMode(13, OUTPUT);
}
// Funcție pentru controlul unui motor
// Intrare: pinii m1 și m2, direcția și viteza
void StartMotor (int m1, int m2, int forward, int speed)
{

 if (speed==0) // oprire
 {
 digitalWrite(m1, 0);
 digitalWrite(m2, 0);
 }
 else
 {
 if (forward)
 {
 digitalWrite(m2, 0);

 analogWrite(m1, speed); // folosire PWM
 }
 else
 {
 digitalWrite(m1, 0);
 analogWrite(m2, speed);
 }
 }
}
// Funcție de siguranță
// Execută oprire motoare, urmată de delay
void delayStopped(int ms)
{
 StartMotor (mpin00, mpin01, 0, 0);
 StartMotor (mpin10, mpin11, 0, 0);
 delay(ms);
}
// Utilizare servo
// Poziționare în trei unghiuri
// La final, rămâne în mijloc (90 grade)
void playWithServo(int pin)
{
 srv.attach(pin);
 srv.write(0);
 delay(1000);
 srv.write(180);
 delay(1000);
 srv.write(90);
 delay(1000);
 srv.detach();
}
void receiveEvent(int bytes) {
 x = Wire.read(); // citim un caracter din I2C
}


void loop() {
Serial.print(x);
Serial.print(" ");

if (x == 1)
{//fata
    StartMotor (mpin00, mpin01, 1, 45);
    StartMotor (mpin10, mpin11, 1, 45);
    
    delay (500);
    delayStopped(500);
  
}

else if (x == 2)
{//spate
    StartMotor (mpin00, mpin01, 0, 75);
    StartMotor (mpin10, mpin11, 0, 75);

    delay (500);
    delayStopped(500);  
}

else if (x == 3)
{
  //dreapta fata
 StartMotor (mpin00, mpin01, 1, 50);
   StartMotor (mpin10, mpin11, 0, 50);

   delay (500);
    delayStopped(500);

    StartMotor (mpin00, mpin01, 1, 45);
    StartMotor (mpin10, mpin11, 1, 45);
    
    delay (500);
    delayStopped(500);
}

else if(x == 4)
{
  //lateral stanga fata
   StartMotor (mpin00, mpin01, 0, 50);
   StartMotor (mpin10, mpin11, 1, 50);

   delay (500);
    delayStopped(500);

    StartMotor (mpin00, mpin01, 1, 45);
    StartMotor (mpin10, mpin11, 1, 45);
    
    delay (500);
    delayStopped(500);

}

else if(x == 5)
{
  //lateral dreapta spate
    StartMotor (mpin00, mpin01, 0, 50);
    StartMotor (mpin10, mpin11, 1, 50);

    delay (500);
    delayStopped(500);


     StartMotor (mpin00, mpin01, 0, 75);
    StartMotor (mpin10, mpin11, 0, 75);

    delay (500);
    delayStopped(500);  

}

else if(x == 6)
{
  //lateral stanga spate
   StartMotor (mpin00, mpin01, 1, 50);
    StartMotor (mpin10, mpin11, 0, 50);

    delay (500);
    delayStopped(500);


     StartMotor (mpin00, mpin01, 0, 75);
    StartMotor (mpin10, mpin11, 0, 75);

    delay (500);
    delayStopped(500);  
}
}
