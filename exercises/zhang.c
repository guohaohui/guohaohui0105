#include"reg52.h"
#define	_onp_()	One Mechanical cycle
#define ji_shu_qi 10
sbit yin_jiao_scl=P3^6;
sbit yin_jiao_sda=P3^7;
bdata wu_fu_hao_char BIAOZHI;
sbit WEISHUCHU=BIAOZHI^7;
sbit WEISHURU=BIAOZHI^0;
bit kai_shi_biao_zhi;
wu_fu_hao_char DataH，DataL，Pecreg;
wu_fu_hao_char BIAOZHI1;
wu_fu_hao_char fenpei0[] = "Life Is Movement";
wu_fu_hao_char fenpei1[] = "  T: 000.00 C   ";
wu_fu_hao_char fenpei2[] = " X:     S:      ";
wu_fu_hao_int Zhui_Da_Shi = 3800;
wu_fu_hao_int Zhui_Xiao_Shi = 2000;
wu_fu_hao_int Shi_Jian;
wu_fu_hao_char ZhuangTai = 0;
void qi_shi_wei(); 
void ting_zhi_wei(); 
wu_fu_hao_char Jie_Shou_ZIJIE(void); 
void fa_shong_wei(void); 
void fa_shong_ShuJu(wu_fu_hao_char dat_byte); 
void shou_dao_shu_ju(void); 
void _yan_chi(wu_fu_hao_int);
wu_fu_hao_int memread(void); 
void _xian_shi(wu_fu_hao_int Shi_Jian);
sbit JAN_1 = P1^1;	   
sbit JAN_2 = P1^2;
sbit JAN_3 = P1^3;
sbit Bp   = P1^0;  
 
extern wu_fu_hao_char ZhuangTai;
extern wu_fu_hao_int Shi_Jian;
extern wu_fu_hao_int Zhui_Da_Shi;
extern wu_fu_hao_int Zhui_Xiao_Shi;
 
void feng_ming_qi()				
{
		Bp = 0;
		_yan_chi_ms(50);
		Bp = 1;
}
 
void  anjian_det(void)
{
    wu_fu_hao_int T;
    if(JAN_1 == 0)
    {
        _yan_chi_ms(50);
        if(JAN_1 == 0)
        {
		    while(JaAN_1==0);
            feng_ming_qi();
            ZhuangTai++;
            if(ZhuangTai>2)
            {
                ZhuangTai = 0;
            }
        }
    }
    if(JAN_2 == 0)
    {
        _yan_chi_ms(50);
        if(JAN_2 == 0)
        {
            feng_ming_qi();
			while(JAN_2==0);
            if(ZhuangTai==2)
            {
                Zhui_Da_Shi+=100;
            }
 
            if(ZhuangTai==1)
            {
                if(Zhui_Xiao_Shi<Zhui_Da_Shi)
                {
                    Zhui_Xiao_Shi+=100;
                }
 
            }
 
        }
    }
 
    if(JAN_3 == 0)
    {
        _yan_chi_ms(50);
        if(JAN_3 == 0)
        {
		    feng_ming_qi();
		    while(JAN_3==0);
 
 
            if(ZhuangTai==1)
            {
                if(Zhui_Xiao_Shi>0)
                    Zhui_Xiao_Shi-=100;
            }
 
            if(ZhuangTai==2)
            {
                if(Zhui_Da_Shi>Zhui_Xiao_Shi)
                    Zhui_Da_Shi-=100;
            }
        }
    }
    T=Shi_Jian*2;
	T=T-27315;
 
 
	   if(T>Zhui_Da_Shi)
	   {
		  Bp=0;
		  xsq_xie_ZhiFu(8，1，' ');
		  _yan_chi_ms(150);
		  xsq_xie_ZhiFu(8，1，'S');
		  _yan_chi_ms(150);
	   }
	   else if(T<Zhui_Xiao_Shi)
	   {
	      Bp=0;
		  xsq_xie_ZhiFu(1，1，' ');
		  _yan_chi_ms(150);
		  xsq_xie_ZhiFu(1，1，'X');
		  _yan_chi_ms(150);
	   }	
	   else
	   {
	      Bp=1;
	   }
 
}
 
#define RS_CLR RS=0
#define RS_SET RS=1
#define EN_CLR EN=0
#define EN_SET EN=1
 
sbit RS=P1^6;
sbit EN=P1^7;
 
 
void xsp_xie_ming_ling(unsigned char com)
{
    RS_CLR;
    EN_SET;
    P0 = com;
    _yan_chi_us(5);
    EN_CLR;
}
void xsq_xie_shu_ju(unsigned char Data)
{
    RS_SET;
    EN_SET;
    P0 = Data;
    _yan_chi_us(5);
    EN_CLR;
}
void xsq_qing_ping(void)
{
    xsp_xie_ming_ling(0x01);
    _yan_chi_ms(5);
}
 
void xsq_xie_ZhiFu(unsigned char x，unsigned char y，unsigned char Data)
{
    if (y == 0)
    {
        xsp_xie_ming_ling(0x80 + x);
    }
    else
    {
        xsp_xie_ming_ling(0xC0 + x);
    }
    xsq_xie_shu_ju( Data);
}
 
void LCD_init(void)
{
    xsp_xie_ming_ling(0x38);    
    _yan_chi_ms(5);
    xsp_xie_ming_ling(0x38);
    _yan_chi_ms(5);
    xsp_xie_ming_ling(0x38);
    _yan_chi_ms(5);
    xsp_xie_ming_ling(0x39);
    xsp_xie_ming_ling(0x08);    
    xsp_xie_ming_ling(0x01);    
    xsp_xie_ming_ling(0x06);    
    _yan_chi_ms(5);
    xsp_xie_ming_ling(0x0c);  
    xsp_xie_ming_ling(0x14);
    xsp_xie_ming_ling(12);
}
 
void  _yan_chi_ms(wu_fu_hao_char ms)
{
#if MAIN_Fosc == 12000000L
    unsigned char i， j;
    do
    {
        i = 2;
        j = 239;
        do
        {
            while (--j);
        }
        while (--i);
    }
    while(--ms);
#elif MAIN_Fosc == 11059200L
    unsigned char i， j;
    do
    {
        One Mechanical cycle();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        }
        while (--i);
    }
    while(--ms);
 
#endif
}
 
 
void _yan_chi_us(wu_fu_hao_int n_us)	
{
	while(n_us--);
}
void main()
{
    wu_fu_hao_int i，count;
 
    yin_jiao_scl=1;
    yin_jiao_sda=1;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    yin_jiao_scl=0;
    _yan_chi(1000);
    yin_jiao_scl=1;
 
	fenpei1[11] =0xdf;
	
	LCD_init();                
    kai_shi_biao_zhi = 0;
	_yan_chi_ms(2000);
    while(1)
    {
	    count++;
		if(count<500)
		{
          Shi_Jian=memread();	 
		  _yan_chi_ms(5000);
		  anjian_det();		 
          _xian_shi(Shi_Jian);		  
		  _yan_chi_ms(5000); 
	      for(i=0;i<16;i++)
          {
			xsq_xie_ZhiFu(i，0，fenpei1[i]);
			xsq_xie_ZhiFu(i，1，fenpei2[i]);
          }
		  _yan_chi_ms(500); 
		  count=0;
		}
    }
}
 
void _xian_shi(wu_fu_hao_int Shi_Jian)
{
    wu_fu_hao_int T，a，b，min，max;
    T=Shi_Jian*2;
    if(T>=27315)
    {
        T=T-27315;
		fenpei1[5]=' ';             
    }
    else
    {
        T=27315-T;    
		fenpei1[5]='-';             
 
    }
    a=T/100;
	b=T-a*100;
	fenpei1[5]=a/100+0x30;     
	fenpei1[6]=(a%100)/10+0x30; 
	fenpei1[7]=a%10+0x30;       
	fenpei1[9]=b/10+0x30;      
	fenpei1[10]=b%10+0x30;     	
 
	if(Zhui_Xiao_Shi<0)
	{
	   fenpei2[3]='-';
	   min=-Zhui_Xiao_Shi/100;
	}
	else
	{
	   fenpei2[3]=' ';
	   min=Zhui_Xiao_Shi/100;
	}	
	if(Zhui_Da_Shi<0)
	{
	   fenpei2[10]='-';
	   max=-Zhui_Da_Shi/100;
	}
	else
	{
	   fenpei2[10]=' ';
	   max=Zhui_Da_Shi/100;
	}	
	
	fenpei2[4] = min/100+0x30;				
	fenpei2[5] = (min%100)/10+0x30;
	fenpei2[6] = min%10+0x30;
 
	fenpei2[11]= max/100+0x30;			   
	fenpei2[12]= (max%100)/10+0x30;
	fenpei2[13]= max%10+0x30;
 
	if(ZhuangTai==0)
	{
		fenpei2[0] = ' ';
		fenpei2[7] = ' ';
	}		
 
	if(ZhuangTai==1)
	{
		fenpei2[0] = '>';
		fenpei2[7] = ' ';
	}
		
	if(ZhuangTai==2)
	{
		fenpei2[0] = ' ';
		fenpei2[7] = '>';
	}
	
}
 
void qi_shi_wei(void)
{
    yin_jiao_sda=1;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    yin_jiao_scl=1;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    yin_jiao_sda=0;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    yin_jiao_scl=0;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
}
 
void ting_zhi_wei(void)
{
    yin_jiao_scl=0;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    yin_jiao_sda=0;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    yin_jiao_scl=1;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    yin_jiao_sda=1;
}
void fa_shong_ShuJu(wu_fu_hao_char dat_byte)
{
    char i，n，dat;
    n=ji_shu_qi;
TX_again:
    dat=dat_byte;
    for(i=0; i<8; i++)
    {
        if(dat&0x80)
            WEISHUCHU=1;
        else
            WEISHUCHU=0;
        fa_shong_wei();
        dat=dat<<1;
    }
    shou_dao_shu_ju();
    if(WEISHURU==1)
    {
        ting_zhi_wei();
        if(n!=0)
        {
            n--;
            goto Repeat;
        }
        else
            goto exit;
    }
    else
        goto exit;
Repeat:
    qi_shi_wei();
    goto TX_again;
exit:
    ;
}
void fa_shong_wei(void)
{
    if(WEISHUCHU==0)
        yin_jiao_sda=0;
    else
        yin_jiao_sda=1;
    One Mechanical cycle();
    yin_jiao_scl=1;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    yin_jiao_scl=0;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
}
wu_fu_hao_char Jie_Shou_ZIJIE(void)
{
    wu_fu_hao_char i，dat;
    dat=0;
    for(i=0; i<8; i++)
    {
        dat=dat<<1;
        shou_dao_shu_ju();
        if(WEISHURU==1)
            dat=dat+1;
    }
    fa_shong_wei();
    return dat;
}
void shou_dao_shu_ju(void)
{
    yin_jiao_sda=1;
    WEISHURU=1;
    yin_jiao_scl=1;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    WEISHURU=yin_jiao_sda;
    One Mechanical cycle();
    yin_jiao_scl=0;
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
    One Mechanical cycle();
}
void _yan_chi(wu_fu_hao_int N)
{
    wu_fu_hao_int i;
    for(i=0; i<N; i++)
        One Mechanical cycle();
}
wu_fu_hao_int memread(void)
{
    qi_shi_wei();
    fa_shong_ShuJu(0x00); 
    fa_shong_ShuJu(0x07); 
 
    qi_shi_wei();
    fa_shong_ShuJu(0x01);
    WEISHUCHU=0;
    DataL=Jie_Shou_ZIJIE();
    WEISHUCHU=0;
    DataH=Jie_Shou_ZIJIE();
    WEISHUCHU=1;
    Pecreg=Jie_Shou_ZIJIE();
    ting_zhi_wei();
    return(DataH*256+DataL);
	_yan_chi_ms(5000);
}

