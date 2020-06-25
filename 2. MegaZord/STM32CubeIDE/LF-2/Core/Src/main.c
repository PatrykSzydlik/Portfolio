/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define VMED 350
#define KP 6
#define KD 5
#define PRZESTRZAL 140
#define SPEED_1 75
#define SPEED_2 50
#define SPEED_3 35
#define DZIELNIK 15
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim21;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
int predkosc_zadana = VMED;									//Predkosc zadana
uint16_t prog = 0; 								//Prog wykrycia czarnej linii
uint32_t pomiar[9];								//Wartosci pomiaru z czujnikow
uint16_t czujniki[9];						//Flaga wykrycia linii na czujniku
int wzor_wag[9] = { -75, -50, -35, -16, 0, 16, 35, 50, 75 };
int wagi[9];						//Wagi kazdego z czujnikow
int korekta = 0;								//Korekta predkosci obrotu kol
int poprzednia_korekta = 0;									//Poprzednia korekta
int przestrzelony = 0;								//Czy przestrzelono zakret
int Kp = KP, Kd = KD;										//Zmienne kp i kd
int regulacja = 0;										//Wartosc regulacji PD
int start = 0;												//FLaga startu jazdy
int zacznij_pomiar = 0;						//Flaga poczatku analizy pomiarow
int lewy_silnik;											//PWM lewego silnika
int prawy_silnik;										//PWM prawego silnika
int inicjuj = 0;
int kat_prosty = 0;
int chyba_kat_prosty = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM21_Init(void);
/* USER CODE BEGIN PFP */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if (start == 1) {
		start = 0;
	} else if (start == 0) {
		start = 1;
		inicjuj = 1;
	};

	HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);

}



int abs(int zmienna) {
	if (zmienna < 0) {
		zmienna = -zmienna;
	};
	return zmienna;
}

void analiza_czujnikow(uint32_t wartosci[9]) {

	czujniki[0] = wartosci[8];
	czujniki[1] = wartosci[7];
	czujniki[2] = wartosci[6];
	czujniki[3] = wartosci[5];
	czujniki[4] = wartosci[4];
	czujniki[5] = wartosci[0];
	czujniki[6] = wartosci[1];
	czujniki[7] = wartosci[2];
	czujniki[8] = wartosci[3];

	for (int i = 0; i < 9; ++i) {
		if (czujniki[i] > prog) {
			czujniki[i] = 1;
		} else {
			czujniki[i] = 0;
		};
	};

	kat_prosty = 0;

	if (czujniki[2] + czujniki[3] + czujniki[4] == 3
			&& czujniki[5] + czujniki[6] == 0) {
		kat_prosty = -1;
		przestrzelony = -1;
	} else if (czujniki[6] + czujniki[4] + czujniki[5] == 3
			&& czujniki[2] + czujniki[3] == 0) {
		kat_prosty = 1;
		przestrzelony = 1;
	};

}

int analiza_polozenia() {
	int error = 0;
	int ile = 0;
	int dzielnik = 1;

	// Wolniejsza jazda na zakr�tach

	if (czujniki[0] + czujniki[8] > 0) {
		predkosc_zadana = SPEED_3 * VMED / 100;
		Kp = KP+10;
	} else if (czujniki[1] + czujniki[7] > 0) {
		predkosc_zadana = SPEED_2 * VMED / 100;
		Kp = KP+6;
	} else if (czujniki[2] + czujniki[6] > 0) {
		predkosc_zadana = SPEED_1 * VMED / 100;
		Kp = KP+3;
	} else if (czujniki[3] + czujniki[4] + czujniki[5] > 0) {
		predkosc_zadana = VMED;
		Kp = KP;
	};

	//Nowe wagi dla aktualnej predkosci

	for (int i = 0; i < 9; ++i) {
		wagi[i] = (wzor_wag[i] * predkosc_zadana) / 100;
	};

	//Jezeli przestrzelony to zmniejsz reakcje po powrocie na tras�

	if (przestrzelony != 0) {
		dzielnik = DZIELNIK;
	};

	//Nadanie warto�ci czujnikom

	for (int i = 0; i < 9; ++i) {
		error += czujniki[i] * wagi[i] / dzielnik;
		ile += czujniki[i];
	};

	//Je�li wykrywa lini� to jedzie wed�ug czujnik�w

	if (ile > 0) {
		error /= ile;
	} else if (ile == 0) {

		// Obs�uga przestrzelenia

		if (poprzednia_korekta > wagi[7]) {
			error = wagi[8]*PRZESTRZAL/100;
			przestrzelony = 1;

		} else if (poprzednia_korekta < wagi[1]) {
			error = wagi[0]*PRZESTRZAL/100;
			przestrzelony = -1;
		} else {
			error = poprzednia_korekta;
		};
	};

	//Usuniecie flagi przestrzelenia gdy wroci na tor

	if (przestrzelony == 1 && error <= wagi[5]) {
		przestrzelony = 0;
	} else if (przestrzelony == -1 && error >= wagi[3]) {
		przestrzelony = 0;
	};
	return error;
}

int PD() {
	int rozniczka = 0;
	rozniczka = korekta - poprzednia_korekta;
	poprzednia_korekta = korekta;
	return Kp * korekta / 10 + Kd * rozniczka / 100;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM6) {
		analiza_czujnikow(pomiar);
		korekta = analiza_polozenia();
		regulacja = PD();
		lewy_silnik = predkosc_zadana + regulacja;
		prawy_silnik = predkosc_zadana - regulacja;
	};

	if (htim->Instance == TIM21) {
		HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
	};
}
;

void PWM(int lewy, int prawy) {
	if (lewy >= 0) {
		if (lewy > 999) {
			lewy = 999;
		};
		HAL_GPIO_WritePin(L_1_GPIO_Port, L_1_Pin, 1);
		HAL_GPIO_WritePin(L_2_GPIO_Port, L_2_Pin, 0);
	} else if (lewy < 0) {
		if (lewy < -999) {
			lewy = -999;
		};
		HAL_GPIO_WritePin(L_1_GPIO_Port, L_1_Pin, 0);
		HAL_GPIO_WritePin(L_2_GPIO_Port, L_2_Pin, 1);
	};

	if (prawy >= 0) {
		if (prawy > 999) {
			prawy = 999;
		};
		HAL_GPIO_WritePin(P_1_GPIO_Port, P_1_Pin, 1);
		HAL_GPIO_WritePin(P_2_GPIO_Port, P_2_Pin, 0);
	} else if (prawy < 0) {
		if (prawy < -999) {
			prawy = -999;
		};
		HAL_GPIO_WritePin(P_1_GPIO_Port, P_1_Pin, 0);
		HAL_GPIO_WritePin(P_2_GPIO_Port, P_2_Pin, 1);
	};

	TIM2->CCR1 = abs(lewy);
	TIM2->CCR2 = abs(prawy);
}
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
  MX_DMA_Init();
  MX_ADC_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  MX_TIM21_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADC_Start_DMA(&hadc, pomiar, 9);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim21);
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_Delay(1000);
	  HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
	  /*
	  if (inicjuj == 1) {
	 		prog = pomiar[8] + (pomiar[4] - pomiar[8]) * 2 / 3;
	 		HAL_Delay(2000);
	 		inicjuj = 0;
	 	  };
	  if (zacznij_pomiar == 1) {
		analiza_czujnikow(pomiar);
		korekta = analiza_polozenia();
		regulacja = PD();

		zacznij_pomiar = 0;
		lewy_silnik = predkosc_zadana + regulacja;
		prawy_silnik = predkosc_zadana - regulacja;
	  };
	  if (start == 1) {
		//if (kat_prosty == 0) {

		PWM(lewy_silnik, prawy_silnik);
		/*
		 } else if (kat_prosty == 1) {
		 przestrzelony = 1;
		 HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
		 PWM(VMED / 3, 5);
		 HAL_Delay(33 * 8900 / VMED);
		 HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
		 } else if (kat_prosty == -1) {
		 przestrzelony = -1;
		 HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 1);
		 PWM(5, VMED / 3);
		 HAL_Delay(33 * 8900 / VMED);
		 HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, 0);
		 };*/
	  /*} else if (start == 0) {
		lewy_silnik = 0;
		prawy_silnik = 0;
		PWM(lewy_silnik, prawy_silnik);
	  };
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	 /* HAL_Delay(1000);
	  HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
	  HAL_Delay(1000);
	  HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
	  HAL_Delay(1000);
	  HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
	  */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_39CYCLES_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_2;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_3;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_4;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_6;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_7;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_8;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_9;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 32;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 999;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM21 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM21_Init(void)
{

  /* USER CODE BEGIN TIM21_Init 0 */

  /* USER CODE END TIM21_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM21_Init 1 */

  /* USER CODE END TIM21_Init 1 */
  htim21.Instance = TIM21;
  htim21.Init.Prescaler = 32000;
  htim21.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim21.Init.Period = 999;
  htim21.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim21.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim21) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim21, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim21) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim21, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim21, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM21_Init 2 */

  /* USER CODE END TIM21_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_0_Pin|LED_1_Pin|LED_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, L_2_Pin|L_1_Pin|P_2_Pin|P_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Przycisk_Pin */
  GPIO_InitStruct.Pin = Przycisk_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Przycisk_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_0_Pin LED_1_Pin LED_2_Pin */
  GPIO_InitStruct.Pin = LED_0_Pin|LED_1_Pin|LED_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : L_2_Pin L_1_Pin P_2_Pin P_1_Pin */
  GPIO_InitStruct.Pin = L_2_Pin|L_1_Pin|P_2_Pin|P_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
