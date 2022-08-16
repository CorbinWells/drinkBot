#include <Keypad.h>

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
}
void loop()
{
char key = keypad.getKey();

//dispense coke 
if (key == pass1[currentPostion])
{
currentPostion ++;
}
if (currentPostion == 2) 
{
  digitalWrite (pump1, LOW); //pump 2 on
  delay(10*SECONDS);
  digitalWrite (pump1, HIGH);   // turns off  pump 2
  delay(1*SECONDS);
  currentPostion = 0;
}
//Jack
if (key == pass2[currentPostion])
{
currentPostion ++;
}
if (currentPostion == 2) 
{
  digitalWrite (pump2, LOW); //pump 2 on
  delay(5*SECONDS);
  digitalWrite (pump2, HIGH);   // turns off Curacao pump 2
  delay(1*SECONDS);
  currentPostion = 0;
}

//jack and coke
if (key == pass3[currentPostion])
{
currentPostion ++;
}
if (currentPostion == 2) //This part defines how many digits our code will have.In this case we have 3 digits //(123).
{
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
