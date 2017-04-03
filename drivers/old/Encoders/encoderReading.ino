
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
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), pulse1, RISING);
  attachInterrupt(digitalPinToInterrupt(3), pulse2, RISING);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
      byte echo = Serial.read();
      
      outBuf.sh = pulseCount1;
      Serial.write(outBuf.buf, 2);
      pulseCount1 = 0;
      
      outBuf.sh = pulseCount2;
      Serial.write(outBuf.buf, 2);
      pulseCount2 = 0;
  }
  
}

void pulse1(){
  if (digitalRead(4)==0)
    pulseCount1++;
  else
    pulseCount1--;
}


void pulse2(){
  if (digitalRead(5)==0)
    pulseCount2--;
  else
    pulseCount2++;
}

