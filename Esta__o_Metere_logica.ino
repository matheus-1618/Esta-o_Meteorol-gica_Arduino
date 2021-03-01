//Incluindo bibliotecas
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_BMP280.h> 

//Definindo constantes do código
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_BMP280 bmp;
const int DHT_PIN=2;
DHT dht(DHT_PIN,DHT22);

float umid,temp;

//Gera o símbolo de Celsius
const byte Celsius_symbol = 1;
const byte Celsius_bitmap[8] = {
    B11100,
    B10100,
    B11100,
    B00000,
    B00000,
    B00000,
    B00000,
};

const byte pacman_symbol=0;
const byte pacman_bitmap[8] = {
  B00000,
  B00000,
  B01110,
  B11011,
  B11100,
  B01110,
  B00000,
  B00000
};

void setup() {
    analogReference(INTERNAL);
    int leitura_adc = analogRead(A0);
    lcd.init();
    dht.begin();
    lcd.createChar(Celsius_symbol, Celsius_bitmap);
    lcd.createChar(pacman_symbol, pacman_bitmap);
    if(!bmp.begin(0x76)){ 
    //IMPRIME O TEXTO NO MONITOR SERIAL
    lcd.print("Sensor BMP280 não foi identificado! Verifique as conexões.");
    // Trava o arduino em um loop while que nunca termina... while(true)
    while(1==1) {}; 
  
}
}
void loop() {
  //Medindo temperatura com o LM35
  int leitura_adc = analogRead(A0);
  // Converte o valor lido para um valor em volts
  // 1.1 ou 1.1f para forçar numero real
  float voltagem = leitura_adc * (1.1f/1023);
  // Calcula a temperatura
  // LM35: 10mV => 1 grau C
  float temperatura = voltagem * 100.0;
  //Utilizando a inversa da calibração
  float temperatura_real= temperatura*1.03039 -1.00517;

  //Identifica umidade
  umid = dht.readHumidity();
  umid = umid*1.22867487 -27.67607;

  //Identifica pressão e altitude 


  //Identifica a luminosidade
  int bin;
  float tensao, res, lum;
  bin = analogRead(A1);
  tensao = bin*1.1/1023.0;
  res = 330*(5.0/tensao+1);
  lum = pow(10, 5-log10(res));

  //Lendo dados no LCD
  lcd.setBacklight(1);
  lcd.setCursor(0, 0);
  lcd.print("    INSPER ");
  lcd.setCursor(11, 0);
  lcd.write(pacman_symbol);
  lcd.setCursor(0,1);
  lcd.print("  INSTRUMED             ");
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("Integrantes:         ");
  lcd.setCursor(0, 1);
  lcd.print("Ykaro Andrade        ");
  delay(3000);
  lcd.setCursor(0, 1);
  lcd.print("Matheus Oliveira           !");
  delay(3000);
  lcd.setCursor(0, 1);
  lcd.print("Adney Costa                  ");
  lcd.setCursor(0,1);
  delay(3000);

  //Lendo Temperatura
  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print("Temperatura:           ");
  lcd.setCursor(0,1);
  lcd.print(temperatura);
  lcd.setCursor(4, 1);
  lcd.write(Celsius_symbol);
  lcd.setCursor(5,1);
  lcd.print("C          ");
  delay(3000);

  //Lendo Umidade
  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print("Umidade Medida:           ");
  lcd.setCursor(0,1);
  lcd.print(umid);
  lcd.print("%");
  delay(3000);

  //Lendo Pressão
  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print(F("Pressao:         "));
  lcd.setCursor(0,1);
  lcd.print(bmp.readPressure()*9.869*0.000001);
  lcd.print("atm            ");
  delay(3000);

  //Lendo Altitude
  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print(F("Altitude:       "));
  lcd.setCursor(0,1);
  lcd.print(bmp.readAltitude(1020.6));
  lcd.print("metros                 ");
  delay(3000);
  
  //Lendo a luminosidade
  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print("Luminosidade:       ");
  lcd.setCursor(0,1);
  lcd.print(lum);
  lcd.print("lux                 ");
  delay(3000);
  
}
