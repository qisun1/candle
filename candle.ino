#include <tinyNeoPixel.h>
#include <avr/sleep.h>
#define LED_PIN 0
#define MICROPHONE_PIN 1
#define POWERSWITCH_PIN 2
#define TILT_PIN 3
#define IDLE_PIN 4

#define INIT_R 1000
#define INIT_G 0
#define INIT_B 0


#define autoOffTime 180000 // auto turn off after this milliseconds, 3 min= 180000

tinyNeoPixel pixels = tinyNeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);
bool turnOffFlag=true;
unsigned long wakeupTime;

int LED_R = INIT_R;
int LED_G = INIT_G;
int LED_B = INIT_B;
bool range2 = false;

void setup() {
 set_sleep_mode(SLEEP_MODE_PWR_DOWN);
 sleep_enable();
  pinMode(TILT_PIN, INPUT_PULLUP);

  pinMode(LED_PIN, OUTPUT);
  
  pinMode(IDLE_PIN, OUTPUT);
  digitalWrite(IDLE_PIN, LOW);


  pixels.begin();
}



ISR(PORTA_PORT_vect) {
  PORTA.INTFLAGS = PORT_INT2_bm;
  PORTA.PIN2CTRL = PORT_PULLUPEN_bm;
  wakeupTime = millis();
  turnOffFlag=false;
  
  pinMode(POWERSWITCH_PIN, OUTPUT);
  digitalWrite(POWERSWITCH_PIN, LOW);
  pinMode(MICROPHONE_PIN, INPUT);
      LED_R = INIT_R;
      LED_G = INIT_G;
      LED_B = INIT_B;   
  pixels.setPixelColor(0, pixels.Color(LED_G/10, LED_R/10, LED_B/10)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void loop() {
  unsigned long  currentTime = millis();
  if ((turnOffFlag) || ((currentTime-wakeupTime )>autoOffTime)){

    PORTA.PIN2CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc; //  Trigger on falling edge
    pinMode(MICROPHONE_PIN, OUTPUT);
    digitalWrite(MICROPHONE_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    pinMode(POWERSWITCH_PIN, INPUT_PULLUP);
    sleep_cpu();
  }

    delay(50);
    int val = analogRead(MICROPHONE_PIN);  // read the input pin
    if (val >700)
    {
      turnOffFlag = true;
    }

   if (digitalRead(TILT_PIN) == LOW) {
    LED_R += 10;
    LED_G += 15;
    LED_B += 10;
    if (LED_R >= 2550)
    {
      LED_R = 2550;
    }
    if (LED_G >= 2550)
    {
      LED_G = 2550;
    }
    if (LED_B >= 2550)
    {
      LED_B = 2550;
    }

    if ((LED_R>=2550) && (LED_G>=2550) && (LED_B>=2550))
    {
      LED_R = INIT_R;
      LED_G = INIT_G;
      LED_B = INIT_B;   
    }
    
    pixels.setPixelColor(0, pixels.Color(LED_G/10, LED_R/10, LED_B/10)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
   }
}
