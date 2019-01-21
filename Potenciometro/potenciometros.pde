import processing.serial.*;
import controlP5.*;
ControlP5 cp5;
Serial Puerto;    // El puerto serial
int xPos = 20;     // Posicion horizontal del grafico
float inByte = 0; // Variable de almacenamiento para la lectura del potenciometro 
 
void setup () {
  
  cp5=new ControlP5(this);
  size(600, 500);   // Tamano de la pantalla:
   
  println(Serial.list()); // Muestra el puerto conectado
  Puerto = new Serial(this, Serial.list()[0], 9600); // En el lugar de [0], debe ir el puerto
                                                     // al que esta conectado el Arduino
  Puerto.bufferUntil('\n'); // Lee el puerto serial hasta encontrar un LF (Line feed)
  background(100);          // Fondo de pantalla
  rect(20,20,400,400);
  
  cp5.addSlider("R")
   .setPosition(500,200)
   .setSize(50,200)
   .setRange(0,200)
   .setColorActive(color(200,0,0))
   .setColorBackground(color(100,0,0))
   .setColorForeground(color(200,0,0))
   .setValue(100);
 
}
 
void draw () {
  
  cp5.getController("R").setValue(inByte);
  
  stroke(127, 34, 255); // Color de la linea 
  line(xPos, 418, xPos, 418 - inByte); // Dibuja la linea
 
  if (xPos >= 422) { // Verifica que hemos llegado al limite de pantalla
    xPos = 20;          // Reseteo de la posicion a la posicion inicial
    background(100);   // Fondo de pantalla
       fill(255);
  rect(20,20,400,400);
   
  } 
  else { xPos++; } // Nos movemos en la posicion horizontal 
}
 
void serialEvent (Serial Puerto) {
  String inString = Puerto.readStringUntil('\n'); // Lee la cadena hasta encontrar un enter
 
  if (inString != null) {
    inString = trim(inString); // Se quita los espacios en blanco:
    inByte = float(inString);  // Convierte en flotante el String leido
    println(inByte);           // Muestra el dato convertido
    inByte = map(inByte, 0, 1024, 0, 395); // Convierte el dato en la altura de salida
  }
}