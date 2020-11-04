
//WSCH_ADC.C�ļ�
#include "stmTemp.h"

/*********************************************************************************************************
** Function name:           User_Adc_Init
** Descriptions:            ADC��ʼ��
** input parameters:        none
** Returned value:          none
*********************************************************************************************************/

void Delay_mS(uint16_t ms)
{
	uint32_t i, j;
	j = ms * 19200; // j = ms / 1000.0 * 48000000 / 2.5;  
	for (i=0; i<j; i++) {
	}
} 




void User_Adc_Init(void)  //ADCͨ����ʼ��
{
    ADC_InitTypeDef ADC_InitStructure; 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1    , ENABLE );   //ʹ��GPIOA,ADC1ͨ��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //��Ƶ����6ʱ��Ϊ72M/6=12MHz
    
    ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;   //ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1; //˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC1, &ADC_InitStructure); //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
    ADC_TempSensorVrefintCmd(ENABLE); //�����ڲ��¶ȴ�����
    ADC_Cmd(ADC1, ENABLE);  //ʹ��ָ����ADC1
    
    ADC_ResetCalibration(ADC1); //����ָ����ADC1�ĸ�λ�Ĵ���
    while(ADC_GetResetCalibrationStatus(ADC1)); //��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));      //��ȡָ��ADC1��У׼����,����״̬��ȴ�
}
 
/*********************************************************************************************************
** Function name:           Get_Adc
** Descriptions:            ��ȡADC����ֵ
** input parameters:        ch:ͨ��
** Returned value:          ���һ��ADC�������ת�����
*********************************************************************************************************/
uint16_t Get_Adc(uint8_t ch)
{
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );  //ADC1,ADCͨ��3,��һ��ת��,����ʱ��Ϊ239.5����                    
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);     //ʹ��ָ����ADC1�����ת����������
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
    return ADC_GetConversionValue(ADC1);    //�������һ��ADC1�������ת�����
}
/*********************************************************************************************************
** Function name:           Get_Temp
** Descriptions:            ȡ10�β���ֵ,Ȼ��ƽ��
** input parameters:        none
** Returned value:          10�β���ƽ��ֵ
*********************************************************************************************************/
uint16_t Get_Temp(void)
{
    uint16_t temp_val=0;
    uint8_t t;
    for(t=0;t<10;t++)
    {
        temp_val += Get_Adc(ADC_Channel_16);      //TampSensor
        Delay_mS(5);
    }
    return temp_val/10;
}
/*********************************************************************************************************
** Function name:           Get_Adc_Average
** Descriptions:            ��ȡͨ��ch��ת��ֵ��ȡtimes�β���ֵ,Ȼ��ƽ��
** input parameters:        ch��ͨ��
                            times����������
** Returned value:          times�β���ƽ��ֵ
*********************************************************************************************************/
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times)
{
    uint32_t temp_val=0;
    uint8_t t;
    for(t=0;t<times;t++)
    {
        temp_val += Get_Adc(ch);
        Delay_mS(5);
    }
    return temp_val/times;
}
/*********************************************************************************************************
** Function name:           Get_Temprate
** Descriptions:            ��ȡSTM32�ڲ��¶ȴ�������ֵ
** input parameters:        none
** Returned value:          �¶�ֵ(������100��,��λ:��.)
*********************************************************************************************************/
short Get_Temprate(void)    //��ȡ�ڲ��¶ȴ������¶�ֵ
{
    uint32_t adcx;
    short result;
    double temperate;
    adcx = Get_Adc_Average(ADC_Channel_16,50);  //��ȡͨ��16,50��ȡƽ��
    temperate = (float)adcx*(3.3/4096);       //��ѹֵ 
    temperate = (1.43-temperate)/0.0043+25;   //ת��Ϊ�¶�ֵ     
    result = temperate*=100;                  //����100��.
    return result;
}


/*******************************************
*Name: DecToChar
*Description: BCDת�ַ�
*param: *s��Դ����
        *d����д������
        DataCnt�����ݳ���
********************************************/
void DecToChar(unsigned char *s,unsigned char *d,unsigned char DataCnt)
{
    unsigned char temp1,temp2,i;
    for(i=0;i<DataCnt;i++)
    {
        temp1 = *s/10;
        *d = HexToChar(temp1);
        d = d + 1;
        temp2 = *s%10;
        *d = HexToChar(temp2);
        d = d + 1;
        s = s + 1;
    }
}
/*******************************************
*Name: HexToChar
*Description: ��16����ת�����ַ�������
*param: temp:����������
********************************************/
uint8_t HexToChar(unsigned char temp)
{
    uint8_t dst;
    if (temp < 10)
    {
        dst = temp + '0';
    }
    else
    {
        dst = temp -10 +'A';
    }
    return dst;
}


