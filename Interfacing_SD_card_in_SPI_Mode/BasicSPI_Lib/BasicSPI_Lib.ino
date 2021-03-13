int MOSI_Idle = 0xFF;
int Dummy_Data = 0x00;
int command[] = {0x40,0x00,0x00,0x00,0x00,0x95}
void setup() {
  // put your setup code here, to run once:
  Serial(9600);
  Serial.begin();

  Synchronize();                      /* Initialize SD into SPI mode*/
  Enable_SPI_Mode();
  GetResponse();
  
}

int GetResponse(){
  bool Status = 0;                    /* Status=0 --> good, else not good*/
  SPI_Configutation();
  PORTB = (0<<2)|(1<<3);            
  SPI_MasterTransmit(0x00);           /*Send dummy buffer for response*/
}

void Enable_SPI_Mode(){
  SPI_Configutation();
  PORTB = (0<<2)|(1<<3);              /* chipselect low*/
  for(int i=0,i<6,i++){
    SPI_MasterTransmit(command[i]);   /*Transmit Command Buffer*/
  }
  PORTB |= (0<<2);                    /*ChipSelect Low*/
}


void Synchronize(){
  int count = 160;
  PORTB = (1<<2)|(1<<3);
  do{
    PORTB = ((bool)count<<5);
    delayMicroseconds(5);
    count--;
  }while(count!=0);
}

void SPI_Configutation(void)
{
/* Set MOSI and SCK output, all others input */
DDRB = (1<<5)|(1<<3);                 /* B5 is SCK,B3 is MOSI*/
/* Enable SPI, Master, set clock rate fck/16 */
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(int cData)
{
/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF)))
;
}

void SPI_MasterEND(void)
{
SPCR = (0<<SPE)|(1<<MSTR)|(1<<SPR0);
}

/*void State_Machine(){
  switch(State){
    case Init:
    SPI_MasterInit();
    
    break;
    case SendCommand:
    case Wait_delay
    case Recieve:
    case end_task:
  }
}*/

void loop() {
  // put your main code here, to run repeatedly:

}
