#include<Wire.h>
int confirmation=1;
int info=0;
void setup() {
 Serial.begin(115200);
 Wire.onReceive(receiveEvent);
// Wire.onRequest(sendConfirmation);
 Wire.begin(70);
}

void loop() {
  Serial.println("running");
  delay(100); 
}

void receiveEvent(int number)
{
  Serial.println("in receive event");
  if(Wire.available()>0)
  { 
    info=Wire.read();
    Serial.println(info);  
  }
}

void sendConfirmation()
{ Serial.println("in send confirmation");
  Wire.write(1);
  Serial.println("having sex");  
}
