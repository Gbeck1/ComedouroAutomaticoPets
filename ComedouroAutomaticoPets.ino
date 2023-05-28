#include <DS3231.h>
DS3231 rtc(SDA, SCL);
Time T;                                   //Variável para armazenar o horario atual
int Hora_Atual, Min_Atual;                //Variáveis para armazenar a hora e minuto atual para comparação
int Hora_Alimentacao1, Min_Alimentacao1;  //Variáveis do tempo da primeira refeição
int Hora_Alimentacao2, Min_Alimentacao2;  //Variáveis do tempo da segunda refeição
int Contador1, Contador2;                 //Contadores de qual refeição foi realizada;

#include <Servo.h>
Servo Meu_Servo;

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 8, d5 = 7, d6 = 6, d7 = 5;     //Define a pinagem do LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define PinBotao 2
#define PinInc 3
#define PinDec 4

int X=0;

  void setup() {
  rtc.begin();                              //Inicia o módulo RTC
 // rtc.setTime(18, 07, 10);                // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(28, 05, 2023);             // Set the date to January 1st, 2014
  lcd.begin(16, 2);
  Meu_Servo.attach(9);                      //Define pino 2 para atuação do servo

  Hora_Alimentacao1 = 14;                   //Hora da primeira refeição
  Min_Alimentacao1 = 35;                    //Minuto da primeira refeição
  Contador1 = 0;

  Hora_Alimentacao2 = 14;                   //Hora da segunda refeição
  Min_Alimentacao2 = 37;                    //Minuto da segunda refeição
  Contador2 = 0;
  
  pinMode(PinBotao,INPUT_PULLUP);
  pinMode(PinInc,INPUT_PULLUP);
  pinMode(PinDec,INPUT_PULLUP);
  
}

void loop() {
  T = rtc.getTime();           //Variável recebe o horário do módulo
  Hora_Atual = T.hour;         //Armazena a Hora atual na variável
  Min_Atual = T.min;           //Armazena o Minuto atual na variável
  Meu_Servo.write(10);                    //Inicia o servo na posição fechada

  lcd.setCursor(0,0);
  lcd.print("Hora:");
  lcd.print(rtc.getTimeStr());
  lcd.setCursor(13,1);
  lcd.print("X:");
  lcd.setCursor(15,1);
  lcd.print(X);

  if(Hora_Atual == Hora_Alimentacao1 && Min_Atual==Min_Alimentacao1 && Contador1==0){ //Compara o horario atual com o programado como primeira refeição
    Meu_Servo.write(70);
    delay(1000);
    Meu_Servo.write(10);
    Contador1=1;
  }
  
  if(Hora_Atual == Hora_Alimentacao2 && Min_Atual==Min_Alimentacao2 && Contador2==0){ //Compara o horário atual com o programado como segunda refeição
    Meu_Servo.write(70);
    delay(1000);
    Meu_Servo.write(10);
    Contador2=1;
  }
if(X==0){                                                          //Modo X=0 apenas mostra o usuário a próxima refeição que será realizada
  if (Contador1 == 0 || Contador1 == 1 && Contador2 == 1 ){
    
    lcd.setCursor(0,1);
    lcd.print("R1:");
    
    if (Hora_Alimentacao1<10){  //melhor visualização das horas
    lcd.setCursor(3,1);
    lcd.print("0");
    lcd.setCursor(4,1);
    lcd.print(Hora_Alimentacao1);
    lcd.print("h");
    }

    else{
    lcd.print(Hora_Alimentacao1);
    lcd.print("h");
    }

    if (Min_Alimentacao1<10){   //melhor visualização dos minutos
    lcd.setCursor(6,1);
    lcd.print("0");
    lcd.setCursor(7,1);
    lcd.print(Min_Alimentacao1);
    lcd.print("min");
    }

     else{
    lcd.setCursor(6,1);
    lcd.print(Min_Alimentacao1);
    lcd.print("min");
     }

  }

  if (Contador1 == 1 && Contador2 == 0){

    lcd.setCursor(0,1);
    lcd.print("R2:");

      if (Hora_Alimentacao2<10){  //melhor visualização das horas
        lcd.setCursor(3,1);
        lcd.print("0");
        lcd.setCursor(4,1);
        lcd.print(Hora_Alimentacao2);
        lcd.print("h");
      }
      else{
        lcd.print(Hora_Alimentacao2);
        lcd.print("h");
      }
      if (Min_Alimentacao1<10){   //melhor visualização dos minutos
          lcd.setCursor(6,1);
          lcd.print("0");
        lcd.setCursor(7,1);
        lcd.print(Min_Alimentacao2);
          lcd.print("min");
      }
      else{
        lcd.setCursor(6,1);
        lcd.print(Min_Alimentacao2);
        lcd.print("min");
      }
   }
}

   if (Hora_Atual == 0 && Min_Atual == 0){
      Contador1 = 0;
      Contador2 = 0; 
  }
  delay(50);
  
  if (digitalRead(2)==0 && X<6){
      X++;
      delay(50); 
    }
    
    if(X==5){
      X=0;
      delay(50);
    }

  if(X==1){
    lcd.setCursor(0,1);
    lcd.print("R1:");
    if (Hora_Alimentacao1<10){  //melhor visualização das horas
    lcd.setCursor(3,1);
    lcd.print("0");
    lcd.setCursor(4,1);
    lcd.print(Hora_Alimentacao1);
    lcd.print("h");
    }

    else{
      lcd.print(Hora_Alimentacao1);
      lcd.print("h");
    }

    if (Min_Alimentacao1<10){   //melhor visualização dos minutos
      lcd.setCursor(6,1);
      lcd.print("0");
      lcd.setCursor(7,1);
      lcd.print(Min_Alimentacao1);
      lcd.print("min");
    }

     else{
       lcd.setCursor(6,1);
       lcd.print(Min_Alimentacao1);
       lcd.print("min");
     }


    if(digitalRead(3)==0 && Min_Alimentacao1<=60){
      Min_Alimentacao1++;
      delay(50);
    }

    if (Min_Alimentacao1==60){
      Min_Alimentacao1=0;
      delay(50); 
    }

    if(digitalRead(4)==0 && Min_Alimentacao1>=0){
      Min_Alimentacao1--;
      delay(50);
    }
    if (Min_Alimentacao1==-1){
      Min_Alimentacao1=59;
      delay(50); 
    }
  }

  if(X==2){
    lcd.setCursor(0,1);
    lcd.print("R1:");
    if (Hora_Alimentacao1<10){  //melhor visualização das horas
    lcd.setCursor(3,1);
    lcd.print("0");
    lcd.setCursor(4,1);
    lcd.print(Hora_Alimentacao1);
    lcd.print("h");
    }

    else{
      lcd.print(Hora_Alimentacao1);
      lcd.print("h");
    }

    if (Min_Alimentacao1<10){   //melhor visualização dos minutos
      lcd.setCursor(6,1);
      lcd.print("0");
      lcd.setCursor(7,1);
      lcd.print(Min_Alimentacao1);
      lcd.print("min");
    }

     else{
       lcd.setCursor(6,1);
       lcd.print(Min_Alimentacao1);
       lcd.print("min");
     }
    if(digitalRead(3)==0 && Hora_Alimentacao1<=24){
      Hora_Alimentacao1++;
      delay(50);
    }

    if (Hora_Alimentacao1==24){
      Hora_Alimentacao1=0;
      delay(50); 
    }

   

    if(digitalRead(4)==0 && Hora_Alimentacao1>=0){
      Hora_Alimentacao1--;
      delay(50);
    }

    if (Hora_Alimentacao1==-1){
      Hora_Alimentacao1=23;
      delay(50); 
    }
   

  }

  if(X==3){
    lcd.setCursor(0,1);
    lcd.print("R2:");

      if (Hora_Alimentacao2<10){  //melhor visualização das horas
        lcd.setCursor(3,1);
        lcd.print("0");
        lcd.setCursor(4,1);
        lcd.print(Hora_Alimentacao2);
        lcd.print("h");
      }
      else{
        lcd.print(Hora_Alimentacao2);
        lcd.print("h");
      }
      if (Min_Alimentacao2<10){   //melhor visualização dos minutos
          lcd.setCursor(6,1);
          lcd.print("0");
        lcd.setCursor(7,1);
        lcd.print(Min_Alimentacao2);
          lcd.print("min");
      }
      else{
        lcd.setCursor(6,1);
        lcd.print(Min_Alimentacao2);
        lcd.print("min");
      }
    if(digitalRead(3)==0 && Min_Alimentacao2<=60){
      Min_Alimentacao2++;
      delay(50);
    }

    if (Min_Alimentacao2==60){
      Min_Alimentacao2=0;
      delay(50); 
    }

    if(digitalRead(4)==0 && Min_Alimentacao2>=0){
      Min_Alimentacao2--;
      delay(50);
    }

    if (Min_Alimentacao2==-1){
      Min_Alimentacao2=59;
      delay(50); 
    }

  }
  if(X==4){
    lcd.setCursor(0,1);
    lcd.print("R2:");

      if (Hora_Alimentacao2<10){  //melhor visualização das horas
        lcd.setCursor(3,1);
        lcd.print("0");
        lcd.setCursor(4,1);
        lcd.print(Hora_Alimentacao2);
        lcd.print("h");
      }
      else{
        lcd.print(Hora_Alimentacao2);
        lcd.print("h");
      }
      if (Min_Alimentacao1<10){   //melhor visualização dos minutos
          lcd.setCursor(6,1);
          lcd.print("0");
        lcd.setCursor(7,1);
        lcd.print(Min_Alimentacao2);
          lcd.print("min");
      }
      else{
        lcd.setCursor(6,1);
        lcd.print(Min_Alimentacao2);
        lcd.print("min");
      }
    if(digitalRead(3)==0 && Hora_Alimentacao2<=24){
      Hora_Alimentacao2++;
      delay(50);
    }
    if (Hora_Alimentacao2==24){
      Hora_Alimentacao2=0;
      delay(50); 
    }

    if(digitalRead(4)==0 && Hora_Alimentacao2>=0){
      Hora_Alimentacao2--;
      delay(50);
    }
    if (Hora_Alimentacao2==-1){
      Hora_Alimentacao2=23;
      delay(50); 
    }

    }
    delay(50);
  }







