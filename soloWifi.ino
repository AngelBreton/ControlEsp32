//DETECTAR NULL
#include <Arduino.h>  
//Temperature Sensor
#include <OneWire.h>
#include <DallasTemperature.h>
//Communicacion UART
#include <HardwareSerial.h>

//Sensor TDS
const int sensorPin1 = 27; // sensor TDS 1
const int sensorPin2 = 14;  //Sensor TDS 2
const int sensorPin3 = 12;  //Sensor TDS 2
const int sensorPin4 = 13;  //Sensor TDS 2

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
//Comunicacion Serial
HardwareSerial Unit1(0); 

//------------- Configuracion Sensor temperatura --------------
#define ONE_WIRE_BUS 4
//Comunicar que vamos a utilizar la interfaz oneWire
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//Indica que el sensor utilizará la interfaz OneWire
//Obtener la direccion de cada sensor
//Nivel1
DeviceAddress sensor1 = { 0x28, 0xED, 0xEB, 0x75, 0xD0, 0x1, 0x3C, 0x3E };
//Nivel2
DeviceAddress sensor2 = { 0x28, 0xBB, 0xF6, 0x76, 0xE0, 0x1, 0x3C, 0x64 };
//Nivel3
DeviceAddress sensor3= { 0x28, 0x5, 0xED, 0x76, 0xE0, 0x1, 0x3C, 0x7C };
//Nivel4
DeviceAddress sensor4= { 0x28, 0xC4, 0x7C, 0x96, 0xF0, 0x1, 0x3C, 0xAD };
//---Respaldo de direcciones temperatura
//Nivel1
//DeviceAddress sensor1 = { 0x28, 0xED, 0xEB, 0x75, 0xD0, 0x1, 0x3C, 0x3E };
////Nivel2
//DeviceAddress sensor2 = { 0x28, 0xBB, 0xF6, 0x76, 0xE0, 0x1, 0x3C, 0x64 };
////Nivel3
//DeviceAddress sensor3= { 0x28, 0x5, 0xED, 0x76, 0xE0, 0x1, 0x3C, 0x7C };
////Nivel4
//DeviceAddress sensor4= { 0x28, 0xC4, 0x7C, 0x96, 0xF0, 0x1, 0x3C, 0xAD };
////
////------------- Configuracion Sensor TDS
float tdsValue=0, tdsValue2=0, tdsValue3=0, tdsValue4=0;

//
////------------- Configuracion Sensor PH
const int potPin=36, potPin2=39, potPin3=34, potPin4=35;
float ph, ph2, ph3, ph4;
float Value=0, Value2=0, Value3=0, Value4=0;
//
                      // Calibracion Sensor PH
float calibration = 82.04; //change this value to calibrate
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

//                    //Contador
int contador=0;
                   

void setup() {

  Serial.begin(115200);
//   //defines entradas y salidas
  pinMode(bombaAgua, OUTPUT);
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

  Unit1.begin(115200, SERIAL_8N1, 3, 1); 

}

void loop() {

//      variableNivelAgua = medirAgua(NivelAgua1);
//      variableNivelAgua2 = medirAgua(NivelAgua2);
//
//   
//    if(variableNivelAgua<1000||variableNivelAgua2<1000||variableNivelAgua3<1000||variableNivelAgua4<1000){
//      Serial.println("Seleccione una hortaliza en la app por favor");
//        //llenado nivel1      
//        //encender bomba de agua hasta que se active sensor nivel de agua
//        variableNivelAgua = medirAgua(NivelAgua1);
//        //variableNivelAgua2 = medirAgua(nivelAgua2);
//        
//        variableNivelAgua2 = 1001;
//        variableNivelAgua = medirAgua(NivelAgua1);
//        
//        Serial.println("Medicion sensor");
//        Serial.println(variableNivelAgua);
//        
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

  delay(1000);
//
////-------Obtener la conductividad--------------
  tdsValue=leerConductividad(sensorPin1);
  Serial.println("cond1");
  Serial.println(tdsValue);
  delay(1000);

//------- Obtener el ph ----------------------
  ph=leerPH(potPin);
  Serial.println("ph1");
  Serial.println(ph);


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


  float leerConductividad(int sensorConductividad){
    int valor1 = analogRead(sensorConductividad);
      Serial.println("sensorValue");
      Serial.println(valor1);
    float tds1 = (133.42 * pow(2.71828, 0.0041 * valor1)) - 53.67;
    return tds1;
  }

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
    return phValue;
  }



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

  
 
