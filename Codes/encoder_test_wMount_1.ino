int en1 = A0;
int en2 = A1;
int newReading1=0,newReading2=0;
int oldReading1=0,oldReading2=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(en1, INPUT);
  pinMode(en2, INPUT);
  Serial.begin(9600);
}

void loop() {
  newReading1 = digitalRead(en1);
//  newReading2 = digitalRead(en2);
  //if (newReading1!= oldReading1) {
    Serial.println(newReading1);
    //Serial.print(" ");
  //}
// if (newReading2 != oldReading2) {
//    Serial.print(newReading2);
//    Serial.print(" ");
//  }
  
  oldReading1 = newReading1;
//  oldReading2 = newReading2;  
  //Serial.println();
  // put your main code here, to run repeatedly:

}
