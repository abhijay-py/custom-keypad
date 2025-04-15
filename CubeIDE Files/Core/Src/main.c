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

//Special Keys
const uint8_t print_screen = 0x46;
const uint8_t scroll_lock = 0x47;
const uint8_t pause = 0x48;
const uint8_t insert = 0x49;
const uint8_t start_line = 0x4A; //Known as home
const uint8_t page_up = 0x4B;
const uint8_t delete = 0x4C;
const uint8_t end_line = 0x4D; //Known as end
const uint8_t page_down = 0x4E;

//Special Characters
const uint8_t dash_underscore = 0x2D;
const uint8_t equals_plus = 0x2E
const uint8_t right_brackets = 0x2F;
const uint8_t left_brackets = 0x30;
const uint8_t backslash_line = 0x31;
const uint8_t semi_colon = 0x33;
const uint8_t quotes = 0x34;
const uint8_t accent_tilde = 0x35;
const uint8_t comma_less_than = 0x36;
const uint8_t period_greater_than = 0x37;
const uint8_t forward_slash_question = 0x38;

//Special Options
const uint8_t enter = 0x28;
const uint8_t esc = 0x29;
const uint8_t backspace = 0x2A;
const uint8_t tab = 0x2B;
const uint8_t space = 0x2C;
const uint8_t caps_lock = 0x39;

//Arrow Keys
const uint8_t right_arrow = 0x4F;
const uint8_t left_arrow = 0x50;
const uint8_t down_arrow = 0x51;
const uint8_t up_arrow = 0x52;

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

//Volume
const uint8_t volume_mute = 0x7F;
const uint8_t volume_up = 0x80;
const uint8_t volume_down = 0x81;


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
KeyboardReport keyboardOut = {0, 0, 0, 0, 0, 0, 0, 0};
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
  keyboardOut.MODIFIER = 0x0;
  while (1)
  {
    /* USER CODE END WHILE */
	  //Functions: Volume Up, Volume Down, Volume Mute, 6 Keys
	  keyboardOut.KEYCODE1 = 0x0;
	  keyboardOut.KEYCODE2 = 0x0;
	  keyboardOut.KEYCODE3 = 0x0;
	  keyboardOut.KEYCODE4 = 0x0;
	  keyboardOut.KEYCODE5 = 0x0;
	  keyboardOut.KEYCODE6 = 0x0;
	  USBD_HID_SendReport(&hUsbDeviceHS, &keyboardOut, sizeof(keyboardOut));
    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 48;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
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

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
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

  /*Configure GPIO pins : PB15 PB3 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
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
