
int16_t pulseCount1;
int16_t pulseCount2;  

union int16union {
  int16_t sh;
  byte buf[2];
};

int16union outBuf;

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
 // pinMode(3,INPUT);
  pinMode(4,INPUT);
 // pinMode(5,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), pulse1, RISING);
//  attachInterrupt(digitalPinToInterrupt(3), pulse2, RISING);
  
}

void loop() {
  /*
  Serial.println(digitalRead(2));
  Serial.println(digitalRead(4));
  Serial.println("\n");
  */
    //Serial.println(Serial.available());
  if (Serial.available() > 0){
      Serial.println("test");
      byte echo = Serial.read();
      //int8_t sample[2] = {'#', '#'};
      //outBuf.sh = pulseCount1;
      //Serial.write((char*)sample, 2);
      //Serial.write(outBuf.buf, 2);
      Serial.println(pulseCount1);
      pulseCount1 = 0;
   /*   
      outBuf.sh = pulseCount2;
      Serial.write(outBuf.buf, 2);
      pulseCount2 = 0;
  */
  }  
}

void pulse1(){
  //Serial.print("I'M WORKING (pulse1)");
  if (digitalRead(4)==0)
    pulseCount1++;
  else
    pulseCount1--;
}
/*
void pulse2(){
  if (digitalRead(5)==0)
    pulseCount2--;
  else
    pulseCount2++;
}
*/
