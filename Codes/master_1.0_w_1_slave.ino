#include<Wire.h>
int confirmation[2]={0,0};
int recieved_confirmation = 0;
int air=52,ground=20;
int Home=0;
int mSpeed[2]={100,240}; //(groundSpeed,airSpeed)
int flag[2]={0,1};
int botMotion=1;

void setup() {
Serial.begin(115200);
Wire.begin();
}

void loop() {
while(1)
{
 receiveConfirmation();
 if(confirmation[0]==1&&confirmation[1]==1)
   {
    break;
   }
   Serial.print(flag[0]);
Serial.print("\t");
Serial.println(flag[1]);
}
setFlag();
//Serial.println("break");

if (flag[0]==1 && flag[1]==0)
  {
  slaveWrite(ground,air,mSpeed[0],mSpeed[1],botMotion,1);
  }
  
if (flag[0]==0&&flag[1]==1)
  {
  slaveWrite(air,ground,mSpeed[1],mSpeed[0],botMotion,1);
  }
 if (flag[0]==1&&flag[1]==1 || flag[0] == 0 && flag[1] == 0) {
  Serial.println("Both flags 1 or 0, you are fucked!");
 }
}

void receiveConfirmation()
{
 Wire.requestFrom(1,1);
   if(Wire.available()>0)
   {
   recieved_confirmation= Wire.read();
   switch(recieved_confirmation) {
    case 0:
      confirmation[0] =1;
      confirmation[1] =1;
      break;
    case 1:
      confirmation[0] =1;
      confirmation[1] =0;
      break;
    case 2:
      confirmation[0] =0;
      confirmation[1] =1;
      break;
    case 3:
      confirmation[0] =0;
      confirmation[1] =0;
      break;
   }
   Serial.println(recieved_confirmation);
//   Serial.print(confirmation[0]);
//   Serial.print("\t");
//   Serial.println(confirmation[1]);
   }
}

void setFlag()
{
  //Serial.println("set flag");
  if(confirmation[0] == 1) {
    if (flag[0] == 0) {
      flag[0] =1;
    } else {
      flag[0] = 0;
    }
   // Serial.println("changing flag");  
  }
  if(confirmation[1] == 1) {
    if (flag[1] == 0) {
      flag[1] =1;
    } else {
      flag[1] = 0;
    }
   // Serial.println("changing flag");  
  }
}

void slaveWrite(int a,int b,int c,int d,int e,int f)
{
Wire.beginTransmission(f);
Serial.println("slave writing started");
Wire.write(a);
Wire.write(b);
Wire.write(c);
Wire.write(d);
Wire.write(e);
Wire.endTransmission();
Serial.println("slave write done");
}

