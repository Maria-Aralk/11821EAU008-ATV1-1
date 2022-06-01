/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         startup.c
  * @author       clara1
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
  * @brief        Interrupt Service Routines.
  * @brief        CMSIS Cortex-M4 Device Peripheral Access Layer System Source File.
  *
  *   This file provides two functions and one global variable to be called from 
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and 
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32f4xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick 
  *                                  timer or configure other parameters.
  *                                     
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
//mudancas realizadas apos laboratorio do dia 31/05
/* Includes */
//#include "main.h"
#include "stdint.h"
#include "stdlib.h"
/* USER CODE BEGIN Includes */
#define SRAM_START  0x20000000U                     
#define SRAM_SIZE   (128U * 1024U)                  
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))    
#define STACK_START SRAM_END                        

/* USER CODE END Includes */

int main (void);
void reset_handler     (void);
void nmi_handler       (void) __attribute__ ((weak, alias("default_handler")));
void hardfault_handler (void) __attribute__ ((weak, alias("default_handler")));
void memmanage_handler (void) __attribute__ ((weak, alias("default_handler")));
void busfault_handler  (void) __attribute__ ((weak, alias("default_handler")));
void usagefault_handler(void) __attribute__ ((weak, alias("default_handler")));
void svc_handler       (void) __attribute__ ((weak, alias("default_handler")));
void debugmon_handler  (void) __attribute__ ((weak, alias("default_handler")));
void pendsv_handler    (void) __attribute__ ((weak, alias("default_handler")));
void systick_handler   (void) __attribute__ ((weak, alias("default_handler")));
//continuacao
extern uint32_t _sdata;       /* Inicio da secao .data */
extern uint32_t _edata;       /* Fim da secao .data */
extern uint32_t _la_data;     /* Endereco de carga na RAM da secao .data */
extern uint32_t _etext;
extern uint32_t _sbss;        /* Inicio da secao .bss */
extern uint32_t _ebss;        /* Fim da secao .bss */

uint32_t vectors[] __attribute__((section(".isr_vectors"))) =
{
    STACK_START,                    /* 0x0000 0000 */
    (uint32_t)reset_handler,        /* 0x0000 0004 */
    (uint32_t)nmi_handler,          /* 0x0000 0008 */
    (uint32_t)hardfault_handler,    /* 0x0000 000c */
    (uint32_t)memmanage_handler,    /* 0x0000 0010 */
    (uint32_t)busfault_handler,     /* 0x0000 0014 */
    (uint32_t)usagefault_handler,   /* 0x0000 0018 */
    0,                              /* 0x0000 001c */
    0,                              /* 0x0000 0020 */
    0,                              /* 0x0000 0024 */
    0,                              /* 0x0000 0028 */
    (uint32_t)svc_handler,          /* 0x0000 002c */
    (uint32_t)debugmon_handler,     /* 0x0000 0030 */
    0,                              /* 0x0000 0034 */
    (uint32_t)pendsv_handler,       /* 0x0000 0038 */
    (uint32_t)systick_handler,      /* 0x0000 003c */
};

void reset_handler(void)
{
    uint32_t i;
    
    /* Copia a secao .data para a RAM */
    
    uint32_t oI = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pD = (uint8_t*)&_sdata;                      /* SRAM */
    uint8_t *pS = (uint8_t*)&_etext;                      /* FLASH */
    for(i =0; i < oI; i++)
    {
        *pD++ = *pS++;
    }                                                       
    
    /* Preenche a secao .bss com zero */
    
    oI = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pD = (uint8_t*)&_sbss;
    for(i =0; i < oI; i++)
    {
        *pD++ = 0;
    }
    /* Chama a funcao main() */
    
    main();
}

void default_handler(void){
    while(1){};


  return EXIT_SUCCESS;
} 