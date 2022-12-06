#include <Wire.h>//Include the Wire library to talk I2C
#include <Arduino.h>
#include <AceSorting.h>
#define MCP4725_ADDR 0x60
using ace_sorting::shellSortKnuth;

int search(int arr[], int n, int x) 
{ 
    //Initialize indices for binary search 
    int i, j, index1=0, index2=n-1; 
  
    //Loop until the two indices meet 
    while (index1 <= index2) 
    { 
        //Find the midpoint of the array 
        i = (index1 + index2)/2; 
  
        //If the midpoint value matches the input value, return the index 
        if( arr[i] == x ) 
            return i; 
  
        //If the midpoint value is less than the input value, move the left index forward 
        else if( arr[i] < x ) 
            index1 = i+1; 
  
        //Otherwise move the right index backward 
        else
            index2 = i-1; 
    } 
  
    //If the two indices have crossed each other, compare the absolute values of the left and right indices 
    if (index1 > index2) 
    { 
        //If the absolute value of the left index is less than the absolute value of the right index, return the left index 
        if (abs(arr[index1]-x) < abs(arr[index2]-x)) 
            return index1; 
        
        //Otherwise, return the right index 
        else
            return index2; 
    } 
  
    //If no value is found, return -1 
    return -1; 
}




int c[]  = {0, 580, 580*2, 580*3, 580*4, 580*5, 580*6};
int cs[] = {48, 48 + 580, 48 + 580*2, 48 + 580*3, 48 + 580*4, 48 + 580*5, 48 + 580*6};
int d[]  = {97, 97 + 580, 97 + 580*2, 97 + 580*3, 97 + 580*4, 97 + 580*5, 97 + 580*6};
int ds[] = {145, 145 + 580, 145 + 580*2, 145 + 580*3, 145 + 580*4, 145 + 580*5, 145 + 580*6};
int e[]  = {193, 193 + 580, 193 + 580*2, 193 + 580*3, 193 + 580*4, 193 + 580*5, 193 + 580*6};
int f[]  = {241, 241 + 580, 241 + 580*2, 241 + 580*3, 241 + 580*4, 241 + 580*5, 241 + 580*6};
int fs[] = {290, 290 + 580, 290 + 580*2, 290 + 580*3, 290 + 580*4, 290 + 580*5, 290 + 580*6};
int g[]  = {338, 338 + 580, 338 + 580*2, 338 + 580*3, 338 + 580*4, 338 + 580*5, 338 + 580*6};
int gs[] = {387, 387 + 580, 387 + 580*2, 387 + 580*3, 387 + 580*4, 387 + 580*5, 387 + 580*6};
int a[]  = {435, 435 + 580, 435 + 580*2, 435 + 580*3, 435 + 580*4, 435 + 580*5, 435 + 580*6};
int as[] = {483, 483 + 580, 483 + 580*2, 483 + 580*3, 483 + 580*4, 483 + 580*5, 483 + 580*6};
int b[]  = {532, 532 + 580, 532 + 580*2, 532 + 580*3, 532 + 580*4, 532 + 580*5, 532 + 580*6};

//different lines commented out to test different keys
int all_notes[] = {0, 580, 580*2, 580*3, 580*4, 580*5, 580*6,
48, 48 + 580, 48 + 580*2, 48 + 580*3, 48 + 580*4, 48 + 580*5, 48 + 580*6,
97, 97 + 580, 97 + 580*2, 97 + 580*3, 97 + 580*4, 97 + 580*5, 97 + 580*6,
145, 145 + 580, 145 + 580*2, 145 + 580*3, 145 + 580*4, 145 + 580*5, 145 + 580*6,
193, 193 + 580, 193 + 580*2, 193 + 580*3, 193 + 580*4, 193 + 580*5, 193 + 580*6,
241, 241 + 580, 241 + 580*2, 241 + 580*3, 241 + 580*4, 241 + 580*5, 241 + 580*6,
290, 290 + 580, 290 + 580*2, 290 + 580*3, 290 + 580*4, 290 + 580*5, 290 + 580*6,
338, 338 + 580, 338 + 580*2, 338 + 580*3, 338 + 580*4, 338 + 580*5, 338 + 580*6,
387, 387 + 580, 387 + 580*2, 387 + 580*3, 387 + 580*4, 387 + 580*5, 387 + 580*6,
435, 435 + 580, 435 + 580*2, 435 + 580*3, 435 + 580*4, 435 + 580*5, 435 + 580*6,
483, 483 + 580, 483 + 580*2, 483 + 580*3, 483 + 580*4, 483 + 580*5, 483 + 580*6,
532, 532 + 580, 532 + 580*2, 532 + 580*3, 532 + 580*4, 532 + 580*5, 532 + 580*6};

//If making this into a better product there should be a way to select the notes and maybe using them to calculate
//the minimum distance between notes to reduce unesecary time looking up and sending data.


int number_of_notes = 0;
void setup() {
  number_of_notes = sizeof(all_notes)/sizeof(all_notes[0]);
  shellSortKnuth(all_notes, number_of_notes);
  Wire.begin();
  pinMode(A6, INPUT);
  Serial.begin(9600);
} 
int input1Pin = A6;
float CV1_in = 0;
int CV1_pitch = 0;
int CV1_quantized = 0;
bool first_loop = true;

void loop() {

  CV1_in = analogRead(A6);
  CV1_pitch = (int)(CV1_in*2*1.5);
  //Serial.println(CV1_pitch);
  //Serial.println(CV1_quantized);
  
  //Look up and send a new note if there is a possibility that a note could change.
  if(abs(CV1_pitch - CV1_quantized) > (48/2)){
    Serial.println(CV1_quantized);
    CV1_quantized = search(all_notes, number_of_notes, CV1_pitch);
    Wire.beginTransmission(MCP4725_ADDR);
    Wire.write(64); 
    Wire.write(CV1_quantized >> 4);        // the 8 most significant bits...
    Wire.write((CV1_quantized & 15) << 4); // the 4 least significant bits...
    Wire.endTransmission();
  }
  delay(1);
}
