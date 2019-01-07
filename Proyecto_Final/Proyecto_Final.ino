//////////Librerias/////////
#include <DHT.h>
#include <MQ135.h>
#include <MQ7.h>
#include <CS_MQ7.h>
#include <SD.h>
//////////MICROSD/////////////
File myFile;
/////////LED//////////////////
const int ledPin =  8;
//////////BOTON////////////
const int buttonPin = 2;
int ledState = LOW;
boolean buttonState = LOW;
int pressed = 0;
//////////////DTH11///////////
int DHTPIN = 3; // Definimos el pin digital donde se conecta el sensor
DHT dht(DHTPIN, DHT11);// Inicializamos el sensor DHT11
//////////////MQ135//////////
int An2 = 2;
MQ135 gasSensor = MQ135(An2);
////////////MQ7//////////////
int An1 = 1;
MQ7 mq7(An1, 5.0);
/////////////Rayos UV //////////
int An3 = 3; //3.3v
int An4 = 4; //OUT
////// VAriables ////
int temp;
int hume;
int uv;
int nox;
int co;
/////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Inicializamos comunicación serie
  ////// UV/////
  pinMode(An4, INPUT);
  pinMode(An3, INPUT);
  ////DTH11////
  dht.begin();// Comenzamos el sensor DHT
  ////LED////
  pinMode(ledPin, OUTPUT);
  ////BOTON////
  pinMode(buttonPin, INPUT);
  //////SD/////
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
  //////////SD-Exel///////////
  if (!SD.exists("datalog.csv"))
  {
    myFile = SD.open("datalog.csv", FILE_WRITE);
    if (myFile) {
      Serial.println("Archivo nuevo, Escribiendo encabezado(fila 1)");
      myFile.println("Sensor1,Sensor2,Sensor3,Sensor4,Sensor5");
      myFile.close();
    } else {
      Serial.println("Error creando el archivo datalog.csv");
    }
  }
}
////////////////////////////////////////////////////////////
void loop() {

  //////BOTON////////
  if (debounceButton(buttonState) == HIGH && buttonState == LOW) {
    pressed++;
    buttonState = HIGH;
  }
  else if (debounceButton(buttonState) == LOW && buttonState == HIGH) {
    buttonState = LOW;
  }
  if (pressed == 1) {
    //////SD-OPEN//////
    myFile = SD.open("data.txt", FILE_WRITE);//abrimos  el archivo
    myFile = SD.open("datalog.csv", FILE_WRITE);
    if (myFile) {
      Serial.print("Tomando datos - "); Serial.println("Escribiendo SD: ");
      ///////LED/////////
      digitalWrite(ledPin, HIGH);
      ///////DHT11///////////
      hume = dht.readHumidity();
      temp = dht.readTemperature();
      /////////UV/////////
      uv = analogRead(An3);
      /////////MQ7//////////
      co = analogRead(An1);
      //////////Mq135//////
      nox = analogRead(An2);
      ///////SD-Guardamdo/////////
      myFile.print(hume);
      myFile.print(",");
      myFile.print(temp);
      myFile.print(",");
      myFile.print(uv);
      myFile.print(",");
      myFile.print(nox);
      myFile.print(",");
      myFile.print(co);
      myFile.println(" ");
      /////////SD-Cerrar/////////
      myFile.close();//cerramos el archiv
      ///////Imprimir-Serial//////////
      Serial.print("Humedad: ");
      Serial.print(hume);
      Serial.print("   ");
      Serial.print("Temperatura: ");
      Serial.print(temp);
      Serial.print("   ");
      Serial.print("Uv: ");
      Serial.print(uv);
      Serial.print("   ");
      Serial.print("Nox: ");
      Serial.print(nox);
      Serial.print("   ");
      Serial.print("Co: ");
      Serial.print(co);
      Serial.println(" ");
      //////// Tiempo de espera /////////
      delay(1000);
    }
    else {
      Serial.println("Error al abrir el archivo");
    }
    delay(100);
    pressed = 1;
  }
  else if (pressed == 2) {
    Serial.println("Sistema Fuera");
    digitalWrite(ledPin, LOW);
    pressed = 0;
  }
}

boolean debounceButton(boolean state) {
  boolean stateNow = digitalRead(buttonPin);
  if (state != stateNow) {
    delay(10);
    stateNow = digitalRead(buttonPin);
  }
  return stateNow;
}
