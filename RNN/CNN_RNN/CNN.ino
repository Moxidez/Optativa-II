#include "datos_entrenamiento.h"
// definicion de matricez de CNN
float matriz_s [60][5];  // datos validos
float matriz_d [90][5]; // datos de desecho
float matriz_r [30][5]; // datos de desecho
float matriz_dr [90][5]; // datos de desecho
int col = 0; // variable de recorrido de col de matriz de mayor volumen
int fil;  // variable de recorrido de filas de matriz de mayor volumen
int col_s = 0; // variable que recorre columnas para matriz s
int fil_s = 0; // variable que recorre filas matriz s
int fil_s1 = 3; // variable que recorre matriz s cuando realiza knn con matriz d
int fil_d = 0; // variable que recorre filas en matriz d
int col_d = 0; // variable que recorre columnas en matriz d
float promedio; // variable de promedio
float sumatoria = 0; //variable parcial para encontrar distancia mas corta
int etiqueta = 1; // variable para ciclo de conteo entre etiquetas
int i = 0; // variable de seleccion de etiquetas
float dist = 0; // variable parcial para encontrar distancia mas corta
float dist_total; // variable global para almacenar distancia mas corta
float dist_mayor = 2000; // variable para encontrar la distancia menor
float label; // variable que almacena etiqueta de distancia mas corta
int se1;
float suma = 0; //variable parcial para encontrar distancia mas corta
int se2;
int se3;
int sa1;
int sa2;
int sa3;
int j;
void setup() {
  Serial.begin(9600);
  // ciclo que permite encontrar los puntos medios por cada etiqueta
  //recorre cada posicion de filas por etiquetas y encuentra el promedio de cada
  // columna
  for (; etiqueta < 4; etiqueta++) { // ciclo que recorre por etiqueta
    for (; col < 4; col++) { // ciclo que recorre por columna
      for (fil = i; fil < 30 * etiqueta; fil++) { // ciclo que recorre por filas
        sumatoria = sumatoria + matriz[fil][col]; // almacenamiento de sumatoria
      }
      promedio = sumatoria / 30; // promedio por columna
      matriz_s[etiqueta - 1][col] = promedio; // almacenar promedios en matriz S
      sumatoria = 0; // vuelve a cero para siguiente columna
      fil = 0; // fila vuelve a cero para recorrer nuevamente filas
    }
    col = 0; // variable vuelve a cero para recorrer nuevamente columnas
    i = 30 * etiqueta; // variable que que cuenta determina el numero de datos por etiqueta
  }

  col = 0;
  fil = 0;
  // metodo para llenar etiquetas en vector
  //una vez encontrado puntos medios
  for (; fil < 3; fil++) {
    matriz_s[fil][4] = fil + 1; // llenar etiquetas en matriz S
  }
  fil = 0;
  /*
     Metodo para implementar el algoritmo CNN dentro de Arduino
     La matriz almacenada en el archivo .h se encontraron los puntos medios
     por cada etiqueta
     se realiza k-nn por cada punto de la matriz de mayor volumen teniendo como matriz
     de entrenamiento a la matriz que solo contiene los puntos medios llamada matriz s
     Cuando un dato ingresa desde la matriz de mayor volumen a knn y es clasificado adecuadamente se almacane en matriz d
     caso contrario en matriz s.
     con la matriz d con datos, se vuelve a realizar knn con matriz de entrenamiento la matriz s, si sigue
     clasificando adecuadamente se almacena en martiz d, caso contrario matriz s
     Se conserva matriz s, el resto se descarta
  */

  // metodo de knn con matriz de mayor volumen y knn con matriz s  de entrenamiento

  for (; fil < 90; fil++) { // ciclo que recorre por cada fila de matriz de mayor volumen
    for (; fil_s < 3; fil_s++) { // recorre por filas de la matriz s
      for (; col_s < 4; col_s++) { // recorre por filas de ambas matrices
        dist = dist + pow(matriz[fil][col_s] - matriz_s[fil_s][col_s], 2); // distancia entre dos puntos
      }
      dist_total = sqrt(dist); // distancia entre dos puntos
      if (dist_total < dist_mayor) { // comparacion para encontrar distancia menor
        dist_mayor = dist_total;
        label = matriz_s[fil_s][4]; //
      }// endif
      dist = 0; // por cada lectura de fila se encera distancia
      col_s = 0; //vuelve a cero para leer nuevamente columnas
    }//end for fil_S
    fil_s = 0;
    dist_mayor = 2000;
    // si el algoritmo knn clasifico correctamente, almacena en matriz d
    // caso contrario en matriz s
    if (label == matriz[fil][4]) {
      // almacena los datos en matriz d
      for (; col_d < 5; col_d++) {
        matriz_d[fil_d][col_d] = matriz[fil][col_d];
      }
      col_d = 0;
      fil_d++;
    }
    else {
      // almancena los datos en matriz s
      for (; col_s < 5; col_s++) {
        matriz_s[fil_s1][col_s] = matriz[fil][col_s];
      }
      col_s = 0;
      fil_s1++;
    }
  }
  // imprime los valores almacenados en matriz s
  //////////////////////////////////////////////////
  // una vez realizado el proceso en matriz de alto volumen
  // se realiza el mismo proceso con matriz d
  fil = 0;
  fil_s = 0;
  col_s = 0;
  for (; fil < fil_d; fil++) { // recorre los datos filas de matriz d
    for (; fil_s < 3; fil_s++) { // recorre los datos de filas de matriz s
      for (; col_s < 4; col_s++) { // recorre las columnas de ambas matrices
        dist = dist + pow(matriz_d[fil][col_s] - matriz_s[fil_s][col_s], 2); //distancia entre dos puntos
      }
      dist_total = sqrt(dist); // distancia entre dos puntos
      if (dist_total < dist_mayor) { // compara con distancia menor
        dist_mayor = dist_total;
        label = matriz_s[fil_s][4]; // almacena etiqueta de distancia menor
      }// endif
      dist = 0;
      col_s = 0;
    }//end for fil_S
    fil_s = 0;
    dist_mayor = 2000;
    // si clasifica correctamente el sistema no realiza ninguna accion
    if (label == matriz_d[fil][4]) {
    }
    // si clasifica de forma erronea, almacena en matriz s
    else {
      for (; col_s < 5; col_s++) {
        matriz_s[fil_s1][col_s] = matriz[fil][col_d];
      }
      col_s = 0;
      fil_s1++;
    }
  }
  ////////////////////////////////////////////////
  // imprime los valores almacenados en matriz s
  Serial.print("Matriz CNN");
  Serial.println(' ');
  fil_s = 0;
  for (; fil_s < fil_s1; fil_s++) {
    for (; col_s < 5; col_s++) {
      Serial.print(matriz_s[fil_s][col_s]);
      Serial.print(',');
    }
    col_s = 0;
    Serial.println(' ');
  }

  //////////////////////////////////////////////////////////////////////
  Serial.print("Datos por etiqueta");
  Serial.println(' ');
  for (j = 0 ; j < fil_s ; j ++) {    // para recorrer las filas
    if (matriz_s [j] [ 4 ] == 1 ) {
      se1 ++;
    } else if (matriz_s [j] [ 4 ] == 2 ) {
      se2 ++;
    } else if (matriz_s [j] [ 4 ] == 3 ) {
      se3 ++;
    }
  }
  Serial.print("Datos 1= "); Serial.println (se1);
  Serial.print("Datos 2= "); Serial.println (se2);
  Serial.print("Datos 3= "); Serial.println (se3);
  ///////////////////Ordenar matriz///////////////
  float mayor0;
  float mayor1;
  float mayor2;
  float mayor3;
  float mayor4;
  int x = 0;
  for ( i = 0; i <= 9; i++) {   // leer las filas
    for ( x = 0; x <= 9; x++) {   // usamos para crear un for anidado y un bucle
      if (matriz_s[i][4] > matriz_s[x][4]) { // si numero actual es mayor a numero siguiente
        mayor0 = matriz_s[i][0];     // auxiliar es igual a numero actual
        mayor1 = matriz_s[i][1];
        mayor2 = matriz_s[i][2];
        mayor3 = matriz_s[i][3];
        mayor4 = matriz_s[i][4];
        matriz_s[i][0] = matriz_s[x][0];
        matriz_s[i][1] = matriz_s[x][1];
        matriz_s[i][2] = matriz_s[x][2];
        matriz_s[i][3] = matriz_s[x][3];
        matriz_s[i][4] = matriz_s[x][4];    // numero actual va a ser iguala numero siguiente
        matriz_s[x][0] = mayor0;   // numero siguiente va a ser iguala  auxiliar
        matriz_s[x][1] = mayor1;
        matriz_s[x][2] = mayor2;
        matriz_s[x][3] = mayor3;
        matriz_s[x][4] = mayor4;
      }
    }
  }

  ////////////////////////////////////////////////
  // imprime los valores almacenados en matriz s
  Serial.print("Matriz CNN Ordenada");
  Serial.println(' ');
  fil_s = 0;
  for (; fil_s < fil_s1; fil_s++) {
    for (; col_s < 5; col_s++) {
      Serial.print(matriz_s[fil_s][col_s]);
      Serial.print(',');
    }
    col_s = 0;
    Serial.println(' ');
  }
  ////////////////////////////////////////////////
  for (i = 0; i <= 3; i++) {  // para recorrer las columnas
    for ( j = 0; j <= 4 ; j++) {  // para recorrer las filas
      suma +=  matriz_s[j][i]; // se guarda en la variable
      promedio = suma / 5.0;   // la suma total se divide para el numero de datos
    }
    matriz_r[2][i] = promedio;
    matriz_r[2][4] = 3;
    suma = 0;      // se reinicia la suma
    promedio = 0;
    for ( j = 5; j <= 7; j++) {   // para recorrer las filas
      suma +=  matriz_s[j][i]; // se guarda en la variable
      promedio = suma / 3.0;   // la suma total se divide para el numero de datos
    }
    matriz_r[1][i] = promedio;
    matriz_r[1][4] = 2;
    suma = 0;      // se reinicia la suma
    promedio = 0;
    for ( j = 8; j <= 8; j++) {   // para recorrer las filas
      suma +=  matriz_s[j][i]; // se guarda en la variable
      promedio = suma / 1.0;   // la suma total se divide para el numero de datos
    }
    matriz_r[0][i] = promedio;
    matriz_r[0][4] = 1;
    suma = 0;      // se reinicia la suma
    promedio = 0;
  }
  //////////////////////////////////////////////
  Serial.print("Radios RNN");
  Serial.println(' ');
  for (int z = 0; z < 3; z++) {
    for (int x = 0; x < 5; x++) {
      Serial.print(matriz_r[z][x]);
      Serial.print(',');
    }
    Serial.println(' ');
  }
  /////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  for (; fil < 90; fil++) { // ciclo que recorre por cada fila de matriz de mayor volumen
    for (; fil_s < 3; fil_s++) { // recorre por filas de la matriz s
      for (; col_s < 4; col_s++) { // recorre por filas de ambas matrices
        dist = dist + pow(matriz[fil][col_s] - matriz_r[fil_s][col_s], 2); // distancia entre dos puntos
      }
      dist_total = sqrt(dist); // distancia entre dos puntos
      if (dist_total < dist_mayor) { // comparacion para encontrar distancia menor
        dist_mayor = dist_total;
        label = matriz_r[fil_s][4]; //
      }// endif
      dist = 0; // por cada lectura de fila se encera distancia
      col_s = 0; //vuelve a cero para leer nuevamente columnas
    }//end for fil_S
    fil_s = 0;
    dist_mayor = 2000;
    // si el algoritmo knn clasifico correctamente, almacena en matriz d
    // caso contrario en matriz s
    if (label == matriz[fil][4]) {
      // almacena los datos en matriz d
      for (; col_d < 5; col_d++) {
        matriz_dr[fil_d][col_d] = matriz[fil][col_d];
      }
      col_d = 0;
      fil_d++;
    }
    else {
      // almancena los datos en matriz s
      for (; col_s < 5; col_s++) {
        matriz_r[fil_s1][col_s] = matriz[fil][col_s];
      }
      col_s = 0;
      fil_s1++;
    }
  }
  //////////////////////////////////////////////////
  // una vez realizado el proceso en matriz de alto volumen
  // se realiza el mismo proceso con matriz d
  fil = 0;
  fil_s = 0;
  col_s = 0;
  for (; fil < fil_d; fil++) { // recorre los datos filas de matriz d
    for (; fil_s < 3; fil_s++) { // recorre los datos de filas de matriz s
      for (; col_s < 4; col_s++) { // recorre las columnas de ambas matrices
        dist = dist + pow(matriz_dr[fil][col_s] - matriz_r[fil_s][col_s], 2); //distancia entre dos puntos
      }
      dist_total = sqrt(dist); // distancia entre dos puntos
      if (dist_total < dist_mayor) { // compara con distancia menor
        dist_mayor = dist_total;
        label = matriz_r[fil_s][4]; // almacena etiqueta de distancia menor
      }// endif
      dist = 0;
      col_s = 0;
    }//end for fil_S
    fil_s = 0;
    dist_mayor = 2000;
    // si clasifica correctamente el sistema no realiza ninguna accion
    if (label == matriz_dr[fil][4]) {
    }
    // si clasifica de forma erronea, almacena en matriz s
    else {
      for (; col_s < 5; col_s++) {
        matriz_r[fil_s1][col_s] = matriz[fil][col_s];
      }
      col_s = 0;
      fil_s1++;
    }
  }
  ///////////////////////////////////////////
  Serial.print("Matriz RNN");
  Serial.println(' ');
  fil_s = 86;
  for (; fil_s < fil_s1; fil_s++) {
    for (; col_s < 5; col_s++) {
      Serial.print(matriz_dr[fil_s][col_s]);
      Serial.print(',');
    }
    col_s = 0;
    Serial.println(' ');
  }
  fil_s1 = -1;
    //////////////////////////////////////////////////////////////////////
  Serial.print("Datos por etiqueta");
  Serial.println(' ');
  for (j = 0 ; j < fil_s ; j ++) {    // para recorrer las filas
    if (matriz_dr [j] [ 4 ] == 1 ) {
      sa1 ++;
    } else if (matriz_dr [j] [ 4 ] == 2 ) {
      sa2 ++;
    } else if (matriz_dr [j] [ 4 ] == 3 ) {
      sa3 ++;
    }
  }
  Serial.print("Datos 1= "); Serial.println (sa1);
  Serial.print("Datos 2= "); Serial.println (sa2);
  Serial.print("Datos 3= "); Serial.println (sa3-2);
}
void loop() {

}
