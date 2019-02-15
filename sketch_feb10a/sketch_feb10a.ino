
int humedad ;
int temperatura ;
int uv  ;
int co2  ;
int nox ;

//Variables de texto para transformar a las variables numéricas.
String h, t, u, c, n;

//Variable para construir mensaje con todas las variables de texto.
String mensaje;


void conversionString() {

  h = String(humedad);
  t = String(temperatura);
  u = String(uv);
  c = String(co2);
  n = String(nox);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  conversionString();
  mensaje = String(h + "/" + t + "/" + u + "/" + c + "/" + n + "/");
  Serial.println(mensaje);
  humedad = getRitmo();
  temperatura = getRitmo1();
  uv = getRitmo2();
  co2 = getRitmo3();
  nox = getRitmo4();
  delay(1000);

}

int getRitmo() {
  int valor;
  valor = random(15, 80);
  return valor;
}
int getRitmo1() {
  int valor1;
  valor1 = random(15, 40);
  return valor1;
}
int getRitmo2() {
  int valor2;
  valor2 = random(1, 6);
  return valor2;
}
int getRitmo3() {
  int valor3;
  valor3 = random(15, 60);
  return valor3;
}
int getRitmo4() {
  int valor4;
  valor4 = random(200, 500);
  return valor4;
}
