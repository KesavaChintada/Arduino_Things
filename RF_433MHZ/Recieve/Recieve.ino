int buff = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(1,INPUT);
  Serial.begin(9600);
  DDRB = 0xff;
}

void WritePort(int port){
  PORTB = port;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    buff = Serial.read();
    WritePort(buff);
  }
}
