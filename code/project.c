/*
 * File:   project.c
 * Author: ah427
 *
 * Created on 21 ?????, 2024, 08:41 ?
 */


#include <xc.h>
//#include <builtins.h>
#include "project.h"
#define _XTAL_FREQ 80000000UL

Relay_t relay1 = { .Port = GPIO_PORTC, .Pin = GPIO_PIN0, .Status = RELAY_TURN_OFF};
Relay_t relay2 = { .Port = GPIO_PORTC, .Pin = GPIO_PIN1, .Status = RELAY_TURN_OFF};

button_t btn_two_motors = {
  .button_pin = {
    .Direction = GPIO_INPUT,
    .Port = GPIO_PORTC,
    .Pin = GPIO_PIN2,
    .Logic = GPIO_LOW
  },  
  .button_active = BUTTON_ACTIVE_HIGH,
  .button_status = BUTTON_RELEASED
};

button_t btn_switch_motor = {
  .button_pin = {
    .Direction = GPIO_INPUT,
    .Port = GPIO_PORTC,
    .Pin = GPIO_PIN3,
    .Logic = GPIO_LOW
  },  
  .button_active = BUTTON_ACTIVE_HIGH,
  .button_status = BUTTON_RELEASED
};

void initialization(void);

button_status_t status_two_motors = BUTTON_RELEASED;
button_status_t status_switch_motor = BUTTON_RELEASED;

volatile uint8 flag_change_status_two_motors = 0;
volatile uint8 flag_change_status_switch_motor = 0;


void main(void) {
    initialization();
    while(1){
        button_read_status(&btn_two_motors, &status_two_motors);
        button_read_status(&btn_switch_motor, &status_switch_motor);

        if((BUTTON_PRESSED == status_two_motors) && (0 == flag_change_status_two_motors)){
            flag_change_status_two_motors = 1;
             __delay_ms(30);
            Relay_Turn_On(&relay2);
            Relay_Turn_On(&relay1);
           
        }
        else if((BUTTON_PRESSED == status_two_motors) && (1 == flag_change_status_two_motors)){
            flag_change_status_two_motors = 0;
            __delay_ms(30);
            Relay_Turn_Off(&relay1);
            Relay_Turn_Off(&relay2);
        }
        else{
            /*Nothing*/
        }
        
        
        if((BUTTON_PRESSED == status_switch_motor) && (0 == flag_change_status_switch_motor)){
            flag_change_status_switch_motor = 1;
             __delay_ms(30);
            Relay_Turn_On(&relay1);
            Relay_Turn_Off(&relay2);
        }
        else if((BUTTON_PRESSED == status_switch_motor) && (1 == flag_change_status_switch_motor)){
            flag_change_status_switch_motor = 0;
            __delay_ms(30);
            Relay_Turn_Off(&relay1);
            Relay_Turn_On(&relay2);
        }
        else{
            /*Nothing*/
        }
        
    }
    
    return;
}

void initialization(void){
    Relay_initialize(&relay1);
    Relay_initialize(&relay2);
    
    button_initialize(&btn_two_motors);
    button_initialize(&btn_switch_motor);


}
