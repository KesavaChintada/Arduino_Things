int eePromWriteOnlyConfig = 0x00;
int eePromRead_EN = 0x01;
int eePromMasterWrite_EN = 0x04;
int eePromWrite_EN = 0x02;
unsigned int Count_Data_Address = 0x0001;
int Count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Lets start");

  Count = Read_eeProm(Count_Data_Address);
  Serial.print("the Data in EEPROM is:");
  Serial.print(Count);
  Serial.println("the new value:");
    EECR |= eePromWriteOnlyConfig;
  
}


int Read_eeProm(unsigned int Address){
  while((EECR) & (eePromWrite_EN));
  EEAR = Address;
  EECR|= eePromRead_EN;
  return EEDR; 
}


void Write_eeProm(unsigned int Address,int Data){
   while((EECR & eePromWrite_EN)&&(SPMCSR & (1<<SELFPRGEN))){
    //wait for the MasterWrite bit to clear i.e finish the previous write operation.
  }
  EEAR = Address ;
  EEDR = Data;
  
  EECR |= eePromMasterWrite_EN;
  EECR |= eePromWrite_EN;
}


void loop() {
  // put your main code here, to run repeatedly:
 Serial.println(Read_eeProm(Count_Data_Address));
 Count++;
 Write_eeProm(Count_Data_Address,Count);
 Serial.println(Count);
 
 delay(1000);
}
