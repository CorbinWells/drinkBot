#include <Keypad.h>

int blue = A0;
int red = A1;
int green = A2;

#define echo 9 // Echo Pin
#define trig 10 // Trigger Pin
long travel_time, distance; // Duration used to calculate distance

char* pass1 = "13"; //coke 
char* pass2 = "14"; //jack
char* pass3 = "16"; //jack and coke
int currentPostion = 0;

int pump1= 11; //coke pump
int pump2= 12; //jack pump

const unsigned long SECONDS = 1000;
const unsigned long MINUTES = SECONDS * 60;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  pinMode(pump1,OUTPUT);
  digitalWrite (pump1, HIGH); 
  
  pinMode(pump2,OUTPUT);
  digitalWrite (pump2, HIGH); 

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(trig, OUTPUT); //set the trigpin to output
  pinMode(echo, INPUT); //Set th echo pin to output
}
void loop()
{
char key = keypad.getKey();

digitalWrite(trig, LOW); 
delayMicroseconds(2); 
//Sending a high pulse to trigger the Ultrasound Module
digitalWrite(trig, HIGH);
delayMicroseconds(10); 
digitalWrite(trig, LOW);
travel_time = pulseIn(echo, HIGH);
//Calculating the distance
distance = (travel_time*0.034)/2;
// Sending the distance to computer 
Serial.println(distance);
//Delay for next reading.
delay(30);
  if (distance > 13){
  digitalWrite (red, HIGH);
  digitalWrite (green, HIGH);
  digitalWrite (blue, HIGH);
  }
  else if (distance < 13){
  digitalWrite (red, LOW);
  digitalWrite (green, HIGH);
  digitalWrite (blue, LOW);
  }
//dispense coke 
if (key == pass1[currentPostion] && distance < 13)
{
currentPostion ++;
}
if (currentPostion == 2) 
{
  digitalWrite (green, LOW);
  digitalWrite (blue, LOW);
  digitalWrite (red, HIGH);
  digitalWrite (pump1, LOW); //pump 2 on
  delay(10*SECONDS);
  digitalWrite (pump1, HIGH);   // turns off  pump 2
  delay(1*SECONDS);
  currentPostion = 0;
}
//Jack
if (key == pass2[currentPostion] && distance < 13)
{
currentPostion ++;
}
if (currentPostion == 2) 
{
  digitalWrite (green, LOW);
  digitalWrite (blue, LOW);
  digitalWrite (red, HIGH);
  digitalWrite (pump2, LOW); //pump 2 on
  delay(5*SECONDS);
  digitalWrite (pump2, HIGH);   // turns off Curacao pump 2
  delay(1*SECONDS);
  currentPostion = 0;
}

//jack and coke
if (key == pass3[currentPostion] && distance < 13)
{
currentPostion ++;
}
if (currentPostion == 2) //This part defines how many digits our code will have.In this case we have 3 digits //(123).
{
  digitalWrite (green, LOW);
  digitalWrite (blue, LOW);
  digitalWrite (red, HIGH);
  digitalWrite (pump1, LOW); 
  digitalWrite (pump2, LOW); 
  delay(5*SECONDS);
  digitalWrite (pump2, HIGH);   
  delay(5*SECONDS);
  digitalWrite (pump1, HIGH); 
  delay(1*SECONDS);
  currentPostion = 0;
}
}
