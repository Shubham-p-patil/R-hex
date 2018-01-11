int hPins[2] = {2,3}; 
int ePins[2] = {A3,A2};
int motor2Pins[2] = {A0,A1}; //Direction pin for left motor
int motor1Pins[2] = {5,6}; //Direction pin for right motor
int pwmPins[2] = {9,10}; //PWM pins for motor 1(left) and motor 2(right)
int count[2] = {0,0};  //Number of ticks to be rotated as instructed by master
int ticks[2] = {0,0}; //Actual encoder count of motor 1(left) and motor 2(right)
int newTicks[2]={0,0},oldTicks[2]={0,0},botMotion=1;
int finalPosition[2]={0,0};
int mSpeed[2]={0,0};
int temp1=20,temp2=52,flag1=0,flag2=1;
int pwmSlow=150,pwmFast=60;
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
  //attachInterrupt(digitalPinToInterrupt(ePins[0]),incrementTick0, FALLING);
  //attachInterrupt(digitalPinToInterrupt(ePins[1]),incrementTick1, FALLING);
  attachInterrupt(digitalPinToInterrupt(hPins[0]),resetTicks1, FALLING);
  attachInterrupt(digitalPinToInterrupt(hPins[1]),resetTicks2, FALLING);
  Serial.begin(115200);

}

void loop() {
  //Serial.print(flag1);
  //Serial.print("  ");
   //Serial.print(flag2);
  //Serial.print("  ");
  Serial.print(ticks[0]);
  Serial.print("  ");
 // Serial.print(digitalRead(hPins[0]));
  //Serial.print(" ");
  //Serial.print(newTicks[0]);
  //Serial.print(" ");
  //Serial.print(digitalRead(hPins[1]));
  //Serial.print(" ");
 // Serial.print(newTicks[1]);
  //Serial.print(" ");
  //Serial.print(ticks[0]);
  //Serial.print(" ");
  Serial.print(ticks[1]);
  Serial.print(" ");
   newTicks[0]= digitalRead(ePins[0]);
   newTicks[1]= digitalRead(ePins[1]);
if (newTicks[0]!= oldTicks[0]) {
    ticks[0]++;
   // Serial.println(newTicks[0]);
    //Serial.print(" ");
  }
if (newTicks[1]!= oldTicks[1]) {
    ticks[1]++;
    //Serial.println(newTicks[1]);
    //Serial.print(" ");
  }
 oldTicks[0] = newTicks[0];  
 oldTicks[1] = newTicks[1]; 

if(flag1==0)
{
  if(temp1!=ticks[0])
  {
    motor1Drive(botMotion,pwmFast);
  }
  else {
    flag1=1;
    motor1Stop();
  }
}
else if(flag1==1){
  if(temp2!=ticks[0]) 
  {
    motor1Drive(botMotion,pwmSlow);
  }
  else {
     flag1=0;
     motor1Stop();
  }




}

if(flag2==0)
{
  if(temp1!=ticks[1])
 {
  motor2Drive(botMotion,pwmSlow);
  }
 else
 {
  flag2=1;
  motor2Stop();   
 }
}
else if (flag2==1){
  if(temp1!=ticks[1])
 {
  motor2Drive(botMotion,pwmFast);
  }
  else
  {
     flag2=0;
   motor2Stop();
    }
  }
  //Serial.println();

Serial.println();
}

void resetTicks1()
{
ticks[0]=0;
//Serial.println("home");
}

void resetTicks2()
{
ticks[1]=0;
//Serial.println("home");
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
  digitalWrite(motor1Pins[0],LOW);
  digitalWrite(motor1Pins[1],HIGH);
  delay(10);
 digitalWrite(motor1Pins[0],HIGH);
  digitalWrite(motor1Pins[1],HIGH);
  delay(200);
 }
 void motor2Stop()
{
  digitalWrite(motor2Pins[0],LOW);
  digitalWrite(motor2Pins[1],HIGH);
 delay(10);
 digitalWrite(motor2Pins[0],HIGH);
  digitalWrite(motor2Pins[1],HIGH);
 delay(200);
 }

