//////////Librerias/////////
#include <DHT.h>
#include <MQ135.h>
#include <MQ7.h>
#include <CS_MQ7.h>
//////////////DTH11///////////
int DHTPIN = 9; // Definimos el pin digital donde se conecta el sensor
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
const int ledPin =  8;
int temp;
int hume;
int uv;
int ref;
int nox;
int co;
int cop;
int noxp;
int hic;
int outv;
int uvint;
////////////////////////////////////////////////////////
String h, t, u, c, n;
String mensaje;
/////////////////////////////////////////////////////////
#include "datos_03.h"
int on = 0;
int result;
float vector [5] ; ///// Variable variable
/////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Inicializamos comunicación serie
  ////// UV/////
  pinMode(An4, INPUT);
  pinMode(An3, INPUT);
  ////DTH11////
  dht.begin();// Comenzamos el sensor DHT
  //////SD/////
  pinMode(ledPin, OUTPUT);
}
////////////////////////////////////////////////////////////
float knn (int fila, int col, int k, int label, float datos[]) {
  int c = 0; // movernos en columnas
  int f = 0; // movernos en fila
  float k_vecinos_dist[k]; // vector de almacenamiento de k distancias menores
  float etiquetas [2][label]; // matriz y conteo de etiquetas
  float dist = 0; // variable que almacena cada distancia
  float dist_total = 0; // varaible para almacenamiento de distancia
  // llenar vector k_vecinos_dist con valores altos
  float eti_menor[k]; //vector de etiquetas de distancia menor
  int k_cont = 0;
  int i = 0;
  float clase; // retornar etiqueta
  float comparacion; // comparar k-vecino mayor
  for (; c < k; c++) {
    k_vecinos_dist[c] = 2000.0 + c; // valores altos y ordenados
  }
  c = 0; // reiniciar varaible
  // llenar matriz etiquetas
  for (; c < label; c++) {
    etiquetas[0][c] = c + 1; // lleno con valores de etiqueta
    etiquetas[1][c] = 0; // lleno con el conteo de etiqueta
  }
  c = 0; //renicio variable
  // la distacia mas corta del nuevo punto hacia la matriz

  for (; f < fila; f++) {
    for (; c < col - 1; c++) {
      dist = dist + pow((matriz[f][c] - datos[c]), 2); // distancia entre dos puntos
    }
    dist_total = sqrt(dist); // raiz de la formula
    // Serial.println(dist_total);
    for (; k_cont < k; k_cont++) { // determinar las k distancias menores y ordenarlas
      if (dist_total < k_vecinos_dist[k_cont]) {
        k_vecinos_dist[k_cont] = dist_total; // asignar nuevo valor a vector de distancias menores
        eti_menor[k_cont] = matriz[f][col - 1]; // col =5 , 4
      }
    }
    k_cont = 0;
    dist = 0;
    dist_total = 0;
    c = 0;
  } //for fila

  // seleccion de los k vecino
  for (; c < label; c++) {
    for (; k_cont < k; k_cont++) { // recorro cada posicion de eti_menor y comparo con etiquetas y cuento si son iguales
      if (etiquetas[0][c] == eti_menor[k_cont]) {
        i++;
        etiquetas[1][c] = i;
      }
    }
    k_cont = 0;
    i = 0;
  }
  c = 1;
  comparacion = etiquetas[1][0];
  clase = etiquetas[0][0];
  for (; c < label; c++) {
    if (etiquetas[1][c] > comparacion) { // comparacion entre valores de suma de etiqueta
      clase = etiquetas[0][c];
      comparacion = etiquetas[1][c];
    }
  }
  comparacion = 0;
  c = 0;
  return clase;
}
////////////////////////////////////////////////////////////
void loop() {
  digitalWrite(ledPin, HIGH);
  ///////DHT11///////////
  hume = dht.readHumidity();
  temp = dht.readTemperature();
  hic = dht.computeHeatIndex(temp, hume, false);
  /////////UV/////////
  uv = analogRead(An4);
  ref = analogRead(An3);
  outv = 3.3 / ref * uv;
  uvint = map(outv, 0.99, 2.9, 0.0, 15.0);
  /////////MQ7//////////
  co = analogRead(An1);
  //////////Mq135//////
  nox = analogRead(An2);
  ///////////////////////
  h = String(hume);
  t = String(hic);
  u = String(outv);
  c = String(co);
  n = String(nox);
  
  ///////////////////////
  vector [0] = hume;
    vector [1] = hic;
    vector [2] = outv;
    vector [3] = co;
    vector [4] = nox;
    //////////////////////
    result = knn(61, 6, 3, 3, vector);
  ///////////////////////////
  mensaje = String(h + "/" + t + "/" + u + "/" + c + "/" + n + "/"+ result + "/");
  Serial.println(mensaje);
  delay(1000);

}
