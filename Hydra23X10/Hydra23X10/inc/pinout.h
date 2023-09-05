//#ifndef pinout_HEADER // prevent double dipping
#define pinout_HEADER
////////////////////////////////////////////////////////////////////////////////
//
// File:    pinout.h
//
////////////////////////////////////////////////////////////////////////////////
//
// Purpose: Contains pinout specific defines, global references, and method prototypes
//
////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013  HYREL 3D, LLC.   All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////
//
// WARNING WARNING WARNING
//
// The STM32F4x series of parts powers on utilizing several pins for JTAG/SW debug
// Care should be take to not use these pins
//
//        PORT A[13] - JTMS/SWDIO    - AF0 - Input w/ pulldown
//        PORT A[14] - JTCK/SWCLK    - AF0 - Input w/ pulldown
//        PORT A[15] - JTDI          - AF0 - Input w/ pullup
//        PORT B[3]  - JTDO/TRACESWO - AF0 - Output pushpull at 50MHz
//        PORT B[4]  - NJTRST        - AF0 - Input w/ pullup
//
// Additionally, two other pins have limited drive (3ma) as they are special input
// to allow the connection of a low speed crystal oscilator and these pins need
// to have low parasitics (see spec)
//
//        PORT C[14]
//        PORT C[15]
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  pinout specific global defines and macros needed by other modules
////////////////////////////////////////////////////////////////////////////////
//#include "main.h"
//Pnp Spi for feeders
#define PnP_Enable		   (PIN_PORT_A | PIN_NUM_09  | PIN_INIT_LOW  | OUTPUT_PP_50MHZ)
#define PnP_Enable_Set     GPIOA->BSRRL = PIN_MASK_09                 //index to the set bit register
#define PnP_Enable_Clr     GPIOA->BSRRH = PIN_MASK_09 //index to the Clear bit register

#define PnP_Rclk		   (PIN_PORT_C | PIN_NUM_11  | PIN_INIT_LOW  | OUTPUT_PP_50MHZ)
#define PnP_Rclk_Set	   GPIOC->BSRRL = PIN_MASK_11                  //index to the set bit register
#define PnP_Rclk_Clr       GPIOC->BSRRH = PIN_MASK_11  //index to the Clear bit register

#define SPi3_Mosi		  (PIN_PORT_C | PIN_NUM_12  | PIN_INIT_LOW  | OUTPUT_PP_50MHZ)
#define SPi3_Sclk		  (PIN_PORT_C | PIN_NUM_10  | PIN_INIT_LOW  | OUTPUT_PP_50MHZ)

//#ifdef USE_AB_ENCODER
#define CO2_LASER_PWM   (PIN_AF_TIM2       | PIN_OTYPE_PUSHPULL | PIN_OSPEED_100MHZ | PIN_PORT_A | PIN_NUM_03 | PIN_INIT_HIGH)


//#define PANEL_ENC_A     (INPUT_PULLUP      | PIN_PORT_A | PIN_NUM_00 | PIN_AF_TIM5)
//#define PANEL_ENC_B     (INPUT_PULLUP      | PIN_PORT_A | PIN_NUM_01 | PIN_AF_TIM5)
//#define PANEL_ENC_SEL   (INPUT_PULLUP      | PIN_PORT_A | PIN_NUM_04)




#define AIN5            (ANALOG_FLOATING   | PIN_PORT_F | PIN_NUM_07)
#define AIN6            (ANALOG_FLOATING   | PIN_PORT_F | PIN_NUM_08)
#define J17_13          (PIN_UNDEFINED     | PIN_PORT_H | PIN_NUM_08)  // undefined
#define J17_14          (PIN_UNDEFINED     | PIN_PORT_H | PIN_NUM_10)  // undefined
#define J17_15          (PIN_UNDEFINED     | PIN_PORT_H | PIN_NUM_09)  // undefined
#define J17_16          (PIN_UNDEFINED     | PIN_PORT_H | PIN_NUM_11)  // undefined


#define X_DIR           (OUTPUT_PP_50MHZ   | PIN_PORT_E | PIN_NUM_05)//X10
#define X_HOME          (INPUT_FLOATING    | PIN_PORT_E | PIN_NUM_01)//X10
#define X_STEP          (OUTPUT_PP_50MHZ   | PIN_PORT_E | PIN_NUM_04)//X10
//#define X_STEP          (OUTPUT_PP_50MHZ   | PIN_PORT_A | PIN_NUM_08)//X10
#define Y_DIR           (OUTPUT_PP_50MHZ   | PIN_PORT_E | PIN_NUM_06)//10
#define Y_HOME          (INPUT_FLOATING      | PIN_PORT_E | PIN_NUM_03)
#define Y_STEP          (OUTPUT_PP_50MHZ   | PIN_PORT_A | PIN_NUM_08)//X10
//#define Y_STEP          (OUTPUT_PP_50MHZ   | PIN_PORT_E | PIN_NUM_04)//X10
#define Z_DIR           (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_14)//x10
#define Z_HOME          (INPUT_FLOATING    | PIN_PORT_E | PIN_NUM_00)
#define Z_STEP          (OUTPUT_PP_50MHZ   | PIN_PORT_B | PIN_NUM_05)
#define A_DIR           (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_06)
#define A_HOME          (INPUT_PULLUP      | PIN_PORT_B | PIN_NUM_03)
#define A_STEP          (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_04)
#define AIN7            (ANALOG_FLOATING   | PIN_PORT_F | PIN_NUM_09)
#define AIN8            (ANALOG_FLOATING   | PIN_PORT_F | PIN_NUM_10)
#define B_DIR           (OUTPUT_PP_50MHZ   | PIN_PORT_B | PIN_NUM_00  | PIN_INIT_LOW)
#define B_HOME          (INPUT_PULLUP      | PIN_PORT_E | PIN_NUM_07)
#define B_STEP          (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_15 | PIN_INIT_LOW)
#define LATHE_STEP      (PIN_AF_TIM9       | PIN_OTYPE_PUSHPULL | PIN_OSPEED_100MHZ | PIN_PORT_E | PIN_NUM_06 | PIN_INIT_HIGH)
#define BOOT1           (PIN_UNDEFINED     | PIN_PORT_B | PIN_NUM_02)  // undefined
#define C_DIR           (OUTPUT_PP_50MHZ   | PIN_PORT_A | PIN_NUM_10)
#define C_HOME          (INPUT_PULLUP      | PIN_PORT_A | PIN_NUM_06)
#define C_L1            (INPUT_PULLUP      | PIN_PORT_C | PIN_NUM_05)  //emo detect
#define C_STEP          (OUTPUT_PP_50MHZ   | PIN_PORT_A | PIN_NUM_02 | PIN_INIT_LOW)

#define CAN1_RX         (PIN_AF_CAN1       | PIN_PORT_D | PIN_NUM_00 | PIN_PUPPD_PULLUP)//PB0
#define CAN1_TX         (PIN_AF_CAN1       | PIN_PORT_D | PIN_NUM_01)                   //PB1
#define CAN2_RX         (PIN_AF_CAN2       | PIN_PORT_B | PIN_NUM_12 | PIN_PUPPD_PULLUP)//PB12
#define CAN2_TX         (PIN_AF_CAN2       | PIN_PORT_B | PIN_NUM_13)                  //PB13
#define DAC2_OUT        (ANALOG_FLOATING   | PIN_PORT_A | PIN_NUM_05)
//#define DRAIN1          (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_11)
//#define DRAIN2          (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_11)
//#define DRAIN3          (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_11)
//#define DRAIN4          (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_11)
#define CAN_TX_LED      (OUTPUT_PP_50MHZ   | PIN_PORT_F | PIN_NUM_06)
#define HEARTBEAT       (OUTPUT_PP_2MHZ    | PIN_PORT_C | PIN_NUM_13)
#define HSS_AUX_PWR1    (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_05)  //M601 J59 pin 1 AUX1
#define HSS_AUX_PWR2    (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_07)  //M602 J59 pin 2 AUX2
#define HSS_AUX_PWR4    (OUTPUT_PP_50MHZ   | PIN_PORT_B | PIN_NUM_04)  //M603 J59 pin 3 AUX4
#define HSS_AUX_PWR5    (OUTPUT_PP_50MHZ   | PIN_PORT_C | PIN_NUM_04)  //M604 J59 pin 4 AUX5
#define HSS_AUX_PWR6    (OUTPUT_PP_50MHZ   | PIN_PORT_D | PIN_NUM_10)  //M605
#define HSS_AUX_PWR7    (OUTPUT_PP_50MHZ   | PIN_PORT_B | PIN_NUM_11)  //M606
#define HSS_AUX_PWR8    (OUTPUT_PP_50MHZ   | PIN_PORT_B | PIN_NUM_10)  //CO2 Laser SSR AC ON
#define HSS_AUX_PWR9    (OUTPUT_PP_50MHZ   | PIN_PORT_E | PIN_NUM_15)  //co2 laser pump
#define J18_13          (PIN_UNDEFINED     | PIN_PORT_B | PIN_NUM_01)  // undefined
#define J18_14          (PIN_UNDEFINED     | PIN_PORT_H | PIN_NUM_03)  // undefined
#define J18_15          (PIN_UNDEFINED     | PIN_PORT_H | PIN_NUM_04)  // undefined
#define J19_9           (PIN_UNDEFINED     | PIN_PORT_H | PIN_NUM_02)  // undefined
#define NC_SPARE        (PIN_UNDEFINED     | PIN_PORT_B | PIN_NUM_10)  // undefined
#define OSC_IN          (PIN_UNDEFINED     | PIN_PORT_H | PIN_NUM_00)  // undefined
#define OSC_OUT         (PIN_UNDEFINED     | PIN_PORT_H | PIN_NUM_01)  // undefined
#define OSC32_IN        (ANALOG_FLOATING   | PIN_PORT_C | PIN_NUM_14)
#define OSC32_OUT       (ANALOG_FLOATING   | PIN_PORT_C | PIN_NUM_15)
#define OTG_FS_DM       (PIN_AF_OTG_FS     | PIN_OSPEED_100MHZ | PIN_PORT_A | PIN_NUM_11)
#define OTG_FS_DP       (PIN_AF_OTG_FS     | PIN_OSPEED_100MHZ | PIN_PORT_A | PIN_NUM_12)
#define OTG_FS_ID       (PIN_AF_OTG_FS     | PIN_OSPEED_100MHZ | PIN_PORT_A | PIN_NUM_10)
#define START           (INPUT_PULLUP      | PIN_PORT_A | PIN_NUM_00)

#define RX3             (PIN_AF_USART3     | PIN_PORT_D | PIN_NUM_09)
#define TX3             (PIN_AF_USART3     | PIN_PORT_D | PIN_NUM_08)
#define RX6             (PIN_AF_USART6     | PIN_PORT_C | PIN_NUM_07)
#define TX6             (PIN_AF_USART6     | PIN_PORT_C | PIN_NUM_06)



#define GB_DEBUG_PIN1           (OUTPUT_PP_50MHZ      | PIN_PORT_F | PIN_NUM_07 | PIN_INIT_LOW)  // sel0
#define GB_DEBUG_PIN1_SET       (GPIOF->BSRRL = GPIO_Pin_7)
#define GB_DEBUG_PIN1_CLEAR     (GPIOF->BSRRH = GPIO_Pin_7)
#define GB_DEBUG_PIN1_READ      (GPIOF->IDR & GPIO_Pin_7)
#define GB_DEBUG_PIN1_TOGGLE    {if (GB_DEBUG_PIN1_READ) {GB_DEBUG_PIN1_CLEAR;} else {GB_DEBUG_PIN1_SET;}}

#define GB_DEBUG_PIN2           (OUTPUT_PP_50MHZ      | PIN_PORT_F | PIN_NUM_08 | PIN_INIT_LOW)
#define GB_DEBUG_PIN2_SET       GPIOF->BSRRL = GPIO_Pin_8
#define GB_DEBUG_PIN2_CLEAR     GPIOF->BSRRH = GPIO_Pin_8

#define GB_DEBUG_PIN3           (OUTPUT_PP_50MHZ      | PIN_PORT_H | PIN_NUM_08 | PIN_INIT_LOW)
#define GB_DEBUG_PIN3_SET       GPIOH->BSRRL = GPIO_Pin_8
#define GB_DEBUG_PIN3_CLEAR     GPIOH->BSRRH = GPIO_Pin_8

#define GB_DEBUG_PIN4           (OUTPUT_PP_50MHZ      | PIN_PORT_H | PIN_NUM_10 | PIN_INIT_LOW)
#define GB_DEBUG_PIN4_SET       GPIOH->BSRRL = GPIO_Pin_10
#define GB_DEBUG_PIN4_CLEAR     GPIOH->BSRRH = GPIO_Pin_10

#define GB_DEBUG_PIN5           (OUTPUT_PP_50MHZ      | PIN_PORT_H | PIN_NUM_09 | PIN_INIT_LOW)
#define GB_DEBUG_PIN5_SET       GPIOH->BSRRL = GPIO_Pin_9
#define GB_DEBUG_PIN5_CLEAR     GPIOH->BSRRH = GPIO_Pin_9

#define GB_DEBUG_PIN6           (OUTPUT_PP_50MHZ      | PIN_PORT_H | PIN_NUM_11 | PIN_INIT_LOW) // sel5
#define GB_DEBUG_PIN6_SET       GPIOH->BSRRL = GPIO_Pin_11
#define GB_DEBUG_PIN6_CLEAR     GPIOH->BSRRH = GPIO_Pin_11

#define PWM_CO2_laserPower		(PIN_AF_TIM4      | PIN_PORT_B | PIN_NUM_08)  //Tim4-<CCR3
#define PWM_Spindle_Speed		(PIN_AF_TIM4      | PIN_PORT_B | PIN_NUM_09)  //Tim4->CCR4 
#define TPIC_6595_D				(OUTPUT_PP_50MHZ  | PIN_PORT_D | PIN_NUM_11 | PIN_INIT_LOW)
#define TPIC_6595_CLR			(OUTPUT_PP_50MHZ  | PIN_PORT_D | PIN_NUM_12 | PIN_INIT_LOW)
#define TPIC_6595_SCLK			(OUTPUT_PP_50MHZ  | PIN_PORT_D | PIN_NUM_13 | PIN_INIT_LOW)//enable
#define TPIC_6595_RCLK			(OUTPUT_PP_50MHZ  | PIN_PORT_B | PIN_NUM_14 | PIN_INIT_LOW)//change on rev 11







#undef J19_10
#undef CO2_LASER_PWM
#undef DAC1_OUT
#define J19_10          PIN_UNDEFINED
#define CO2_LASER_PWM   PIN_UNDEFINED
#define DAC1_OUT        PIN_UNDEFINED



//#define GB_DEBUG_PIN7           (OUTPUT_PP_50MHZ      | PIN_PORT_A | PIN_NUM_00 | PIN_INIT_LOW) // a
//#define GB_DEBUG_PIN7_SET       GPIOA->BSRRL = GPIO_Pin_0
//#define GB_DEBUG_PIN7_CLEAR     GPIOA->BSRRH = GPIO_Pin_0
//
//#define GB_DEBUG_PIN8           (OUTPUT_PP_50MHZ      | PIN_PORT_A | PIN_NUM_01 | PIN_INIT_LOW) // b
//#define GB_DEBUG_PIN8_SET       GPIOA->BSRRL = GPIO_Pin_1
//#define GB_DEBUG_PIN8_CLEAR     GPIOA->BSRRH = GPIO_Pin_1
//
//#define GB_DEBUG_PIN9           (OUTPUT_PP_50MHZ      | PIN_PORT_A | PIN_NUM_04 | PIN_INIT_LOW) // s
//#define GB_DEBUG_PIN9_SET       GPIOA->BSRRL = GPIO_Pin_4
//#define GB_DEBUG_PIN9_CLEAR     GPIOA->BSRRH = GPIO_Pin_4




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define EMO_PIN C_L1

////////////////////////////////////////////////////////////////////////////////
//  Global Variables defined in pinout that can be referenced by other modules
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Public Methods available in pinout
////////////////////////////////////////////////////////////////////////////////


//#endif // #ifndef pinout_HEADER // prevent double dipping - MUST BE LAST LINE OF FILE
