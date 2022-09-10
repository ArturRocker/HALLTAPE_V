#include <GyverTM1637.h>
#include <AnalogKey.h>
#include <GyverButton.h>

//encoder pins************************
int ENC1 = 3;
int ENC2 = 4;
GButton butt1(2);          //conecting the button to pin D2
GyverTM1637 disp(5, 6);    //conecting the TM1637 (CLK,DIO) 

int Pos = 0; 
int State;    
int LastState;  

const int P = 76;//Perimeter
const int N = 30;//Encoder steps per revelation

float distance = 0; //Distance 

void setup() 
{ 
  //encoder pins setup
  pinMode (ENC2 ,INPUT_PULLUP);
  pinMode (ENC1 ,INPUT_PULLUP);

  //button setup
  butt1.setDebounce(50);        // настройка антидребезга (по умолчанию 80 мс)
  butt1.setTimeout(300);        // настройка таймаута на удержание (по умолчанию 500 мс)
  butt1.setClickTimeout(600);   // настройка таймаута между кликами (по умолчанию 300 мс)
  
  //display setup
  disp.clear();
  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
  disp.clear();
  disp.displayByte(_H, _A, _L, _L);
  delay(1000);
  disp.clear();
  disp.displayByte(_t, _A, _P, _E);
  delay(1000);
  LastState = digitalRead(ENC2);    
} 

void loop() { 
 //if HALLTAPE does not work change swap the ENC2 and ENC1 
  State = digitalRead(ENC2);
   if (State != LastState)
   {     
     if (digitalRead(ENC1) != State) 
     { 
       Pos --;
     }
     else 
     {
       Pos ++;//if tape works the wrong way swap the Pos ++ and Pos -- 
     }
   } 

  //distance calculation 
  distance = (P/N) * Pos ;

  //showing the distance 
  disp.clear();
  disp.displayInt(static_cast<int>(distance)); 
  
  //checking the button
  butt1.tick();
  if (butt1.isPress()) distance = 0;
  //updating the State 
  LastState = State;
 }
