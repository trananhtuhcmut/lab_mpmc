#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"

#define MAX_BUFFER_SIZE 30

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

extern uint8_t command_flag;
extern uint8_t command_data[MAX_BUFFER_SIZE];
extern uint32_t ADC_value;

extern uint32_t timeout_counter;

void command_parser_fsm(void);
void uart_communication_fsm(void);

#endif /* INC_FSM_H_ */
