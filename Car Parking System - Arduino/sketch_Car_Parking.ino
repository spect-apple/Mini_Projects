//MCI mini project
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //Change the HEX address
#include <Servo.h> 

Servo myservo1;

int IR1 = 2;
int IR2 = 4;

int Slot = 4;           //Enter Total number of parking Slots

int flag1 = 0;
int flag2 = 0;

void setup() {
  lcd.init();
  lcd.backlight();
pinMode(IR1, INPUT);
pinMode(IR2, INPUT);
  
myservo1.attach(3);
myservo1.write(100);

lcd.setCursor (0,0);
lcd.print("     ARDUINO    ");
lcd.setCursor (0,1);
lcd.print(" PARKING SYSTEM ");
delay (2000);
lcd.clear();  
}
void loop()
{
  if(digitalRead(IR1)==LOW && flag1==0 && flag2==0)
  { 
    if(Slot>0){
      myservo1.write(0); flag1=1;
      while(flag1==1 && flag2==0)
      {
        if(digitalRead(IR2)==LOW)
        {
          flag2=1;
          while(flag1==1 && flag2==1)
          {
            if(digitalRead(IR1)==HIGH){while(digitalRead(IR1)==HIGH){if(digitalRead(IR2)==HIGH)
            {
              Slot=Slot-1;
              flag1=2;
              flag2=2;
              break;              
            }}}
            else if(digitalRead(IR2)==HIGH){while(digitalRead(IR2)==HIGH){if(digitalRead(IR1)==HIGH)
            {
              flag1=0;
              flag2=0;
              break;
            }}}
          }        
        }
        else if(digitalRead(IR1)==HIGH){flag1=0;}
      }}
      else{
        lcd.setCursor (0,0);
        lcd.print("    SORRY :(    ");  
        lcd.setCursor (0,1);
        lcd.print("  Parking Full  "); 
        delay (3000);
        lcd.clear(); 
      }
  }
  if(digitalRead(IR2)==LOW && flag1==0 && flag2==0 && Slot<4)
  { 
    flag2=1;
    myservo1.write(0);
    while(flag1==0 && flag2==1)
    {
      if(digitalRead(IR1)==LOW)
      {
        flag1=1;
        while(flag1==1 && flag2==1)
        {
          if(digitalRead(IR2)==HIGH){while(digitalRead(IR2)==HIGH){if (digitalRead(IR1)==HIGH)
          {
            Slot=Slot+1;
            flag1=2;
            flag2=2;
            break;
          }}}
          else if(digitalRead(IR1)==HIGH){while(digitalRead(IR1)==HIGH){if(digitalRead(IR2)==HIGH)
          {
            flag1=0;
            flag2=0;
            break;
          }}}
        }
      }
      else if(digitalRead(IR2)==HIGH){flag2=0;}
    }

  }

  if(flag1==0 && flag2==0)
  {
    delay (1000);
    myservo1.write(100);
    flag1=0; flag2=0;
  }
  if(flag1==2 && flag2==2)
  {
    delay (1000);
    myservo1.write(100);
    flag1=0; flag2=0;
  }

  lcd.setCursor (0,0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor (0,1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);

}