//Observação: Caso não funcione, colocar o arduíno conectado ao computador

// Ativa biblioteca Dabble custom_settings
#define CUSTOM_SETTINGS

// Inclui apenas o módulo GamePad do Dabble
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

// Definição dos pinos ligados à ponte H / motores
#define INT1 2   // Motor 1  pino 1
#define INT2 3   // Motor 1  pino 2
#define INT3 4   // Motor 2  pino 1
#define INT4 5   // Motor 2  pino 2

void setup()
{
  // Inicializa a comunicação serial
  Serial.begin(250000);

  // Inicializa o Dabble
  // 9600 = baud rate(velocidade transmissão de dados) do Bluetooth
  // 7 = pino RX
  // 6 = pino TX
  Dabble.begin(9600,7,6);  

  // Define os pinos dos motores como saída ( os da ponte H)
  pinMode(INT1,OUTPUT);
  pinMode(INT2,OUTPUT);
  pinMode(INT3,OUTPUT);                                                                    
  pinMode(INT4,OUTPUT);

  // Garante que o robô inicie parado
  Stop();
}

void loop() {

  // Atualiza os dados recebidos do aplicativo Dabble
  Dabble.processInput();          

  // Se o botão "para cima" do GamePad for pressionado
  if(GamePad.isUpPressed())
  {
    forward();   // Move o robô pra frente
  }
  // Se o botão "para baixo" for pressionado
  else if(GamePad.isDownPressed())
  {
    backward();  // Move o robô para trás
  }
  // Se o botão "esquerda" for pressionado
  else if(GamePad.isLeftPressed())
  {
    left();      // Gira o robô pra esquerda
  }
  // Se o botão "direita" for pressionado
  else if(GamePad.isRightPressed())
  {
    right();     // Gira o robô pra direita
  }
  // Se nenhum botão estiver pressionado
  else
  {
    Stop();      // Para o robô
  }
}

// move o robô pra frente
void forward() {
  digitalWrite(INT1,LOW);
  digitalWrite(INT2,HIGH);
  digitalWrite(INT3,HIGH);
  digitalWrite(INT4,LOW);
}

// move o robô pra trás
void backward() {
  digitalWrite(INT1,HIGH);
  digitalWrite(INT2,LOW);
  digitalWrite(INT3,LOW);
  digitalWrite(INT4,HIGH);
}

// gira o robô pra esquerda
void left() {
  digitalWrite(INT1,HIGH);
  digitalWrite(INT2,LOW);
  digitalWrite(INT3,HIGH);
  digitalWrite(INT4,LOW);    
}

// gira o robô pra direita
void right() {
  digitalWrite(INT1,LOW);
  digitalWrite(INT2,HIGH);
  digitalWrite(INT3,LOW);
  digitalWrite(INT4,HIGH);  
}

// para completamente os motores
void Stop() {
  digitalWrite(INT1,LOW);
  digitalWrite(INT2,LOW);
  digitalWrite(INT3,LOW);
  digitalWrite(INT4,LOW);  
}
