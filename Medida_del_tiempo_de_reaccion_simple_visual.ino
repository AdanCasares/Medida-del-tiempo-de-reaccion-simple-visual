/////////////////////////////////////////////////////////////////////////
//
//  Medida del tiempo de reacción simple visual
//
//  Autor: Adán Casares Ruiz
//  Última modificación: 23/03/19
//  Plataforma: Arduino
//
//  Funcionalidad: Medir el tiempo de reacción visual de una persona y
//  realizar una serie de operaciones estadísticas básicas, para luego
//  mostrarlas por pantalla.
//
/////////////////////////////////////////////////////////////////////////

#include <rgb_lcd.h>
#include <string.h>

const int touch = 2;      // Entrada digital del sensor táctil
const int botton = 8;     // Entrada digital del botón
const int led = 4;        // Salida digital: LED
rgb_lcd lcd;

int myArray[5];
int tSuma = 0;

void setup() {
  pinMode(touch, INPUT);
  pinMode(botton, INPUT);
  pinMode(led, OUTPUT);
  lcd.begin(16, 2);
  randomSeed(millis());
}

/////////////////////////////////////////////////////////////////////////
//  Función que calcula la desviación típica
/////////////////////////////////////////////////////////////////////////

int desviacionTipica(int tSuma, int myArray[]) {

  int sum = 0;
  for (int i = 0; i < 5; i++) {

    sum = pow((myArray[i] - tSuma / 5), 2) + sum;

  }
  sum = sum / 5;
  sum = sqrt(sum);
  return sum;
}

void loop() {
  while (1) {

    if (digitalRead(touch) == HIGH) {
      //  Iniciamos el programa cuando tocamos el sensor táctil
      int i = 0;                //  Inicializamos el contador
      int tMax = 0;             //  Inicializamos el tiempo máximo
      while (i < 5) {
        lcd.noDisplay();
        digitalWrite(led, HIGH);            //  Encendemos el led
        int second = random(5000, 7000);    //Esperamos 5 y 7 segundos
        randomSeed(second);
        delay(second);
        digitalWrite(led, LOW);             //  Apagamos el led
        int t0 = millis();


        while (digitalRead(botton) == LOW) {
          //  Esperamos el tiempo de reacción del usuario
        }
        int t1 = millis();      //  Medimos el tiempo de reacción
        int t = t1 - t0;
        if (t >= 70) {       //  Comprobamos si NO ha hecho trampas
          myArray[i] = t;
          //  Guardamos el tiempo de reacción en un array
          tSuma = tSuma + t;

        }
        if (t > tMax) {   //  Comprobamos el tiempo de reacción máximo
          tMax = t;
        }

        lcd.display();

        if (t < 70) {     //  Comprobamos si el usuario ha hecho trampas
          lcd.print("Error");
          delay(5000);
          lcd.clear();
        }
        else {
          lcd.print(t);  //  Mostramos por pantalla el tiempo de reacción
          delay(5000);
          lcd.clear();
          i++;
        }
      }

      int desTip = desviacionTipica(tSuma, myArray);

      lcd.print("Media: ");        //  Mostramos por pantalla la media
      lcd.print(tSuma / 5);
      lcd.setCursor(0, 1);
      lcd.print("Maximo: ");       //  Mostramos por pantalla el máximo
      lcd.print(tMax);
      delay(5000);
      lcd.clear();
      lcd.print("Desv. Tip.: ");   //  Mostramos la desviación típica
      lcd.print(desTip);
      delay(5000);
      lcd.clear();
    }
  }
}
