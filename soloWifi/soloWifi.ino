//ESCLAVOO

#include <HardwareSerial.h>

HardwareSerial Unit2(1); // use UART2

int pin_relay = 23;

int phMas1 = 32;
int phMenos1 = 33;
int macros1 = 25;
int micros1 = 26;
int phMas2 = 27;
int phMenos2 = 14;
int macros2 = 12;
int micros2 = 13;


void setup()
{
  Serial.begin(115200);
  Unit2.begin(115200, SERIAL_8N1, 10, 9);
  pinMode(pin_relay, OUTPUT);
  
}
void loop()
{
  while(Unit2.available()){
    String mensaje = Unit2.readStringUntil('\n'); // Lee el mensaje recibido hasta encontrar un salto de línea
    Serial.println("" + mensaje);
    Serial.println(mensaje.length());
    char lastChar = mensaje.charAt(8);
    Serial.println(lastChar);
    char lastChar2 = mensaje.charAt(7);
    Serial.println(lastChar2);
    int lastInt = lastChar - '0';
    Serial.println(lastChar);
    if(lastChar2 == 'e') {   
      switch (lastInt) {
        case 1: // Si la opción es 1
          digitalWrite(phMas1, LOW);
          break;
        case 2: // Si la opción es 2
          digitalWrite(phMenos1, LOW);
          break;
        case 3: // Si la opción es 3
          digitalWrite(macros1, LOW);
          break;
        case 4: // Si la opción es 4
          digitalWrite(micros1, LOW);
          break;
          default: // Si la opción no coincide con ningún caso
                  // Código a ejecutar si la opción no coincide con ningún caso
                  break;
      }
    }
    if(lastChar2 == 'o') {
      switch (lastInt) {
        case 1: // Si la opción es 1
          digitalWrite(phMas1, HIGH);
          break;
        case 2: // Si la opción es 2
          digitalWrite(phMenos1, HIGH);
          break;
        case 3: // Si la opción es 3
          digitalWrite(macros1, HIGH);
          break;
        case 4: // Si la opción es 4
          digitalWrite(micros1, HIGH);
          break;
          default: // Si la opción no coincide con ningún caso
                  // Código a ejecutar si la opción no coincide con ningún caso
                  break;
      }

    }
  }
}
