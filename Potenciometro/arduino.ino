void setup() {
  Serial.begin(9600); // Inicia la comunicación Serial a 9600 bps
}
 
void loop() {
  Serial.println(analogRead(A0)); // Envia el valor de la entrada analogica:
  delay(10); // Espera un bit para la conversion analoga - digital para estabilizar despues de leer


}
