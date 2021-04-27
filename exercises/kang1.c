/*******************************************
  名  称：温度参数无线参数传输---接收端程序 
  传感器：WenDUS18B20温湿度传感器
  显 示：LCWenDU1602液晶显示器
  说 明：通过无线通信方式实时接收来自发送端环境温度数值
  		 显示温度。温度0-50
            按键K1、K2、K3设置上下限 
			初始温度：上限30度 下限10度
   报警方式：超过温度1上限时 WenDU1灯亮，蜂鸣器响；
			 低于温度1下限时 WenDU2灯亮，蜂鸣器响；
			 超过温度2上限时 WenDU3灯亮，蜂鸣器响；
			 低于温度2下限时 WenDU4灯亮，蜂鸣器响；
			 正常温湿度范围值时，WenDU1 WenDU2 WenDU3 WenDU4 灯不亮
********************************************/

#include<reg52.h>
#include<intrins.h>
#include  <math.h>

#define not_fu_hao_zhi_fu unsigned char
#define not_fu_hao_zheng_xing unsigned int
#define   ShuJuPort P0	 //定义LCWenDU1602液晶显示器所占用的数据端口   

//****************************************24L01端口与单片机IO口连接设置****************************************

sbit ce_select=P1^0; //发送或接受模式选择端
sbit csn_signal=P1^1; //SPI片选信号
sbit shi_zhong=P1^2; //SPI时钟线
sbit shu_ju_shu_chu=P1^3; //数据输出端
sbit shu_ju_jie_shou=P1^4; //数据接收端
sbit zhong_duan=P1^5; //可屏蔽中断脚
      				  
sbit ye_jing_peng_enable=P2^5;     //LCWenDU1602液晶显示器使能端口	
sbit ye_jing_ping_rs=P2^7;	 //LCWenDU1602液晶显示器数据/命令选择端口
sbit ye_jing_ping_rw=P2^6;	 //LCWenDU1602液晶显示器读/写选择端口

sbit WenDU1=P1^6;	   //温度1过高指示灯
sbit WenDU2=P1^7;	   //温度1过低指示灯
sbit WenDU3=P3^0;	   //温度2过高指示灯
sbit WenDU4=P3^1;	   //温度2过低指示灯

sbit FShiNengGMINGQI=P2^0;	   //蜂鸣器报警控制端

sbit jdq1=P3^3;
sbit jdq2=P3^4;

sbit K1=P3^5;	   //设置键/确定键
sbit K2=P3^6;	   //数字调整键  加1
sbit K3=P3^7;	   //数字调整键  减1

not_fu_hao_zheng_xing wendu1,wendu2; //温度变量类型
not_fu_hao_zheng_xing temperature_h1=30, temperature_l1=10;//温度1上下限变量
not_fu_hao_zheng_xing temperature_h2=30, temperature_l2=10;//温度2上下限变量
not_fu_hao_zhi_fu AnJianBiaoZhi_1=0;   //按键标志位   根据按键次数执行操作内容
not_fu_hao_zheng_xing i=0;//接收到数据标志位
//*********************************************NRF24L01*************************************

#define ChuangKouFaSong_AWenDUR_WIWenDUTH    5   	// 5 not_fu_hao_zheng_xings ChuangKouFaSong address width
#define ChuangKouDu_AWenDUR_WIWenDUTH    5   	// 5 not_fu_hao_zheng_xings ChuangKouDu address width
#define ChuangKouFaSong_PLOAWenDU_WIWenDUTH  20  	// 20 not_fu_hao_zheng_xings ChuangKouFaSong payload
#define ChuangKouDu_PLOAWenDU_WIWenDUTH  20  	// 20 not_fu_hao_zheng_xings ChuangKouFaSong payload

not_fu_hao_zhi_fu const ChuangKouFaSong_AWenDUWenDURESS[ChuangKouFaSong_AWenDUR_WIWenDUTH] = {0x00,0xc2,0xc2,0xc2,0x00};	//本地地址
not_fu_hao_zhi_fu const ChuangKouDu0_AWenDUWenDURESS[ChuangKouDu_AWenDUR_WIWenDUTH]= {0x34,0x43,0x10,0x10,0x03}; 	//接收地址 P0  实际地址为：03-10-10-43-34
not_fu_hao_zhi_fu const ChuangKouDu1_AWenDUWenDURESS[ChuangKouDu_AWenDUR_WIWenDUTH]= {0x35,0x43,0x10,0x10,0x03}; 	//接收地址 P1  实际地址为：03-10-10-43-35
not_fu_hao_zhi_fu const ChuangKouDu2_AWenDUWenDURESS[1]= {0x36}; //接收地址 P2  只写入最低位，其余高位与P1 相同，以下类同   实际地址为:03-10-10-43-36
not_fu_hao_zhi_fu const ChuangKouDu3_AWenDUWenDURESS[1]= {0x37}; //接收地址 P3   实际地址为:03-10-10-43-34
not_fu_hao_zhi_fu const ChuangKouDu4_AWenDUWenDURESS[1]= {0x38}; //接收地址 P4   实际地址为:03-10-10-43-38
not_fu_hao_zhi_fu const ChuangKouDu5_AWenDUWenDURESS[1]= {0x39}; //接收地址 P5  实际地址为:03-10-10-43-39
//***************************************NRF24L01寄存器指令*******************************************************

#define REAWenDU_JiChunQI        0x00  	// 读寄存器指令
#define WRITE_JiChunQI       0x20 	// 写寄存器指令
#define DUXIEenDU_ChuangKouDu_PLOAWenDU     0x61  	// 读取接收数据指令
#define WR_ChuangKouFaSong_PLOAWenDU     0xA0  	// 写待发送数据指令
#define FLUSH_ChuangKouFaSong        0xE1 	// 冲洗发送 FIFO指令
#define FLUSH_ChuangKouDu        0xE2  	// 冲洗接收 FIFO指令
#define REUSE_ChuangKouFaSong_PL     0xE3  	// 定义重复装载数据指令
#define NOP             0xFF  	// 保留

//*************************************SPI(nRF24L01)寄存器地址****************************************************

#define PeiZhi          0x00  // 配置收发状态,CRC校验模式以及收发状态响应方式
#define ShiNeng_AA           0x01  // 自动应答功能设置
#define ShiNeng_ChuangKouDuAWenDUWenDUR       0x02  // 可用信道设置
#define SheZhiUP_AW        0x03  // 收发地址宽度设置
#define SheZhiUP_RETR      0x04  // 自动重发功能设置
#define RF_CH           0x05  // 工作频率设置
#define RF_SheZhiUP        0x06  // 发射速率、功耗功能设置
#define ZhuangTaiUS          0x07  // 状态寄存器
#define OBSERVE_ChuangKouFaSong      0x08  // 发送监测功能
#define CWenDU              0x09  // 地址检测           
#define ChuangKouDu_AWenDUWenDUR_P0      0x0A  // 频道0接收数据地址
#define ChuangKouDu_AWenDUWenDUR_P1      0x0B  // 频道1接收数据地址
#define ChuangKouDu_AWenDUWenDUR_P2      0x0C  // 频道2接收数据地址
#define ChuangKouDu_AWenDUWenDUR_P3      0x0WenDU  // 频道3接收数据地址
#define ChuangKouDu_AWenDUWenDUR_P4      0x0E  // 频道4接收数据地址
#define ChuangKouDu_AWenDUWenDUR_P5      0x0F  // 频道5接收数据地址
#define ChuangKouFaSong_AWenDUWenDUR         0x10  // 发送地址寄存器
#define ChuangKouDu_PW_P0        0x11  // 接收频道0接收数据长度
#define ChuangKouDu_PW_P1        0x12  // 接收频道1接收数据长度
#define ChuangKouDu_PW_P2        0x13  // 接收频道2接收数据长度
#define ChuangKouDu_PW_P3        0x14  // 接收频道3接收数据长度
#define ChuangKouDu_PW_P4        0x15  // 接收频道4接收数据长度
#define ChuangKouDu_PW_P5        0x16  // 接收频道5接收数据长度
#define FIFO_ZhuangTaiUS     0x17  // FIFO栈入栈出状态寄存器设置

//********************************24L01程序部分，详情对照中文手册内容解读*****************************************

void WenDUelay(not_fu_hao_zheng_xing s);
void inerWenDUelay_us(not_fu_hao_zhi_fu n);
void ChuShiHua_NRF24L01(void);
not_fu_hao_zhi_fu SPI_DUXIE(not_fu_hao_zhi_fu byte);
not_fu_hao_zhi_fu SPI_du(not_fu_hao_zhi_fu reg);
not_fu_hao_zhi_fu SPI_DUXIE_Reg(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu value);
not_fu_hao_zhi_fu SPI_du_HuanChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuanChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fus);
not_fu_hao_zhi_fu SPI_xie_HuanChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuanChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fus);
not_fu_hao_zhi_fu nRF24L01_ChuanKouFaReadPacket(not_fu_hao_zhi_fu* rx_buf);
void nRF24L01_ChuanKouFaShuPacket(not_fu_hao_zhi_fu * tx_buf);

/********************延时函数,延时一毫秒************************/

void yanshi(not_fu_hao_zheng_xing z)
{
	not_fu_hao_zheng_xing x,y;
	for(x=112;x>0;x--)
		for(y=z;y>0;y--);
}

/**************************1602显示操作设置****************************/

void xie_ru_zhi_ling(char zhi_ling)  //写指令函数
{
	ye_jing_ping_rs=0;
	P0=zhi_ling;
	yanshi(1);
	ye_jing_peng_enable=1;
	yanshi(1);
	ye_jing_peng_enable=0;
}

void xie_ru_shujua(not_fu_hao_zhi_fu shuju) //写数据函数
{
	ye_jing_ping_rs=1;
	P0=shuju ;
	yanshi(1);
	ye_jing_peng_enable=1;
	yanshi(1);
	ye_jing_peng_enable=0;
}

void xie_ru_ZhiFuChuan(not_fu_hao_zhi_fu *ZhiFuChuan)//写字符串函数
{
	while(*ZhiFuChuan!='\0')
	{
		xie_ru_shujua(*ZhiFuChuan++);
		yanshi(1);
	}
} 

void ChuShiHua_1602() //1602液晶显示器的初始化设置
{ 
	ye_jing_ping_rw=0;
	ye_jing_peng_enable=0;
	xie_ru_zhi_ling(0x38);	//显示模式设置	
	xie_ru_zhi_ling(0x0c);	//显示开关,光标关闭
	xie_ru_zhi_ling(0x06);	//显示光标移动设置
	xie_ru_zhi_ling(0x01);	//清除屏幕
	xie_ru_zhi_ling(0x80);	//数据指针移到第一行第一个位置
}
void wendu_disp_1()   //显示子函数
{	 
	xie_ru_zhi_ling(0x89);
	xie_ru_shujua((temperature_l1/10)%10+48);
	xie_ru_shujua(temperature_l1%10+48);
	xie_ru_ZhiFuChuan("<T<");
	xie_ru_shujua((temperature_h1/10)%10+48);
	xie_ru_shujua(temperature_h1%10+48);

	xie_ru_zhi_ling(0xc9);
	xie_ru_shujua((temperature_l2/10)%10+48);
	xie_ru_shujua(temperature_l2%10+48);
	xie_ru_ZhiFuChuan("<T<");
	xie_ru_shujua((temperature_h2/10)%10+48);
	xie_ru_shujua(temperature_h2%10+48);
}
void AnJianscan()	//按键扫描
{
	if(K1==0)	
	{
		yanshi(5);  //按键消除抖动判断
		if(K1==0)
			{
			 AnJianBiaoZhi_1++;   //键一按下，标志位加一
			 while(!K1);
			}	
	}
	if(AnJianBiaoZhi_1==5){AnJianBiaoZhi_1=0;xie_ru_zhi_ling(0x0c);}
	if(AnJianBiaoZhi_1==1){xie_ru_zhi_ling(0x8a);xie_ru_zhi_ling(0x0d);} //温度1下限末位打开光标 
	if(AnJianBiaoZhi_1==2){xie_ru_zhi_ling(0x8f);xie_ru_zhi_ling(0x0d);} //温度1上限末位打开光标
	if(AnJianBiaoZhi_1==3){xie_ru_zhi_ling(0xca);xie_ru_zhi_ling(0x0d);} //温度2下限末位打开光标 
	if(AnJianBiaoZhi_1==4){xie_ru_zhi_ling(0xcf);xie_ru_zhi_ling(0x0d);} //温度2上限末位打开光标
	if(AnJianBiaoZhi_1!=0)
	{			
		if(K2==0)	//限值加键
		{		
			yanshi(5);   //按键消除抖动判断
			if(K2==0)
			{
				while(!K2);				
				if(AnJianBiaoZhi_1==1)		//下限值加一
				{
					temperature_l1++;
					if(temperature_l1==100)temperature_l1=0;
					xie_ru_zhi_ling(0x89);
					xie_ru_shujua(temperature_l1/10+48);
					xie_ru_shujua(temperature_l1%10+48);
				}
				if(AnJianBiaoZhi_1==2)		//上限值加一
				{
					 temperature_h1++;
	                 if(temperature_h1==100)temperature_h1=0;             
	                 xie_ru_zhi_ling(0x8e);
	                 xie_ru_shujua(temperature_h1/10+48);
					 xie_ru_shujua(temperature_h1%10+48);						 
				}
				
				if(AnJianBiaoZhi_1==3)		//下限值加一
				{
					temperature_l2++;
					if(temperature_l2==100)temperature_l2=0;
					xie_ru_zhi_ling(0xc9);
					xie_ru_shujua(temperature_l2/10+48);
					xie_ru_shujua(temperature_l2%10+48);
				}
				if(AnJianBiaoZhi_1==4)
				{
					 temperature_h2++;
	                 if(temperature_h2==100)temperature_h2=0;             
	                 xie_ru_zhi_ling(0xce);
	                 xie_ru_shujua(temperature_h2/10+48);
					 xie_ru_shujua(temperature_h2%10+48);						 
				}
			}
		} 
		if(K3==0)		  ///限值减键
		{
			yanshi(5);    //按键消除抖动判断
			if(K3==0)
			{
				while(!K3);
				if(AnJianBiaoZhi_1==1)			//下限值减一
				{
					temperature_l1--;
					if(temperature_l1==0)temperature_l1=99;
					xie_ru_zhi_ling(0x89);
					xie_ru_shujua(temperature_l1/10+48);
					xie_ru_shujua(temperature_l1%10+48);
				}
				if(AnJianBiaoZhi_1==2)			  //上限值减一
				{
					 temperature_h1--;
	                 if(temperature_h1==0)temperature_h1=99;             
	                 xie_ru_zhi_ling(0x8e);
	                 xie_ru_shujua(temperature_h1/10+48);
					 xie_ru_shujua(temperature_h1%10+48);						 
				}
				
				if(AnJianBiaoZhi_1==3)			//下限值减一
				{
					temperature_l2--;
					if(temperature_l2==0)temperature_l2=99;
					xie_ru_zhi_ling(0xc9);
					xie_ru_shujua(temperature_l2/10+48);
					xie_ru_shujua(temperature_l2%10+48);
				}
				if(AnJianBiaoZhi_1==4)			  //上限值减一
				{
					 temperature_h2--;
	                 if(temperature_h2==0)temperature_h2=99;             
	                 xie_ru_zhi_ling(0xce);
	                 xie_ru_shujua(temperature_h2/10+48);
					 xie_ru_shujua(temperature_h2%10+48);						 
				}
			}
		} 										
	}	
}

void CallThePolice()	//报警判断函数  
{ 
	if(wendu1<=(temperature_h1*10)&&wendu1>=(temperature_l1*10)&&wendu2<=(temperature_h2*10)&&wendu2>=(temperature_l2*10))   //两个温度为正常值
		 {WenDU1=WenDU2=WenDU3=WenDU4=1;FShiNengGMINGQI=1;} //灯全灭  蜂鸣器不响 

	if(wendu1>(temperature_h1*10))   //温度1大于设定上限值
	     {WenDU1=0;FShiNengGMINGQI=0;} //WenDU1灯亮  蜂鸣器响  
	else {WenDU1=1;}	    
	if(wendu1<(temperature_l1*10))   //温度1低于下限值
		 {WenDU2=0;FShiNengGMINGQI=0;} //WenDU2灯亮  蜂鸣器响 
	else {WenDU2=1;}	  
	
	if(wendu2>(temperature_h2*10))   //温度2大于设定上限值
	     {WenDU3=0;FShiNengGMINGQI=0;} //WenDU3灯亮  蜂鸣器响 
	else {WenDU3=1;}		     
	if(wendu2<(temperature_l2*10))   //温度2低于下限值
		 {WenDU4=0;FShiNengGMINGQI=0;} //WenDU4灯亮  蜂鸣器响 
	else {WenDU4=1;}	
 if((wendu1>(temperature_h1*10))||(wendu2>(temperature_h2*10)))
 jdq1=0;
 else
 jdq1=1;
 if((wendu1<(temperature_l1*10))||(wendu2<(temperature_l2*10)))
	 jdq2=0;
 else
	 jdq2=1;
 
}
//******************************************************************************************

not_fu_hao_zhi_fu 	bshujua sta;   //状态标志
sbit	ChuangKouDu_WenDUR	=sta^6;
sbit	ChuangKouFaSong_WenDUS	=sta^5;
sbit	MAX_RT	=sta^4;

/******************************************************************************************
/*延时函数
/******************************************************************************************/

void inerWenDUelay_us(not_fu_hao_zhi_fu n)
{
	for(;n>0;n--)
		_nop_();
}

//****************************************************************************************
/*NRF24L01初始化
//***************************************************************************************/

void ChuShiHua_NRF24L01(void)
{
    inerWenDUelay_us(100);
 	ce_select=0;    // chip enable
 	csn_signal=1;   // Spi  disable 
 	shi_zhong=0;   // 
	SPI_xie_HuanChun(WRITE_JiChunQI + ChuangKouFaSong_AWenDUWenDUR, ChuangKouFaSong_AWenDUWenDURESS, ChuangKouFaSong_AWenDUR_WIWenDUTH);    // 写发射端地址	
	SPI_xie_HuanChun(WRITE_JiChunQI + ChuangKouDu_AWenDUWenDUR_P0,ChuangKouDu0_AWenDUWenDURESS, ChuangKouDu_AWenDUR_WIWenDUTH);
	SPI_xie_HuanChun(WRITE_JiChunQI + ChuangKouDu_AWenDUWenDUR_P1,ChuangKouDu1_AWenDUWenDURESS, ChuangKouDu_AWenDUR_WIWenDUTH); // 写接收端地址P1
	SPI_xie_HuanChun(WRITE_JiChunQI + ChuangKouDu_AWenDUWenDUR_P2, ChuangKouDu2_AWenDUWenDURESS, 1); // 写接收端地址 P2
 	SPI_xie_HuanChun(WRITE_JiChunQI + ChuangKouDu_AWenDUWenDUR_P3, ChuangKouDu3_AWenDUWenDURESS, 1); // 写接收端地址 P3
 	SPI_xie_HuanChun(WRITE_JiChunQI + ChuangKouDu_AWenDUWenDUR_P4, ChuangKouDu4_AWenDUWenDURESS, 1); // 写接收端地址 P4
 	SPI_xie_HuanChun(WRITE_JiChunQI + ChuangKouDu_AWenDUWenDUR_P5, ChuangKouDu5_AWenDUWenDURESS, 1); // 写接收端地址 P5

	SPI_DUXIE_Reg(WRITE_JiChunQI + ShiNeng_AA, 0x3f);      //  频道0-2自动	ACK应答允许	
	SPI_DUXIE_Reg(WRITE_JiChunQI + ShiNeng_ChuangKouDuAWenDUWenDUR, 0x3f);  //  允许接收地址有频道0-2，如果需要多频道可以参考Page21  
	SPI_DUXIE_Reg(WRITE_JiChunQI + RF_CH, 0);        //   设置信道工作为2.4GHZ，收发必须一致
	
	SPI_DUXIE_Reg(WRITE_JiChunQI + ChuangKouDu_PW_P0, ChuangKouDu_PLOAWenDU_WIWenDUTH); //设置接收数据长度，本次设置为ChuangKouDu_PLOAWenDU_WIWenDUTH字节
	SPI_DUXIE_Reg(WRITE_JiChunQI + ChuangKouDu_PW_P1, ChuangKouDu_PLOAWenDU_WIWenDUTH); //设置接收数据长度，本次设置为32字节
	SPI_DUXIE_Reg(WRITE_JiChunQI + ChuangKouDu_PW_P2, ChuangKouDu_PLOAWenDU_WIWenDUTH); //设置接收数据长度,本次设置为ChuangKouDu_PLOAWenDU_WIWenDUTH字节
  	SPI_DUXIE_Reg(WRITE_JiChunQI + ChuangKouDu_PW_P3, ChuangKouDu_PLOAWenDU_WIWenDUTH); //设置接收数据长度,本次设置为ChuangKouDu_PLOAWenDU_WIWenDUTH字节
 	SPI_DUXIE_Reg(WRITE_JiChunQI + ChuangKouDu_PW_P4, ChuangKouDu_PLOAWenDU_WIWenDUTH); //设置接收数据长度,本次设置为ChuangKouDu_PLOAWenDU_WIWenDUTH字节
 	SPI_DUXIE_Reg(WRITE_JiChunQI + ChuangKouDu_PW_P5, ChuangKouDu_PLOAWenDU_WIWenDUTH); //设置接收数据长度,本次设置为ChuangKouDu_PLOAWenDU_WIWenDUTH字节
	
	SPI_DUXIE_Reg(WRITE_JiChunQI + RF_SheZhiUP, 0x07);   		//设置发射速率为1MHZ，发射功率为最大值0dB
}

//*******************************************************************************************
/****************************************************************************************************
/*函数：not_fu_hao_zheng_xing SPI_DUXIE(not_fu_hao_zheng_xing not_fu_hao_zhi_fu)
/*功能：NRF24L01的SPI写时序
/****************************************************************************************************/

not_fu_hao_zhi_fu SPI_DUXIE(not_fu_hao_zhi_fu byte)
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
/*函数：not_fu_hao_zhi_fu SPI_du(not_fu_hao_zhi_fu reg)
/*功能：NRF24L01的SPI时序
/****************************************************************************************************/

not_fu_hao_zhi_fu SPI_du(not_fu_hao_zhi_fu reg)
{
	not_fu_hao_zhi_fu reg_val;
	
	csn_signal = 0;                // csn_signal low, ChuShiHuaialize SPI communication...
	SPI_DUXIE(reg);            // Select register to read from..
	reg_val = SPI_DUXIE(0);    // ..then read registervalue
	csn_signal = 1;                // csn_signal high, terminate SPI communication
	
	return(reg_val);        // return register value
}

/****************************************************************************************************/
/*功能：NRF24L01读写寄存器函数
/****************************************************************************************************/

not_fu_hao_zhi_fu SPI_DUXIE_Reg(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu value)
{
	not_fu_hao_zhi_fu status;
	
	csn_signal = 0;                   // csn_signal low, ChuShiHua SPI transaction
	status = SPI_DUXIE(reg);      // select register
	SPI_DUXIE(value);             // ..and xie_ru value to it..
	csn_signal = 1;                   // csn_signal high again
	
	return(status);            // return nRF24L01 status not_fu_hao_zhi_fu
}

/****************************************************************************************************/
/*函数：not_fu_hao_zheng_xing SPI_du_HuanChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuanChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fus)
/*功能: 用于读数据，reg：为寄存器地址，pHuanChun：为待读出数据地址，not_fu_hao_zhi_fus：读出数据的个数
/****************************************************************************************************/

not_fu_hao_zhi_fu SPI_du_HuanChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuanChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fus)
{
	not_fu_hao_zhi_fu status,not_fu_hao_zhi_fu_ctr;
	
	csn_signal = 0;                    		// Set csn_signal low, ChuShiHua SPI tranaction
	status = SPI_DUXIE(reg);       		// Select register to xie_ru to and read status not_fu_hao_zhi_fu
	
	for(not_fu_hao_zhi_fu_ctr=0;not_fu_hao_zhi_fu_ctr<not_fu_hao_zhi_fus;not_fu_hao_zhi_fu_ctr++)
		pHuanChun[not_fu_hao_zhi_fu_ctr] = SPI_DUXIE(0);    // 
	
	csn_signal = 1;                           
	
	return(status);                    // return nRF24L01 status not_fu_hao_zhi_fu
}

/*********************************************************************************************************/
/*函数：not_fu_hao_zheng_xing SPI_xie_HuanChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuanChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fus)
/*功能: 用于写数据：为寄存器地址，pHuanChun：为待写入数据地址，not_fu_hao_zhi_fus：写入数据的个数
/*********************************************************************************************************/

not_fu_hao_zhi_fu SPI_xie_HuanChun(not_fu_hao_zhi_fu reg, not_fu_hao_zhi_fu *pHuanChun, not_fu_hao_zhi_fu not_fu_hao_zhi_fus)
{
	not_fu_hao_zhi_fu status,not_fu_hao_zhi_fu_ctr;
	
	csn_signal = 0;            //SPI使能       
	status = SPI_DUXIE(reg);   
	for(not_fu_hao_zhi_fu_ctr=0; not_fu_hao_zhi_fu_ctr<not_fu_hao_zhi_fus; not_fu_hao_zhi_fu_ctr++) //
		SPI_DUXIE(*pHuanChun++);
	csn_signal = 1;           //关闭SPI
	return(status);    // 
}

/******************************************************************************************************
/*函数：unsigned char nRF24L01_ChuanKouFaReadPacket(unsigned char* rx_buf)
/*功能：数据读取后放如rx_buf接收缓冲区中
/******************************************************************************************************/

not_fu_hao_zhi_fu nRF24L01_ChuanKouFaReadPacket(not_fu_hao_zhi_fu *rx_buf)
{	 
    not_fu_hao_zhi_fu revale=0;
	SPI_xie_HuanChun(WRITE_JiChunQI + ChuangKouDu_AWenDUWenDUR_P0,ChuangKouDu0_AWenDUWenDURESS, ChuangKouDu_AWenDUR_WIWenDUTH);
	ce_select=0;
	SPI_DUXIE_Reg(WRITE_JiChunQI + PeiZhi, 0x0f);   		// zhong_duan收发完成中断响应，16位CRC	，主接收
	ce_select = 1; 
	inerWenDUelay_us(130);
	sta=SPI_du(ZhuangTaiUS);	// 读取状态寄存其来判断数据接收状况
	if(ChuangKouDu_WenDUR)				// 判断是否接收到数据
	{	    
		ce_select = 0; 			//SPI使能
		SPI_du_HuanChun(DUXIEenDU_ChuangKouDu_PLOAWenDU,rx_buf,ChuangKouDu_PLOAWenDU_WIWenDUTH);// read receive payload from ChuangKouDu_FIFO buffer
		revale =1;			//读取数据完成标志
		if(i==0){xie_ru_zhi_ling(0x01);i=1;}
		switch(sta%16/2) 
		{	
			case 0:    {
							wendu1=rx_buf[1]*256+rx_buf[2];
							xie_ru_zhi_ling(0x80);					//显示接收的第一个温度值
							xie_ru_ZhiFuChuan("1#");
							xie_ru_shujua(((rx_buf[1]*256+rx_buf[2])/100)%10+48);
							xie_ru_shujua(((rx_buf[1]*256+rx_buf[2])/10)%10+48);
							xie_ru_shujua('.');
							xie_ru_shujua((rx_buf[1]*256+rx_buf[2])%10+48);
							xie_ru_shujua(0xdf);
							xie_ru_shujua('c');  
							xie_ru_ZhiFuChuan(" ");	 	
						break;
						}
	        case 1:     {
						wendu2=rx_buf[1]*256+rx_buf[2];
						xie_ru_zhi_ling(0xc0);						 //显示接收的第二个温度值	
						xie_ru_ZhiFuChuan("2#");
						xie_ru_shujua(((rx_buf[1]*256+rx_buf[2])/100)%10+48);
						xie_ru_shujua(((rx_buf[1]*256+rx_buf[2])/10)%10+48);
						xie_ru_shujua('.');
						xie_ru_shujua((rx_buf[1]*256+rx_buf[2])%10+48);
						xie_ru_shujua(0xdf);
						xie_ru_shujua('c');  
						xie_ru_ZhiFuChuan(" ");
 						break;
						} 
		}
				wendu_disp_1();//显示子函数
				CallThePolice();			//上下限报警	
	}
	SPI_DUXIE_Reg(WRITE_JiChunQI+ZhuangTaiUS,sta);   //接收到数据后ChuangKouDu_WenDUR,ChuangKouFaSong_WenDUS,MAX_PT都置高为1，通过写1来清楚中断标志
	return revale;
}

/***************************主函数**************************/

void  main()
{
    not_fu_hao_zhi_fu ChuanKouFaReadHuanChun[20]={0};
	ChuShiHua_1602();    //1602液晶初始化函数
	ChuShiHua_NRF24L01();
	xie_ru_ZhiFuChuan("Start receiving ");	   
	while(1)
	{  	  
		nRF24L01_ChuanKouFaReadPacket(ChuanKouFaReadHuanChun);	// Transmit ChuanKouFaShu buffer shujua	数据的赋值在此函数内进行 
		AnJianscan();			 //设置温度上下限
		yanshi(100);
		ChuanKouFaReadHuanChun[1] = 0x00; //缓存器1内容清零
		ChuanKouFaReadHuanChun[2] = 0x00; //缓存器2内容清零	

	}										
}

