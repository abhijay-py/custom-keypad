/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//Keyboard Constants
//Function Keys
const uint8_t f1 = 0x3A;
const uint8_t f2 = 0x3B;
const uint8_t f3 = 0x3C;
const uint8_t f4 = 0x3D;
const uint8_t f5 = 0x3E;
const uint8_t f6 = 0x3F;
const uint8_t f7 = 0x40;
const uint8_t f8 = 0x41;
const uint8_t f9 = 0x42;
const uint8_t f10 = 0x43;
const uint8_t f11 = 0x44;
const uint8_t f12 = 0x45;
const uint8_t f13 = 0x68;
const uint8_t f14 = 0x69;
const uint8_t f15 = 0x6A;
const uint8_t f16 = 0x6B;
const uint8_t f17 = 0x6C;
const uint8_t f18 = 0x6D;
const uint8_t f19 = 0x6E;
const uint8_t f20 = 0x6F;
const uint8_t f21 = 0x70;
const uint8_t f22 = 0x71;
const uint8_t f23 = 0x72;
const uint8_t f24 = 0x73;

//Special Options
const uint8_t space = 0x2C;

//Numbers
const uint8_t exclaim_one = 0x1E;
const uint8_t at_two = 0x1F;
const uint8_t hashtag_three = 0x20;
const uint8_t dollar_four = 0x21;
const uint8_t percent_five = 0x22;
const uint8_t exponent_six = 0x23;
const uint8_t and_seven = 0x24;
const uint8_t star_eight = 0x25;
const uint8_t left_p_nine = 0x26;
const uint8_t right_p_zero = 0x27;

//Alphabet
const uint8_t key_a = 0x04;
const uint8_t key_b = 0x05;
const uint8_t key_c = 0x06;
const uint8_t key_d = 0x07;
const uint8_t key_e = 0x08;
const uint8_t key_f = 0x09;
const uint8_t key_g = 0x0A;
const uint8_t key_h = 0x0B;
const uint8_t key_i = 0x0C;
const uint8_t key_j = 0x0D;
const uint8_t key_k = 0x0E;
const uint8_t key_l = 0x0F;
const uint8_t key_m = 0x10;
const uint8_t key_n = 0x11;
const uint8_t key_o = 0x12;
const uint8_t key_p = 0x13;
const uint8_t key_q = 0x14;
const uint8_t key_r = 0x15;
const uint8_t key_s = 0x16;
const uint8_t key_t = 0x17;
const uint8_t key_u = 0x18;
const uint8_t key_v = 0x19;
const uint8_t key_w = 0x1A;
const uint8_t key_x = 0x1B;
const uint8_t key_y = 0x1C;
const uint8_t key_z = 0x1D;

//Consumer Report
const uint8_t volume_mute = 0xe2;
const uint8_t volume_up = 0xe9;
const uint8_t volume_down = 0xea;
const uint8_t play_pause = 0xcd;
const uint8_t prev_song = 0xb6;
const uint8_t next_song = 0xb5;

//Keyboard Modifier Constants (or/and to clear)
const uint8_t left_ctrl = 0x01;
const uint8_t left_shift = 0x02;
const uint8_t left_alt = 0x04;
const uint8_t left_gui = 0x08; //Often Windows key
const uint8_t right_ctrl = 0x10;
const uint8_t right_shift = 0x20;
const uint8_t right_alt = 0x40;
const uint8_t right_gui = 0x80; //Often FN key


//Setup Variables
extern USBD_HandleTypeDef hUsbDeviceHS;
const IC_Pin KEY_ONE = (IC_Pin){.pin_letter = GPIOB, .pin_num = GPIO_PIN_5, .input = 1};
const IC_Pin KEY_TWO = (IC_Pin){.pin_letter = GPIOB, .pin_num = GPIO_PIN_9, .input = 1};
const IC_Pin KEY_THREE = (IC_Pin){.pin_letter = GPIOB, .pin_num = GPIO_PIN_0, .input = 1};
const IC_Pin KEY_FOUR = (IC_Pin){.pin_letter = GPIOB, .pin_num = GPIO_PIN_6, .input = 1};
const IC_Pin KEY_FIVE = (IC_Pin){.pin_letter = GPIOA, .pin_num = GPIO_PIN_6, .input = 1};
const IC_Pin KEY_SIX = (IC_Pin){.pin_letter = GPIOC, .pin_num = GPIO_PIN_4, .input = 1};
const IC_Pin ROTARY_SWITCH = (IC_Pin){.pin_letter = GPIOA, .pin_num = GPIO_PIN_15, .input = 1};
const IC_Pin ROTARY_A = (IC_Pin){.pin_letter = GPIOB, .pin_num = GPIO_PIN_3, .input = 1};
const IC_Pin ROTARY_B = (IC_Pin){.pin_letter = GPIOB, .pin_num = GPIO_PIN_4, .input = 1};
const IC_Pin DEBUG_ELEVEN = (IC_Pin){.pin_letter = GPIOC, .pin_num = GPIO_PIN_11, .input = 0};
const IC_Pin DEBUG_TWELVE = (IC_Pin){.pin_letter = GPIOC, .pin_num = GPIO_PIN_12, .input = 0};


volatile int32_t encoder_pos = 0;
static uint8_t prev_state = 0;
static const int8_t decode_table[4][4] = {
    {  0, +1, -1,  0 },
    { -1,  0,  0, +1 },
    { +1,  0,  0, -1 },
    {  0, -1, +1,  0 }
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int key_one, key_two, key_three, key_four, key_five, key_six, rotary_SW, prev_rotary_SW, volume_up_b, volume_down_b, prev_key_two,  prev_key_one, prev_key_three, prev_key_four, prev_key_five, prev_key_six;
  uint8_t report_volup[] = {0x02, volume_up, 0x00};
  uint8_t report_voldown[] = {0x02, volume_down, 0x00};
  uint8_t report_volmute[] = {0x02, volume_mute, 0x00};
  uint8_t report_play[] = {0x02, play_pause, 0x00};
  uint8_t report_next[] = {0x02, next_song, 0x00};
  uint8_t report_prev[] = {0x02, prev_song, 0x00};
  uint8_t report_rewind[] = {0x02, rewind_track, 0x00};
  uint8_t report_ff[] = {0x02, fast_forward, 0x00};
  uint8_t blank_rep[] = {0x02, 0x00, 0x00};
  uint8_t last_send;
  uint8_t modifier = 0x00;
  int last_pos = 0;
  prev_rotary_SW = 0;
  prev_key_two = 0;
  prev_key_one = 0;
  prev_key_four = 0;
  prev_key_six = 0;
  prev_key_five = 0;
  prev_key_three = 0;
  int delta = 0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  if (hUsbDeviceHS.dev_state == USBD_STATE_CONFIGURED) {
	      write_pin(DEBUG_TWELVE, 1);
	  }

	  key_one = read_pin(KEY_ONE);
	  key_two = read_pin(KEY_TWO);
	  key_three = read_pin(KEY_THREE);

	  rotary_SW = read_pin(ROTARY_SWITCH);
	  delta = encoder_pos - last_pos;

	  if (delta >= 3) {
		  volume_up_b = 1;
		  volume_down_b = 0;
		  last_pos += 3;
	  }
	  else if (delta <= -3) {
		  volume_up_b = 0;
		  volume_down_b = 1;
		  last_pos -= 3;
	  }
	  else {
		  volume_up_b = 0;
		  volume_down_b = 0;
	  }
//	  if (volume_down_b) {
//		  USBD_HID_SendReport(&hUsbDeviceHS, &report_vol, sizeof(report_vol));
//	  }
	  if (key_two && !prev_key_two) {
		  USBD_HID_SendReport(&hUsbDeviceHS, &report_play, sizeof(report_play));
	  }
	  else if (key_one && !prev_key_one) {
		  USBD_HID_SendReport(&hUsbDeviceHS, &report_prev, sizeof(report_prev));
	  }
	  else if (key_three && !prev_key_three) {
	      USBD_HID_SendReport(&hUsbDeviceHS, &report_next, sizeof(report_next));
	  }
	  else if (prev_rotary_SW != rotary_SW && rotary_SW) {
		  USBD_HID_SendReport(&hUsbDeviceHS, &report_volmute, sizeof(report_volmute));
	  }
	  else if (volume_up_b) {
		  USBD_HID_SendReport(&hUsbDeviceHS, &report_volup, sizeof(report_volup));
	  }
	  else if (volume_down_b) {
		  USBD_HID_SendReport(&hUsbDeviceHS, &report_voldown, sizeof(report_voldown));
	  }

	  USBD_HID_SendReport(&hUsbDeviceHS, &blank_rep, sizeof(blank_rep));
	  HAL_Delay(10);
	  key_four = read_pin(KEY_FOUR);
	  key_five = read_pin(KEY_FIVE);
	  key_six = read_pin(KEY_SIX);
	  key_send(&hUsbDeviceHS, 0x00, key_four ? space : 0x00, key_five ? key_z : 0x00, key_six ? key_x : 0x00, 0x00, 0x00, 0x00);
	  HAL_Delay(10);
	  key_send(&hUsbDeviceHS, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	  write_pin(DEBUG_TWELVE, 0);
	  HAL_Delay(15);
	  if (key_one || key_two || key_three || key_four || key_five || key_six || rotary_SW || volume_up_b || volume_down_b) {
		  write_pin(DEBUG_ELEVEN, 1);
	  }
	  else {
		  write_pin(DEBUG_ELEVEN, 0);
	  }
	  prev_rotary_SW = rotary_SW;
	  prev_key_one = key_one;
	  prev_key_three = key_three;
	  prev_key_two = key_two;
	  prev_key_four = key_four;
	  prev_key_five = key_five;
	  prev_key_six = key_six;

//	  HAL_Delay(100);
//	  USBD_HID_SendReport(&hUsbDeviceHS, &keyboardOut, sizeof(keyboardOut));
//	  HAL_Delay(1000);
//	  write_pin(DEBUG_ELEVEN, 0);
//	  write_pin(DEBUG_TWELVE, 0);
//	  HAL_Delay(500);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /*AXI clock gating */
  RCC->CKGAENR = 0xFFFFFFFF;

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA6 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PC4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB5 PB6 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void encoder_update(void) {
    uint8_t a = read_pin(ROTARY_A);
    uint8_t b = read_pin(ROTARY_B);
    uint8_t curr_state = (a << 1) | b;

    encoder_pos += decode_table[prev_state][curr_state];
    prev_state = curr_state;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_3 || GPIO_Pin == GPIO_PIN_4) {
		encoder_update();
	}
}


uint8_t key_send(PCD_HandleTypeDef* usb, uint8_t modifier, uint8_t key_one, uint8_t key_two, uint8_t key_three, uint8_t key_four,  uint8_t key_five,  uint8_t key_six) {
	uint8_t reportKey[] = {0x01, modifier, 0x00, key_one, key_two, key_three, key_four, key_five, key_six};
	USBD_HID_SendReport(usb, &reportKey, sizeof(reportKey));
}
int write_pin(IC_Pin pin, int value)
{
	if (pin.input == 1) {
		return -1;
	}
	if (value == 0) {
		HAL_GPIO_WritePin(pin.pin_letter, pin.pin_num, GPIO_PIN_RESET);
	}
	else {
		HAL_GPIO_WritePin(pin.pin_letter, pin.pin_num, GPIO_PIN_SET);
	}
	return 0;
}
int read_pin(IC_Pin pin)
{
	if (pin.input == 0) {
		return -1;
	}

	GPIO_PinState value = HAL_GPIO_ReadPin(pin.pin_letter, pin.pin_num);

	if (value == GPIO_PIN_SET){
		return 1;
	}
	return 0;
}
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
