#include "fsm.h"
#include <string.h>
#include <stdio.h>

// FSM 1: Command Parser
typedef enum {
    INIT_CMD,
    READ_CMD
} ParserState;

ParserState parser_state = INIT_CMD;
uint8_t cmd_index = 0;

// FSM 2: UART Communication
typedef enum {
    WAIT_RST,
    WAIT_OK
} CommState;




CommState comm_state = WAIT_RST;
uint32_t timeout_timer = 0;
char tx_buffer[50]; // Buffer sending

extern UART_HandleTypeDef huart2;


// FSM 1
void command_parser_fsm(void) {
    switch (parser_state) {
        case INIT_CMD:
            if (temp == '!') { //See ! -> Change state
                parser_state = READ_CMD;
                cmd_index = 0;
            }
            break;

        case READ_CMD:
            if (temp == '!') {
                cmd_index = 0;
            } else if (temp == '#') { //See # -> Change state
                parser_state = INIT_CMD;
                command_data[cmd_index] = '\0'; // Add to complete string
                command_flag = 1; //Flag -> To FSM 2
            } else {
                command_data[cmd_index++] = temp; //Store char
                if (cmd_index >= MAX_BUFFER_SIZE) cmd_index = 0; //Max -> invalid -> comeback
            }
            break;
    }
}

// FSM 2
uint32_t timeout_counter = 0; // Counter

void uart_communication_fsm(void) {
    switch (comm_state) {
        case WAIT_RST:
            if (command_flag == 1) {
                command_flag = 0;
                if (strcmp((char*)command_data, "RST") == 0) {
                    sprintf(tx_buffer, "!ADC=%lu#\r\n", ADC_value);
                    HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, strlen(tx_buffer), 1000);
                  comm_state = WAIT_OK;
                   timeout_counter = 0;


//                    // Test voltage
//                        uint32_t voltage_x100 = (ADC_value * 500) / 4095;
//                        uint32_t v_nguyen = voltage_x100 / 100;
//                        uint32_t v_thapphan = voltage_x100 % 100;
//
//                        sprintf(tx_buffer, "!ADC=%lu#\r\n!VOLT=%lu.%02lu#\r\n", ADC_value, v_nguyen, v_thapphan);
//                        HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, strlen(tx_buffer), 1000);
//                        comm_state = WAIT_OK;
//                        timeout_counter = 0;

                }
            }
            break;

        case WAIT_OK:
            if (command_flag == 1) {
                command_flag = 0;
                if (strcmp((char*)command_data, "OK") == 0) {
                    sprintf(tx_buffer, "!Completed transmit#\r\n");
                    HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, strlen(tx_buffer), 1000);
                    comm_state = WAIT_RST;
                }
            }

            // 10ms tick -> 3s
            // If no ok, transmit again
            if (timeout_counter >= 300) {
                HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, strlen(tx_buffer), 1000);
                timeout_counter = 0;
            }
            break;
    }
}
