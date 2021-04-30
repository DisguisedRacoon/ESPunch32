
#include "ESP32Wiimote.h"
#include <stdlib.h>

#include <Tone32.h>
void callback(){
  //degeaba
}
ESP32Wiimote wiimote;
#define BUZZER_PIN 5
#define BUZZER_CHANNEL 0
static bool logging = true;
static long last_ms = 0;
//static int num_run = 0, num_updates = 0;
bool ca=false;
int combo=0;
int maxx=0 , maxy=0 , maxz , naxx=0 , naxy=0 , naxz=0;
void csound(){ tone(BUZZER_PIN, NOTE_B4, 100, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_A4, 100, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_G4, 100, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_F4, 200, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_E4, 300, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_D4, 400, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_C4, 500, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);}
void osound(){tone(BUZZER_PIN, NOTE_C4, 100, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_D4, 100, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_E4, 150, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_F4, 200, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_G4, 200, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_A4, 250, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  tone(BUZZER_PIN, NOTE_B4, 300, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);}
void wsound(){tone(BUZZER_PIN, NOTE_F4, 50, BUZZER_CHANNEL);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  delay(50);}
void setup()
{
    Serial.begin(115200);
    Serial.println("ESP32Wiimote");
    
    wiimote.init();
    if (! logging)
        wiimote.addFilter(ACTION_IGNORE, FILTER_ACCEL); // optional
    
    Serial.println("Started");
    last_ms = millis();
    osound();
}

void loop()
{
    wiimote.task();
   // num_run++;

    if (wiimote.available() > 0) 
    {
        ButtonState  button  = wiimote.getButtonState();
        AccelState   accel   = wiimote.getAccelState();
        NunchukState nunchuk = wiimote.getNunchukState();

        if (logging)
        {
            
      
            if(naxx==255 || naxy==255 || naxz==255 || maxx==211 || maxy==211 || maxz==211){maxx=0; maxy=0; maxz=0;naxx=0; naxy=0; naxz=0;combo++;wsound();}
            //resetare valori, auto
             if(ca!=(button & BUTTON_C)){Serial.print(" c "); maxx=0; maxy=0; maxz=0; naxx=0; naxy=0; naxz=0;}
             
            if(ca!=(button & BUTTON_HOME)){Serial.print(" home ");csound();touchAttachInterrupt(5, callback, 20);esp_sleep_enable_touchpad_wakeup();esp_deep_sleep_start();}
            //inchidere rapida
            if(abs(accel.xAxis)>maxx){maxx=abs(accel.xAxis); Serial.printf(", wiimote.axis: %3d/%3d/%3d", maxx, maxy, maxz);}
            if(abs(accel.yAxis)>maxy){maxy=abs(accel.yAxis); Serial.printf(", wiimote.axis: %3d/%3d/%3d", maxx, maxy, maxz); }
            if(abs(accel.zAxis)>maxz){maxz=abs(accel.zAxis); Serial.printf(", wiimote.axis: %3d/%3d/%3d", maxx, maxy, maxz); }
            if(abs(nunchuk.xAxis)>naxx){naxx=abs(nunchuk.xAxis);Serial.printf(", nunchuk.axis: %3d/%3d/%3d", naxx, naxy, naxz);}
            if(abs(nunchuk.yAxis)>naxy){naxy=abs(nunchuk.yAxis);Serial.printf(", nunchuk.axis: %3d/%3d/%3d", naxx, naxy, naxz); }
            if(abs(nunchuk.zAxis)>naxz){naxz=abs(nunchuk.zAxis);Serial.printf(", nunchuk.axis: %3d/%3d/%3d", naxx, naxy, naxz); }
            //date>>debug
            
        }
    }

    delay(10);
}
