/**
 ******************************************************************************
 * File Name          : gpio_setup.c
 * Description        : Set up STM32 Discovery board 
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "gpio_setup.h"


/*
 * Perform the configuration of the STM32 Discovery board
 * to allow input from the user button and output to LEDs
 */
void board_setup(){
  HAL_Init();    // Initialize the hardware timers - required to set delays
  SystemClock_Config();   // Configure the system clocks
  gpio_setup();  // Configure the GPIO to perfprm suitable I/O
}


/*
 * System Clock Configuration
 */
void SystemClock_Config(void) {

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/**
 * Set up GPIO ports to perform input and output required
 * for the washing machine
 */
void gpio_setup(void) {

	// define a structure to be in port setup
  GPIO_InitTypeDef GPIO_InitStruct;

	// start the GPIO port E clock
  __HAL_RCC_GPIOE_CLK_ENABLE();
	
	// configuration of GPIO port E for input
  GPIO_InitStruct.Alternate = 0; //
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pin = ALL_PINS;              // set all pins needed
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
		// start the GPIO port D clock
  __HAL_RCC_GPIOD_CLK_ENABLE();
	
	// configuration of GPIO port D for output
  GPIO_InitStruct.Alternate = 0; //
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pin = ALL_PINS;              // set all pins needed
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	// start the GPIO port C clock
  __HAL_RCC_GPIOC_CLK_ENABLE();
	
  // this configuration routine not working - configure manually below
//	// configuration of GPIO port C for output
//  GPIO_InitStruct.Alternate = 0; //
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pin = ALL_PINS;              // set all pins needed
//  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	// port C addresses
  #define GPIO_C_BASE_ADDR  0x40000000 + 0x08000000 + 0x00000800
  #define GPIO_C_MODE  (GPIO_C_BASE_ADDR)
  #define GPIO_C_SPEED (GPIO_C_BASE_ADDR + 0x08)
  #define GPIO_C_PULL  (GPIO_C_BASE_ADDR + 0x0C)
  #define GPIO_C_IDR   (GPIO_C_BASE_ADDR + 0x10)
  #define GPIO_C_ODR   (GPIO_C_BASE_ADDR + 0x14)
  #define GPIO_C_ODR   (GPIO_C_BASE_ADDR + 0x14)

	// pointers to port C registers
  uint32_t *GPIO_C_Mode_Addr  = (uint32_t *) GPIO_C_MODE;
  uint32_t *GPIO_C_Speed_Addr = (uint32_t *) GPIO_C_SPEED;
  uint32_t *GPIO_C_Pull_Addr  = (uint32_t *) GPIO_C_PULL;
  //uint16_t *GPIO_C_Idr_Addr   = (uint16_t *) GPIO_C_IDR;
  //uint16_t *GPIO_C_Odr_Addr   = (uint16_t *) GPIO_C_ODR;
	
	// port C - set to output
  uint32_t GPIO_C_Mode = 0x55555555;  // 0b01010101010101010101010101010101  00 = input, 01 = output
  uint32_t GPIO_C_Speed = 0xFFFFFFFF; // 0b11111111111111111111111111111111  11 - high speed output only
  uint32_t GPIO_C_Pull = 0xaaaaaaaa;  // 0b10101010101010101010101010101010  00 none, 01 = pull up, 10 pull down

  // configure port C
  *GPIO_C_Mode_Addr =  (uint32_t) GPIO_C_Mode;
  *GPIO_C_Speed_Addr = (uint32_t) GPIO_C_Speed;
  *GPIO_C_Pull_Addr =  (uint32_t) GPIO_C_Pull;
}


// catch configuration issues
#ifdef USE_FULL_ASSERT
/**
 * @brief Reports the name of the source file and the source line number
 * where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
 * @}
 */

/**
 * @}
 */
