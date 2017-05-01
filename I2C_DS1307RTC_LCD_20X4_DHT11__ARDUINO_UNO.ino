// version 00.00.05 de 1 de mayo
#include <DHT11.h>

int pin=2;
DHT11 dht11(pin);

#include <Wire.h> 
#include "RTClib.h"
RTC_DS1307 RTC;
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
//LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C             lcd(I2C_ADDR,2, 1, 0, 4, 5, 6, 7);


void setup () {
Wire.begin(); // Inicia el puerto I2C
RTC.begin(); // Inicia la comunicación con el RTC
//RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
Serial.begin(9600); // Establece la velocidad de datos del puerto serie

lcd.begin (20,4);    // Inicializar el display con 20 caraceres 4 lineas
       lcd.clear();
       lcd.setBacklightPin(3,POSITIVE);
       lcd.setBacklight(HIGH);
 lcd.home ();                   // go home

 
}
void loop(){
DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
  Serial.print("Fecha=");
Serial.print(now.year(), DEC); // Año
Serial.print('/');
Serial.print(now.month(), DEC); // Mes
Serial.print('/');
Serial.print(now.day(), DEC); // Dia
Serial.print("     ");
Serial.print("Hora=");
Serial.print(now.hour(), DEC); // Horas
Serial.print(':');
Serial.print(now.minute(), DEC); // Minutos
Serial.print(':');
Serial.print(now.second(), DEC); // Segundos
Serial.println();
// enviamos al lcd fecha y hoa
  lcd.clear();//Limpiamos la LCD
    lcd.setCursor(2,0);
    lcd.print("Fecha ");    
lcd.print(now.day(), DEC); // dia
lcd.print("/");
lcd.print(now.month(), DEC); //mes
lcd.print("/");
lcd.print(now.year(), DEC); //año
lcd.setCursor(2,1);
lcd.print("Hora ");
lcd.print(now.hour(), DEC); //horas
lcd.print(":");
lcd.print(now.minute(), DEC); //minutos
lcd.print(":");
lcd.print(now.second(), DEC); //segundos

 int err;
       float temp, hum;
       if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
          {
             Serial.print("Temperatura: ");
             Serial.print(temp);
             Serial.print(" Humedad: ");
             Serial.print(hum);
             Serial.println();

             lcd.setCursor(2,2);
             lcd.print("Temperatura: ");
             lcd.print(temp);
             lcd.setCursor(2,3);
             lcd.print("Humedad: ");
             lcd.print(hum);
          }
       else
          {
             Serial.println();
             Serial.print("Error Num :");
             Serial.print(err);
             Serial.println();
          }
     delay(1000);            //Recordad que solo lee una vez por segundo
//delay(200); // La información se actualiza cada 1 seg.


}
