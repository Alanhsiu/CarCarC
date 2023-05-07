#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "GUI.h"
#include "mtb_st7789v.h"
#include "cy8ckit_028_tft_pins.h" /* This is part of the CY8CKIT-028-TFT shield library. */
#include "mtb_light_sensor.h"
#include "cy_retarget_io.h"
//#include "LCDConf.h"

#define LIGHT_SENSOR_PIN (P10_0)
cyhal_adc_t adc;
mtb_light_sensor_t light_sensor;
extern GUI_CONST_STORAGE GUI_BITMAP bmYvonne;
/* The pins above are defined by the CY8CKIT-028-TFT library. If the display is being used on different hardware the mappings will be different. */
const mtb_st7789v_pins_t tft_pins =
{
    .db08 = CY8CKIT_028_TFT_PIN_DISPLAY_DB8,
    .db09 = CY8CKIT_028_TFT_PIN_DISPLAY_DB9,
    .db10 = CY8CKIT_028_TFT_PIN_DISPLAY_DB10,
    .db11 = CY8CKIT_028_TFT_PIN_DISPLAY_DB11,
    .db12 = CY8CKIT_028_TFT_PIN_DISPLAY_DB12,
    .db13 = CY8CKIT_028_TFT_PIN_DISPLAY_DB13,
    .db14 = CY8CKIT_028_TFT_PIN_DISPLAY_DB14,
    .db15 = CY8CKIT_028_TFT_PIN_DISPLAY_DB15,
    .nrd  = CY8CKIT_028_TFT_PIN_DISPLAY_NRD,
    .nwr  = CY8CKIT_028_TFT_PIN_DISPLAY_NWR,
    .dc   = CY8CKIT_028_TFT_PIN_DISPLAY_DC,
    .rst  = CY8CKIT_028_TFT_PIN_DISPLAY_RST
};

int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    CY_ASSERT(result == CY_RSLT_SUCCESS);
    Cy_GPIO_Pin_FastInit(P9_7_PORT, P9_7_NUM, CY_GPIO_DM_PULLUP, 1UL, P9_7_GPIO);

	/* UART init failed. Stop program execution */
    CY_ASSERT(result == CY_RSLT_SUCCESS);
    Cy_GPIO_Pin_FastInit(P10_7_PORT, P10_7_NUM, CY_GPIO_DM_PULLUP, 1UL, P10_7_GPIO);
	/* UART init failed. Stop program execution */
    CY_ASSERT(result == CY_RSLT_SUCCESS);
    result = cyhal_adc_init(&adc, LIGHT_SENSOR_PIN, NULL);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    result = mtb_light_sensor_init(&light_sensor, &adc, LIGHT_SENSOR_PIN);
    CY_ASSERT(result == CY_RSLT_SUCCESS);
    __enable_irq();

    /* Initialize the display controller */
    result = mtb_st7789v_init8(&tft_pins);
    CY_ASSERT(result == CY_RSLT_SUCCESS);
    __enable_irq();
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                 CY_RETARGET_IO_BAUDRATE);
    CY_ASSERT(result == CY_RSLT_SUCCESS);
    GUI_Init();
    GUI_SetColor(GUI_WHITE);
    GUI_SetBkColor(GUI_BLUE);
    GUI_SetFont(GUI_FONT_8X16X3X3);
    GUI_SetTextAlign(GUI_TA_CENTER);
//    GUI_Rect rect={0,0,GUI_GetScreenSizeX()/2, GUI_GetScreenSizeY()/2};
//    GUI_DispStringAt("I love Infineon", GUI_GetScreenSizeX()/2, GUI_GetScreenSizeY()/2);
    GUI_DrawBitmap(&bmYvonne,0,0);
//    tLCD_APIList * textDirection=GUI_ROTATE_0;
//    GUI_DispStringInRectEx("Excuse Me", &rect, GUI_TA_HCENTER | GUI_TA_VCENTER, strlen("Excuse Me") - 1, textDirection);
    uint8_t read_data; /* Variable to store the received character
                        * through terminal */
    uint8_t last=0UL;
    uint8_t lastLight=0UL;
    uint8_t light=0UL;
    for(;;)
    {
    	read_data=Cy_GPIO_Read(P9_7_PORT, P9_7_NUM);
    	printf("%d\r\n",read_data);
//    	direction=Cy_GPIO_Read(P9_6_PORT, P9_6_NUM);
//    	textDirection=direction==0UL?GUI_ROTATE_0:GUI_ROTATE_180;
    	if(read_data==1UL&&last!=1UL)
    	{
			GUI_Clear();
		    GUI_SetTextAlign(GUI_TA_CENTER);
		    GUI_DispStringAt("Excuse Me", GUI_GetScreenSizeX()/2, GUI_GetScreenSizeY()/2);
//		    GUI_DispStringInRectEx("Excuse Me", &rect, GUI_TA_HCENTER | GUI_TA_VCENTER, strlen("Excuse Me") - 1, textDirection);
			last=1UL;
    	}
    	else if(read_data==0UL&&last!=0UL)
    	{
			GUI_Clear();
		    GUI_SetTextAlign(GUI_TA_CENTER);
			GUI_DrawBitmap(&bmYvonne,0,0);
//		    GUI_DispStringAt("I love Infineon", GUI_GetScreenSizeX()/2, GUI_GetScreenSizeY()/2);
//		    GUI_DispStringInRectEx("Good Morning", &rect, GUI_TA_HCENTER | GUI_TA_VCENTER, strlen("Good Morning") - 1, textDirection);
			last=0UL;
    	}
    	lastLight=light;
    	light = mtb_light_sensor_light_level(&light_sensor);

    	printf("light: %d %d\r\n",lastLight,light);
    	if(light<=3UL&&lastLight>3UL)
    	{
    		Cy_GPIO_Write(P10_7_PORT, P10_7_NUM,1);
    	}
    	else if(light>3UL&&lastLight<=3UL)
    	{
    		Cy_GPIO_Write(P10_7_PORT, P10_7_NUM,0);
    	}
    	cyhal_system_delay_ms(200);
    }
}
