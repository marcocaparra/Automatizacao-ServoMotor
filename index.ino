// Inclusão das bibliotecas
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//LCD 16x2 I2C
LiquidCrystal_I2C lcd(0x20, 16, 2); 

//Servos 
Servo servo1;
Servo servo2;

//Pinos
const int botaoSelecionaServo = 6;
const int botaoMudaAngulo = 7;
const int pinoServo1 = 3;
const int pinoServo2 = 5;

// Estado
int ServoAtual = 1;
int angulos[] = {0, 90, 180}; //angulos[0] = 0, angulos[1] = 90, angulos[2] = 180
               //0,  1,   2
int anguloAtual1 = 1;
int anguloAtual2 = 1;

// Controle de botão
bool botao1Anterior = LOW;
bool botao2Anterior = LOW;


void setup(){
lcd.init();
lcd.backlight();
  
pinMode(botaoSelecionaServo, INPUT);
pinMode(botaoMudaAngulo, INPUT);
  
servo1.attach(pinoServo1);
servo2.attach(pinoServo2);
  
atualizarLCD();
}

void loop(){
  bool botao1 = digitalRead(botaoSelecionaServo);
  bool botao2 = digitalRead(botaoMudaAngulo);
  
  if (botao1 == HIGH && botao1Anterior == LOW){
    ServoAtual = (ServoAtual == 1) ? 2 : 1;
    atualizarLCD();
    delay(200);
  }
  
  if (botao2 == HIGH && botao2Anterior == LOW){
    if (ServoAtual == 1){
    	anguloAtual1 = (anguloAtual1 + 1) % 3;
      	servo1.write(angulos[anguloAtual1]);
    } else {
		anguloAtual2 = (anguloAtual2 + 1) % 3;
      	servo2.write(angulos[anguloAtual2]);
    }
    atualizarLCD();
    delay(200);
  }
    botao1Anterior = botao1;
    botao2Anterior = botao2;
}

void atualizarLCD(){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Servo: ");
lcd.print(ServoAtual);
lcd.setCursor(0,1);
lcd.print("Angulo: ");
  if (ServoAtual == 1){
   lcd.print(angulos[anguloAtual1]); 
  } else {
  lcd.print(angulos[anguloAtual2]);
  } 
}
