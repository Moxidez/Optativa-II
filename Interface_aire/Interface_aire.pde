////////Librerias///////
import controlP5.*;
ControlP5 cp5;
/////////////////////////
import processing.serial.*;
Serial port;
String mensaje = null;
//////////////////////////////
Textlabel myTextlabelA;
Textlabel myTextlabel1;
Textlabel myTextlabel2;
Textlabel myTextlabel3;
Textlabel myTextlabel4;
Textlabel myTextlabel5;
Textlabel myTextlabel6;
Textlabel myTextlabel7;
Textlabel myTextlabel8;
Textlabel myTextlabel9;
Textlabel myTextlabel0;

Textarea myTextarea;
Textarea myTextarea1;
Textarea myTextarea2;
Accordion accordion;

Slider slider;
Slider slider1;
Slider slider2;
Slider slider3;
Slider slider4;


Button boton;

Chart myChart;
Chart myChart1;
Chart myChart2;
Chart myChart3;
Chart myChart4;


PImage img;
PImage img1;



int c = 0;
int i=0;
int nox;
float hume;
float tem ;
float ruv ;
float co ;
float no;

Println console;

//////////Interface/////////////////
void setup() {
  size(1400, 800);

  //////////////////////////////////////
  img = loadImage("ibarra.jpg");
  img1 = loadImage("analisis.jpg");
  image(img, 700, 575, 250, 150);
  image(img1, 1000, 575, 250, 150); 
  ///////////////////////////////////
  //port = new Serial(this, "COM7", 9600);
  ////////////////////////////////////
  cp5 = new ControlP5(this);
  cp5.enableShortcuts();

  myTextlabelA = cp5.addTextlabel("label")
    .setText("Proyecto de embebidos 'Control de la calidad del aire'")
    .setPosition(275, 50)
    .setColorValue(0xff00ff00)
    .setFont(createFont("Georgia", 30))
    ;

  myTextarea = cp5.addTextarea("txt")
    .setPosition(700, 100)
    .setSize(500, 200)
    .setFont(createFont("Times New Roman", 18))
    .setLineHeight(14)
    .setColor(color(0))
    .setColorBackground(color(0, 100))
    .setColorForeground(color(255, 100));
  ;
  myTextarea.setText("Este proyecto se enfoca en la medición de la calidad del aire en 3 ambientes controlados por "
    +" mediante una red de sensores, que estará compuesta por módulos de comunicación, tarjetas "
    +" embebidas y otros componentes electrónicos, con el fin de adquirir la información que procesa"
    +" cada sensor para visualizarla en una interfaz y posteriormente visualizarlos en una interface gráfica"
    +" “Processing”, para obtener los datos que vamos a alojar en la tarjeta embebida Micro SD; como"
    +" parte primordial de la medición, es necesario identificar y entender el funcionamiento de los "
    +" diferentes sensores y su viabilidad para implementarlos en la red."
    );

  myTextlabel1 = cp5.addTextlabel("label1")
    .setText("Toma de Datos y Muestras Graficas")
    .setPosition(775, 300)
    .setColor(color(0))
    .setFont(createFont("Georgia", 15))
    ;

  cp5.addButton("CONECTAR")
    .setValue(0)
    .setPosition(700, 350)
    .setSize(200, 19)
    ;
  cp5.addButton("APAGAR")
    .setValue(100)
    .setPosition(950, 350)
    .setSize(200, 19)
    ;

  myTextlabel2 = cp5.addTextlabel("label2")
    .setText("Muestras Graficas")
    .setPosition(40, 100)
    .setColorValue(0)
    .setFont(createFont("Georgia", 15))
    ;

  myTextlabel3 = cp5.addTextlabel("label3")
    .setText("Ibarra Limpia")
    .setPosition(700, 550)
    .setColorValue(0)
    .setFont(createFont("Georgia", 15))
    ;


  myTextlabel4 = cp5.addTextlabel("label4")
    .setText("Analisis de datos")
    .setPosition(1000, 550)
    .setColorValue(0)
    .setFont(createFont("Georgia", 15))
    ;

  myTextlabel0 = cp5.addTextlabel("labe20")
    .setText("Resultados de los parametros recibidos")
    .setPosition(700, 400)
    .setColorValue(0)
    .setFont(createFont("Georgia", 15))
    ;
  myTextlabel0 = cp5.addTextlabel("labe21")
    .setText("Temperatura")
    .setPosition(700, 450)
    .setColorValue(0)
    .setFont(createFont("ARIAL", 10))
    ;
  myTextlabel0 = cp5.addTextlabel("labe22")
    .setText("Humedad")
    .setPosition(800, 450)
    .setColorValue(0)
    .setFont(createFont("ARIAL", 10))
    ;
  myTextlabel0 = cp5.addTextlabel("labe23")
    .setText("Rayos UV")
    .setPosition(900, 450)
    .setColorValue(0)
    .setFont(createFont("ARIAL", 10))
    ;
  myTextlabel0 = cp5.addTextlabel("labe24")
    .setText("NOX")
    .setPosition(1000, 450)
    .setColorValue(0)
    .setFont(createFont("ARIAL", 10))
    ;
  myTextlabel0 = cp5.addTextlabel("labe25")
    .setText("CO2")
    .setPosition(1100, 450)
    .setColorValue(0)
    .setFont(createFont("ARIAL", 10))
    ;
  myTextlabel5 = cp5.addTextlabel("label5")
    .setText("Muestras de datos en tiempo real")
    .setPosition(50, 525)
    .setColorValue(0)
    .setFont(createFont("Georgia", 15))
    ;

  myTextarea2 = cp5.addTextarea("txt2")
    .setPosition(50, 550)
    .setSize(450, 200)
    .setFont(createFont("", 10))
    .setColor(color(200))
    .setLineHeight(14)
    .setColorBackground(color(0, 100))
    .setColorForeground(color(255, 100));
  ;
  myTextlabelA = cp5.addTextlabel("labe111")
    .setText("la contaminacion se analiza por medio del cambio del fondo")
    .setPosition(700, 750)
    .setColorValue(0)
    .setFont(createFont("Georgia", 15))
    ;
  console = cp5.addConsole(myTextarea2);//

  gui();
}

////////////Programacion////////////
void draw() {
  background(0);     
  ////////////////////////////////////////////

  if (port.available()>0) {
    mensaje = port.readStringUntil('\n');
  }
  if (mensaje!=null) {
    int[] values = int(split(mensaje, '/'));
    //println(values[0] + " " + values[1]+ " " + values[2]+ " " + values[3]);

    ///////////////////////////////
    slider.setValue(values[1]);
    slider1.setValue(values[0]);
    slider2.setValue(values[2]);
    slider3.setValue(values[4]);
    slider4.setValue(values[3]);

    ///////////////////////////////
    myChart.push(values[1]);
    myChart1.push(values[0]);
    myChart2.push(values[2]);
    myChart3.push(values[4]);
    myChart4.push(values[3]);
    noStroke();
    hume = (values[0]);
    tem = (values[1]);
    ruv = (values[2]);
    co = (values[3]);
    no = (values[4]);
    println("Humedad = "+"  "+String.format("%.2f", hume)+"\t"+"  "+"Temperatura = "+"  "+String.format("%.2f", tem)+"\t"+"  "+"Rayos Uv  = "+"  "+String.format("%.2f", ruv)+"\t"+"  "+"CO2 = "+"  "+String.format("%.2f", co)+"\t"+"  "+"Nox = "+"  "+String.format("%.2f", no)+"\t");
    /////////////////////////////////
    if (values[5]==1) {
      PImage FONDO1;
      FONDO1= loadImage("1.jpg"); // PONER IMAGEN 
      image (FONDO1, 0, 0);
    } else
      if (values[5]==2) {
        PImage FONDO2;
        FONDO2= loadImage("2.jpg"); // PONER IMAGEN 
        image (FONDO2, 0, 0);
      } else
        if (values[5]==3 ) {
          PImage FONDO3;
          FONDO3= loadImage("3.jpg"); // PONER IMAGEN 
          image (FONDO3, 0, 0);
        }
    ///////////////////////////////
    if (values[0]>=15 && values[0]<=35) {
      fill(0, 255, 0);
      rect(700, 475, 75, 25);
    } else
      if (values[0]>=36 && values[0]<=55) {
        fill(0xffffa500);
        rect(700, 475, 75, 25);
      } else
        if (values[0]>=56 ) {
          fill(255, 0, 0);
          rect(700, 475, 75, 25);
        }
    ///////////////////////////////
    if (values[1]>=15 && values[1]<=24) {
      fill(0, 255, 0);
      rect(800, 475, 75, 25);
    } else
      if (values[1]>=25 && values[1]<=34) {
        fill(0xffffa500);
        rect(800, 475, 75, 25);
      } else
        if (values[1]>=35 ) {
          fill(255, 0, 0);
          rect(800, 475, 75, 25);
        }
    ///////////////////////////////
    if (values[2]>=1 && values[2]<=2) {
      fill(0, 255, 0);
      rect(900, 475, 75, 25);
    } else
      if (values[2]>=3 && values[2]<=4) {
        fill(0xffffa500);
        rect(900, 475, 75, 25);
      } else
        if (values[2]>=5 ) {
          fill(255, 0, 0);
          rect(900, 475, 75, 25);
        }
    ///////////////////////////////
    if (values[3]>=0 && values[3]<=100) {
      fill(0, 255, 0);
      rect(1000, 475, 75, 25);
    } else
      if (values[3]>=101 && values[3]<=200) {
        fill(0xffffa500);
        rect(1000, 475, 75, 25);
      } else
        if (values[3]>=201 ) {
          fill(255, 0, 0);
          rect(1000, 475, 75, 25);
        }
    ///////////////////////////////
    if (values[4]>=0 && values[4]<=50) {
      fill(0, 255, 0);
      rect(1100, 475, 75, 25);
    } else
      if (values[4]>=51 && values[4]<=100) {
        fill(0xffffa500);
        rect(1100, 475, 75, 25);
      } else
        if (values[4]>=101) {
          fill(255, 0, 0);
          rect(1100, 475, 75, 25);
        }
    ///////////////////////////////
    delay(1000);
    ///////////////////////////////
  }
}



/////////GUI- metodo grafico /////////

void gui() {

  cp5 = new ControlP5(this);

  // Temperatura//
  Group g1 = cp5.addGroup("                                                                    Temperatura")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(200)
    ;

  myTextlabel6 = cp5.addTextlabel("label3")
    .setText("Muestra de Temperatura")
    .setPosition(10, 10)
    .setColorValue(0xffffffff)
    .setFont(createFont("Georgia", 15))
    .moveTo(g1);
  ;

  slider=cp5.addSlider("Temperatura_C")
    .setPosition(10, 35)
    .setSize(100, 20)
    .setRange(0, 100)
    .setValue(0)
    .moveTo(g1)
    .setColorForeground(color(random(255), random(255), random(255)))
    .setSliderMode(Slider.FLEXIBLE)
    ;

  myChart = cp5.addChart("Osciloscopio Temperatura")
    .setPosition(10, 75)
    .setSize(225, 75)
    .setRange(0, 50)
    .setView(Chart.BAR_CENTERED) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .moveTo(g1)
    ;
  myChart.addDataSet("incoming");
  myChart.setData("incoming", new float[100]);
  ;

  // Humedad //
  Group g2 = cp5.addGroup("                                                                      Humedad")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(200)
    ;
  myTextlabel7 = cp5.addTextlabel("label4")
    .setText("Muestra De Humedad")
    .setPosition(10, 10)
    .setColorValue(0xffffffff)
    .setFont(createFont("Georgia", 15))
    .moveTo(g2);
  ;
  slider1=cp5.addSlider("Control Humedad")
    .setPosition(10, 35)
    .setSize(100, 20)
    .setRange(0, 100)
    .setValue(0)
    .moveTo(g2)
    .setColorForeground(color(random(255), random(255), random(255)))
    .setSliderMode(Slider.FLEXIBLE)
    ;

  myChart1 = cp5.addChart("Osciloscopio Humedad")
    .setPosition(10, 75)
    .setSize(225, 75)
    .setRange(0, 100)
    .setView(Chart.BAR_CENTERED) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .moveTo(g2)
    ;
  myChart1.addDataSet("incoming");
  myChart1.setData("incoming", new float[100]);
  ;

  // Rayos UV //
  Group g3 = cp5.addGroup("                                                                      Rayos UV")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(200)
    ;
  myTextlabel8 = cp5.addTextlabel("label5")
    .setText("Muestra de Rayos UV")
    .setPosition(10, 10)
    .setColorValue(0xffffffff)
    .setFont(createFont("Georgia", 15))
    .moveTo(g3);
  ;
  slider2=cp5.addSlider("Control UV")
    .setPosition(10, 35)
    .setSize(100, 20)
    .setRange(0, 30)
    .setValue(0)
    .moveTo(g3)
    .setColorForeground(color(random(255), random(255), random(255)))
    .setSliderMode(Slider.FLEXIBLE)
    ;

  myChart2 = cp5.addChart("Osciloscopio Rayos UV")
    .setPosition(10, 75)
    .setSize(225, 75)
    .setRange(0, 30)
    .setView(Chart.BAR_CENTERED) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .moveTo(g3)
    ;
  myChart2.addDataSet("incoming");
  myChart2.setData("incoming", new float[100]);
  ;
  //Nox//
  Group g4 = cp5.addGroup("                                                                      Nox")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(200)
    ;
  myTextlabel9 = cp5.addTextlabel("label6")
    .setText("Muestra de NOX")
    .setPosition(10, 10)
    .setColorValue(0xffffffff)
    .setFont(createFont("Georgia", 15))
    .moveTo(g4);
  ;
  slider3=cp5.addSlider("Control Nox")
    .setPosition(10, 35)
    .setSize(100, 20)
    .setRange(0, 150)
    .setValue(0)
    .moveTo(g4)
    .setColorForeground(color(random(255), random(255), random(255)))
    .setSliderMode(Slider.FLEXIBLE)
    ;
  myChart3 = cp5.addChart("Osciloscopio Nox")
    .setPosition(10, 75)
    .setSize(225, 75)
    .setRange(0, 150)
    .setView(Chart.BAR_CENTERED) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .moveTo(g4)
    ;
  myChart3.addDataSet("incoming");
  myChart3.setData("incoming", new float[100]);
  ;
  //CO2//
  Group g5 = cp5.addGroup("                                                                      Cotrol CO2")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(200)
    ;
  myTextlabel0 = cp5.addTextlabel("label7")
    .setText("Muestra de CO")
    .setPosition(10, 10)
    .setColorValue(0xffffffff)
    .setFont(createFont("Georgia", 15))
    .moveTo(g5);
  ;
  slider4=cp5.addSlider("CO2")
    .setPosition(10, 35)
    .setSize(100, 20)
    .setRange(0, 250)
    .setValue(0)
    .moveTo(g5)
    .setColorForeground(color(random(255), random(255), random(255)))
    .setSliderMode(Slider.FLEXIBLE)
    ;
  myChart4 = cp5.addChart("Osciloscopio CO2")
    .setPosition(10, 75)
    .setSize(225, 75)
    .setRange(0, 250)
    .setView(Chart.BAR_CENTERED) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
    .setStrokeWeight(1.5)
    .setColorCaptionLabel(color(255))
    .moveTo(g5)
    ;
  myChart4.addDataSet("incoming");
  myChart4.setData("incoming", new float[100]);
  ;

  // create a new accordion
  // add g1, g2, and g3 to the accordion.
  accordion = cp5.addAccordion("acc")
    .setPosition(40, 150)
    .setSize(50, 50)
    .setBarHeight(500)
    .setWidth(450)
    .addItem(g1)
    .addItem(g2)
    .addItem(g3)
    .addItem(g4)
    .addItem(g5)
    ;

  accordion.setCollapseMode(Accordion.SINGLE);
}


void keyPressed() {
  switch(key) {
    case('1'):
    console.pause();
    break;
    case('2'):
    console.play();
    break;
    case('3'):
    console.setMax(8);
    break;
    case('4'):
    console.setMax(-1);
    break;
    case('5'):
    console.clear();
    break;
  }
}

public void CONECTAR() {
  port = new Serial(this, "COM7", 9600);
  console.play();
}
public void APAGAR() {
  port.clear();
  port.stop();
  console.pause();
  console.clear();
  accordion.close();
  accordion.update();
  background(0);
  fill(0);
  rect(700, 475, 75, 25);
}