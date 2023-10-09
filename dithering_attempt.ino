#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128 // Change this to 96 for 1.27" OLED.

// You can use any (4 or) 5 pins 
// #define MOSI_PIN 2
// #define SCLK_PIN 3
// #define CS_PIN   4
// #define DC_PIN   5
// #define RST_PIN  6


#define MOSI_PIN 11
#define SCLK_PIN 13
#define CS_PIN   10
#define DC_PIN   12
//#define RST_PIN  9

// Color definitions 
#define	BLACK           0x0000
#define WHITE           0xFFFF
#define GREEN           0x1CEA
#define BETTERGREEN     0x3C2A
#define YELLOW          0xF5A7


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

// Option 1: use any pins but a little slower
// Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  

Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN);  



const int numRows = 30;   // Number of rows in the 2D array
const int numCols = 30;   // Number of columns in the 2D array

byte left = 6;
byte down = 6;

byte leftR = 8;
byte downB = 8;



byte myArray[numRows][numCols]; // Declare the 2D array

void setup() {
  // Initialize serial communication at 9600 baud for debugging (optional)
  Serial.begin(9600);
  tft.begin();

  // tft.fillRect(0, 0, 128, 128, BETTERGREEN);
  //  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt  ", YELLOW);

  
  // Seed the random number generator with an analog reading (optional)
  randomSeed(analogRead(0));
  
  // Fill the 2D array with random values (0 or 1)
  // fillArrayWithRandomValues();
  
  // Print the filled array (optional)
 // printArray();
   tft.fillScreen(BLACK);
 fillArrayWithCross();
  erasepixels();
dither();
 drawpixels();


}

void loop() {
//   // Your main code can go here if needed
    // tft.fillScreen(BLACK);
     fillArrayWithCross();
      erasepixels();
  dither();
 drawpixels();
 

}

void fillArrayWithRandomValues() {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      // Generate a random value (either 0 or 1)
      int randomValue = random();
      
      // Store the random value in the 2D array
      myArray[i][j] = randomValue;
    }
  }
}

void fillArrayWithCross() {
  for (int y = 0; y < numRows; y++) {
    for (int x = 0; x < numCols; x++) {
      // Generate a random value (either 0 or 1)
      if(y > 12 && y < 18 && x < 30 || 
         x > 12 && x < 18 && y < 30)
         {
  myArray[x][y] = 3;

         }
      else{  myArray[x][y] = 1;}
    }
  }
}



void printArray() {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      // Print the value at the current position in the array
      Serial.print(myArray[i][j]);
      Serial.print(" ");
    }
    // Move to the next row in the output
    Serial.println();
  }
}

void drawpixels(){

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      // Print the value at the current position in the array
      //     Serial.print(myArray[i][j]);
      // Serial.print(" ");
      if(myArray[i][j]>1){ 
                tft.fillRect(i*4,j *4, -2 , -2, GREEN);
        // tft.drawPixel(i * 4 , j * 4 , WHITE);
        // tft.drawPixel(i * 4-1 , j * 4 , WHITE);
        // tft.drawPixel(i * 4 , j * 4-1 , WHITE);
        // tft.drawPixel(i * 4-1 , j * 4-1 , WHITE);

        //  tft.drawPixel(i * 4-2 , j * 4 , WHITE);
        //   tft.drawPixel(i * 4-2 , j * 4-1 , WHITE);
        //    tft.drawPixel(i * 4-2 , j * 4-2 , WHITE);
        //     tft.drawPixel(i * 4-1 , j * 4-2 , WHITE);
        //      tft.drawPixel(i * 4 , j * 4-2 , WHITE);

             
        //  tft.drawPixel(i * 4-3 , j * 4 , WHITE);
        //   tft.drawPixel(i * 4-3 , j * 4-1 , WHITE);
        //    tft.drawPixel(i * 4-3 , j * 4-2 , WHITE);
        //     tft.drawPixel(i * 4-3 , j * 4-3 , WHITE);
        //      tft.drawPixel(i * 4-2 , j * 4-3 , WHITE);
        //       tft.drawPixel(i * 4-1 , j * 4-3 , WHITE);
        //        tft.drawPixel(i * 4 , j * 4-3 , WHITE);


            //  tft.fillRect(i*4,j *4, i*4 -3 , i*4-3, WHITE);
    

      }
  
    }
 //Serial.println();

  }
 delay(20);
}
void dither() {
   static byte count = 0;
   static byte leftVel = 1;
   static byte downVel = 2;

  for (int i = 0; i < numRows-leftR; i++) {
    for (int j = 0; j < numCols- downB ; j++) {
      // Generate a random value (either 0 or 1)

          if(i> left && j >down){
      byte randomValue = random(4);
 if(randomValue >= myArray[i][j]){

  myArray[i][j] = 0;
 }
 else{  myArray[i][j] = 2; }


    }
  }

  }



 count++;

 if (count  > 5){
  if (leftR <= 0 or left <= 0){

    leftVel = leftVel *-1;
  }
    if (downB <= 0 or down <= 0){

    downVel = downVel *-1;
  }
  count = 0; 
  left = left + leftVel;
  leftR = leftR - leftVel;

  down = down + downVel;
  downB = downB - downVel;
  
  
  }


  Serial.println(count);


}
void erasepixels(){

  for (int i = 0; i  < numRows- leftR +2 ; i++) {
    for (int j = 0; j  < numCols- downB + 2; j++) {
      // Print the value at the current position in the array
      //     Serial.print(myArray[i][j]);
      // Serial.print(" ");
      int x = j;
      int y = i;
      // if(y > 12 && y < 18 && x < 30 || 
      //    x > 12 && x < 18 && y < 30){

      //    }
      // else if(myArray[i][j]>1){ 

       if(i> left -2 && j >down-2 ){

            tft.fillRect(i*4,j *4, -2 , -2, BLACK);
    
    //  tft.drawPixel(i * 4 , j * 4 , BLACK);
    //     tft.drawPixel(i * 4-1 , j * 4 , BLACK);
    //     tft.drawPixel(i * 4 , j * 4-1 , BLACK);
    //     tft.drawPixel(i * 4-1 , j * 4-1 , BLACK);

        //  tft.drawPixel(i * 4-2 , j * 4 , BLACK);
        //   tft.drawPixel(i * 4-2 , j * 4-1 , BLACK);
        //    tft.drawPixel(i * 4-2 , j * 4-2 , BLACK);
        //     tft.drawPixel(i * 4-1 , j * 4-2 , BLACK);
        //      tft.drawPixel(i * 4 , j * 4-2 , BLACK);

             
        //  tft.drawPixel(i * 4-3 , j * 4 , BLACK);
        //   tft.drawPixel(i * 4-3 , j * 4-1 , BLACK);
        //    tft.drawPixel(i * 4-3 , j * 4-2 , BLACK);
        //     tft.drawPixel(i * 4-3 , j * 4-3 , BLACK);
        //      tft.drawPixel(i * 4-2 , j * 4-3 , BLACK);
        //       tft.drawPixel(i * 4-1 , j * 4-3 , BLACK);
        //        tft.drawPixel(i * 4 , j * 4-3 , BLACK);
       }
    
      // }
  
    }
 //Serial.println();
  }

}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0,0);
  tft.setTextColor(color);
  tft.print(text);
}