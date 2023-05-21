//DETECTAR NULL
#include <Arduino.h>
// Wifi
#include <WiFi.h>                                                
#include <IOXhop_FirebaseESP32.h> 
// TDS sensor
#include <EEPROM.h>
#include "GravityTDS.h"   
//Temperature Sensor
#include <OneWire.h>
#include <DallasTemperature.h>
//Communicacion UART
//#include <HardwareSerial.h>
//Enviar Email
#include <ESP_Mail_Client.h>
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "huertohidroponicoipn@gmail.com"  /* Datos de acceso a cuenta. */
#define AUTHOR_PASSWORD "vcroysqktvbecbol"
#define RECIPIENT_EMAIL "angel.breton.1995@gmail.com" /* Correo electrÃ³nico del recipiente*/ 
SMTPSession smtp; /* Objeto SMTP para enviar el correo electrÃ³nico */
void smtpCallback(SMTP_Status status);

//Conectar Firebase                                       
//#define FIREBASE_Host "https://prueba2-20d1c-default-rtdb.firebaseio.com/"                         // Firebase Host
//#define FIREBASE_key "E9ELN82QlxnvafOcl0U9iSjVIxKRsC5BnBSWgfi8"                                // Key de Firebase
#define FIREBASE_Host "https://prueba2-20d1c-default-rtdb.firebaseio.com/"                         // Firebase Host
#define FIREBASE_key "E9ELN82QlxnvafOcl0U9iSjVIxKRsC5BnBSWgfi8" 


//#define Nombre_Wifi "TP-Link_F0FA"                                                                // Nombre de tu internet (SSID)
//#define Wifi_contra "07086243"                                                                 // Contraseña de tu internet
//#define Nombre_Wifi "ARRIS-C992"                                                                // Nombre de tu internet (SSID)
//#define Wifi_contra "8A3EF1F1F3FB9B16"   
//#define Nombre_Wifi "ARRIS-C992"                                                                // Nombre de tu internet (SSID)
//#define Wifi_contra "8A3EF1F1F3FB9B16"   
//#define Nombre_Wifi "Totalplay-2.4G-97d8"                                                                // Nombre de tu internet (SSID)
//#define Wifi_contra "mMuJcW8p3t8xgESf"   
//#define Nombre_Wifi "INFINITUM5F26_2.4"                                                                // Nombre de tu internet (SSID)
//#define Wifi_contra "GC6XxGhMKn"  
//#define Nombre_Wifi "Totalplay-B9AA"                                                                // Nombre de tu internet (SSID)
//#define Wifi_contra "B9AAA77ETMuNYq58"   
 #define Nombre_Wifi "AngelWifi"                                                                // Nombre de tu internet (SSID)
#define Wifi_contra ""  
 

//Sensor TDS
const int sensorPin1 = 27; // sensor TDS 1
const int sensorPin2 = 14;  //Sensor TDS 2
const int sensorPin3 = 12;  //Sensor TDS 2
const int sensorPin4 = 13;  //Sensor TDS 2
//#define TdsSensorPin 27
//#define TdsSensorPin2 14
//#define TdsSensorPin3 12
//#define TdsSensorPin4 13
//
//#define EEPROM_SIZE 512
//
////Bomba de agua
const int bombaAgua = 0;
const int bombaAire1 = 2;  
const int bombaAire2 = 15;  

////Nivel de agua
const int NivelAgua1 = 32;
const int NivelAgua2 = 33;
const int NivelAgua3 = 25;
const int NivelAgua4 = 26;

int variableNivelAgua;
int variableNivelAgua2;
int variableNivelAgua3;
int variableNivelAgua4;

////Electrovalvula llenado de agua
#define llenarNivel1  23
#define llenarNivel2  18
#define llenarNivel3  21
#define llenarNivel4  19
//
////Electrovalvula vaciado agua
#define vaciarNivel1  16
#define vaciarNivel2  5
#define vaciarNivel3  19
#define vaciarNivel4  22
//
////Comunicacion Serial
//HardwareSerial Unit1(0); 

//------------- Configuracion Sensor temperatura --------------
#define ONE_WIRE_BUS 4
//Comunicar que vamos a utilizar la interfaz oneWire
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//Indica que el sensor utilizará la interfaz OneWire
//Obtener la direccion de cada sensor
//DeviceAddress sensor1 = { 0x28, 0xFF, 0x77, 0x62, 0x40, 0x17, 0x4, 0x31 };
DeviceAddress sensor1 = { 0x28, 0xED, 0xEB, 0x75, 0xD0, 0x1, 0x3C, 0x3E };
DeviceAddress sensor2 = { 0x28, 0xFF, 0xB4, 0x6, 0x33, 0x17, 0x3, 0x4B };
DeviceAddress sensor3= { 0x28, 0xFF, 0xA0, 0x11, 0x33, 0x17, 0x3, 0x96 };
DeviceAddress sensor4= { 0x28, 0xFF, 0xA0, 0x11, 0x33, 0x17, 0x3, 0x96 };
//
////------------- Configuracion Sensor TDS
//GravityTDS gravityTds;
//GravityTDS gravityTds2;
//GravityTDS gravityTds3;
//GravityTDS gravityTds4;
//
//float temperature = 25;
float tdsValue=0, tdsValue2=0, tdsValue3=0, tdsValue4=0;
//float a;
//
////------------- Confuguracion Sensor PH
const int potPin=36, potPin2=39, potPin3=34, potPin4=35;
float ph, ph2, ph3, ph4;
float Value=0, Value2=0, Value3=0, Value4=0;
//
                      // Calibracion Sensor PH
float calibration = 21.04; //change this value to calibrate
int sensorValue = 0;
float phValue=0;
unsigned long int avgValue;
float b;
int buf[10],temp;
float phResultado = 0;
//                      //CONFIGURACIÓN GPIOS                    
String valorph, valorph2, valorph3, valorph4;  
String temperatura1,temperatura2,temperatura3,temperatura4;
String conductividad, conductividad2, conductividad3, conductividad4;
float temperatureC1,temperatureC2,temperatureC3,temperatureC4;
//
//                      //VARIABLES HORTALIZAS SELECCIONADAS
String hortaliza1,hortaliza2, hortaliza3, hortaliza4;
//
//                      //Calcular llenado de envases
//float CantidadSustancia1,CantidadDeseada1,CantidadMedidaConductividad1,ConcentracionDispensador1,Volumen1;
//float CantidadSustancia2,CantidadDeseada2,CantidadMedidaConductividad2,ConcentracionDispensador2,Volumen2;
//float CantidadSustancia3,CantidadDeseada3,CantidadMedidaConductividad3,ConcentracionDispensador3,Volumen3;
//float CantidadSustancia4,CantidadDeseada4,CantidadMedidaConductividad4,ConcentracionDispensador4,Volumen4;
//float caudalElectrovalvula;
//float Volumen=20;
//                     //Fechas
String fecha1,fecha2,fecha3,fecha4;
int horasCilantro,horasBrocoli,horasAjo,horasLechuga;
int contadorFecha1,contadorFecha2,contadorFecha3,contadorFecha4;
//
//                    //Contador
int contador=0;
                   

void setup() {

  Serial.begin(115200);
  //TDS
//  EEPROM.begin(EEPROM_SIZE);  //Initialize EEPROM
//
//   //defines entradas y salidas

  pinMode(bombaAgua, OUTPUT);
//  pinMode(bombaAire1, OUTPUT);
//  pinMode(bombaAire2, OUTPUT);
//  pinMode(NivelAgua1, INPUT);
//  pinMode(NivelAgua2, INPUT); 
//  pinMode(NivelAgua3, INPUT); 
//  pinMode(NivelAgua4, INPUT); 
  pinMode(llenarNivel1, OUTPUT);  
  pinMode(llenarNivel2, OUTPUT);  
  pinMode(llenarNivel3, OUTPUT);  
  pinMode(llenarNivel4, OUTPUT);
  pinMode(vaciarNivel1, OUTPUT);  
  pinMode(vaciarNivel2, OUTPUT);  
  pinMode(vaciarNivel3, OUTPUT);  
  pinMode(vaciarNivel4, OUTPUT); 

   //temperature Sensors
  sensors.begin();
// 
//    gravityTds.setPin(TdsSensorPin);
//    gravityTds2.setPin(TdsSensorPin2);
//    gravityTds3.setPin(TdsSensorPin3);
//    gravityTds4.setPin(TdsSensorPin4);
//    
//    gravityTds.setAref(3.3);  //reference voltage on ADC, default 5.0V on Arduino UNO
//    gravityTds2.setAref(3.3);  //reference voltage on ADC, default 5.0V on Arduino UNO
//    gravityTds3.setAref(3.3);  //reference voltage on ADC, default 5.0V on Arduino UNO
//    gravityTds4.setAref(3.3);  //reference voltage on ADC, default 5.0V on Arduino UNO
//    
//    gravityTds.setAdcRange(4096);  //1024 for 10bit ADC;4096 for 12bit ADC
//    gravityTds2.setAdcRange(4096);  //1024 for 10bit ADC;4096 for 12bit ADC
//    gravityTds3.setAdcRange(4096);  //1024 for 10bit ADC;4096 for 12bit ADC
//    gravityTds4.setAdcRange(4096);  //1024 for 10bit ADC;4096 for 12bit ADC
//    
//    gravityTds.begin();  //initialization
//    gravityTds2.begin();  //initialization
//    gravityTds3.begin();  //initialization
//    gravityTds4.begin();  //initialization 
//    delay(1000);       
//                                                 
//  Unit1.begin(115200, SERIAL_8N1, 3, 1); 
        
//  WiFi.begin(Nombre_Wifi, Wifi_contra);                        // __________________________________________________________________              
//  Serial.print(" Conectando a tu WiFi prro :v");               // |                                                                   |
//  while (WiFi.status() != WL_CONNECTED) {                      // |       PROCESO DE CONECCIÓN PARA TU WIFI PERRO :)                  |
//  Serial.print(" conectando... ");                             // |                                                                   |
//  delay(500);                                                  // |___________________________________________________________________|
//  }
//
//  Serial.println();
//  Serial.print("Se logro conectar a tu WIFI!");
//  Serial.println();
      //Serial.print("Direccion IP: ");
      //Serial.println(WiFi.localIP());                                //Mostrando tu dirección IP (mensaje)
//  Firebase.begin(FIREBASE_Host, FIREBASE_key);                         // connect to firebase´
// 
//  Firebase.setString("LECTURAS/cond", "15");  
//  Firebase.setString("LECTURAS/ph", "16");    
//  Firebase.setString("LECTURAS/temp", "17");
  //
//  Firebase.setString("LECTURAS2/cond2", "15");  
//  Firebase.setString("LECTURAS2/ph2", "16");    
//  Firebase.setString("LECTURAS2/temp2", "17");
//  //
//  Firebase.setString("LECTURAS3/cond3", "15");  
//  Firebase.setString("LECTURAS3/ph3", "16");    
//  Firebase.setString("LECTURAS3/temp3", "17");
//  // 
//  Firebase.setString("LECTURAS4/cond4", "15");  
//  Firebase.setString("LECTURAS4/ph4", "16");    
//  Firebase.setString("LECTURAS4/temp4", "17");   

  /** Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1
  */
  smtp.debug(0);

  /* Solicita resultados de envÃ­o */
  smtp.callback(smtpCallback);

  /* Configura datos de sesiÃ³n */
  ESP_Mail_Session session;

  /* Configura la sesiÃ³n */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  //Estado inicial para la salida1 (puede ser lo contrario) 
//  Firebase.setString("Mosco: ", "OFF");  
}

void loop() {
//------Obtener la Hortaliza y fecha final-----------------
//    hortaliza1=Firebase.getString("Hortaliza1"); 
//    hortaliza2=Firebase.getString("Hortaliza2"); 
//    hortaliza3=Firebase.getString("Hortaliza3");
//    hortaliza4=Firebase.getString("Hortaliza4");
//    Serial.println(hortaliza1); 
//    Serial.println(hortaliza2);
//    Serial.println(hortaliza3);
//    Serial.println(hortaliza4);
//    fecha1=Firebase.getString("FECHAS1"); 
//    fecha2=Firebase.getString("FECHAS2"); 
//    fecha3=Firebase.getString("FECHAS3");
//    fecha4=Firebase.getString("FECHAS4");
//    
//    if(hortaliza1.equals("")){
//      Serial.println("Seleccione una hortaliza en la app por favor");
//    }
//    else{
//        //llenado nivel1      
//        //encender bomba de agua hasta que se active sensor nivel de agua
//        variableNivelAgua = medirAgua(NivelAgua1);
//        //variableNivelAgua2 = medirAgua(nivelAgua2);
//        variableNivelAgua2 = 1001;
//        variableNivelAgua = medirAgua(NivelAgua1);
//        Serial.println("Medicion sensor");
//        Serial.println(variableNivelAgua);
//        //variableNivelAgua2 = medirAgua(nivelAgua2);
//        variableNivelAgua2 = 1001;
//
//        while(variableNivelAgua<1000||variableNivelAgua2<1000){  
//          
//          digitalWrite(llenarNivel1,HIGH);
//          digitalWrite(llenarNivel2,HIGH);  
//          digitalWrite(vaciarNivel1,LOW);
//          digitalWrite(vaciarNivel2,LOW);      
//          digitalWrite(bombaAgua,HIGH);
//
//          Serial.println("Dentro del bucle");
//          Serial.println("Medicion sensor 1");
//          Serial.println(variableNivelAgua);
//          Serial.println("Medicion sensor 2");
//          Serial.println(variableNivelAgua2);
//          
//          variableNivelAgua = medirAgua(NivelAgua1);
//          //variableNivelAgua2 = medirAgua(NivelAgua2);
//          if(variableNivelAgua>1000){
//               digitalWrite(llenarNivel1,LOW);
//               digitalWrite(vaciarNivel2,LOW);   
//          }
//          if(variableNivelAgua2>1000){
//               digitalWrite(llenarNivel2,LOW);
//               digitalWrite(vaciarNivel2,LOW);   
//          }
//          if(variableNivelAgua>1000&&variableNivelAgua2>1000){
//            break;
//          }
//        
//          delay(400);
//        }
//        //apaga la bomba y no deja pasar mas agua
//        Serial.println("Fuera del bucle");
//        Serial.println(variableNivelAgua);
//        digitalWrite(bombaAgua,LOW);   
//    }
//  
////------Obtener la temperatura-----------------
  sensors.requestTemperatures();
  temperatureC1=leerTemperatura1();
  temperatureC2=leerTemperatura2();
  temperatureC3=leerTemperatura3();
  temperatureC4=leerTemperatura4();
  Serial.println("temp1");
  Serial.println(temperatureC1);
    Serial.println("temp2");
  Serial.println(temperatureC2);
    Serial.println("temp3");
  Serial.println(temperatureC3);
    Serial.println("temp4");
  Serial.println(temperatureC4);
//  enviarTemperaturas(temperatureC1);
  delay(2000);
//
////-------Obtener la conductividad--------------
  tdsValue=leerConductividad(sensorPin1);
   Serial.println("cond1");
  Serial.println(tdsValue);
//  enviarConductividad1(tdsValue);
  delay(2000);
//  tdsValue2=leerConductividad2(temperatureC2);
//  tdsValue3=leerConductividad3(temperatureC3);
//  tdsValue4=leerConductividad4(temperatureC4);
//  enviarConductividad(tdsValue,tdsValue2,tdsValue3,tdsValue4);
//
//------- Obtener el ph ----------------------
  ph=leerPH(potPin);
  Serial.println("ph1");
  Serial.println(ph);
  enviarPH(ph);

//  //Detecta que tratamiento usar
//  seleccionTratamiento1(hortaliza1);
//  seleccionTratamiento2(hortaliza2);
//  seleccionTratamiento3(hortaliza3);
//  seleccionTratamiento4(hortaliza4);

//------- Enviar correo fuera de rango ----------------------
  
//  if((ph<6||ph>7.2||tdsValue<100||tdsValue>2000||temperatureC1<10||temperatureC1>30)&&contador!=24){
//    String mensaje= "Medicion Fuera de Rango";
//    enviarCorreo("1", mensaje, ph, tdsValue, temperatureC1);
//    contador=24;
//  }
  
//

//
//  //cuentas las horas
//  contador=contador+1;
//  if(contador=24){
//    contador=0;
//  }
//  
//
//  //Modo ahorro de energia activado por 
//  esp_sleep_enable_timer_wakeup(3600000000);//dormir por 1 hora , tiempo en microsegundos
//  esp_deep_sleep_start();
}


//Funciones
  
   int medirAgua(int sensorAgua){
       sensorValue = analogRead(sensorAgua);
      return sensorValue;
    }

  void enviarTemperaturas(float temperatureC1){
     String temperaturaString1;
     temperaturaString1=temperatureC1;
//     String temperaturaString2;
//     temperaturaString2=temperatureC2;
//     String temperaturaString3;
//     temperaturaString3=temperatureC3;
//     String temperaturaString4;
//     temperaturaString4=temperatureC4;
     Firebase.setString("LECTURAS/temp", temperaturaString1);
//     Firebase.setString("LECTURAS2/temp2", temperaturaString2);
//     Firebase.setString("LECTURAS3/temp3", temperaturaString3);
//     Firebase.setString("LECTURAS4/temp4", temperaturaString4);
  }
//  
    float leerTemperatura1(){
    float temperatureC1 = sensors.getTempC(sensor1);
    return temperatureC1;
 }
//  
  float leerTemperatura2(){
    float temperatureC2 = sensors.getTempC(sensor2);
    return temperatureC2;  
  }
  
  float leerTemperatura3(){
    float temperatureC3 = sensors.getTempC(sensor3);
    return temperatureC3;
  }
  
  float leerTemperatura4(){
     float temperatureC4 = sensors.getTempC(sensor4);
     return temperatureC4;
  }
//
//  void enviarConductividad(float tdsValue,float tdsValue2,float tdsValue3,float tdsValue4){
//    conductividad = tdsValue;
//    conductividad2 = tdsValue2;
//    conductividad3 = tdsValue3;
//    conductividad4 = tdsValue4;
//    Firebase.setString("LECTURAS/cond", conductividad);
//    Firebase.setString("LECTURAS2/cond2", conductividad2);
//    Firebase.setString("LECTURAS3/cond3", conductividad3);
//    Firebase.setString("LECTURAS4/cond4", conductividad4);
//  }
//
//  float leerConductividad1(float temperatureC1){
//    gravityTds.setTemperature(temperatureC1);  // set the temperature and execute temperature compensation
//    gravityTds.update();  //sample and calculate
//    tdsValue = gravityTds.getTdsValue();  // then get the value
//    return tdsValue;
//  }

  float leerConductividad(int sensorConductividad){
    int valor1 = analogRead(sensorConductividad);
    float tds1 = (133.42 * pow(2.71828, 0.0041 * valor1)) - 53.67;
    return tds1;
  }

  void enviarConductividad1(float tdsValue){
    conductividad = tdsValue;
    Firebase.setString("LECTURAS/cond", conductividad);
  }

   void enviarConductividad2(float tdsValue){
    conductividad = tdsValue;
    Firebase.setString("LECTURAS2/cond", conductividad);
  }

   void enviarConductividad3(float tdsValue){
    conductividad = tdsValue;
    Firebase.setString("LECTURAS3/cond", conductividad);
  }

   void enviarConductividad4(float tdsValue){
    conductividad = tdsValue;
    Firebase.setString("LECTURAS4/cond", conductividad);
  }

//
//   float leerConductividad2(float temperatureC2){
//    gravityTds2.setTemperature(temperatureC2);  // set the temperature and execute temperature compensation
//    gravityTds2.update();  //sample and calculate
//    tdsValue2 = gravityTds2.getTdsValue();  // then get the value
//    return tdsValue2;
//  }
//
//   float leerConductividad3(float temperatureC3){
//    gravityTds3.setTemperature(temperatureC3);  // set the temperature and execute temperature compensation
//    gravityTds3.update();  //sample and calculate
//    tdsValue3 = gravityTds3.getTdsValue();  // then get the value
//    return tdsValue3;
//  }
//
//   float leerConductividad4(float temperatureC4){
//    gravityTds4.setTemperature(temperatureC4);  // set the temperature and execute temperature compensation
//    gravityTds4.update();  //sample and calculate
//    tdsValue4 = gravityTds4.getTdsValue();  // then get the value
//    return tdsValue4;
//  }
//
float leerPH(int numeroSensor){
    for(int i=0;i<10;i++)
      {
      buf[i]=analogRead(numeroSensor);
      delay(30);
      }
    for(int i=0;i<9;i++)
      {
      for(int j=i+1;j<10;j++)
        {
          if(buf[i]>buf[j])
          {
          temp=buf[i];
          buf[i]=buf[j];
          buf[j]=temp;
          }
        }
    }
    avgValue=0;
    for(int i=2;i<8;i++){
      avgValue+=buf[i];
      float pHVol=(float)avgValue*5.0/1024/6;
      phValue = -5.70 * pHVol + calibration;
     
      delay(500);
    }
     //Serial.print("sensor = ");
     Serial.println(phValue);
    return phValue;
  }

//enviarPH
  void enviarPH(float ph){
    valorph = ph; 
    Firebase.setString("LECTURAS/ph", valorph);
   
  }

//
//  float leerPH1(){
//    Value= analogRead(potPin);
//    float voltage=Value*(3.3/4095.0);
//    ph=(3.3*voltage);
//    return ph;
//  }
//
//  
//  float leerPH2(){
//    Value2= analogRead(potPin2);
//    float voltage2=Value2*(3.3/4095.0);
//    ph2=(3.3*voltage2);
//    return ph2;
//  }
//
//  
//  float leerPH3(){
//    Value3= analogRead(potPin3);
//    float voltage3=Value3*(3.3/4095.0);
//    ph3=(3.3*voltage3);
//    return ph3;
//  }
//
//  
//  float leerPH4(){
//    Value4= analogRead(potPin4);
//    float voltage4=Value4*(3.3/4095.0);
//    ph4=(3.3*voltage4);
//    return ph4;
//  }

//  float seleccionTratamiento1(String hortaliza1){            
//       if (strcmp(hortaliza1.c_str(), "Cilantro") == 0) {
//            while(Unit1.available()){
//              Unit1.write("v1-close"); //cierra valvula macro
//              Unit1.write("v2-close"); //cierra valvula micro
//              Unit1.write("v3-close"); //cierra valvula ph +
//              Unit1.write("v4-close"); //cierra valvula ph -
//          
//              //Obtener la conductividad deseada
//              //Csustancia = (Cdeseada - Cmedida) x V/ Cdispensador
//              CantidadSustancia1=1;
//              while(CantidadSustancia1<=0){
//                CantidadMedidaConductividad1=leerConductividad1(temperatureC1);
//                CantidadSustancia1=(CantidadDeseada1-CantidadMedidaConductividad1)*Volumen/ConcentracionDispensador1;
//                Unit1.write("M1-open");
//                Unit1.write("v1-open");
//                Unit1.write("v2-open");
//                ph=leerPH1();
//                if(ph>6&&ph<6.5){
//                  Unit1.write("v4-close");
//                }
//                if(ph>=6.5){
//                  Unit1.write("v4-open");
//                }
//              }
//              Unit1.write("v1-close"); //cierra valvula macro
//              Unit1.write("v2-close"); //cierra valvula micro
//              Unit1.write("v3-close"); //cierra valvula ph +
//              Unit1.write("v4-close"); //cierra valvula ph -
//
//              return 1;
//            } // llave de cierre agregada
//          
//            // Código para encender
//          } else if (strcmp(hortaliza1.c_str(), "Lechuga") == 0) {
//            return 1;
//            // Código para apagar
//          } else if (strcmp(hortaliza1.c_str(), "Ajo") == 0) {
//            return 1;
//            // Código para parpadear
//          } else if (strcmp(hortaliza1.c_str(), "Brocoli") == 0) {
//            return 1;
//          }
//  }

//  float seleccionTratamiento2(String hortaliza2){            
//       if (strcmp(hortaliza2.c_str(), "Cilantro") == 0) {
//            while(Unit1.available()){
//              Unit1.write("v5-close"); //cierra valvula macro
//              Unit1.write("v6-close"); //cierra valvula micro
//              Unit1.write("v7-close"); //cierra valvula ph +
//              Unit1.write("v8-close"); //cierra valvula ph -
//          
//              //Obtener la conductividad deseada
//              //Csustancia = (Cdeseada - Cmedida) x V/ Cdispensador
//              CantidadSustancia2=1;
//              while(CantidadSustancia2<=0){
//                CantidadMedidaConductividad2=leerConductividad2(temperatureC2);
//                CantidadSustancia2=(CantidadDeseada2-CantidadMedidaConductividad2)*Volumen/ConcentracionDispensador2;
//                Unit1.write("M2-open");
//                Unit1.write("v5-open");
//                Unit1.write("v6-open");
//                ph2=leerPH2();
//                if(ph2>6&&ph2<6.5){
//                  Unit1.write("v8-close");
//                }
//                if(ph>=6.5){
//                  Unit1.write("v8-open");
//                }
//              }
//              Unit1.write("v5-close"); //cierra valvula macro
//              Unit1.write("v6-close"); //cierra valvula micro
//              Unit1.write("v7-close"); //cierra valvula ph +
//              Unit1.write("v8-close"); //cierra valvula ph -
//
//              return 1;
//            } // llave de cierre agregada
//          
//            // Código para encender
//          } else if (strcmp(hortaliza2.c_str(), "Lechuga") == 0) {
//            return 1;
//            // Código para apagar
//          } else if (strcmp(hortaliza2.c_str(), "Ajo") == 0) {
//            return 1;
//            // Código para parpadear
//          } else if (strcmp(hortaliza2.c_str(), "Brocoli") == 0) {
//            return 1;
//          }
//  }

//  float seleccionTratamiento3(String hortaliza3){            
//       if (strcmp(hortaliza3.c_str(), "Cilantro") == 0) {
//            while(Unit1.available()){
//              Unit1.write("v9-close"); //cierra valvula macro
//              Unit1.write("v10-close"); //cierra valvula micro
//              Unit1.write("v11-close"); //cierra valvula ph +
//              Unit1.write("v12-close"); //cierra valvula ph -
//          
//              //Obtener la conductividad deseada
//              //Csustancia = (Cdeseada - Cmedida) x V/ Cdispensador
//              CantidadSustancia3=1;
//              while(CantidadSustancia3<=0){
//                CantidadMedidaConductividad3=leerConductividad3(temperatureC3);
//                CantidadSustancia3=(CantidadDeseada3-CantidadMedidaConductividad3)*Volumen/ConcentracionDispensador1;
//                Unit1.write("M3-open");
//                Unit1.write("v9-open");
//                Unit1.write("v10-open");
//                ph3=leerPH3();
//                if(ph3>6&&ph3<6.5){
//                  Unit1.write("v12-close");
//                }
//                if(ph3>=6.5){
//                  Unit1.write("v12-open");
//                }
//              }
//              Unit1.write("v9-close"); //cierra valvula macro
//              Unit1.write("v10-close"); //cierra valvula micro
//              Unit1.write("v11-close"); //cierra valvula ph +
//              Unit1.write("v12-close"); //cierra valvula ph -
//
//              return 1;
//            } // llave de cierre agregada
//          
//            // Código para encender
//          } else if (strcmp(hortaliza3.c_str(), "Lechuga") == 0) {
//            return 1;
//            // Código para apagar
//          } else if (strcmp(hortaliza3.c_str(), "Ajo") == 0) {
//            return 1;
//            // Código para parpadear
//          } else if (strcmp(hortaliza3.c_str(), "Brocoli") == 0) {
//            return 1;
//          }
//  }


//float seleccionTratamiento4(String hortaliza4){            
//       if (strcmp(hortaliza4.c_str(), "Cilantro") == 0) {
//            while(Unit1.available()){
//              Unit1.write("v13-close"); //cierra valvula macro
//              Unit1.write("v14-close"); //cierra valvula micro
//              Unit1.write("v15-close"); //cierra valvula ph +
//              Unit1.write("v16-close"); //cierra valvula ph -
//          
//              //Obtener la conductividad deseada
//              //Csustancia = (Cdeseada - Cmedida) x V/ Cdispensador
//              CantidadSustancia4=1;
//              while(CantidadSustancia4<=0){
//                CantidadMedidaConductividad4=4(temperatureC4);
//                CantidadSustancia4=(CantidadDeseada4-CantidadMedidaConductividad4)*Volumen/ConcentracionDispensador1;
//                Unit1.write("M4-open");
//                Unit1.write("v13-open");
//                Unit1.write("v14-open");
//                ph4=leerPH4();
//                if(ph4>6&&ph4<6.5){
//                  Unit1.write("v16-close");
//                }
//                if(ph3>=6.5){
//                  Unit1.write("v16-open");
//                }
//              }
//              Unit1.write("v13-close"); //cierra valvula macro
//              Unit1.write("v14-close"); //cierra valvula micro
//              Unit1.write("v15-close"); //cierra valvula ph +
//              Unit1.write("v16-close"); //cierra valvula ph -
//
//              return 1;
//            } // llave de cierre agregada
//          
//            // Código para encender
//          } else if (strcmp(hortaliza4.c_str(), "Lechuga") == 0) {
//            return 1;
//            // Código para apagar
//          } else if (strcmp(hortaliza4.c_str(), "Ajo") == 0) {
//            return 1;
//            // Código para parpadear
//          } else if (strcmp(hortaliza4.c_str(), "Brocoli") == 0) {
//            return 1;
//          }
//  }

  void enviarCorreo(String nivel, String mensaje, float ph, float tdsValue, float temperature){
  SMTP_Message message;
  /* Configura cabecera del mensaje */
  message.sender.name = "App Huerto Vertical";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "App Huerto Vertical en Nivel " + nivel;
  message.addRecipient("Estimado", RECIPIENT_EMAIL);

  int variable=5;
  //Manda texto
  String textMsg = mensaje + "en el nivel " + nivel + "\n ph: " + ph + "\n conductividad: " + tdsValue + "\n temperatura: " + temperature;
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  /* Configura cabecera personalizada */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Conecta al servidor */
//  if (!smtp.connect(&session))
//    return;

  /* Manda correo y cierra sesiÃ³n */
  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Error al enviar el correo electrónico");
  } else {
    Serial.println("Correo electrónico enviado");
  }
}

/* Callback function to get the Email sending status */
  void smtpCallback(SMTP_Status status){
      /* Print the current status */
      Serial.println(status.info());
    
      /* Print the sending result */
      if (status.success()){
        Serial.println("----------------");
        ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
        ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
        Serial.println("----------------\n");
        struct tm dt;
    
        for (size_t i = 0; i < smtp.sendingResult.size(); i++){
          /* Get the result item */
          SMTP_Result result = smtp.sendingResult.getItem(i);
          time_t ts = (time_t)result.timestamp;
          localtime_r(&ts, &dt);
    
          ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
          ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
          ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
          ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients);
          ESP_MAIL_PRINTF("Subject: %s\n", result.subject);
        }
        Serial.println("----------------\n");
      }
}


  
 
