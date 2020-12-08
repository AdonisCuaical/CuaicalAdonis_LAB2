#include <MsTimer2.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, A2, A3, A4, A5);
int horas = 0;
int minutos = 0;
boolean y = false;
boolean x = false;
boolean z = false;
int segundos = 0;
int on = 0;
int estado = 0;
String mensage;
String mensage1;
String mensage2;
String mm = ",";
String mensage3;
String mensage4;
int cont = 0;
int aux;
int auxil;
int auxcont = 0;
int auxmin;
int conversor1 ;
int conversor2;
int leds[4] = {7, 6, 5, 4};
int inentradas[4] = {11, 10, 9, 8};
//
void setup() {
  for (int j = 0; j < 4; j++) {
    pinMode(leds[j], OUTPUT);
    pinMode(inentradas[j], INPUT);
  }
  Serial.begin(9600);
  lcd.begin(16, 4);
  MsTimer2::set(100, reloj);
  MsTimer2::start();
  attachInterrupt(0, modo, HIGH);
  attachInterrupt(1, encendido, HIGH);
}

void loop() {

  if ( y == true) {
    int eled = random(0, 3);
    digitalWrite(leds[eled], HIGH);
    delay(500);
    digitalWrite(leds[eled], LOW);
    delay(500);
  }

  if (x == true && on == 0) {
    segundos = 0;
    delay(1000);
    conversor1 = analogRead(A0);
    conversor1 = map(conversor1, 0, 1023, 0, 59);
    minutos = conversor1;
    delay(1000);
    conversor2 = analogRead(A1);
    conversor2 = map(conversor2, 0, 1023, 0, 23);
    horas = conversor2;
    segundos = 0;
  }
  if (z == true && on == 0) {
    if (digitalRead(inentradas[0]) == HIGH) {
      mensage = "1";
    } else {
      mensage = "desactivado";
    }
    if (digitalRead(inentradas[1]) == HIGH) {
      mensage1 = "2";
    } else {
      mensage1 = "desactivado";
    }
    if (digitalRead(inentradas[2]) == HIGH) {
      mensage2 = "3";
    } else {
      mensage2 = "desactivado";
    }
    if (digitalRead(inentradas[3]) == HIGH) {
      mensage3 = "4";
    } else {
      mensage3 = "desactivado";
    }
    mensage4 = mensage + mm + mensage1 + mm + mensage2 + mm + mensage3;
    if (digitalRead(inentradas[0]) == HIGH || digitalRead(inentradas[1]) == HIGH || digitalRead(inentradas[2]) == HIGH || digitalRead(inentradas[3]) == HIGH) {
      Serial.println(String("Se han activado los sensores:  ") + mensage4);
      delay(500);
    }


  }
}

void reloj() {

  if (segundos < 59) {
    segundos++;
  } else {
    segundos = 0;
    if (minutos < 59) {
      minutos++;
      if ( y == true && auxcont < 2) {
        auxcont++;

      } else {
        auxcont = 0;
        y = false;
      }
    } else {
      minutos = 0;
      if (horas < 23) {
        horas++;
      } else {
        horas = 0;

      }
    }
  }
  lcd.setCursor(5, 0);
  lcd.print(String(horas) + String(":") + String(minutos) + String(":") + String(segundos));


}
void encendido() {
  switch (on) {
    case 0:
      lcd.setCursor(0, 1);
      lcd.print(String("1.Apagar."));
      lcd.setCursor(0, 2);
      lcd.print(String("2.Elegir Modo."));
      on++;
      break;
    case 1:
      if (cont == 1 || cont == 2 || aux == 3) {
        lcd.clear();
        lcd.setCursor(0, 2);
        if (cont == 1) {
          lcd.print("Leds encendidos");
          y = true;
          //encender();
        } else if (cont == 2) {
          lcd.print("Igualando reloj");
          x = true;
          z = false;
        } else if (aux == 3) {
          lcd.print("Sensores on");
          x = false;
          z = true;
          aux = 0;
        } on++;
      }


      break;
    case 2:
      on = 0;
      cont = 0;
      aux = 0;

      break;
  }

}
void modo() {
  if (on == 1) {
    cont++;
  }

  lcd.setCursor(0, 1);
  lcd.print("1.Activ Luces.");
  lcd.setCursor(0, 2);
  lcd.print("2.Cambiar Hora.");
  lcd.setCursor(0, 3);
  lcd.print("3.Activ Sensores.");
  if (cont == 1) {
    lcd.setCursor(15, 3);
    lcd.print(" ");
    lcd.setCursor(15, 1);
    lcd.print("*");


  } else if (cont == 2) {
    lcd.setCursor(15, 1);
    lcd.print(" ");
    lcd.setCursor(15, 2);
    lcd.print("*");

  } else if (cont == 3) {
    lcd.setCursor(15, 2);
    lcd.print(" ");
    lcd.setCursor(15, 3);
    lcd.print("*");
    aux = cont;
    cont = 0;
  }
  auxil = cont;
}
void encender() {


}
