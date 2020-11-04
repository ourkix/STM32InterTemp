
//WSCH_ADC.C文件
#include "stmTemp.h"

/*********************************************************************************************************
** Function name:           User_Adc_Init
** Descriptions:            ADC初始化
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




void User_Adc_Init(void)  //ADC通道初始化
{
    ADC_InitTypeDef ADC_InitStructure; 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1    , ENABLE );   //使能GPIOA,ADC1通道时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //分频因子6时钟为72M/6=12MHz
    
    ADC_DeInit(ADC1);  //将外设 ADC1 的全部寄存器重设为缺省值
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //ADC工作模式:ADC1和ADC2工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;   //模数转换工作在单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //模数转换工作在单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1; //顺序进行规则转换的ADC通道的数目
    ADC_Init(ADC1, &ADC_InitStructure); //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
    ADC_TempSensorVrefintCmd(ENABLE); //开启内部温度传感器
    ADC_Cmd(ADC1, ENABLE);  //使能指定的ADC1
    
    ADC_ResetCalibration(ADC1); //重置指定的ADC1的复位寄存器
    while(ADC_GetResetCalibrationStatus(ADC1)); //获取ADC1重置校准寄存器的状态,设置状态则等待
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));      //获取指定ADC1的校准程序,设置状态则等待
}
 
/*********************************************************************************************************
** Function name:           Get_Adc
** Descriptions:            获取ADC采样值
** input parameters:        ch:通道
** Returned value:          最近一次ADC规则组的转换结果
*********************************************************************************************************/
uint16_t Get_Adc(uint8_t ch)
{
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );  //ADC1,ADC通道3,第一个转换,采样时间为239.5周期                    
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);     //使能指定的ADC1的软件转换启动功能
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
    return ADC_GetConversionValue(ADC1);    //返回最近一次ADC1规则组的转换结果
}
/*********************************************************************************************************
** Function name:           Get_Temp
** Descriptions:            取10次采样值,然后平均
** input parameters:        none
** Returned value:          10次采样平均值
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
** Descriptions:            获取通道ch的转换值，取times次采样值,然后平均
** input parameters:        ch：通道
                            times：采样次数
** Returned value:          times次采样平均值
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
** Descriptions:            获取STM32内部温度传感器的值
** input parameters:        none
** Returned value:          温度值(扩大了100倍,单位:℃.)
*********************************************************************************************************/
short Get_Temprate(void)    //获取内部温度传感器温度值
{
    uint32_t adcx;
    short result;
    double temperate;
    adcx = Get_Adc_Average(ADC_Channel_16,50);  //读取通道16,50次取平均
    temperate = (float)adcx*(3.3/4096);       //电压值 
    temperate = (1.43-temperate)/0.0043+25;   //转换为温度值     
    result = temperate*=100;                  //扩大100倍.
    return result;
}


/*******************************************
*Name: DecToChar
*Description: BCD转字符
*param: *s：源数组
        *d：待写入数组
        DataCnt：数据长度
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
*Description: 将16进制转换成字符型数据
*param: temp:待发送数据
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


