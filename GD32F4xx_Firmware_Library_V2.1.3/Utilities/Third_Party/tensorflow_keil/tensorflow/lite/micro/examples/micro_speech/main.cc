/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/lite/micro/examples/hello_world/main_functions.h"

#include "gd32f4xx.h"
extern "C" {
#include "systick.h" 
}
#include <stdio.h>
#include "main.h"
#include "gd32f450i_eval.h"

extern "C" void  _sys_exit(int)
{
    abort();
    while(1);
} 

//#pragma import(__use_no_semihosting)

// This is the default main used on systems that have the standard C entry
// point. Other devices (for example FreeRTOS or ESP32) that have different
// requirements for entry code (like an app_main function) should specialize
// this main.cc file in a target-specific subfolder.
int main() {
    __asm(".global __use_no_semihosting\n\t");
    gd_eval_com_init(EVAL_COM0);
    printf("start\r\n");
    setup();
    while (true) {
        loop();
    }
}

/* retarget the C library printf function to the USART */
extern "C" int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM0, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM0, USART_FLAG_TBE));
    return ch;
}
