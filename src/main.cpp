#include <Arduino.h>
// #include <SoftwareSerial.h>

uint32_t gas_button_time, gas_time;
bool gas_button_init = false;
bool gas_start = false;
bool gas_valve = false;
// const uint32_t gas_period = (uint32_t)60000 * (uint32_t)30;
const uint32_t gas_period = 6000;
bool a;

#define BUTTON_PIN 2
#define RELAY_PIN 15
// SoftwareSerial DEBUG_SW_USART(3, 1);

void setup() {
  DDRB = 0xFF;
  PORTB = B00000000;
  // DDRB &=~ (1 << DDB2);
  // PORTB |= (0 << DDB2);
  // // pinMode(2, INPUT_PULLUP);
  // \\ CLKPR = 0x80;
  // // CLKPR = 0x04;
  // // DEBUG_SW_USART.begin(1200);
  gas_valve = false;;
}

void read_GAS_button() {
  if((PINB & (1 << PINB2)) >> PINB2) { 
    gas_button_init = false;
  }
  else {
    if(gas_button_init) {
      if(millis() - gas_button_time > 500) {
        gas_time = millis();
        gas_start = true;
        delay(10);
        gas_button_init = false;
      }
    }
    else {
      gas_button_time = millis();
      gas_button_init = true;
    }
  }
}

void loop() {
  // // a = (PINB & PINB2) >> PINB2; 
  // // // a = digitalRead(2);
  // // uint8_t b = (PINB & (1 << PINB2)) >> PINB2;
  PORTB = B11111111;

  // PORTB |= (0 << DDB2);
  delay(1000);
  PORTB = B00000000;

  // PORTB |= (1 << DDB2);
  delay(1000);
  // // DEBUG_SW_USART.print(gas_valve);
  // // DEBUG_SW_USART.print(" ");
  // // DEBUG_SW_USART.println(millis());
  // read_GAS_button();
  // digitalWrite(RELAY_PIN, gas_valve);
  // if(gas_valve) {
  //   PORTA |=(1<< PORTA7);
  // }
  // else  {
  //   PORTA &=~ (1<<PORTA7);
  // }
  // if(gas_start) {
  //   gas_valve = (millis() - gas_time) < gas_period;
  // }
  // else gas_valve = false;
}
