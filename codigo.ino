//Inclui a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
#include <DHT.h>

//Define o pino e o tipo do DHT
#define DHTPIN 9
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/*DECLARANDO AS VARIAVEIS E PINOS TANTO DIGITAIS COMO ANALÓGICOS*/

//VARIAVEIS PARA CONTROLE DE TEMPO
unsigned long previousMillis = 0;
const long interval = 5000; // INTERVALO DE 5 S
const long intervalfogo = 100;

//PINOS A0 E DIGITAIS (DE 13 A 10 E DE 7 A 2)
int ldr = A0; //SENSOR (PINO ANALÓGICO 0)
int ledVerde = 13; //LED VERDE (PINO DIGITAL 13)
int ledAmarelo = 12; //LED AMARELO (PINO DIGITAL 12)
int ledVermelho = 11;//LED VERMELHO (PINO DIGITAL 11)
int buzzer = 10; //BUZZER (PINO DIGITAL 10)
/*Os pinos referentes a (RS, E, D4, D5, D6, D7)
  são passados para o construtor na ordem dada.*/
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


int vldr = 0; //VALOR INICIAL DA LUMINOSIDADE
int LuminosidadeLED; // DEFINE A VARIAVEL DE LUMINOSIDADE PARA MAPEAR
int mediaMovelLuminosidade[10]; // ARRAY DA MÉDIA MOVEL DA LUZ
int mediaMovelUmidade[10]; // ARRAY DA MÉDIA MOVEL DA UMIDADE
int mediaMovelTemperatura[10]; // ARRAY DA MÉDIA MOVEL DA TEMPERATURA
int contagemLeituras = 0; // CONTADOR DE LEITURAS


//VARIAVEIS PARA ARMAZENAR DADOS DE LEITURA
float umidade;
float temperatura;


byte fogo1[] = { B00000, B00100, B00100, B00110, B00111, B00111, B01101, B11001 };
byte fogo2[] = { B01000, B01100, B01010, B01010, B01010, B11011, B10011, B10011 };
byte fogo3[] = { B10000, B10000, B10000, B10100, B10110, B10110, B11001, B11001 };
byte fogo4[] = { B00000, B01000, B01000, B01100, B01100, B01110, B01011, B11001 };
byte lanterna[] = { B00000, B01110, B11111, B11011, B11011, B11111, B01110, B00100 };
byte gota[] = { B00000, B00100, B00100, B01110, B11111, B11111, B11111, B01110 };




void setup() {
  pinMode(ldr, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);//COMEÇA O SERIAL COM A VELOCIDADE DE 9600


  //INICIALIZA O SERIAL MONITOR
  lcd.begin(16, 2);


  //INICIALIZA O SENSOR DHT22
  dht.begin();


  delay(1000);
  // ARRAYS DE FREQUÊNCIA E DE DELAY PARA O SOM DE MARIO
  int frequencies[] = {2637, 2637, 2637, 2093, 2637, 3136, 1568};
  int songdelay[] = {100, 100, 200, 200, 100, 200, 320};

  // TOCA O SOM DE INTRODUÇÃO DO MARIO
  for (int i = 0; i < 7; i++) {
    delay(songdelay[i]);
    tone(buzzer, frequencies[i]);
    delay(80); //DURAÇÃO DE CADA BEEP
    noTone(buzzer);
  }



  //INICIALIZA A ANIMAÇÃO DO DISPLAY
  Introdisplay();

  //ESCREVE O LOGO QUE DURA MOMENTÂNEAMENTE
  lcd.setCursor(6, 0);
  lcd.print("Mind");
  lcd.setCursor(6, 1);
  lcd.print("Sync");
  delay(1000);
  lcd.clear();


  //CRIA OS CHARS
  lcd.createChar(0, fogo1);
  lcd.createChar(1, fogo2);
  lcd.createChar(2, fogo3);
  lcd.createChar(3, fogo4);
  lcd.createChar(4, lanterna);
  lcd.createChar(5, gota);
}

void loop() {
  // CRIA A VARIAVEL CURRENT MILLIS PARA CONTROLAR O TEMPO
  unsigned long currentMillis = millis();



  //IF DE TEMPERATURA
  if (currentMillis - previousMillis < interval) {

    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(temperatura);
    lcd.print(" C ");

    //TEMPERATURA ALTA
    if (temperatura > 15.00) {
      lcd.setCursor(0,0);
      lcd.print("Temp : ALTA     ");
      efeitodefogo();
    }
    //TEMPERATURA 
    else if (temperatura < 10.00) {
      lcd.setCursor(0,0);
      lcd.print("Temp : BAIXA    ");
      lcd.setCursor(11, 1);
      lcd.print("    ");

    }
    //TEMPERATURA NORMAL
    else {
      lcd.setCursor(0,0);
      lcd.print("Temp : ADEQUADA ");
      lcd.setCursor(11, 1);
      lcd.print("    ");
    }

  }
  // ELSE IF DE LUMINOSIDADE
  else if (currentMillis - previousMillis < 2 * interval) {

    lcd.setCursor(0, 0);
    // MENSAGEM PARA LUZ MUITO ALTA
    if (LuminosidadeLED > 70) {
      lcd.setCursor(0, 0);
      lcd.print("Ambiente muito  ");
      lcd.setCursor(0, 1);
      lcd.print("claro    "); 
      lcd.setCursor(10, 1);
      lcd.write(4);
      lcd.write(4);
      lcd.write(4);
      lcd.print("   ");
    }
    // MENSAGEM PARA LUZ "ALTA"
    else if (LuminosidadeLED >= 40 && LuminosidadeLED <= 70) {
      lcd.setCursor(0, 0);
      lcd.print("Ambiente a meia ");
      lcd.setCursor(0, 1);
      lcd.print("luz       "); 
      lcd.setCursor(10, 1);
      lcd.write(4);
      lcd.write(4);
      lcd.print("    ");
    }
    // MENSAGEM PARA LUZ ADEQUADA
    else if (LuminosidadeLED < 40) {
      lcd.setCursor(0, 0);
      lcd.print("Ambiente       ");
      lcd.setCursor(0, 1);
      lcd.print("Escuro   "); 
      lcd.setCursor(10, 1);
      lcd.write(4);
      lcd.print("     ");
    }

  }

  // ELSE IF DE UMIDADE
  else if (currentMillis - previousMillis < 3 * interval) {
    //MENSAGEM UMIDADE ALTA
    if (umidade > 70.00) {
      lcd.setCursor(0, 0);
      lcd.print("Umidade : ALTA  ");
      lcd.setCursor(11, 1);
      lcd.write(5);
      lcd.write(5);
      lcd.write(5);
      lcd.setCursor(9, 1);
      lcd.print("  ");
      lcd.setCursor(14, 1);
      lcd.print("  ");

    }
    //MENSAGEM UMIDADE NORMAL
    else if (umidade >= 50.00 && umidade <= 70.00) {
      lcd.setCursor(0, 0);
      lcd.print("Umidade : NORMAL");
      lcd.setCursor(11, 1);
      lcd.write(5);
      lcd.write(5);
      lcd.setCursor(9, 1);
      lcd.print("  ");
      lcd.setCursor(13, 1);
      lcd.print("   ");
    }
    //MENSAGEM UMIDADE BAIXA
    else if (umidade < 50.00) {
      lcd.setCursor(0, 0);
      lcd.print("Umidade : BAIXA ");
      lcd.setCursor(11, 1);
      lcd.write(5);
      lcd.setCursor(9, 1);
      lcd.print("  ");
      lcd.setCursor(12, 1);
      lcd.print("     ");

    }
    lcd.setCursor(0, 1);
    lcd.print("U:");
    lcd.print(umidade);
    lcd.print(" %");
  }

  // Reset timer
  else {
    previousMillis = currentMillis;
  }


  //VARIAVEIS ARMAZENADORAS DE LEITURA
  vldr = analogRead(ldr);
  LuminosidadeLED = map(vldr, 8, 1015, 100, 0);
  umidade = dht.readHumidity();
  temperatura = dht.readTemperature();



  //CONFIGURAÇÕES DOS SENSORES
  //Vermelho
  if (LuminosidadeLED > 70 || umidade > 70.00 || umidade < 50.00 || temperatura > 30.00 || temperatura < 5.00)
  {
    luzVermelho();
  }
  //Amarelo
  else if (LuminosidadeLED >= 40 && LuminosidadeLED <= 70 || temperatura > 15.00 || temperatura < 11.00)
  {
    luzAmarelo();
  //Verde
  }
  else if (LuminosidadeLED < 40 || (temperatura >= 11.00 && temperatura <= 15.00) || (umidade >= 50.00 && umidade <= 70.00))
  {
    luzVerde();
  }


  //ADICIONA A NOVA LEITURA À MÉDIA MÓVEL
  for (int i = 9; i > 0; i--) {
    mediaMovelLuminosidade[i] = mediaMovelLuminosidade[i - 1];
    mediaMovelUmidade[i] = mediaMovelUmidade[i - 1];
    mediaMovelTemperatura[i] = mediaMovelTemperatura[i - 1];
  }

  mediaMovelLuminosidade[0] = LuminosidadeLED;
  mediaMovelUmidade[0] = umidade;
  mediaMovelTemperatura[0] = temperatura;
  contagemLeituras++;

  // VERIFICA SE JÁ FORAM FEITAS 10 LEITURAS
  if (contagemLeituras >= 10) {
    //CALCULA A MÉDIA DAS ÚLTIMAS 10 LEITURAS
    int somaLuminosidade = 0;
    int somaUmidade = 0;
    int somaTemperatura = 0;
    for (int i = 0; i < 10; i++) {
      somaLuminosidade += mediaMovelLuminosidade[i];
      somaUmidade += mediaMovelUmidade[i];
      somaTemperatura += mediaMovelTemperatura[i];
    }
    LuminosidadeLED = somaLuminosidade / 10;
    umidade = somaUmidade / 10;
    temperatura = somaTemperatura / 10;

    // PRINT DE VALORES NO SERIAL MONITOR
    Serial.print("Intensidade de Luz = ");
    Serial.print(LuminosidadeLED);
    Serial.print(" Temperatura = ");
    Serial.print(temperatura);
    Serial.print(" °C ");
    Serial.print("  Umidade  = ");
    Serial.print(umidade);
    Serial.println(" % ");


  
  }
  //DELAY GERAL DO LOOP
    delay(200);
}


//FUNÇÕES USADAS

/*função para desligar todos os leds e poupar
  espaço, além de garantir que todos os leds
  estarão desligados quando necessario*/
void apagaLeds()
{
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
}

//Função de buzzer intermitente
void buzzerAlternativo() {
  static unsigned long previousBeepMillis = 0;
  static boolean beepState = false;
  unsigned long currentMillis = millis();

  if (currentMillis - previousBeepMillis >= 200) { 
    previousBeepMillis = currentMillis;
    beepState = !beepState;
    if (beepState) {
      tone(buzzer, 2500, 100);
    } else {
      noTone(buzzer);
    }
  }
}

//Função que liga o led verde e desliga o buzzer
void luzVerde()
{
  apagaLeds();
  digitalWrite(ledVerde, HIGH);
  noTone(buzzer);
}

//Função que liga o led amarelo e toca o Buzzer alternativo
void luzAmarelo()
{
  apagaLeds();
  digitalWrite(ledAmarelo, HIGH);
  buzzerAlternativo();
}
//Função que liga o led vermelho e toca o Buzzer contínuo
void luzVermelho()
{
  apagaLeds();
  digitalWrite(ledVermelho, HIGH);
  tone(buzzer, 1000, 3000); //som alto e constante para alertar

}

//Função que executa a introdução do sistema
void Introdisplay() {
  //MOVE POSIÇÕES

  for (int positionCounter = 0; positionCounter < 9; positionCounter++) {
    if (positionCounter == 0) {
      lcd.setCursor(positionCounter, 0);
      lcd.print("d");

    }
    else if (positionCounter == 1) {
      lcd.setCursor(positionCounter - 1, 0);
      lcd.print("nd");

    }
    else if (positionCounter == 2) {
      lcd.setCursor(positionCounter - 2, 0);
      lcd.print("ind");


    }
    else if (positionCounter == 3) {
      lcd.setCursor(positionCounter - 3, 0);
      lcd.print("Mind");
    }
    else {
      lcd.setCursor(positionCounter - 3, 0);
      lcd.print("Mind");
    }
    lcd.setCursor(15 - positionCounter, 1);
    lcd.print("Sync");
    delay(100);
    lcd.clear(); // Limpa o display para o próximo movimento
  }
}

// Função que realiza um efeito de fogo no slide de temperatura
void efeitodefogo() {
  lcd.setCursor(10, 1);
  lcd.write(byte(0));
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.write(byte(0));
  lcd.write(1);
  lcd.write(2);


  delay(200);

  lcd.setCursor(10, 1);
  lcd.write(1);
  lcd.write(2);
  lcd.write(byte(0));
  lcd.write(byte(0));
  lcd.write(1);
  lcd.write(2);


  delay(200);
  lcd.setCursor(10, 1);
  lcd.write(byte(0));
  lcd.write(2);
  lcd.write(3);
  lcd.write(1);
  lcd.write(1);
  lcd.write(3);
}
