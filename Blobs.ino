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
#define RST_PIN  9


// Color definitions
//#define BLACK           0x0000
// #define WHITE           0xFFFF
// #define GREEN           0x1CEA
// #define BETTERGREEN     0x3C2A
// #define YELLOW          0xF5A7


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include <ssd1351.h>


// Option 1: use any pins but a little slower
// Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  


//typedef ssd1351::LowColor Color;
typedef ssd1351::HighColor Color;


// Choose display buffering - NoBuffer or SingleBuffer currently supported
// auto display = ssd1351::SSD1351<Color, ssd1351::NoBuffer, 128, 96>();
auto display = ssd1351::SSD1351<Color, ssd1351::SingleBuffer, 128, 128>(CS_PIN, DC_PIN, RST_PIN, MOSI_PIN, SCLK_PIN);
byte numBlobs = 3;
class Blob {
  public:
    float x, y;
    float r;
    float speedX, speedY;

    Blob() {
      this->x = random(0, 64);
      this->y = random(0, 64);
      this->r = 10;
      this->speedX = random(-1, 1);
      this->speedY = random(-1, 2);
    }

    void update() {
      this->x += this->speedX;
      this->y += this->speedY;

      if (this->x < 0 || this->x > 64) {
        this->speedX *= -1;
      }
      if (this->y < 0 || this->y > 64) {
        this->speedY *= -1;
      }
    }
};





 Color circleColor = ssd1351::RGB(90, 128, 255);
  Color WHITE = ssd1351::RGB(255, 255, 255);
 Color BLACK = ssd1351::RGB(0, 0, 0);




Blob blobs[3];
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

draw();
 display.begin();
 
   display.fillScreen(BLACK);
   for (int i = 0; i < numBlobs; i++) {
    blobs[i] = Blob();
  }
}


void loop() {
     display.fillScreen(BLACK);
   unsigned long before = millis();
  // put your main code here, to run repeatedly:

for (int x = 0; x < 64; x++) {
    for (int y = 0; y < 64; y++) {
      float sum = 0;
      for (int i = 0; i < numBlobs; i++) {
        float xdif = x - blobs[i].x;
        float ydif = y - blobs[i].y;
        float d = sqrt(xdif * xdif + ydif * ydif);
        sum += 10 * blobs[i].r / d;
      }
      //display.drawPixel(x, y, display.ColorHSV(sum, 255, 255));
       //Serial.println("run");
       if(sum>20 && 1>random(2)){
        
        //display.drawPixel(x, y, WHITE);
                  display.drawPixel(y * 2 , x * 2 , WHITE);
                  display.drawPixel(y * 2-1 , x * 2-1 , WHITE);
                  display.drawPixel(y * 2 , x * 2-1 , WHITE);
                  display.drawPixel(y * 2-1 , x * 2 , WHITE);
       }
      
    }
  }
  //display.display();

  for (int i = 0; i < numBlobs; i++) {
    blobs[i].update();
  }
display.updateScreen();
Serial.println(millis() - before);
}

void draw(){
 display.drawPixel(2 , 2 , WHITE);
                  display.drawPixel(2-1 , 2-1 , WHITE);
                  display.drawPixel(2 , 2-1 , WHITE);
                  display.drawPixel(2-1 , 2 , WHITE);

}
