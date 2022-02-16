// Timbre Automatizado para Colegio, empresa, cultivo, etc...  By: http://dinastiatecnologica.com (El Profe Garcia)
// Con Arduino UNO,(RTC), Modulo Rele, Modulo I2C para LCD 2x16 
// Conexion i2C :Arduino UNO  SCL-> A5   SDA->A4  VCC->5V  GND->GND
// Conexion RTC :Arduino UNO    GND->GND VCC->5V SCL-> SCL  SDA->SDA los dos pines despues del ...12,13,GND,AREF,SDA,SCL
// Conexion Rele:Arduino UNO GND->GND  VCC->5V  IN->7
// NOTA: se debe cargar dos veces este programa 1. Con la linea  RTC.adjust(DateTime(__DATE__, __TIME__)); 
//                                              2. Sin esa linea

#include <Wire.h> 
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // inicializa la interfaz I2C del LCD 16x2
RTC_DS1307 RTC;                   // inicializa el modulo RTC
int r_diaSemana;             // almacena el resultado del dia de la semana calculado
int entrada1 = 1;          //creamos una variable de tipo entero para que el arduino reconozca

int entrada4 = 4;
int entrada5 = 5;
int valor_entrada1 = 0;
int valor_entrada2 = 0;
int valor_entrada3 = 0;
int valor_entrada4 = 0;
int valor_entrada5 = 0;
const int pcdani1 = 6;// Pin 6 encargado de activar luz pcdani1, se conecta al Rele 8
const int pcdani2 = 7;// Pin 7 encargado de activar luz pcdani2, se conecta al Rele 7
const int luztaller = 8;// Pin 8 encargado de activar luz taller1, se conecta al Rele 6
const int timbre = 9;// Pin 9 encargado de activar el timbre, se conecta al Rele 5
const int luzestanteria = 10;// Pin 10 encargado de activar el luz estanterias, se conecta al Rele 4
const int luzmostrador = 11;// Pin 11 encargado de activar luz del mostrador y cartel interior, se conecta al Rele3
const int luznegocio = 12;// Pin 12 encargado de activar luz negocio, se conecta al Rele 2
const int cartelexterior = 13;// Pin 13 encargado de activar el cartel exterior, se conecta al Rele 1


unsigned long previousMillis = 0; //Variable que indica el tiempo que ha pasado en ms
const long interval = 1000;       //Variable asignado para el intervalo de tiempo, es 1s
double voltajeInst;             //Variable para la corriente instantanea
double voltajeMax;              //Variable para la corriente máxima
double voltajeMin;              //Variable para la corriente mínima
int potencia;                     //Variable para guardar la potencia
float  Irms;                      //Variable para la corriente rms
int nMuestras=500;                //Numero de muestras realizadas en una medición


unsigned long previousMillis2 = 0; //Variable que indica el tiempo que ha pasado en ms
const long interval2 = 1000;       //Variable asignado para el intervalo de tiempo, es 1s
double voltajeInst2;             //Variable para la corriente instantanea
double voltajeMax2;              //Variable para la corriente máxima
double voltajeMin2;              //Variable para la corriente mínima
int potencia2;                     //Variable para guardar la potencia
float  Irms2;                      //Variable para la corriente rms
int nMuestras2=500;                //Numero de muestras realizadas en una medición


unsigned long previousMillis3 = 0; //Variable que indica el tiempo que ha pasado en ms
const long interval3 = 1000;       //Variable asignado para el intervalo de tiempo, es 1s
double voltajeInst3;             //Variable para la corriente instantanea
double voltajeMax3;              //Variable para la corriente máxima
double voltajeMin3;              //Variable para la corriente mínima
int potencia3;                     //Variable para guardar la potencia
float  Irms3;                      //Variable para la corriente rms
int nMuestras3=500;                //Numero de muestras realizadas en una medición
double Voltage = 0;

unsigned long previousMillis4 = 0; //Variable que indica el tiempo que ha pasado en ms
const long interval4 = 1000;       //Variable asignado para el intervalo de tiempo, es 1s
double voltajeInst4;             //Variable para la corriente instantanea
double voltajeMax4;              //Variable para la corriente máxima
double voltajeMin4;              //Variable para la corriente mínima
int potencia4;                     //Variable para guardar la potencia
float  Irms4;                      //Variable para la corriente rms
int nMuestras4=500;                //Numero de muestras realizadas en una medición




int segundo;
int minuto;
int hora;
int estado=0;
int retardo=100;
int analogo=0;



 

//////////////////////////////// Horario 1 /////////////////////////
// Hora en la que suena el timbre escrito  h1=Hora, m1=Minutos, s1=Segundos
// Cuando no se programa ninguna hora se debe dejar escrito el numero 99  
// se pueden programar 16 timbres por cada horario, _c1 indica que es el horario 1
int h1_c1=03;    int m1_c1=53;    int s1_c1=0;      // luz teclado
int h2_c1=2;    int m2_c1=0;    int s2_c1=0;      //off      
int h3_c1=03;    int m3_c1=16;    int s3_c1=0;      // nada
int h4_c1=99;    int m4_c1=0;    int s4_c1=0;
int h5_c1=20;    int m5_c1=18;    int s5_c1=0;      // taller
int h6_c1=20;    int m6_c1=26;    int s6_c1=0;
int h7_c1=2;    int m7_c1=12;    int s7_c1=0;     // luz blanca pc dani 8:15
int h8_c1=7;    int m8_c1=30;   int s8_c1=0;      //off  12:00
int h9_c1=7;     int m9_c1=1;   int s9_c1=0;      // timbre 8:30 
int h10_c1=12;   int m10_c1=30;  int s10_c1=0;     //off  12:00
int h11_c1=8;    int m11_c1=0;   int s11_c1=0;     // luz general taller 8:15 
int h12_c1=12;   int m12_c1=30;  int s12_c1=0;     //off  12:00
int h13_c1=0;   int m13_c1=59;  int s13_c1=0;     // nada
int h14_c1=99;   int m14_c1=53;  int s14_c1=0;     
int h15_c1=1;   int m15_c1=18;   int s15_c1=0;     // cartel exterior 19:00
int h16_c1=00;   int m16_c1=00;  int s16_c1=0;     //off  00:00


//////////////////////////////// Horario 2 /////////////////////////

int h1_c2=99;    int m1_c2=0;    int s1_c2=0;      //// luz teclado
int h2_c2=99;    int m2_c2=0;    int s2_c2=0;      //off      
int h3_c2=99;    int m3_c2=0;    int s3_c2=0;      //// nada
int h4_c2=99;    int m4_c2=0;    int s4_c2=0;
int h5_c2=99;    int m5_c2=0;    int s5_c2=0;      //// nada
int h6_c2=99;    int m6_c2=0;    int s6_c2=0;
int h7_c2=16;    int m7_c2=0;    int s7_c2=0;      // luz blanca pc dani 16:00
int h8_c2=19;    int m8_c2=30;   int s8_c2=0;      //off  19:30
int h9_c2=3;    int m9_c2=29;   int s9_c2=0;      // timbre 16:00 
int h10_c2=19;   int m10_c2=30;  int s10_c2=0;     //off  19:30
int h11_c2=16;   int m11_c2=00;  int s11_c2=0;     //// luz general taller 16:00 
int h12_c2=19;   int m12_c2=30;  int s12_c2=0;     //off  19:30
int h13_c2=99;   int m13_c2=0;   int s13_c2=0;     // nada
int h14_c2=99;   int m14_c2=0;   int s14_c2=0;     
int h15_c2=99;   int m15_c2=0;   int s15_c2=0;     // cartel exterior 19:00
int h16_c2=99;   int m16_c2=0;   int s16_c2=0;     //off  00:00

//////////////////////////////// Horario 3 /////////////////////////

int h1_c3=7;   int m1_c3=0;   int s1_c3=0;
int h2_c3=8;   int m2_c3=30;  int s2_c3=0;
int h3_c3=9;   int m3_c3=0;   int s3_c3=0;
int h4_c3=9;   int m4_c3=30;  int s4_c3=0;
int h5_c3=9;   int m5_c3=45;  int s5_c3=0;
int h6_c3=10;  int m6_c3=15;  int s6_c3=0;
int h7_c3=10;  int m7_c3=45;  int s7_c3=0;
int h8_c3=11;  int m8_c3=0;   int s8_c3=0;
int h9_c3=11;  int m9_c3=30;  int s9_c3=0;
int h10_c3=12; int m10_c3=0;  int s10_c3=0;
int h11_c3=99; int m11_c3=0;  int s11_c3=0;
int h12_c3=99; int m12_c3=0;  int s12_c3=0;
int h13_c3=99; int m13_c3=0;  int s13_c3=0;
int h14_c3=99; int m14_c3=0;  int s14_c3=0;
int h15_c3=99; int m15_c3=0;  int s15_c3=0;
int h16_c3=99; int m16_c3=0;  int s16_c3=0;
 
////////////////////////////////// Void Setup() ///////////

void setup () { 
  
 pinMode(entrada1, INPUT);  // declaramos el pin como entrada       
 
 pinMode(entrada4, INPUT);
 pinMode(entrada5, INPUT);
 pinMode(pcdani1, OUTPUT);                    // Configura como salida el pin 6
 pinMode(pcdani2, OUTPUT);                    // Configura como salida el pin 7
 pinMode(luztaller, OUTPUT);                  // Configura como salida el pin 8
 pinMode(timbre, OUTPUT);                     // Configura como salida el pin 9
 pinMode(luzestanteria, OUTPUT);              // Configura como salida el pin 10
 pinMode(luzmostrador, OUTPUT);               // Configura como salida el pin 11
 pinMode(luznegocio, OUTPUT);                 // Configura como salida el pin 12
 pinMode(cartelexterior, OUTPUT);             // Configura como salida el pin 13
 Wire.begin();                               
 RTC.begin();                                 // Inicia la comunicaci¢n con el RTC

  
 RTC.adjust(DateTime(__DATE__, __TIME__));  // Lee la fecha y hora del PC (Solo en la primera carga)
                                              // el anterior se usa solo en la configuracion inicial luego se pone como comentario
                                              // y se vuelve a cargar el programa sin esa linea.
 Serial.begin(9600);                          // Establece la velocidad de datos del puerto serie a 9600
 lcd.init();
 lcd.backlight();                             // Coloca luz de fondo al LCD
 lcd.clear();                                 // Borra el  LCD
} 
////////////////////////////////// Void loop() ///////////
void loop(){
  
   
   
   
   
   unsigned long currentMillis = millis(); //Se asigna a esa variable el tiempo que esta pasando
  //Se inicia las variables iniciales para la corriente máxima y mínima
   voltajeMax=0.00;                        
    voltajeMin=5.00;

  //Se toma una medición, para ello se realizan 500 muestras
for(int a=0; a<nMuestras2; a++){           //En este ciclo for se realizan las 500 muestras

    voltajeInst=5.00/1023*analogRead(A0);//Se normaliza el valor obtenido desde el sensor
    
  if(voltajeInst>=voltajeMax){        //Si la corriente instantanea es mayor a la corriente máxima...
    voltajeMax=voltajeInst;           //Se asigna ese valor a la corriente máxima
  }
  if(voltajeInst<=voltajeMin){        //Si la corriente instantanea es mayor a la corriente mínima...
    voltajeMin=voltajeInst;           //Se asigna ese valor a la corriente mínima
  }
}
  float Vpp=voltajeMax-voltajeMin;    //Se halla la corriente pico a pico; 
  //Se obtiene la corriente rms por la siguiente formula, la resta es una tolerancia
  Irms=(5.3568*Vpp)-0.15;              
  if(Irms<=0){                            //Si la corriente rms es menor o igual a 0...
    Irms=0;                               //Se le asigna 0
  }
  potencia=Irms*220;                      //Para hallar la potencia se suma con el voltaje rms
  
 

  //Se revisa si el tiempo transcurrido es mayor o igual a 1 segundo
 if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;       //Se asigna el valor del tiempo actual
  

}


  unsigned long currentMillis2 = millis(); //Se asigna a esa variable el tiempo que esta pasando
  //Se inicia las variables iniciales para la corriente máxima y mínima
   voltajeMax2=0.00;                        
    voltajeMin2=5.00;

  //Se toma una medición, para ello se realizan 500 muestras
for(int a=0; a<nMuestras2; a++){           //En este ciclo for se realizan las 500 muestras

    voltajeInst2=5.00/1023*analogRead(A1);//Se normaliza el valor obtenido desde el sensor
    
  if(voltajeInst2>=voltajeMax2){        //Si la corriente instantanea es mayor a la corriente máxima...
    voltajeMax2=voltajeInst2;           //Se asigna ese valor a la corriente máxima
  }
  if(voltajeInst2<=voltajeMin2){        //Si la corriente instantanea es mayor a la corriente mínima...
    voltajeMin2=voltajeInst2;           //Se asigna ese valor a la corriente mínima
  }
}
  float Vpp2=voltajeMax2-voltajeMin2;    //Se halla la corriente pico a pico; 
  //Se obtiene la corriente rms por la siguiente formula, la resta es una tolerancia
  Irms2=(5.3568*Vpp)-0.15;              
  if(Irms2<=0){                            //Si la corriente rms es menor o igual a 0...
    Irms2=0;                               //Se le asigna 0
  }
  potencia2=Irms2*220;                      //Para hallar la potencia se suma con el voltaje rms
  
 

  //Se revisa si el tiempo transcurrido es mayor o igual a 1 segundo
 if (currentMillis2 - previousMillis2 >= interval) {
    previousMillis2 = currentMillis2;       //Se asigna el valor del tiempo actual
  

} 
 


  unsigned long currentMillis3 = millis(); //Se asigna a esa variable el tiempo que esta pasando
  //Se inicia las variables iniciales para la corriente máxima y mínima
   voltajeMax3=0.00;                        
    voltajeMin3=5.00;

  //Se toma una medición, para ello se realizan 500 muestras
for(int a=0; a<nMuestras3; a++){           //En este ciclo for se realizan las 500 muestras

    voltajeInst3=5.00/1023*analogRead(A2);//Se normaliza el valor obtenido desde el sensor
    
  if(voltajeInst3>=voltajeMax3){        //Si la corriente instantanea es mayor a la corriente máxima...
    voltajeMax3=voltajeInst3;           //Se asigna ese valor a la corriente máxima
  }
  if(voltajeInst3<=voltajeMin3){        //Si la corriente instantanea es mayor a la corriente mínima...
    voltajeMin3=voltajeInst3;           //Se asigna ese valor a la corriente mínima
  }
}
  float Vpp3=voltajeMax3-voltajeMin3;    //Se halla la corriente pico a pico; 
  //Se obtiene la corriente rms por la siguiente formula, la resta es una tolerancia
  Irms3=(5.3568*Vpp)-0.15;              
  if(Irms3<=0){                            //Si la corriente rms es menor o igual a 0...
    Irms3=0;                               //Se le asigna 0
  }
  potencia3=Irms3*220;                      //Para hallar la potencia se suma con el voltaje rms
  
 

  //Se revisa si el tiempo transcurrido es mayor o igual a 1 segundo
 if (currentMillis3 - previousMillis3 >= interval) {
    previousMillis3 = currentMillis3;       //Se asigna el valor del tiempo actual
  

} 
  


 unsigned long currentMillis4 = millis(); //Se asigna a esa variable el tiempo que esta pasando
  //Se inicia las variables iniciales para la corriente máxima y mínima
   voltajeMax4=0.00;                        
    voltajeMin4=5.00;

  //Se toma una medición, para ello se realizan 500 muestras
for(int a=0; a<nMuestras4; a++){           //En este ciclo for se realizan las 500 muestras

    voltajeInst4=5.00/1023*analogRead(A3);//Se normaliza el valor obtenido desde el sensor
    
  if(voltajeInst4>=voltajeMax4){        //Si la corriente instantanea es mayor a la corriente máxima...
    voltajeMax4=voltajeInst4;           //Se asigna ese valor a la corriente máxima
  }
  if(voltajeInst4<=voltajeMin4){        //Si la corriente instantanea es mayor a la corriente mínima...
    voltajeMin4=voltajeInst4;           //Se asigna ese valor a la corriente mínima
  }
}
  float Vpp4=voltajeMax4-voltajeMin4;    //Se halla la corriente pico a pico; 
  //Se obtiene la corriente rms por la siguiente formula, la resta es una tolerancia
  Irms4=(5.3568*Vpp)-0.15;              
  if(Irms4<=0){                            //Si la corriente rms es menor o igual a 0...
    Irms4=0;                               //Se le asigna 0
  }
  potencia4=Irms4*220;                      //Para hallar la potencia se suma con el voltaje rms
  
 

  //Se revisa si el tiempo transcurrido es mayor o igual a 1 segundo
 if (currentMillis4 - previousMillis4 >= interval) {
    previousMillis4 = currentMillis4;       //Se asigna el valor del tiempo actual
  

} 
 

 if(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado== 'a'){                    // on/off de los pin 13 al pin 6
       digitalWrite(13,HIGH);
 }
 if(estado== 'b' ){
       digitalWrite(13,LOW);
 }
 if(estado== 'c'){ 
       digitalWrite(12,HIGH);
 }
 if(estado== 'd' ){
       digitalWrite(12,LOW);
 }
 if(estado== 'e'){ 
       digitalWrite(11,HIGH);
 }
 if(estado== 'f' ){
       digitalWrite(11,LOW);
 }
 if(estado== 'g' ){
       digitalWrite(10,HIGH);
 }
 if(estado== 'h' ){
       digitalWrite(10,LOW);
 }
 if(estado== 'i' ){
        digitalWrite(9,HIGH);
 }
 if(estado== 'j' ){
       digitalWrite(9,LOW);
      }
 if(estado== 'k' ){
        digitalWrite(8,HIGH);
 }
 if(estado== 'l' ){
      digitalWrite(8,LOW);
 }
 if(estado== 'm' ){
       digitalWrite(7,HIGH);
 }
 if(estado== 'n' ){
       digitalWrite(7,LOW);
 }
 if(estado== 'o' ){
      digitalWrite(6,HIGH);
 }
 if(estado== 'p' ){
       digitalWrite(6,LOW);
 }
 
 
 
 
 
 
 
 
 
 valor_entrada1 = Irms; // guardamos la lectura digital en la variable(valor_entrada1) 
 valor_entrada2 = analogRead(A1);
 valor_entrada3 = analogRead(A2);
 valor_entrada4 = analogRead(A3);
 valor_entrada5 = analogRead(A4);
  
 DateTime now = RTC.now();          // Obtiene la fecha y hora del RTC

 int contacto4 = digitalRead(entrada4);    //Lee el valor de los contactos para escoger el horario
 
 int contacto5 = digitalRead(entrada5);    // contacto que activa o desactiva los fines de semana

 Serial.print(now.year(), DEC);  // A§o
 Serial.print('/');
 Serial.print(now.month(), DEC); // Mes
 Serial.print('/');
 Serial.print(now.day(), DEC);   // Dia
 Serial.print(' ');
 Serial.print(now.hour(), DEC);  // Horas
 Serial.print(':');
 Serial.print(now.minute(), DEC); // Minutos
 Serial.print(':');
 Serial.print(now.second(), DEC); // Segundos
 Serial.println();
 lcd.setCursor(0,0);
 lcd.print("D:");
 lcd.print(now.year(), DEC);
 lcd.print("/");
 lcd.print(now.month(), DEC);
 lcd.print("/");
 lcd.print(now.day(), DEC);
 lcd.print(" ");
 lcd.setCursor(0,1);
 lcd.print("T: ");
 lcd.print(now.hour(), DEC);
 lcd.print(":");
 lcd.print(now.minute(), DEC);
 lcd.print(":");
 lcd.print(now.second(), DEC);
 segundo=now.second();
 minuto=now.minute();
 hora=now.hour();

 if (contacto4 <= HIGH){     // si el contacto 4 esta desactivado, despliega -e- entre semana funciona el timbre
    lcd.setCursor(12,0);
    lcd.print("e");
    Serial.print("-e-"); 
 }
 else {                      // si el contacto 4 esta activado, despliega -F- el Fin de semana funciona el timbre
   lcd.setCursor(12,0);
   lcd.print("F");
   Serial.print("-F-");
 }
 
 int r_diaSemana=dia_de_semana();   // llama a la funcion que calcula el dia de la semana y lo almacena en r_diaSemana
 
 if ((r_diaSemana == 6 || r_diaSemana == LOW)&&(contacto5 == HIGH)){  // si el contacto4 de Fin de semana esta apagado y es fin de semana no hace nada
 }
 else {
   if (contacto4 >= HIGH)   // Si el contacto 1 esta activo (Horario 1)    
     horario_1();           // llama a la funcion que activa el horario 1

 }
 
 digitalWrite(timbre, LOW);     // apaga el timbre
 delay(500);                    // La informaci¢n se actualiza cada 1/2 seg.
 lcd.setCursor(9,0);            // Borra parte de la pantalla del LCD
 lcd.print("                ");
 lcd.setCursor(8,1);
 lcd.print("                ");

 
}   



//////////////////////////////// Fin del void loop(), inician las Funciones/////////////////////////

/////////////////////////////// Funcion que activa el Timbre //////////////////////////////////
 
void activar_pcdani1(){
    digitalWrite(pcdani1, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("LUZ ON  ");
    Serial.println("Timbre Activo");
     
}
void desactivar_pcdani1(){
    digitalWrite(pcdani1, LOW); 
    lcd.setCursor(0,0);
    lcd.print("LUZ APAGADA  ");
    Serial.println(" INICTIVO ");
     
}

void comprobando_activar_pcdani2(){
 if (Voltage == 0.51)   // Si el valor_entrada1 esta activo    
     activar_pcdani2();           // llama a la funcion que activa el activar_pcdani2
     }

void activar_pcdani2(){
    digitalWrite(pcdani2, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("LUZ ON  ");
    Serial.println("Activo");
     
}

void comprobando_desactivar_pcdani2(){
 if (valor_entrada1 == 1)   // Si el valor_entrada1 esta activo    
     desactivar_pcdani2();           // llama a la funcion que activa el desactivar_pcdani2
     }
void desactivar_pcdani2(){
    digitalWrite(pcdani2, LOW); 
    lcd.setCursor(0,0);
    lcd.print("LUZ APAGADA  ");
    Serial.println(" INICTIVO ");
     
}

void comprobando_activar_luztaller(){
 if (Irms == 0.00)   // Si el valor_entrada2 esta activo    
     activar_luztaller();           // llama a la funcion que activa el activar_luztaler
     }
void activar_luztaller(){
    digitalWrite(luztaller, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("LUZ ON  ");
    Serial.println("Activo");
     
}

void comprobando_desactivar_luztaller(){
 if (Irms2 >= 0.00)                // Si el valor_entrada2 esta activo    
     desactivar_luztaller();             // llama a la funcion que activa el desactivar_luztaller
     }
void desactivar_luztaller(){
    digitalWrite(luztaller, LOW); 
    lcd.setCursor(0,0);
    lcd.print("LUZ APAGADA  ");
    Serial.println(" INICTIVO ");
     
}

void comprobando_activar_timbre(){
 if (valor_entrada3 == 0)               // Si el valor_entrada3 esta activo    
     activar_timbre();                  // llama a la funcion que activa el activar_timbre
     } 
void activar_timbre(){
    digitalWrite(timbre, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("TIMPRE PRENDIDO  ");
    Serial.println("Activo");
     
}

void comprobando_desactivar_timbre(){
 if (valor_entrada3 == 1)               // Si el valor_entrada3 esta activo    
     desactivar_timbre();               // llama a la funcion que activa el desactivar_timbre
     }
void desactivar_timbre(){
    digitalWrite(timbre, LOW); 
    lcd.setCursor(0,0);
    lcd.print("TIMBRE APAGADA  ");
    Serial.println(" INICTIVO ");
     
}

void activar_luzestanteria(){
    digitalWrite(luzestanteria, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("LUZ ON  ");
    Serial.println("Activo");
     
}
void desactivar_luzestanteria(){
    digitalWrite(luzestanteria, LOW); 
    lcd.setCursor(0,0);
    lcd.print("LUZ APAGADA  ");
    Serial.println(" INICTIVO ");
     
}
void activar_luzmostrador(){
    digitalWrite(luzmostrador, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("LUZ ON  ");
    Serial.println("Activo");
     
}
void desactivar_luzmostrador(){
    digitalWrite(luzmostrador, LOW); 
    lcd.setCursor(0,0);
    lcd.print("LUZ APAGADA  ");
    Serial.println(" INICTIVO ");
     
}
void activar_luznegocio(){
    digitalWrite(luznegocio, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("LUZ ON  ");
    Serial.println("Activo");
     
}
void desactivar_luznegocio(){
    digitalWrite(luznegocio, LOW); 
    lcd.setCursor(0,0);
    lcd.print("LUZ APAGADA  ");
    Serial.println(" INICTIVO ");
     
}
void comprobando_activar_cartelexterior(){
 if (valor_entrada4 >= 1000)               // Si el valor_entrada4 esta activo    
     activar_cartelexterior();                  // llama a la funcion que activa el activar_cartelexterior
     }
void activar_cartelexterior(){
    digitalWrite(cartelexterior, HIGH); 
    lcd.setCursor(0,0);
    lcd.print("LUZ ON  ");
    Serial.println("Activo");
     
}

void comprobando_desactivar_cartelexterior(){
 if (valor_entrada4 >= 1000)               // Si el valor_entrada4 esta activo    
     desactivar_cartelexterior();                  // llama a la funcion que activa el desactivar_cartelexterior
     }
void desactivar_cartelexterior(){
    digitalWrite(cartelexterior, LOW); 
    lcd.setCursor(0,0);
    lcd.print("LUZ APAGADA  ");
    Serial.println(" INICTIVO ");
     
}

/////////////////////////////// Calcula el dia de la Semana //////////////////////////////////
int dia_de_semana(){
 // Encuentar el dia de la semana de una fecha
 int n_dia;
 int r_dia;
 int n_mes;
 int t_mes;
 int n_anno;
 int d_anno;
 int t_siglo=6;

 DateTime now = RTC.now(); //fecha y hora del RTC
 lcd.setCursor(13,1);

 n_anno=(now.year()-2000);
 d_anno=n_anno/4;
 n_dia=now.day();
 n_mes=now.month();

 switch (n_mes) {
    case 1:
      t_mes=0;
      break;
    case 2:
      t_mes=3;
      break;
    case 3:
      t_mes=3;
      break;
    case 4:
      t_mes=6;
      break;
    case 5:
      t_mes=1;
      break;
    case 6:
      t_mes=4;
      break;
    case 7:
      t_mes=6;
      break;
    case 8:
      t_mes=2;
      break;
    case 9:
      t_mes=5;
      break;
    case 10:
      t_mes=0;
      break;
    case 11:
      t_mes=3;
      break;
    case 12:
      t_mes=5;
      break;
    default: 
      t_mes=t_mes;
    break;
 }

 r_dia=n_dia+t_mes+n_anno+d_anno+t_siglo;
 r_dia = r_dia % 7;

 switch (r_dia) {
    case 1:
       lcd.print("Lun");
        Serial.print(" Lun ");
      break;
      case 2:
       lcd.print("Mar");
       Serial.println(" Mar ");
      break;
      case 3:
       lcd.print("Mie");
       Serial.print(" Mie ");
      break;
      case 4:
       lcd.print("Jue");
       Serial.print(" Jue ");
      break;
      case 5:
       lcd.print("Vie");
       Serial.print(" Vie ");
      break;
      case 6:
       lcd.print("Sab");
       Serial.print(" Sab ");
      break;
      case 0:
       lcd.print("Dom");
       Serial.print(" Dom ");
      break;
      default: 
       lcd.print("---");
       Serial.print(" ---");
      break;
 } 
 return r_dia; 
}

/////////////////////Condicional del Horario 1  //////////////////////////////////
void horario_1(){ 
   lcd.setCursor(13,0);
   lcd.print("1");
   Serial.print("Horario_1 ");
   if ((hora==h1_c1) && (minuto==m1_c1) && (segundo==s1_c1))  activar_pcdani1();
   if ((hora==h2_c1) && (minuto==m2_c1) && (segundo==s2_c1))  desactivar_pcdani1();
   if ((hora==h3_c1) && (minuto==m3_c1) && (segundo==s3_c1))  comprobando_activar_pcdani2();
   if ((hora==h4_c1) && (minuto==m4_c1) && (segundo==s4_c1))  comprobando_desactivar_pcdani2();
   if ((hora==h5_c1) && (minuto==m5_c1) && (segundo==s5_c1))  comprobando_activar_luztaller();
   if ((hora==h6_c1) && (minuto==m6_c1) && (segundo==s6_c1))  comprobando_desactivar_luztaller();
   if ((hora==h7_c1) && (minuto==m7_c1) && (segundo==s7_c1))  comprobando_activar_timbre();
   if ((hora==h8_c1) && (minuto==m8_c1) && (segundo==s8_c1))  comprobando_desactivar_timbre();
   if ((hora==h9_c1) && (minuto==m9_c1) && (segundo==s9_c1))  activar_luzestanteria();
   if ((hora==h10_c1) && (minuto==m10_c1) && (segundo==s10_c1))  desactivar_luzestanteria();
   if ((hora==h11_c1) && (minuto==m11_c1) && (segundo==s11_c1))  activar_luzmostrador();
   if ((hora==h12_c1) && (minuto==m12_c1) && (segundo==s12_c1))  desactivar_luzmostrador();
   if ((hora==h13_c1) && (minuto==m13_c1) && (segundo==s13_c1))  activar_luznegocio();
   if ((hora==h14_c1) && (minuto==m14_c1) && (segundo==s14_c1))  desactivar_luznegocio();
   if ((hora==h15_c1) && (minuto==m15_c1) && (segundo==s15_c1))  comprobando_activar_cartelexterior();
   if ((hora==h16_c1) && (minuto==m16_c1) && (segundo==s16_c1))  comprobando_desactivar_cartelexterior();    
}
////////////////////Condicional del Horario 2  //////////////////////////////////
void horario_2(){ 
   lcd.setCursor(14,0);
   lcd.print("2");
   Serial.print("Horario_2 ");
   if ((hora==h1_c2) && (minuto==m1_c2) && (segundo==s1_c2))  activar_pcdani1();
   if ((hora==h2_c2) && (minuto==m2_c2) && (segundo==s2_c2))  desactivar_pcdani1();
   if ((hora==h3_c2) && (minuto==m3_c2) && (segundo==s3_c2))  activar_pcdani2();
   if ((hora==h4_c2) && (minuto==m4_c2) && (segundo==s4_c2))  desactivar_pcdani2();
   if ((hora==h5_c2) && (minuto==m5_c2) && (segundo==s5_c2))  activar_luztaller();
   if ((hora==h6_c2) && (minuto==m6_c2) && (segundo==s6_c2))  desactivar_luztaller();
   if ((hora==h7_c2) && (minuto==m7_c2) && (segundo==s7_c2))  activar_timbre();
   if ((hora==h8_c2) && (minuto==m8_c2) && (segundo==s8_c2))  desactivar_timbre();
   if ((hora==h9_c2) && (minuto==m9_c2) && (segundo==s9_c2))  activar_luzestanteria();
   if ((hora==h10_c2) && (minuto==m10_c2) && (segundo==s10_c2))  desactivar_luzestanteria();
   if ((hora==h11_c2) && (minuto==m11_c2) && (segundo==s11_c2))  activar_luzmostrador();
   if ((hora==h12_c2) && (minuto==m12_c2) && (segundo==s12_c2))  desactivar_luzmostrador();
   if ((hora==h13_c2) && (minuto==m13_c2) && (segundo==s13_c2))  activar_luznegocio();
   if ((hora==h14_c2) && (minuto==m14_c2) && (segundo==s14_c2))  desactivar_luznegocio();
   if ((hora==h15_c2) && (minuto==m15_c2) && (segundo==s15_c2))  activar_cartelexterior();
   if ((hora==h16_c2) && (minuto==m16_c2) && (segundo==s16_c2))  desactivar_cartelexterior();
  
}
//////////////////////Condicional del Horario 3  //////////////////////////////////
void horario_3(){ 
   lcd.setCursor(15,0);
   lcd.print("3");
   Serial.print("Horario_3 ");
   if ((hora==h1_c3) && (minuto==m1_c3) && (segundo==s1_c3))  activar_pcdani1();
   if ((hora==h2_c3) && (minuto==m2_c3) && (segundo==s2_c3))  desactivar_pcdani1();
   if ((hora==h3_c3) && (minuto==m3_c3) && (segundo==s3_c3))  activar_pcdani2();
   if ((hora==h4_c3) && (minuto==m4_c3) && (segundo==s4_c3))  desactivar_pcdani2();
   if ((hora==h5_c3) && (minuto==m5_c3) && (segundo==s5_c3))  activar_luztaller();
   if ((hora==h6_c3) && (minuto==m6_c3) && (segundo==s6_c3))  desactivar_luztaller();
   if ((hora==h7_c3) && (minuto==m7_c3) && (segundo==s7_c3))  activar_timbre();
   if ((hora==h8_c3) && (minuto==m8_c3) && (segundo==s8_c3))  desactivar_timbre();
   if ((hora==h9_c3) && (minuto==m9_c3) && (segundo==s9_c3))  activar_luzestanteria();
   if ((hora==h10_c3) && (minuto==m10_c3) && (segundo==s10_c3))  desactivar_luzestanteria();
   if ((hora==h11_c3) && (minuto==m11_c3) && (segundo==s11_c3))  activar_luzmostrador();
   if ((hora==h12_c3) && (minuto==m12_c3) && (segundo==s12_c3))  desactivar_luzmostrador();
   if ((hora==h13_c3) && (minuto==m13_c3) && (segundo==s13_c3))  activar_luznegocio();
   if ((hora==h14_c3) && (minuto==m14_c3) && (segundo==s14_c3))  desactivar_luznegocio();
   if ((hora==h15_c3) && (minuto==m15_c3) && (segundo==s15_c3))  activar_cartelexterior();
   if ((hora==h16_c3) && (minuto==m16_c3) && (segundo==s16_c3))  desactivar_cartelexterior();
}
