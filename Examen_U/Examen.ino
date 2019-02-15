
#include "baseexamen.h"

// definicion de matricez de CNN
float matriz_s [30][5];  // datos validos
float matriz_d [65][5]; // datos de desecho
int col = 0; // variable de recorrido de col de matriz de mayor volumen
int fil;  // variable de recorrido de filas de matriz de mayor volumen
int col_s = 0; // variable que recorre columnas para matriz s
int fil_s = 0; // variable que recorre filas matriz s
int fil_s1 = 3; // variable que recorre matriz s cuando realiza knn con matriz d
int fil_d = 0; // variable que recorre filas en matriz d
int col_d = 0; // variable que recorre columnas en matriz d
float promedio; // variable de promedio
float suma = 0; //variable parcial para encontrar distancia mas corta
int etiqueta = 1; // variable para ciclo de conteo entre etiquetas
int i = 0; // variable de seleccion de etiquetas
int j = 0;
float dist = 0; // variable parcial para encontrar distancia mas corta
float dist_total; // variable global para almacenar distancia mas corta
float dist_mayor = 2000; // variable para encontrar la distancia menor
float label; // variable que almacena etiqueta de distancia mas corta
int se1;
int se2;
int se3;
int sa1;
int sa2;
int sa3;
////////////////////////////////////////////////////////////////////////
int on = 0, a = 0, b = 0, total = 0;
float result;
////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
for ( j = 0; j <= 74; j++) {   // para recorrer las filas
      if(matriz[j][4]==1){
        se1++;
      }else
      if(matriz[j][4]==2){
        se2++;
      }else
      if(matriz[j][4]==3){
        se3++;
      }
    }
    Serial.println(se1);
    Serial.println(se2);
    Serial.println(se3);
    sa1=se1+se2-1;
    sa2=se1+se2;
    sa3=se1+se2+se3-1;
      for (i = 0; i <= 3; i++) {  // para recorrer las columnas
    for ( j = 0; j < se1; j++) {   // para recorrer las filas
      suma +=  matriz[j][i]; // se guarda en la variable
      promedio = suma / se1;   // la suma total se divide para el numero de datos
    }
    matriz_s[0][i] = promedio;
    matriz_s[0][4] = 1;
    suma = 0;      // se reinicia la suma
    promedio = 0;
    for ( j = se1; j <= sa1; j++) {   // para recorrer las filas
      suma +=  matriz[j][i]; // se guarda en la variable
      promedio = suma / se2;   // la suma total se divide para el numero de datos
    }
    matriz_s[1][i] = promedio;
    matriz_s[1][4] = 2;
    suma = 0;      // se reinicia la suma
    promedio = 0;
    for ( j = 45; j <= sa3; j++) {   // para recorrer las filas
      suma +=  matriz[j][i]; // se guarda en la variable
      promedio = suma / se3;   // la suma total se divide para el numero de datos
    }
    matriz_s[2][i] = promedio;
    matriz_s[2][4] = 3;
    suma = 0;      // se reinicia la suma
    promedio = 0;
  }
  for(int h=0;h<=3;h++){
    for(int j=0;j<=4;j++){
      Serial.println(matriz_s[h][j]);
    }
  }
  
}
