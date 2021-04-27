   /*******************************************
  名  称：温度参数无线传输---发送端程序1
  传感器：WenDuChuanGanQi传感器
  显 示：LCD1602液晶显示器
  说 明：1、实时测试环境温度，1602显示；
         2、24L01无线模块实现无线传输。
********************************************/

#include<reg52.h>
#include<intrins.h>
#include  <math.h>

#define not_fu_hao_zhi_fu unsigned char
#define not_fu_hao_zheng_xing unsigned int
#define   DataPort P0	 //定义LCD1602液晶显示器所占用的数据端口

sbit WDCGQ=P3^7;	     //WenDuChuanGanQi温度传感器  定义使用单片机P37端口   

//**********************24L01端口与单片机IO口连接设置*****************************

sbit ce_select=P1^0; //发送或接受模式选择端
sbit csn_signal=P1^1; //SPI片选信号
sbit shi_zhong=P1^2; //SPI时钟线
sbit shu_ju_shu_chu=P1^3; //数据输出端
sbit shu_ju_jie_shou=P1^4; //数据接收端
sbit zhong_duan=P1^5; //可屏蔽中断脚
       				 
sbit ye_jing_peng_enable=P2^5;     //LCD1602液晶显示器使能端口	
sbit ye_jing_ping_rs=P2^7;	 //LCD1602液晶显示器数据/命令选择端口
sbit ye_jing_ping_rw=P2^6;	 //LCD1602液晶显示器读/写选择端口

not_fu_hao_zheng_xing wendu; //温度变量类型

//*********************************************NRF24L01*************************************

#define ChuangKouFaSong_ADR_KuangDu    5   	// 5 not_fu_hao_zheng_xings ChuangKouFaSong address width
#define ChuangKouDu_ADR_KuangDu    5   	// 5 not_fu_hao_zheng_xings ChuangKouDu address width
#define ChuangKouFaSong_PLOAD_KuangDu  20  	// 20 not_fu_hao_zheng_xings ChuangKouFaSong payload
#define ChuangKouDu_PLOAD_KuangDu  20  	// 20 not_fu_hao_zheng_xings ChuangKouFaSong payload

not_fu_hao_zhi_fu const ChuangKouFaSong_ADDRESS[ChuangKouFaSong_ADR_KuangDu]= {0x34,0x43,0x10,0x10,0x03}; 	//本地地址
not_fu_hao_zhi_fu const ChuangKouDu_ADDRESS[ChuangKouDu_ADR_KuangDu]= {0x34,0x43,0x10,0x10,0x03}; 	//接收地址

//***************************************NRF24L01寄存器指令*******************************************************

#define Du_JiChunQi        0x00  	// 读寄存器指令
#define xie_JiChunQi       0x20 	// 写寄存器指令
#define RD_ChuangKouDu_PLOAD     0x61  	// 读取接收数据指令
#define WR_ChuangKouFaSong_PLOAD     0xA0  	// 写待发送数据指令
#define FLUSH_ChuangKouFaSong        0xE1 	// 冲洗发送 FIFO指令
#define FLUSH_ChuangKouDu        0xE2  	// 冲洗接收 FIFO指令
#define REUSE_ChuangKouFaSong_PL     0xE3  	// 定义重复装载数据指令
#define BaoLiu             0xFF  	// 保留

//*************************************SPI(nRF24L01)寄存器地址****************************************************

#define PeiZhi          0x00  // 配置收发状态,CRC校验模式以及收发状态响应方式
#define ShiNeng_AA           0x01  // 自动应答功能设置
#define ShiNeng_ChuangKouDuADDR       0x02  // 可用信道设置
#define SheZhi_AW        0x03  // 收发地址宽度设置
#define SheZhi_RETR      0x04  // 自动重发功能设置
#define RF_CH           0x05  // 工作频率设置
#define RF_SheZhi        0x06  // 发射速率、功耗功能设置
#define SheZhiUS          0x07  // 状态寄存器
#define OBSERVE_ChuangKouFaSong      0x08  // 发送监测功能
#define CD              0x09  // 地址检测           
#define ChuangKouDu_ADDR_P0      0x0A  // 频道0接收数据地址
#define ChuangKouDu_ADDR_P1      0x0B  // 频道1接收数据地址
#define ChuangKouDu_ADDR_P2      0x0C  // 频道2接收数据地址
#define ChuangKouDu_ADDR_P3      0x0D  // 频道3接收数据地址
#define ChuangKouDu_ADDR_P4      0x0E  // 频道4接收数据地址
#define ChuangKouDu_ADDR_P5      0x0F  // 频道5接收数据地址
#define ChuangKouFaSong_ADDR         0x10  // 发送地址寄存器
#define ChuangKouDu_PW_P0        0x11  // 接收频道0接收数据长度
#define ChuangKouDu_PW_P1        0x12  // 接收频道1接收数据长度
#define ChuangKouDu_PW_P2        0x13  // 接收频道2接收数据长度
#define ChuangKouDu_PW_P3        0x14  // 接收频道3接收数据长度
#define ChuangKouDu_PW_P4        0x15  // 接收频道4接收数据长度
#define ChuangKouDu_PW_P5        0x16  // 接收频道5接收数据长度
#define FIFO_SheZhiUS     0x17  // FIFO栈入栈出状态寄存器设置

//***********************24L01程序部分，详情对照中文手册内容解读***********************

void Yan_Chi(not_fu_hao_zheng_xing s);
void inerYan_Chi_wei_miao(not_fu_hao_zhi_fu n);
void chu_shi_hua_NRF24L01(void);
not_fu_hao_zhi_fu SPI_duxie(not_fu_hao_zhi_fu byte);
not_fu_hao_zhi_fu SPI_duru(not_fu_hao_zhi_fu reg);
not_fu_hao_zhi_fu SPI_duxie_Reg(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu value);
not_fu_hao_zhi_fu SPI_duru_HuangChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuangChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fwei_miao);
not_fu_hao_zhi_fu SPI_Write_HuangChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuangChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fwei_miao);
not_fu_hao_zhi_fu nRF24L01_RxPacket(not_fu_hao_zhi_fu* rx_huanchun);
void nRF24L01_ChuanKouFaShuJuBao(not_fu_hao_zhi_fu * tx_huanchun);


/********************延时函数,延时一毫秒************************/

void YANSHI(not_fu_hao_zheng_xing z)
{
	not_fu_hao_zheng_xing x,y;
	for(x=112;x>0;x--)
		for(y=z;y>0;y--);
}


/**************************1602显示操作设置****************************/

void xie_ru_ming_ling(char ming_ling)  //写指令函数
{
	ye_jing_ping_rs=0;
	P0=ming_ling;
	YANSHI(1);
	ye_jing_peng_enable=1;
	YANSHI(1);
	ye_jing_peng_enable=0;
}

void xie_ru_shu_ju(not_fu_hao_zhi_fu dat) //写数据函数
{
	ye_jing_ping_rs=1;
	P0=dat ;
	YANSHI(1);
	ye_jing_peng_enable=1;
	YANSHI(1);
	ye_jing_peng_enable=0;
}

void xie_ru_zhi_fu_chuan(not_fu_hao_zhi_fu *zhi_fu_chuan)//写字符串函数
{
	while(*zhi_fu_chuan!='\0')
	{
		xie_ru_shu_ju(*zhi_fu_chuan++);
		YANSHI(1);
	}
} 

void chu_shi_hua_1602() //1602液晶显示器的初始化设置
{
	ye_jing_ping_rw=0;
	ye_jing_peng_enable=0;
	xie_ru_ming_ling(0x38);	//显示模式设置	
	xie_ru_ming_ling(0x0c);	//显示开关,光标关闭
	xie_ru_ming_ling(0x06);	//显示光标移动设置
	xie_ru_ming_ling(0x01);	//清除屏幕
	xie_ru_ming_ling(0x80);	//数据指针移到第一行第一个位置
}

/////	 ////			 ds18b20

bit chu_shi_hua_WenDuChuanGanQi()
{ 
	not_fu_hao_zhi_fu num;
	bit flag;
	WDCGQ=1;
	for(num=0;num<2;num++);  //先拉高
	WDCGQ=0;
	for(num=0;num<200;num++);  // 480-960wei_miao	powerup
	WDCGQ=1;
	for(num=0;num<20;num++);	//  >60wei_miao   wait
	flag=WDCGQ;					// 响应
	for(num=0;num<150;num++);	//	 60-240wei_miao ds18b20存在信号
	WDCGQ=1;
	return flag;
}

void WenDuChuanGanQi_WR_CHAR(not_fu_hao_zhi_fu byte)	// 先写低位
{	
	not_fu_hao_zhi_fu num;
	not_fu_hao_zhi_fu num1;
	for(num1=0;num1<8;num1++)
	{	 	
		WDCGQ=0;		//拉低
		_nop_();	//下拉1wei_miao
		_nop_();
		WDCGQ=byte&0x01;
		for(num=0;num<20;num++);	//  >60wei_miao   wait
		byte>>=1;	
		WDCGQ=1;	  //拉高	
		_nop_();
		_nop_();
	}		
}

not_fu_hao_zhi_fu WenDuChuanGanQi_RD_CHAR()	//先读低位
{
	not_fu_hao_zhi_fu num;
	not_fu_hao_zhi_fu num1;
	not_fu_hao_zhi_fu byte=0;
	for(num1=0;num1<8;num1++)
	{
		WDCGQ=0;  	//拉低
		_nop_();
		WDCGQ=1;
		for(num=0;num<1;num++);  // <10wei_miao 	
		byte>>=1;
		if(WDCGQ==1)
			byte|=0x80;
		else 
			byte|=0x00;
		WDCGQ=1;	//拉高
		_nop_();
		_nop_();
		for(num=0;num<20;num++);  //  >60wei_miao
		
	}
	return byte;
}

void WenDuChuanGanQi_WShiNengDU()
{
	not_fu_hao_zhi_fu temperaturel=0;
	not_fu_hao_zhi_fu temperatureh=0;
	if(chu_shi_hua_WenDuChuanGanQi()==0)
	{
		WenDuChuanGanQi_WR_CHAR(0xcc);
		WenDuChuanGanQi_WR_CHAR(0x44);
		YANSHI(1000);
		if(chu_shi_hua_WenDuChuanGanQi()==0)
		{	
			WenDuChuanGanQi_WR_CHAR(0xcc);
			WenDuChuanGanQi_WR_CHAR(0xBE);
			_nop_();
			temperaturel=WenDuChuanGanQi_RD_CHAR();
			temperatureh=WenDuChuanGanQi_RD_CHAR();
			wendu=(temperatureh*256+temperaturel)*0.625; //温度比正常大10倍
			chu_shi_hua_WenDuChuanGanQi();
		}			
	}
}
/***************毫秒延时********************/

void YANSHI_nms(unsigned int k)	
{						
   unsigned int i,j;				
   for(i=0;i<k;i++)
{			
   for(j=0;j<121;j++)			
{;}}						
}
//******************************************************************************************

not_fu_hao_zhi_fu 	bshu_ju sta;   //状态标志
sbit	ChuangKouDu_DR	=sta^6;
sbit	ChuangKouFaSong_DS	=sta^5;
sbit	MAX_RT	=sta^4;

/******************************************************************************************
/*延时函数
/******************************************************************************************/

void inerYan_Chi_wei_miao(not_fu_hao_zhi_fu n)
{
	for(;n>0;n--)
		_nop_();
}

//****************************************************************************************
/*NRF24L01初始化
//***************************************************************************************/

void chu_shi_hua_NRF24L01(void)
{
    inerYan_Chi_wei_miao(100);
 	ce_select=0;    // chip enable
 	csn_signal=1;   // Spi  disable 
 	shi_zhong=0;   // 
	SPI_Write_HuangChun(xie_JiChunQi + ChuangKouFaSong_ADDR, ChuangKouFaSong_ADDRESS, ChuangKouFaSong_ADR_KuangDu);    // 写发射端地址	
	SPI_Write_HuangChun(xie_JiChunQi + ChuangKouDu_ADDR_P0,ChuangKouDu_ADDRESS, ChuangKouDu_ADR_KuangDu);	 // 写接收端地址
	SPI_duxie_Reg(xie_JiChunQi + ShiNeng_AA, 0x03);      //  频道1自动	ACK应答允许	
	SPI_duxie_Reg(xie_JiChunQi + ShiNeng_ChuangKouDuADDR, 0x03);  //  允许接收地址只有频道1，如果需要多频道可以参考Page21  
	SPI_duxie_Reg(xie_JiChunQi + RF_CH, 0);        //   设置信道工作为2.4GHZ，收发必须一致
	SPI_duxie_Reg(xie_JiChunQi + ChuangKouDu_PW_P0, ChuangKouDu_PLOAD_KuangDu); //设置接收数据长度，本次设置为32字节
	SPI_duxie_Reg(xie_JiChunQi + RF_SheZhi, 0x07);   		//设置发射速率为1MHZ，发射功率为最大值0dB
}

//*******************************************************************************************
/****************************************************************************************************
/*函数：not_fu_hao_zheng_xing SPI_duxie(not_fu_hao_zheng_xing not_fu_hao_zhi_fu)
/*功能：NRF24L01的SPI写时序
/****************************************************************************************************/

not_fu_hao_zhi_fu SPI_duxie(not_fu_hao_zhi_fu byte)
{
	not_fu_hao_zhi_fu bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		shu_ju_shu_chu = (byte & 0x80);         // output 'not_fu_hao_zhi_fu', MSB to shu_ju_shu_chu
		byte = (byte << 1);           // shift next bit into MSB..
		shi_zhong = 1;                      // Set shi_zhong high..
		byte |= shu_ju_jie_shou;       		  // capture current shu_ju_jie_shou bit
		shi_zhong = 0;            		  // ..then set shi_zhong low again
   	}
    return(byte);           		  // return read not_fu_hao_zhi_fu
}

/****************************************************************************************************
/*函数：not_fu_hao_zhi_fu SPI_duru(not_fu_hao_zhi_fu reg)
/*功能：NRF24L01的SPI时序
/****************************************************************************************************/

not_fu_hao_zhi_fu SPI_duru(not_fu_hao_zhi_fu reg)
{
	not_fu_hao_zhi_fu reg_val;
	
	csn_signal = 0;                // csn_signal low, chu_shi_huaialize SPI communication...
	SPI_duxie(reg);            // Select register to read from..
	reg_val = SPI_duxie(0);    // ..then read registervalue
	csn_signal = 1;                // csn_signal high, terminate SPI communication
	
	return(reg_val);        // return register value
}

/****************************************************************************************************/
/*功能：NRF24L01读写寄存器函数
/****************************************************************************************************/

not_fu_hao_zhi_fu SPI_duxie_Reg(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu value)
{
	not_fu_hao_zhi_fu statwei_miao;
	
	csn_signal = 0;                   // csn_signal low, chu_shi_hua SPI transaction
	statwei_miao = SPI_duxie(reg);      // select register
	SPI_duxie(value);             // ..and xie_ru value to it..
	csn_signal = 1;                   // csn_signal high again
	
	return(statwei_miao);            // return nRF24L01 statwei_miao not_fu_hao_zhi_fu
}

/*********************************************************************************************************/
/*函数：not_fu_hao_zheng_xing SPI_Write_HuangChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuangChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fwei_miao)
/*功能: 用于写数据：reg为寄存器地址，pHuangChun：为待写入数据地址，not_fu_hao_zhi_fwei_miao：写入数据的个数
/*********************************************************************************************************/

not_fu_hao_zhi_fu SPI_Write_HuangChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuangChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fwei_miao)
{
	not_fu_hao_zhi_fu statwei_miao,not_fu_hao_zhi_fu_ctr;
	
	csn_signal = 0;            //SPI使能       
	statwei_miao = SPI_duxie(reg);   
	for(not_fu_hao_zhi_fu_ctr=0; not_fu_hao_zhi_fu_ctr<not_fu_hao_zhi_fwei_miao; not_fu_hao_zhi_fu_ctr++) //
		SPI_duxie(*pHuangChun++);
	csn_signal = 1;           //关闭SPI
	return(statwei_miao);    // 
}

/***********************************************************************************************************/
/*函数：void nRF24L01_ChuanKouFaShuJuBao(unsigned char * tx_huanchun)
/*功能：发送 tx_huanchun中数据
/**********************************************************************************************************/

void nRF24L01_ChuanKouFaShuJuBao(not_fu_hao_zhi_fu *tx_huanchun)
{
	ce_select=0;			//StandBy I模式	
	SPI_Write_HuangChun(xie_JiChunQi + ChuangKouFaSong_ADDR, ChuangKouFaSong_ADDRESS, ChuangKouFaSong_ADR_KuangDu);
	SPI_Write_HuangChun(xie_JiChunQi + ChuangKouDu_ADDR_P0, ChuangKouFaSong_ADDRESS, ChuangKouFaSong_ADR_KuangDu); // 发射端地址
	SPI_Write_HuangChun(WR_ChuangKouFaSong_PLOAD, tx_huanchun, ChuangKouFaSong_PLOAD_KuangDu); 			 // 装载数据	
	SPI_duxie_Reg(xie_JiChunQi + PeiZhi, 0x0e);   		 // zhong_duan收发完成中断响应，16位CRC，主发送
	ce_select=1;		 //置高ce_select，激发数据发送
	inerYan_Chi_wei_miao(20);	
}

/***************************主函数**************************/

main()
{
    not_fu_hao_zhi_fu TxHuangChun[20]={0};
	YANSHI_nms(200);	    //延时200ms	
	chu_shi_hua_1602();
	chu_shi_hua_NRF24L01();

	while(1)
	{  
		if( chu_shi_hua_WenDuChuanGanQi()==0)  	
     	{   
			WenDuChuanGanQi_WShiNengDU(); 
			xie_ru_ming_ling(0x80);
			xie_ru_zhi_fu_chuan(" temperature 1#");
			xie_ru_ming_ling(0x80+0x44);
			xie_ru_shu_ju((wendu/100)%10+48);
			xie_ru_shu_ju((wendu/10)%10+48);
			xie_ru_shu_ju('.');
			xie_ru_shu_ju(wendu%10+48);
			xie_ru_shu_ju(0xdf);
			xie_ru_shu_ju('c'); 
			TxHuangChun[1]=wendu/256;	  //将高八位装入
			TxHuangChun[2]=wendu%256;	  //装入低八位
		} 	 	
		nRF24L01_ChuanKouFaShuJuBao(TxHuangChun);	// Transmit Tx huanchunfer shu_ju   发送数据
		TxHuangChun[1] = 0x00;    //缓存器1内容清零
		TxHuangChun[2] = 0x00;    //缓存器2内容清零
		sta=SPI_duru(SheZhiUS);
		SPI_duxie_Reg(xie_JiChunQi+SheZhiUS,sta);
		csn_signal=0;
		SPI_duxie(FLUSH_ChuangKouFaSong);   //清空发送缓冲
		csn_signal=1;
	}										
}

