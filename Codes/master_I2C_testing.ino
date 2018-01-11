#include<Wire.h>
int confirmation=0;
int info=10;
void setup() {
Serial.begin(115200);
Serial.println("started");
Wire.begin();
}

void loop() {
Serial.println("in the loop");
Wire.beginTransmission(69);
Serial.println("transmission started");
Wire.write(info);
Serial.println("send");
int x=Wire.endTransmission();
Serial.println(x);
Wire.requestFrom(69,1);
 Serial.println("requesting");
 if(Wire.available()>0)
   {
  confirmation = Wire.read();
   Serial.println("confirmation received");
    Serial.println(confirmation);
   }
if(confirmation>0)
{Serial.println("i just had sex");}
delay(100);
}
