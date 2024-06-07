/*
	Global Solution
    
Sistema de captura de lixo do mar
De acordo com a distância do lixo ao sistema o servo motor abre sua porta e armazena o lixo, fechando novamente depois de 5s.

Materiais usados:
- 2 servo motor;
- 1 sensor de distância (HC-SR04);
- Tela LCD I2C;
- Arduino UNO;
- Breadboard; 
- Fios.

Funcionamento:
- Se aparecer alguma coisa em uma distância de pelo menos 130cm, o sistema irá abrir.
- Após 5s, o sistema fecha novamente. 
- A tela LCD sempre vai mostrar a distância das coisas na frente do sistema. 
*/

//Declarando as bibliotecas utilizadas.
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//Declarando o servo.
Servo servo1, servo2;

//Declarando o tamanho da tela.
LiquidCrystal_I2C lcd(32, 16, 2);

//Declarando as variáveis do sensor de distância.
const int trigPin = 9;
const int echoPin = 10;
double duration; 
int distanceCm;

//Indicando as portas dos servos.
int servoD = 6;
int servoE = 5;


void setup()
{
  //Iniciando os servos, a tela e o sensor de distância.
  servo1.attach(servoD);
  servo2.attach(servoE);
  servo1.write(90);
  servo2.write(90);
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("Sistema ligado");
  lcd.backlight();
  lcd.display();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  //Funcionamento do sensor. 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  //Ajustando a tela para mostrar a distância.
  lcd.setCursor(0,0); 
  lcd.print("Distance: "); 
  lcd.print(distanceCm); 
  lcd.print(" cm");
  delay(10);
  
  //Caso a distância seja menor que 130cm, os servos se ativam e abrem a porta.
  if (distanceCm <= 130) {
  	servo1.write(0);
   	servo2.write(0);
    //Tempo necessário para  objeto adentrar no sistema.
    delay(5000);
    //Fechamento das portas
    servo1.write(90);
    servo2.write(90);
    
    
  } 
  
}
