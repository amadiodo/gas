#include <Arduino.h>

uint32_t gas_button_time, gas_time;
bool gas_button_init = false;
bool gas_start = false;
bool gas_valve = false;
bool blink_status;
const uint32_t gas_period = (uint32_t)2000 * 1;
uint32_t breathe_old;
bool inspire = true;
uint8_t breathe_PWM;

void setup() {
  DDRB |= (1 << PB4);
  DDRB |= (1 << PB0);
  DDRB |= (1 << PB1);
  DDRB &=~ (1 << DDB2);
  DDRB &=~ (1 << DDB3);
  PORTB |= (1 << DDB3);
  CLKPR = 0x80;
  // CLKPR = 0x04;
  CLKPR = B00000000;
  gas_valve = false;
}

void read_GAS_button() {
  if((PINB & (1 << PINB3)) >> PINB3) { 
    gas_button_init = false;
  }
  else {
    if(gas_button_init) {
      if(millis() - gas_button_time > 50) {
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

void breathe() {
  // uint32_t breathe_delay = 1;
  // if(millis() - breathe_old > breathe_delay) {
  //   breathe_old = millis();
  //   if(inspire) {
  //     if(breathe_PWM >= 255) inspire = false;
  //     else breathe_PWM++;
  //   }
  //   else {
  //     if(breathe_PWM == 0) inspire = true;
  //     else breathe_PWM--;
  //   }
  //   analogWrite(1, breathe_PWM);
  // }

  if(millis() - breathe_old > 20) {
    breathe_old = millis();
    if(blink_status)  PORTB &=~ (1<< DDB1);
    else PORTB |= (1 << DDB1);
    blink_status = !blink_status;
  }
}

void loop() {

  if ((PINB & (1 << PINB2)) >> PINB2) PORTB &=~ (1<< DDB0);
  else PORTB |= (1 << DDB0);

  read_GAS_button();
  if(gas_valve) PORTB |= (1 << DDB4);
  else  PORTB &=~ (1<< DDB4);
  if(gas_start) gas_valve = (millis() - gas_time) < gas_period;
  else gas_valve = false;
  breathe();
}
