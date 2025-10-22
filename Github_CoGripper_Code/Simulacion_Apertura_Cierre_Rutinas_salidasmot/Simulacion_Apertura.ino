#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN_RGB1 10
#define A_IN1 1 
#define A_IN2 2 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN_RGB1, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  
  // Configurar PWM para el motor
  ledcAttach(1, 1000, 10);
  ledcAttach(2, 1000, 10);
  
  // Configurar NeoPixel
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  
  strip.begin();
  strip.setBrightness(250);
  strip.show(); // Inicializar todos los LEDs apagados
}

void loop() {
  // CERRADO: Verde sólido por 2 segundos
  ledcWrite(A_IN1, 0);
  ledcWrite(A_IN2, 0);
  solidColor(strip.Color(0, 255, 0), 2000);  // Verde sólido 2 seg
  
  // ABRIENDO: Motor abre + Verde parpadeando
  ledcWrite(A_IN1, 500);
  ledcWrite(A_IN2, 0);
  blinkColorNonBlocking(strip.Color(0, 255, 0), 250, 4);  // Verde parpadea mientras abre (1 segundo total)
  
  // ABIERTO: Amarillo sólido por 2 segundos
  ledcWrite(A_IN1, 0);
  ledcWrite(A_IN2, 0);
  solidColor(strip.Color(255, 255, 0), 2000);  // Amarillo sólido 2 seg
  
  // CERRANDO: Motor cierra + Verde parpadeando
  ledcWrite(A_IN1, 0);
  ledcWrite(A_IN2, 500);
  blinkColorNonBlocking(strip.Color(0, 255, 0), 250, 4);  // Verde parpadea mientras cierra (1 segundo total)
}

// Mostrar un color sólido por un tiempo determinado
void solidColor(uint32_t c, uint16_t duration) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(duration);
}

// Parpadear sin detener el motor (no apaga el motor durante los delays)
void blinkColorNonBlocking(uint32_t c, uint16_t interval, uint8_t times) {
  for(uint8_t i=0; i<times; i++) {
    // Encender
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, c);
    }
    strip.show();
    delay(interval);
    
    // Apagar
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, 0);
    }
    strip.show();
    delay(interval);
  }
}