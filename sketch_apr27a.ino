#include <math.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//VCC-5v, GND-gnd, SDA-20, SCL-21
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin();
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("An error has ocurred");
    while(true);
  }

  display.clearDisplay();
  display.setCursor(0,10);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.println("Holaaaaaaaaa");
  display.display();

}

void loop() {



  graficar(f1);
  delay(3000);

  graficar(f2);
  delay(3000);

  graficar(f3);
  delay(3000);



}




//Implementacion de Metodo de Biseccion

float f1(float x){
  return pow(x, 4) + 3 * pow(x, 3) - 2;
}

float f2(float x){
  return x * x - 4; // raíz en ±2
}

float f3(float x){
  return sin(x) - 0.5;
}


double bisectionMethod(float (*func)(float), float min, float max, float xrAnterior){
  float xa = min;
  float xb = max;

  float xr = (xa + xb) / 2;

  float fxa = func(xa);
  float fxr = func(xr);

  double error;

  if (xrAnterior == 0) {
    error = 100;
  } else {
    error = abs((xr - xrAnterior) / xr) * 100;
  }

  if (error < 3) return xr;

  if ((fxa * fxr) > 0){
    return bisectionMethod(func, xr, xb, xr);
  } else {
    return bisectionMethod(func, xa, xr, xr);
  }
}


void graficar(float (*func)(float)) {

  float xMin = -10;
  float xMax = 10;
  float yMin = -10;
  float yMax = 10;

  display.clearDisplay();

  // 🔹 Dibujar ejes
  int ejeX = map(0, yMin * 100, yMax * 100, SCREEN_HEIGHT, 0);
  int ejeY = map(0, xMin * 100, xMax * 100, 0, SCREEN_WIDTH);

  display.drawLine(0, ejeX, SCREEN_WIDTH, ejeX, WHITE); // eje X
  display.drawLine(ejeY, 0, ejeY, SCREEN_HEIGHT, WHITE); // eje Y

  int prevX = 0;
  int prevY = 0;
  bool firstPoint = true;

  for (int px = 0; px < SCREEN_WIDTH; px++) {

    float x = xMin + (xMax - xMin) * px / SCREEN_WIDTH;
    float y = func(x);

    int py = map(y * 100, yMin * 100, yMax * 100, SCREEN_HEIGHT, 0);

    if (py >= 0 && py < SCREEN_HEIGHT) {

      if (!firstPoint) {
        display.drawLine(prevX, prevY, px, py, WHITE);
      }

      prevX = px;
      prevY = py;
      firstPoint = false;
    }
  }

  display.display();
}




