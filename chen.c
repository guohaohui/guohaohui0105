#include <reg52.h>	         //调用单片机头文件
#define urch unsigned char  //无符号字符型 宏定义	变量范围0~255
#define urin  unsigned int	 //无符号整型 宏定义	变量范围0~65535

#include "lcd1602.h"
#include "iic.h"

urch bianliangzhi,i;		//变量

urch biao_shi_la_en;  //边加
urch biao_shi_la_en_bianliangzhi;

sbit jidianqidingyi = P2^2;  //继电器定义
sbit feng_ming_qi_ding_yi  = P3^3;  //蜂鸣器定义

sbit beiguan = P2^3;  //背光

urin biao_shi_shi_jian;

urch huan_chunf[5];
urch biao_shi___en;

urin biao_shi___guan;

urch shu_ma_guan_i;
urch dis_shu_ma_guan[7]={0};

urch MiMaBaoChun[7]={6,5,4,3,2,1};	    //密码保存
urch MiMaBaoChun_bj[7]={1,2,3,4,5,6};	//密码比较
urch code MiMaBaoChun_r[6] = {1,2,3,1,2,3} ;
urch code MiMaBaoChun_gl[6] = {5,2,0,0,2,5} ;
urch MiMaBaoChun_xg[6];	//密码修改
urch biao_shi___MiMaBaoChun;      //密码正确否
urch biao_shi___MiMaBaoChun_cichu1;//密码错误次数

bit biao_shi___200ms=1;     //200ms标志位

urch an_jian_can;

urch mimneu_1,mimneu_i;



#include "iic.h"


/***********************1ms延时函数*****************************/
void yan_shi_1ms(urin q)
{
	urin i,j;
	for(i=0;i<q;i++)
		for(j=0;j<120;j++);
}


void an_jian()	 //独立按键程序
{
	static urch an_jian_new = 0, an_jian_l;
	an_jian_can = 20;                   //按键值还原
	P1 = 0x0f;
	if((P1 & 0x0f) != 0x0f)		//按键按下
	{
		yan_shi_1ms(1);	     	//按键消抖动
		if(((P1 & 0x0f) != 0x0f) && (an_jian_new == 1))
		{						//确认是按键按下
			an_jian_new = 0;
			an_jian_l = (P1 | 0xf0);   //矩阵键盘扫描
			P1 = an_jian_l;
			switch(P1)
			{
				case 0xee:  an_jian_can = 1;  break;  //得到按键值 
				case 0xde:  an_jian_can = 4;  break;   //得到按键值 
				case 0xbe:  an_jian_can = 7;  break;   //得到按键值 
				case 0x7e:  an_jian_can = 10;  break;   //得到按键值 
	
				case 0xed:  an_jian_can = 0;  break;  //得到按键值 
				case 0xdd:  an_jian_can = 8;  break;   //得到按键值 
				case 0xbd:  an_jian_can = 5;  break;   //得到按键值 
				case 0x7d:  an_jian_can = 2;  break;   //得到按键值 
	
				case 0xeb:  an_jian_can = 3;  break;  //得到按键值 
				case 0xdb:  an_jian_can = 6;  break;   //得到按键值 
				case 0xbb:  an_jian_can = 9;  break;   //得到按键值 
				case 0x7b:  an_jian_can = 11;  break;   //得到按键值 
	
				case 0xe7:  an_jian_can = 15;  break;  //得到按键值 
				case 0xd7:  an_jian_can = 14;  break;  //得到按键值 
				case 0xb7:  an_jian_can = 13;  break;   //得到按键值 
				case 0x77:  an_jian_can = 12;  break;  //得到按键值  

			}	
		}			
	}
	else 
	{
		an_jian_new = 1;
		biao_shi_la_en = 0;
	}	
}


/*****************密码还原********************/
void MiMaBaoChun_return()
{
	
	if(biao_shi_la_en == 1)
	{
		biao_shi_la_en_bianliangzhi ++;
		if(biao_shi_la_en_bianliangzhi > 13)	 //按下3秒钟就自动密码还原	
		{
			biao_shi_la_en_bianliangzhi = 0;	
			biao_shi_la_en = 0;
			write_24c02_8(6,0,MiMaBaoChun_r);		
			feng_ming_qi_ding_yi = 0;
			yan_shi_1ms(500);
			feng_ming_qi_ding_yi = 1;	  
			read_24c02_8(6,0,MiMaBaoChun);
		}
	}		
}

/***************把数组清空**********************/
void qing_kong_shuzu(urch *p)
{
	for(i=0;i<7;i++)
		p[i] = 0;
}

/*************定时器0初始化程序***************/
void time_init()	  
{
	EA   = 1;	 	  //开总中断
	TMOD = 0X11;	  //定时器0、工作方式1
	ET0  = 1;		  //开定时器0中断 
	TR0  = 1;		  //允许定时器0定时
}

/******************下载程序密码初始化**********************/	   
void MiMaBaoChun_chushifa()
{
	scl = 0;
	bianliangzhi = read_24c02(10) ;
	if(bianliangzhi != 75)
	{
		bianliangzhi = 75;
		feng_ming_qi_ding_yi = 0;
		write_24c02(10,bianliangzhi);
		yan_shi_1ms(200);
		write_24c02_8(6,0,MiMaBaoChun_r);
		yan_shi_1ms(200);
		read_24c02_8(6,0,MiMaBaoChun);
		feng_ming_qi_ding_yi = 1;	  
	}
}


/****************按键功能处理********************/	   
void an_jian_with()
{
	static urch bianliangzhi;
	if(an_jian_can == 14)   //手动关闭密码锁
		jidianqidingyi = 1;
	if(an_jian_can == 10)	 //用做密码从新回到初始值 
	{				  
	   biao_shi_la_en = 1;	  //连加使能
	   biao_shi_la_en_bianliangzhi = 0;
	}
	if(mimneu_1 == 0)
	{
		if(an_jian_can <= 9)
		if(mimneu_i < 6)   //密码输入
		{
			mimneu_i ++;
			if(mimneu_i > 6)
				mimneu_i = 6;
			shu_ma_guan_i = mimneu_i;
			for(i=6;i>0;i--)
				MiMaBaoChun_bj[i] = MiMaBaoChun_bj[i-1];	
			MiMaBaoChun_bj[0] = an_jian_can;
			for(i=0;i<shu_ma_guan_i;i++)
				dis_shu_ma_guan[i] ='*';//0x30 + MiMaBaoChun_bj[i];
			write_string(2,7,dis_shu_ma_guan);	
			lcd1602_guanbiao(1,7 + mimneu_i + 0x40);  //开光标
		}	
		if(an_jian_can == 11) 	//密码删除
		{
			for(i=0;i<mimneu_i;i++)
				MiMaBaoChun_bj[i] = MiMaBaoChun_bj[i+1];	  
			mimneu_i --;
			MiMaBaoChun_bj[mimneu_i] = ' ';	
			dis_shu_ma_guan[mimneu_i] = ' ';
			write_string(2,7,dis_shu_ma_guan);	
			lcd1602_guanbiao(1,7 + mimneu_i + 0x40);  //开光标
		}
		if(an_jian_can == 15)  //确认键
		{
			bianliangzhi = 0;
			for(i=0;i<6;i++)
			{
				if(MiMaBaoChun_bj[i] == MiMaBaoChun_gl[i]) //判断管理员密码
				{
				 	bianliangzhi ++;
					if(bianliangzhi >= 6)  //密码正确
					{
						write_string(2,0,"    return      ");
						feng_ming_qi_ding_yi = 0;
						yan_shi_1ms(200);
						read_24c02_8(6,0,MiMaBaoChun);
						feng_ming_qi_ding_yi = 1;	  
						yan_shi_1ms(2000);
					}
				}
			}
			if(bianliangzhi < 6)
			for(i=0;i<6;i++)
			{
				if(MiMaBaoChun_bj[i] == MiMaBaoChun[i])
				{
					biao_shi___MiMaBaoChun = 1;	 //密码正确
					jidianqidingyi = 0;     //打开密码锁
					for(i=0;i<6;i++)
						dis_shu_ma_guan[i] = 0xbf;
				}
				else 
				{
					biao_shi___MiMaBaoChun = 0;
					biao_shi___MiMaBaoChun_cichu1 ++;
					write_string(1,0," Password error ");	
					write_string(2,0,"   cishu:       ");
					write_sfm2(2,9,biao_shi___MiMaBaoChun_cichu1);
					yan_shi_1ms(280);
			
					for(i=0;i<6;i++)
					{
						feng_ming_qi_ding_yi = ~beep;
						yan_shi_1ms(200);
					}
					feng_ming_qi_ding_yi = 1;
					yan_shi_1ms(800);
					break;               //密码不正确
				}
			}
			qing_kong_shuzu(dis_shu_ma_guan); 
			write_string(1,0," Password Lock  ");	
			write_string(2,0," Input:         ");
			lcd1602_guanbiao(1,7+0x40);  //开光标
			mimneu_i = 0;
		}
	}									
}

/****************修改密码********************/	   
void xiugai_MiMaBaoChun()
{
	if(an_jian_can == 13)   //修改密码
	{
		if((jidianqidingyi == 0) && (mimneu_1 == 0))
		{
			mimneu_1 = 1;	mimneu_i = 0;
			qing_kong_shuzu(MiMaBaoChun_bj); 	 //数据清空
			qing_kong_shuzu(dis_shu_ma_guan); 
			write_string(1,0,"Input1:          ");	
			write_string(2,0,"Input2:          ");
			lcd1602_guanbiao(1,7);  //开光标
		}	
	}
	if(mimneu_1 == 1)   //第一次输入修改的密码
	{
		if(an_jian_can <= 9)
		{
			if(mimneu_i < 6)
			{
				mimneu_i ++;
				if(mimneu_i > 6)
					mimneu_i = 6;
				shu_ma_guan_i = mimneu_i;
				for(i=7;i>0;i--)
					MiMaBaoChun_bj[i] = MiMaBaoChun_bj[i-1];	
				MiMaBaoChun_bj[0] = an_jian_can;
				for(i=0;i<mimneu_i;i++)
					dis_shu_ma_guan[i] ='*';
				write_string(1,7,dis_shu_ma_guan);
				lcd1602_guanbiao(1,7 + mimneu_i);  //开光标	
			}	
		}
		if(an_jian_can == 11)  //删除键
		{
			for(i=0;i<mimneu_i;i++)
				MiMaBaoChun_bj[i] = MiMaBaoChun_bj[i+1];	
			mimneu_i --;
			MiMaBaoChun_bj[mimneu_i] = ' ';	
			dis_shu_ma_guan[mimneu_i] = ' ';
			write_string(1,7,dis_shu_ma_guan);	
			lcd1602_guanbiao(1,7 + mimneu_i);  //开光标	
		}	
		if(an_jian_can == 15)  //确定键
		{
			qing_kong_shuzu(MiMaBaoChun_xg); 
			qing_kong_shuzu(dis_shu_ma_guan); 
			lcd1602_guanbiao(1,8 + 0x40);  //开光标
			mimneu_1 = 2;
		    mimneu_i = 0;
			an_jian_can = 20;
		}
	}
	if(mimneu_1 == 2)   //第二次输入修改的密码
	{
		if(an_jian_can <= 9)
		{
			if(mimneu_i < 6)
			{
				mimneu_i ++;		
				if(mimneu_i > 6)
					mimneu_i = 6;
				for(i=5;i>0;i--)
					MiMaBaoChun_xg[i] = MiMaBaoChun_xg[i-1];	
				MiMaBaoChun_xg[0] = an_jian_can;
				for(i=0;i<mimneu_i;i++)
					dis_shu_ma_guan[i] ='*';//0x30 + MiMaBaoChun_xg[i];
				write_string(2,7,dis_shu_ma_guan);	   
				lcd1602_guanbiao(1,7 + mimneu_i + 0x40);  //开光标
			}	
		}
		if(an_jian_can == 11)  //删除键
		{
			for(i=0;i<mimneu_i;i++)
				MiMaBaoChun_xg[i] = MiMaBaoChun_xg[i+1];	
			MiMaBaoChun_xg[mimneu_i] = ' ';	
			dis_shu_ma_guan[mimneu_i] = ' ';
			write_string(2,7,dis_shu_ma_guan);	
			lcd1602_guanbiao(1,7 + mimneu_i + 0x40);  //开光标
		}	
		if(an_jian_can == 15)  //确定键
		{
			for(i=0;i<6;i++)
			{
				if(MiMaBaoChun_bj[i] == MiMaBaoChun_xg[i])
				{
					biao_shi___MiMaBaoChun = 1;	 //两次输入的密码一样			
				}
				else 
				{
					biao_shi___MiMaBaoChun = 0;
					write_string(1,0," Password Error ");	
					write_string(2,0,"     reenter    ");
					yan_shi_1ms(300);
					for(i=0;i<6;i++)
					{
						feng_ming_qi_ding_yi = ~beep;		//提示三声
						yan_shi_1ms(300);
					}
					feng_ming_qi_ding_yi = 1;
					yan_shi_1ms(1000);
					break;               //密码不正确
				}
			}
			if(biao_shi___MiMaBaoChun == 1)		 //两次输入的密码一样的
			{			
				for(i=0;i<6;i++)
				{
					write_string(1,0,"    Password    ");	
					write_string(2,0,"    Succeed     ");
					MiMaBaoChun[i] = MiMaBaoChun_bj[i];   //保存密码
				}
				write_24c02_8(6,0,MiMaBaoChun);
				yan_shi_1ms(300);
				feng_ming_qi_ding_yi = 0;
				yan_shi_1ms(2000);
				feng_ming_qi_ding_yi = 1;
			}
			qing_kong_shuzu(MiMaBaoChun_xg); 
			qing_kong_shuzu(dis_shu_ma_guan); 
			write_string(1,0," Password Lock  ");	
			write_string(2,0," Input:         ");
			lcd1602_guanbiao(1,7+0x40);  //开光标
			mimneu_1 = 0;
		    mimneu_i = 0;

		}
	}	
}  



/****************串口初始化程序*******************/	   
void init_uart()  //串口初始化程序
{
	EA = 1;
	ES = 1;	 
	TR1 = 1;
	SCON = 0X50;	   //串口方式1
	TMOD |= 0X20;
	TH1 = 0XFD;
	TL1 = 0XFD;
}

/******************蓝牙*********************/	   
void lianya_kz()   //蓝牙
{
	if(huan_chunf[0]=='O'&&huan_chunf[1]=='N')	//第一个字节为O，第二个字节为N，第三个字节为控制码
	{
	 	if(huan_chunf[2] == 'A')	  // 上
			an_jian_can = 15;
	 	if(huan_chunf[2] == 'B')	  // 下
			an_jian_can = 12;
	 	if(huan_chunf[2] == 'C')	  // 左
		{
			an_jian_can = 11;
			if(mimneu_1 == 0)
				jidianqidingyi = 1; 
		}
	 	if(huan_chunf[2] == 'D')	  // 右
			an_jian_can = 13;
	 	if(huan_chunf[2] == 'E')	  // 
			an_jian_can = 0;
	 	if(huan_chunf[2] == '1')	
			an_jian_can = 1;
	 	if(huan_chunf[2] == '2')
			an_jian_can = 2;	
	 	if(huan_chunf[2] == '3')
			an_jian_can = 3;	
	 	if(huan_chunf[2] == '4')
			an_jian_can = 4;	
	 	if(huan_chunf[2] == '5')
			an_jian_can = 5;	
	 	if(huan_chunf[2] == '6')
			an_jian_can = 6;	
	 	if(huan_chunf[2] == '7')
			an_jian_can = 7;	
	 	if(huan_chunf[2] == '8')
			an_jian_can = 8;	
	 	if(huan_chunf[2] == '9')
			an_jian_can = 9;
		feng_ming_qi_ding_yi = 0;
		yan_shi_1ms(20);
		feng_ming_qi_ding_yi = 1;
	}
}



/******************主程序**********************/	   
void main()
{
	static urin bianliangzhi ;
	MiMaBaoChun_chushifa();
	time_init();   //定时器初始化
	read_24c02_8(6,0,MiMaBaoChun);
	init_1602(); 
	beiguan = 0;
	lianya_kz() ;  //蓝牙
	while(1)
	{	
		if(biao_shi___MiMaBaoChun_cichu1 < 3)     //错误三次按键不能用了
		{
			lianya_kz();   //蓝牙
			an_jian();					 //按键函数
			if(an_jian_can < 20)
			{
				if(beiguan == 0)
				{
					if(mimneu_1 == 0)
						an_jian_with();			 //按键处理函数
					xiugai_MiMaBaoChun();       //修改密码
				}
				else 
					beiguan = 0;
				biao_shi_shi_jian = 0;		
			}
		}

		if(biao_shi___200ms == 1)
		{
			biao_shi___200ms = 0;	 
			if(beiguan == 0)	 //延时关闭锁20秒关闭背光
			{
				biao_shi_shi_jian ++;
//				write_sfm2(2,10,biao_shi_shi_jian);
				if(biao_shi_shi_jian >= 5 * 30)	//30秒  
				{
					biao_shi_shi_jian = 0;
					beiguan = 1;	//关闭背光
				}
			}
			if(jidianqidingyi == 0)  //延时关闭锁
			{
				biao_shi___guan++;
				if(biao_shi___guan >= 5 * 10)	//10秒  
				{
					biao_shi___guan = 0;
				    jidianqidingyi = 1;   //关闭密码锁
				}
			}else 
				biao_shi___guan = 0;	
			if(biao_shi___MiMaBaoChun_cichu1 >= 3)
			{
				bianliangzhi ++;	   //200ms
				feng_ming_qi_ding_yi = ~beep;  //蜂鸣器报警
				if(bianliangzhi >= 5 * 60)	//1分钟  
				{
					bianliangzhi = 0;
					feng_ming_qi_ding_yi = 1;
					biao_shi___MiMaBaoChun_cichu1 = 0;
				}
			}
			MiMaBaoChun_return();		 //密码还原
		}
		yan_shi_1ms(1);  
	}
}

/*************定时器0中断服务程序***************/
void time0_int() interrupt 1
{	
	static urch bianliangzhi;
	TH0 = 0x3c;
	TL0 = 0xb0;     // 50ms	 12M

    bianliangzhi ++;
	if(bianliangzhi % 4 == 0)  
	{ 	
		biao_shi___200ms = 1;
	}	
}

/****************串口中断程序******************/
void uatr0() interrupt 4
{
	static urch i=0,dat;
	if(RI)	                 //是否接收中断
	{
		RI=0;
		dat=SBUF;
		if((dat=='O') && (i==0)) //接收数据第一帧
		{
			huan_chunf[i]=dat;
			biao_shi___en=1;        //开始接收数据
		}
		else if(biao_shi___en==1)
		{
			i++;
			huan_chunf[i]=dat;
			if(i>=2)
			{
				i=0;biao_shi___en=2;
			}  // 停止接收
		}
	}
}	


