
#include "ESP32Wiimote.h"
#include <stdlib.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Tone32.h>

ESP32Wiimote wiimote;
String header;
void callback(){
  //degeaba
}

  int nrnr1=0,nrnr2=0; 
const char* ssid = "TEST";
const char* password = "12345678";
#define BUZZER_PIN 5
#define BUZZER_CHANNEL 0
static bool logging = true;
static long last_ms = 0;
//static int num_run = 0, num_updates = 0;
bool ca=false;
int combo1=0;
int combo2=0;
char cc1[2]={'0','0'}, cc2[2]={'0','0'};
bool multiplayer = false;
bool player =true;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
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
  WiFiServer server(80);
void setup()
{
    Serial.begin(115200);
    Serial.println("ESP32Wiimote");
    Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
// Print local IP address and start web server
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
server.begin();
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
WiFiClient client = server.available();
    if (wiimote.available() > 0) 
    {
        ButtonState  button  = wiimote.getButtonState();
        AccelState   accel   = wiimote.getAccelState();
        NunchukState nunchuk = wiimote.getNunchukState();

        if (logging)
        {
            
      
            if(player)if(naxx==255 || naxy==255 || naxz==255 || maxx==255 || maxy==255 || maxz==255){maxx=0; maxy=0; maxz=0;naxx=0; naxy=0; naxz=0;combo1++;wsound(); sprintf(cc1, "%d", combo1);}
            if(!player)if(naxx==255 || naxy==255 || naxz==255 || maxx==255 || maxy==255 || maxz==255){maxx=0; maxy=0; maxz=0;naxx=0; naxy=0; naxz=0;combo2++;wsound(); sprintf(cc2, "%d", combo2);}
            //resetare valori, auto
             if(ca!=(button & BUTTON_C)){Serial.print(" c "); maxx=0; maxy=0; maxz=0; naxx=0; naxy=0; naxz=0;combo1=0;combo2=0;}
             if(ca!=(button & BUTTON_PLUS)){multiplayer=true;}
             if(button && BUTTON_TWO && multiplayer){player=false;}
             if(button && BUTTON_ONE && multiplayer){player=true;}
            if(ca!=(button & BUTTON_HOME)){Serial.print(" home ");csound();touchAttachInterrupt( 4, callback, 20);esp_sleep_enable_touchpad_wakeup();esp_deep_sleep_start();}
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
if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
   if(client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            // Web Page Heading
            client.println("<body><h1>ES-Sport</h1>");
            
            //display info p1
            client.println("<p>Player1: " + (String)cc1 + "</p>");
              
            
            // Display info p2  
            client.println("<p>Player2: " + (String)cc2 + "</p>");     
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
    delay(10);
}
