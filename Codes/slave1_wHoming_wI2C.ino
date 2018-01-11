# include<Wire.h>

int ePins[2] = {2,3}; 
int hPins[2] = {A2,A3};
int motor2Pins[2] = {A0,A1}; //Direction pin for left motor
int motor1Pins[2] = {5,6}; //Direction pin for right motor
int pwmPins[2] = {9,10}; //PWM pins for motor 1(left) and motor 2(right)

int count[2] = {0,0};  //Number of ticks to be rotated as instructed by master
int ticks[2] = {0,0}; //Actual encoder count of motor 1(left) and motor 2(right)
int newTicks[2]={0,0},oldTicks[2]={0,0},botMotion=1;
int magState[2] = {0,0};
int confirmation[2] = {1,1}; //0-Both done, 1-motor1done, 2-motor2done 3-none done
int encrypted_confirmation=0;s
int mSpeed[2]={0,0};
int hSpeed=150;

void setup() {
  pinMode(ePins[0],INPUT);
  pinMode(ePins[1],INPUT);
  pinMode(hPins[0],INPUT);
  pinMode(hPins[1],INPUT);
  pinMode(motor1Pins[0],OUTPUT);
  pinMode(motor1Pins[1],OUTPUT);
  pinMode(motor2Pins[0],OUTPUT);
  pinMode(motor2Pins[1],OUTPUT);
  pinMode(pwmPins[0],OUTPUT);
  pinMode(pwmPins[1],OUTPUT);
  
  Serial.begin(115200);
  
  Wire.begin(1);
  Wire.onReceive(receiveInfo);
  Wire.onRequest(sendConfirmation);
  
  homing();
}

void loop() {
  //Routine to check encoder states
  newTicks[0]= digitalRead(ePins[0]);
  newTicks[1]= digitalRead(ePins[1]);
  if (newTicks[0]!= oldTicks[0]) {
    ticks[0]++;
  }
  if (newTicks[1]!= oldTicks[1]) {
    ticks[1]++;
  }
 oldTicks[0] = newTicks[0];  
 oldTicks[1] = newTicks[1];  

 //Routine to check magneotmeter state
 magState[0] = analogRead(hPins[0]);
 magState[1] = analogRead(hPins[1]);
 if (magState[0]<400) {
  ticks[0] = 0;
 }
 if (magState[1]<400) {
  ticks[1] = 0;
 }
 
 if(count[0] != ticks[0] && confirmation[0] == 0) {
  motor1Drive(botMotion,mSpeed[0]);
 }
 else {
  confirmation[0]=1;
  motor1Stop();
  Serial.println("MOTOR 1 STOPPED");
 }
 
 if(count[1] != ticks[1] && confirmation[1] == 0) {
  motor2Drive(botMotion,mSpeed[1]);
 } 
 else {
  confirmation[1]=1;
  motor2Stop();
  Serial.println("MOTOR 2 STOPPED");
 }
// printSensorStats();

}


void sendConfirmation()
{
  if (confirmation[0] == 1 && confirmation[1] == 1) {
    encrypted_confirmation = 0;
  }
  if (confirmation[0] == 1 && confirmation[1] == 0) {
    encrypted_confirmation = 1;
  }
  if (confirmation[0] == 0 && confirmation[1] == 1) {
    encrypted_confirmation = 2;
  }
  if (confirmation[0] == 0 && confirmation[1] == 0) {
    encrypted_confirmation = 3;
  }
 Wire.write(encrypted_confirmation);
Serial.println(encrypted_confirmation);
// Serial.print(confirmation[0]);
// Serial.print("\t");
// Serial.println(confirmation[1]); 
// Serial.println("Confirmation sent succesfully!");
}

void receiveInfo(int num)
{
if(Wire.available()<=5)
  {
    count[0]=Wire.read();
    count[1]=Wire.read();
    mSpeed[0]=Wire.read();
    mSpeed[1]=Wire.read();
    botMotion=Wire.read();
//    Serial.print(count[0]);
//   Serial.print("\t");
//    Serial.print(count[1]);
//    Serial.print("\t");
//    Serial.print(mSpeed[0]);
//    Serial.print("\t");
//    Serial.print(mSpeed[1]);
//    Serial.print("\t");
//    Serial.println(botMotion);
  }
  confirmation[0] = 0;
  confirmation[1] = 0;  
  Serial.println("CONFIRMATIONS SET TO ZERO");
}

void motor1Drive(int x, int y)
{ 
  analogWrite(pwmPins[0],y);
  if(x==1)
  {
  digitalWrite(motor1Pins[0],HIGH);
  digitalWrite(motor1Pins[1],LOW); 
  }
  if(x==2)
  {
  digitalWrite(motor1Pins[0],LOW);
  digitalWrite(motor1Pins[1],HIGH); 
  }
  if(x==3)
  {
  digitalWrite(motor1Pins[0],HIGH);
  digitalWrite(motor1Pins[1],LOW); 
  }
  if(x==4)
  {
  digitalWrite(motor1Pins[0],LOW);
  digitalWrite(motor1Pins[1],HIGH); 
  }
}

void motor2Drive(int x,int y)
{ 
  analogWrite(pwmPins[1],y);
  if(x==1)
  {
  digitalWrite(motor2Pins[0],HIGH);
  digitalWrite(motor2Pins[1],LOW); 
  }
  if(x==2)
  {
  digitalWrite(motor2Pins[0],LOW);
  digitalWrite(motor2Pins[1],HIGH); 
  }
  if(x==3)
  {
  digitalWrite(motor2Pins[0],LOW);
  digitalWrite(motor2Pins[1],HIGH); 
  }
  if(x==4)
  {
  digitalWrite(motor2Pins[0],HIGH);
  digitalWrite(motor2Pins[1],LOW); 
  }
}

void motor1Stop()
{
  digitalWrite(motor1Pins[0],HIGH);
  digitalWrite(motor1Pins[1],HIGH);
  delay(2);
 }
 void motor2Stop()
{
  digitalWrite(motor2Pins[0],HIGH);
  digitalWrite(motor2Pins[1],HIGH);
  delay(2);
 }

void homing()
{
 int hState0= digitalRead(hPins[0]);
 int hState1= digitalRead(hPins[1]);
  while(hState0||hState1)
  {
    Serial.println("homing");
    if(hState0)
      {motor1Drive(1,hSpeed);}
    if(hState1)
      {motor2Drive(1,hSpeed);}
    hState0= digitalRead(hPins[0]);
    hState1= digitalRead(hPins[1]);
  }
  digitalWrite(motor1Pins[0],LOW);
  digitalWrite(motor1Pins[1],HIGH);
  digitalWrite(motor2Pins[0],LOW);
  digitalWrite(motor2Pins[1],HIGH);
  delay(5);
  digitalWrite(motor1Pins[0],HIGH);
  digitalWrite(motor1Pins[1],HIGH);
  digitalWrite(motor2Pins[0],HIGH);
  digitalWrite(motor2Pins[1],HIGH);
  delay(300);
}

void printSensorStats() {
// Serial.println(digitalRead(hPins[0]));
// Serial.println(" ");
// Serial.println(digitalRead(hPins[1]));
// Serial.println(" ");
// Serial.println(newTicks[0]);
// Serial.println(" ");
// Serial.println(newTicks[1]);
// Serial.println(" ");
 Serial.print(ticks[0]);
 Serial.print(" ");
 Serial.print(ticks[1]);
 Serial.print(" ");
Serial.println();
 }
