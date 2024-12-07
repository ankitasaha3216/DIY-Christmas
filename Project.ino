/****************************************************************
 This program was written by Ankita Saha and Pragya Singh for the ECE 1100 class's final project.
 The project entails a "DIY Christmas". This includes playing "We Wish You a Merry Christmas" on buzzer,
 an LED lights display, and a Christmas message on an LCD display.
*****************************************************************/
// libraries
#include <LiquidCrystal.h>// include the library code
#define BUZZER_PIN 13 // defining the buzzer to a pin

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2,3,4,5,6,7);

// comfortable delay time
int tim = 400;

// vars for led grouping
int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;
/*********************************************************/
void setup() {

  // in order to switch modes, set up potentiometer
  Serial.begin(9600);

  // set up led groups
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // set up the lcd display
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
}
/*********************************************************/
void loop() {

  int dial = analogRead(A0);
  
  if (dial > 600) {
    lcdDisplay();
  } else if (dial < 600 && dial > 300) {
    lights();
  } else {
    song();
  }
  
  Serial.println(dial);
  delay(1);        // delay in between reads for stability
}

void lcdDisplay() {

  // make arrays for displaying
  char array1[]="Merry Christmas!!         ";  //the string to print on the LCD
  char array2[]="Ho Ho Ho                  ";  //the string to print on the LCD

  lcd.setCursor(15,0);  // set the cursor to column 15, line 0
  for (int p1 = 0; p1 < 26; p1++) {
    lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
    lcd.print(array1[p1]);  // Print a message to the LCD.
    delay(tim);  //wait for 400 ms
  }
  lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
  lcd.setCursor(15,1);  // set the cursor to column 15, line 1
  for (int p2 = 0; p2 < 26; p2++) {
    lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
    lcd.print(array2[p2]);  // Print a message to the LCD.
    delay(tim);  //wait for 400 ms
  }

  lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
}

void lights() {
  digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); // wait for a second
  digitalWrite(led2, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(led3, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  digitalWrite(led3, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); // wait for a second
  digitalWrite(led4, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(led4, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
}

/****/

const float C_4 = 261.63;
const float C_SHARP_4 = 277.18;
const float D_4 = 293.66;
const float D_SHARP_4 = 311.13;
const float E_4 = 329.63;
const float F_4 = 349.23;
const float F_SHARP_4 = 369.99;
const float G_4 = 392;
const float G_SHARP_4 = 415.30;
const float A_4 = 440;
const float A_SHARP_4 = 466.16;
const float B_4 = 493.88;

/****/
void song() {
    
    // we wish you a merry chirstmans
  int melody[] =  {
      C_4, F_4, G_4, F_4, E_4, D_4,
      G_4, A_4, G_4, F_4, E_4, C_4,
      A_4, A_SHARP_4, A_4, G_4, F_4, D_4, 
      C_4, D_4, G_4, E_4, F_4
  };
  int durations[] = {
      4, 4, 4, 4, 4, 2, 
      4, 4, 4, 4, 4, 2, 
      4, 4, 4, 4, 4, 2,
      4, 4, 4, 4, 4
  };

  // check the array sizes for the for loop to work
  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {

    // to calculate note duration, use division
    int duration = 1000 / durations[note];
    // 2 is half note, 4 is quarter, 8 is eighth note
    // play the tone
    tone(BUZZER_PIN, melody[note], duration);

    // use a pause inbetween notes
    int pause = duration * 1.30;
    delay(pause);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
delay(100);
}
