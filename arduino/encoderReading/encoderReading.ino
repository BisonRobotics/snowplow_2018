volatile short pulseCount1;
volatile short pulseCount2;  
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
     Serial.write(echo);
    if (echo == '!'){
      Serial.write(pulseCount1); //for binary
      //Serial.print(pulseCount1); //for ASCI
      pulseCount1 = 0;
      //Serial.print(",");
      Serial.write(pulseCount2);
      //Serial.Print(pulseCount2);
      pulseCount2 = 0;
      //Serial.print(" \n");
    }
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

