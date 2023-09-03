#include "main.h"
#include "gpio.h"


#ifdef USE_HYDRA_IO
extern boolean isSpecialBuildMachine(void);
void pinInitAll(void)
{
	//	pinInit(CO2_LASER_PWM);
//		pinInit(PANEL_ENC_A);
//		pinInit(PANEL_ENC_B);
//		pinInit(PANEL_ENC_SEL);;

		pinInit(AIN5);
		pinInit(AIN6);
		pinInit(J17_13);   // undefined
		pinInit(J17_14);   // undefined
		pinInit(J17_15);   // undefined
		pinInit(J17_16);   // undefined



	pinInit(X_DIR);
	pinInit(X_HOME);
	pinInit(X_STEP);
	pinInit(Y_DIR);
	pinInit(Y_HOME);
	pinInit(Y_STEP);
	pinInit(Z_DIR);
	pinInit(Z_HOME);
	pinInit(Z_STEP);
		pinInit(A_DIR);
		pinInit(A_HOME);
		pinInit(A_STEP);
		pinInit(AIN7);
		pinInit(AIN8);
		pinInit(B_DIR);
		pinInit(B_HOME);
		pinInit(B_STEP);
		pinInit(BOOT1);   // undefined
		pinInit(C_DIR);
		pinInit(C_HOME);
		pinInit(C_STEP);
		pinInit(CAN1_RX);
		pinInit(CAN1_TX);
		pinInit(CAN2_RX);
		pinInit(CAN2_TX);

		pinInit(DAC2_OUT);
		pinInit(DRAIN1);
		pinInit(DRAIN2);
		pinInit(DRAIN3);
		pinInit(DRAIN4);
		pinInit(CAN_TX_LED);
		HEARTBEAT_PIN = HEARTBEAT;
		pinInit(HEARTBEAT_PIN);
		pinInit(HSS_AUX_PWR1);
		pinInit(HSS_AUX_PWR2);
		pinInit(HSS_AUX_PWR4);
		pinInit(HSS_AUX_PWR5);
		pinInit(HSS_AUX_PWR6);
		pinInit(HSS_AUX_PWR7);
		pinInit(HSS_AUX_PWR8);
		pinInit(HSS_AUX_PWR9);

		//pinInit(J18_13);   // undefined
		//pinInit(J18_14);   // undefined
		//pinInit(J18_15);   // undefined
		//pinInit(J19_9);   // undefined

		//pinInit(MOTOR_EN);
		pinInit(NC_SPARE);   // undefined
//		pinInit(OSC_IN);   // undefined
//		pinInit(OSC_OUT);   // undefined
//		pinInit(OSC32_IN);
//		pinInit(OSC32_OUT);
//		pinInit(OTG_FS_DM);
//		pinInit(OTG_FS_DP);
//		pinInit(OTG_FS_ID);
		pinInit(RX6);

//		pinInit(SPI3_CS);
//		pinInit(SPI3_MISO);
//		pinInit(SPI3_MOSI);
//		pinInit(SPI3_NSS_NOT);
//		pinInit(SPI3_SCK);
//		pinInit(SPI3_SPARE);
		pinInit(START);
		pinInit(TX6);
	pinInit(PnP_Rclk);
	pinInit(PnP_Enable);
	pinInit(SPi3_Mosi);
	pinInit(SPi3_Sclk);
	
	pinInit(PWM_CO2_laserPower);
	pinInit(PWM_Spindle_Speed);

}
#endif  // USE_HYDRA_IO

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef MEGASONIC_HYDRA
void pinInitAll(void)
{
	HEARTBEAT_PIN = HEARTBEAT;
	pinInit(HEARTBEAT_PIN);
	pinInit(CAN_RX_LED);
	pinInit(CAN_TX_LED);

	pinInit(CAN1_RX);
	pinInit(CAN1_TX);

	pinInit(CAN2_RX);
	pinInit(CAN2_TX);

	pinInit(OTG_FS_DM);
	pinInit(OTG_FS_DP);
}
#endif //MEGASONIC_HYDRA

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifdef MEGASONIC_HYREL
void pinInitAll(void)
{
	HEARTBEAT_PIN = HEARTBEAT;
	pinInit(HEARTBEAT_PIN);
	pinInit(CAN_RX_LED);
	pinInit(CAN_TX_LED);

	pinInit(CAN1_RX);
	pinInit(CAN1_TX);

//  pinInit(OTG_FS_DM);
//  pinInit(OTG_FS_DP);
}
#endif //MEGASONIC_HYREL
