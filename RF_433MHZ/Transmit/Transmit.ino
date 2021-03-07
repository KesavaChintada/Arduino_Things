int data = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(D0,OUTPUT);
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(data>=10){
    data = 0;
  }
  else{
  Serial.write(++data);
  }
  delay(1000);
}
