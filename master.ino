#include <Wire.h>

int scale = 3;


void setup()
{
// Initialize serial communication at 115200 baud
Serial.begin(9600);
Wire.begin(); 
}

void loop()
{
// Get raw accelerometer data for each axis
int x = analogRead(A0);
int y = analogRead(A1);
int z = analogRead(A2);

String dirFataSpate = "";
String dirStDr = "";

int fata;
int dreapta;
int directie; // 0 - stop, 1 - fata, 2 - spate, 3 - fata dreapta, 4 - fata stanga, 5 - spate dreapta, 6 - spate stanga

//int xOk = ((float)x - 331.5)/65*9.8;
//int yOk = ((float)y - 329.5)/68.5*9.8;
//int zOk =((float)z - 340)/68*9.8;

int xOk = x % 255;
int yOk = y % 255;
int zOk = z % 255;


Serial.print("x:");
Serial.print(xOk); //print x value on serial monitor
Serial.print("\t");
Serial.print("y:");
Serial.print(yOk); //print y value on serial monitor
Serial.print("\t");
Serial.print("z:");
Serial.print(zOk); //print z value on serial monitor
Serial.print("\n");

if(yOk > 100){
dirFataSpate = "Fata";
fata = 1;
}
else if(yOk < 45){
dirFataSpate = "Spate";
fata = -1;
}
else
{
dirFataSpate = "Stop";
fata = 0;
}

if(xOk > 100){
dirStDr = "Dreapta";
dreapta = 1;
}
else if(xOk < 50){
dirStDr = "Stanga";
dreapta = -1;
}
else
{
dirStDr = "Stop";
dreapta = 0;
}

if(fata == 1){
        if(dreapta == 1){
          directie = 3;
        }
        else if(dreapta == -1){
          directie = 4;
        }
        else{
          directie = 1;
        }
      }
else if(fata == -1){
      if(dreapta == 1){
          directie = 5;
        }
        else if(dreapta == -1){
          directie = 6;
        }
        else{
          directie = 2;
        }
}
Serial.print(fata);
Serial.print('\t');
Serial.print(dreapta);
Serial.print('\n');
Serial.print('\n');
Serial.print(directie);
Serial.print('\n');
Serial.print('\n');

Wire.beginTransmission(9);
Wire.write(directie);
Wire.endTransmission();

delay(500);
}
