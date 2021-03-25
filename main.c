#include<reg52.h>        //包含头文件
#include<intrins.h>
#define U16_character unsigned char      //宏定义
#define U16_plastic unsigned int
//上次烧录代码校验和：030CF3H 030BD3H
sbit Button_To_Add = P3^4; // 频率+ 按键，对应SW2
sbit KeysToReduce = P3^5; // 频率_ 按键，对应SW3
sbit TheKeySwitch = P3^6; // 波形切换按键，对应SW4
sbit StepSet = P3^3; // 步进设置按键，对应SW1

sbit Light_emittingDiode_0 = P2^3; // 正弦波，红灯，对应LED1
sbit Light_emittingDiode_1 = P2^2; // 矩形波，黄灯，对应LED2
sbit Light_emittingDiode_2 = P2^1; // 三角波，绿灯，对应LED3
sbit Light_emittingDiode_3 = P2^0; // 锯齿波，白灯，对应LED4

sbit lcdBeiguang_k = P2^4;
sbit LCDPanelControl_rs = P2^5; //液晶控制引脚，还有一个控制脚是RW，因为我们只需要向液晶里写数据系那是就好了，所以，我们直接将RW引脚接地
sbit LcdPanelControl_rw = P2^6;
sbit LcdPanelControl_en = P2^7;

char figure, waveform_, u; //定义全局变量
unsigned int frequency_ = 100, Stepping_ = 1, Stepping__tmp = 1; //频率初始值是10Hz，步进值默认是0.1，显示步进值变量
U16_character code numbers[] = "0123456789"; //定义显示的数组
U16_character code numbers1[] = "Fout=     Wave form:"; //初始化显示字符
unsigned int TimerLoadsVariables; //定义定时器装载值变量 
int Counter_H, Counter_L, zhuangtai; //定义全局变量
/*_____________________定时器相关计算↓_____________________
 * 累加溢出型：
 * 累加最大值__M；置入初值__X；单片机机器周期(定时器脉冲周期)__T
 * （ M _ X ）T = 定时值； T为12*晶振周期，即 T = 12*[1/12Mhz]=1/1Mhz=1/1 000 000
 * 程序中需要的定时值为需产生波形周期的1/64；
 * 需波形的频率为fx，周期为 1/fx                  
 * 所以，产生波形周期的1/64为 1/(fx*64),即为所需定时值
 * 即：（ M _ X ）T = 1/(fx*64) 
 * 定时器装载值 X = M _ [1/(fx*64*T)]
 *             X = M _ (15625 / fx)
 * 其中， fx = frequency_/10；
 * 所以， X = M _ (156250 / frequency_)  
 * 
 * 定义宏 TIMER_FACTOR 为系数 156250    
 * 定时器装载值 TimerLoadsVariables = 65535 _ (TIMER_FACTOR / frequency_) 
 _____________________定时器相关计算↑_____________________*/

#define TIMER_FACTOR 150000//156250

//自定义字符
U16_character code zifu[] = {//此数组内数据为液晶上显示波形符号的自定义字符
    0x0e, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x11, 0x11, 0x0e, 0x00, //正弦波	   0  1

    0x00, 0x07, 0x04, 0x04, 0x04, 0x04, 0x1c, 0x00,
    0x00, 0x1c, 0x04, 0x04, 0x04, 0x04, 0x07, 0x00, //矩形波	   2  3

    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00,
    0x00, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, //三角波	   4  5

    0x00, 0x01, 0x03, 0x05, 0x09, 0x11, 0x00, 0x00, //锯齿波	   6
};
U16_character code SineWave[64] = {//此数组内的数据为，da输出对应电压值对应的数字量，0是0V，255是5V 
    135, 145, 158, 167, 176, 188, 199, 209, 218, 226, 234, 240, 245, 249, 252, 254, 254, 253, 251, 247, 243, 237, 230, 222, 213, 204, 193, 182, 170, 158,
    146, 133, 121, 108, 96, 84, 72, 61, 50, 41, 32, 24, 17, 11, 7, 3, 1, 0, 0, 2, 5, 9, 14, 20, 28, 36, 45, 55, 66, 78, 90, 102, 114, 128
}; //正弦波取码
U16_character code RectangularWave[64] = {//一个周期是采样64个点， 所以数组内是64个数据
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
}; //矩形波取码

U16_character code TriangleWave[64] = {
    0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248,
    248, 240, 232, 224, 216, 208, 200, 192, 184, 176, 168, 160, 152, 144, 136, 128, 120, 112, 104, 96, 88, 80, 72, 64, 56, 48, 40, 32, 24, 16, 8, 0
}; //三角波取码
U16_character code SawtoothWave[64] = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 45, 49, 53, 57, 61, 65, 69, 73, 77, 81, 85, 89, 93, 97, 101, 105, 109, 113, 117, 121, 125, 130, 134, 138, 142,
    146, 150, 154, 158, 162, 166, 170, 174, 178, 182, 186, 190, 194, 198, 202, 206, 210, 215, 219, 223, 227, 231, 235, 239, 243, 247, 251, 255
}; //锯齿波取码

void yanshi_time(U16_plastic xms) //延时函数
{
    int a, b;
    for (a = xms; a > 0; a--)
        for (b = 110; b > 0; b--);
}

void xie_com(U16_character com) //写命令函数
{
    LCDPanelControl_rs = 0;
    LcdPanelControl_en = 0;
    
    P0 = com;
    yanshi_time(1);
    LcdPanelControl_en = 1;
    yanshi_time(1);
    LcdPanelControl_en = 0;
}

void xie_date(U16_character date) //写数据函数
{
    LCDPanelControl_rs = 1;
    LcdPanelControl_en = 0;
    
    P0 = date;
    yanshi_time(1);
    LcdPanelControl_en = 1;
    yanshi_time(1);
    LcdPanelControl_en = 0;
}

//自定义字符集

void Lcd_memory()
{
    U16_plastic i, j, k = 0, temp = 0x40;
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 8; j++)
        {
            xie_com(temp + j);
            xie_date(zifu[k]);
            k++;
        }
        temp = temp + 8;
    }
}

void init_lcd() //初始化函数
{
    U16_character i;
    LcdPanelControl_en = 0; //默认开始状态为关使能端，见时序图
    LcdPanelControl_rw = 0; // 液晶控制引脚RW，因为我们只需要向液晶里写数据系那是就好了，所以，我们直接将RW引脚置低(或接地)
    lcdBeiguang_k = 0; // 开背光
    Lcd_memory();
    xie_com(0x01); //显示清屏，将上次的内容清除，默认为0x01.
    xie_com(0x0f);
    xie_com(0x38); //显示模式设置，默认为0x38,不用变。 
    xie_com(0x0c); //显示功能设置0x0f为开显示，显示光标，光标闪烁；0x0c为开显示，不显光标，光标不闪
    xie_com(0x06); //设置光标状态默认0x06,为读一个字符光标加1. 
    xie_com(0x80); //设置初始化数据指针，是在读指令的操作里进行的
    for (i = 10; i < 20; i++) //显示初始化
    {
        xie_date(numbers1[i]); //显示第一行字符
    }
    xie_com(0x80 + 0x40); //选择第二行
    for (i = 0; i < 9; i++)
    {
        xie_date(numbers1[i]); //显示第二行字符
    }
    xie_com(0x80 + 10); //选择第一行第十个位置

    xie_date(0);
    xie_date(1);
    xie_date(0);
    xie_date(1);
    xie_date(0);
    xie_date(1); //显示自定义的波形图案
    
    xie_com(0x80 + 0x40 + 9); //选择第二行第九个位置
    xie_date(' ');
    xie_date('1');
    xie_date('0');
    xie_date('.');
    xie_date('0');
    xie_date('H');
    xie_date('z'); //显示初始的频率值
    
}

void initclock() //定时器初始化函数
{
    TMOD = 0x01; //定时器的工作方式
    TH0 = Counter_H;
    TL0 = Counter_L; //定时器赋初值
    EA = 1; //打开中断总开关
    ET0 = 1; //打开定时器允许中断开关
    TR0 = 1; //打开定时器定时开关
}

void display() //显示函数
{
    U16_character qian, bai, shi, ge; //定义变量用于显示
    qian = frequency_ / 1000; //将频率值拆成一位的数据，将数据除以1000，得到的商是一位数，赋值给qian
    bai = frequency_ % 1000 / 100; //将频率除以1000的余数再除以100就得到了频率的百位，赋值给bai
    shi = frequency_ % 1000 % 100 / 10; //同上，得到频率的十位
    ge = frequency_ % 1000 % 100 % 10 / 1;
    xie_com(0x80 + 0x40 + 9); //选中第二行第九个位置

    if (qian == 0) //千位如果为0
        xie_date(' '); //不显示
    else //千位不为0
        xie_date(numbers[qian]); //正常显示千位
    if (qian == 0 && bai == 0) //千位和百位都为0
        xie_date(' '); //百位不显示
    else //不都为0
        xie_date(numbers[bai]); //百位正常显示
    xie_date(numbers[shi]); //显示十位数
    xie_date('.'); //显示小数点
    xie_date(numbers[ge]); //显示个位
    xie_date('H'); //显示频率的单位Hz
    xie_date('z');
    if (waveform_ == 0) //判断波形为正弦波
    {
        xie_com(0x80 + 10); //选中一行频率图案位置
        xie_date(0); //显示正弦波图案
        xie_date(1);
        xie_date(0);
        xie_date(1);
        xie_date(0);
        xie_date(1);
        Light_emittingDiode_3 = 1;
        Light_emittingDiode_0 = 0; //点亮正弦波指示灯
    }
    if (waveform_ == 1) //注释同上
    {
        xie_com(0x80 + 10);
        xie_date(2);
        xie_date(3);
        xie_date(2);
        xie_date(3);
        xie_date(2);
        xie_date(3);
        Light_emittingDiode_0 = 1;
        Light_emittingDiode_1 = 0;
    }


    if (waveform_ == 2)
    {
        xie_com(0x80 + 10);
        xie_date(4);
        xie_date(5);
        xie_date(4);
        xie_date(5);
        xie_date(4);
        xie_date(5);
        Light_emittingDiode_1 = 1;
        Light_emittingDiode_2 = 0;
    }
    if (waveform_ == 3)
    {
        xie_com(0x80 + 10);
        xie_date(6);
        xie_date(6);
        xie_date(6);
        xie_date(6);
        xie_date(6);
        xie_date(6);
        Light_emittingDiode_2 = 1;
        Light_emittingDiode_3 = 0;
    }
}

void keyscan() //频率调节键盘检测函数
{
    if (Button_To_Add == 0) //加按键是否按下
    {
        EA = 0; //关闭中断
        yanshi_time(2); //延时去抖
        if (Button_To_Add == 0) //再次判断
        {
            while (!Button_To_Add); //按键松开
            frequency_ += Stepping_; //频率以步进值加
            if (frequency_ > 1000) //最大加到100Hz，加到最大后回归最小10Hz
            {
                frequency_ = 100; //10Hz
            }
            display(); //显示函数
            TimerLoadsVariables = 65536 - (TIMER_FACTOR / frequency_); //计算频率
            /*频率值最小是10Hz，frequency_的值是100（因为要显示小数点后一位）,150000/100=1500，这个1500就是定时器需要计时的，单位是us，65536_1500得到的是定时器的初值，
            先不管初值，先看定时时间，1500us，一个波形的周期是由64个定时组成的，所以，一个波形周期就是64*1500us=96000，也就是96ms，约等
            于100ms，也就是10Hz的频率*/
            Counter_H = TimerLoadsVariables / 256; //将定时器的初值赋值给变量
            Counter_L = TimerLoadsVariables % 256;
            EA = 1; //打开中断总开关
        }
    }
    if (KeysToReduce == 0) //减按键按下
    {

        yanshi_time(5);
        if (KeysToReduce == 0)
        {
            EA = 0;
            while (!KeysToReduce);
            frequency_ -= Stepping_; //频率以步进值减
            if (frequency_ < 100) //减小到10Hz，循环为最大频率100.
            {
                frequency_ = 1000; 
            }
            display();
            TimerLoadsVariables = 65536 - (TIMER_FACTOR / frequency_);
            Counter_H = TimerLoadsVariables / 256;
            Counter_L = TimerLoadsVariables % 256;
            EA = 1;
        }
    }
    if (TheKeySwitch == 0) //波形切换按键
    {
        yanshi_time(5);
        if (TheKeySwitch == 0)
        {
            EA = 0;
            while (!TheKeySwitch);
            waveform_++; //波形切换
            if (waveform_ >= 4) //4种波形
            {
                waveform_ = 0;
            }
            display();
            EA = 1;
        }
    }
}

void Stepping_display() //步进值设置界面显示程序
{
    U16_plastic bai, shi, ge; //定义步进值 百十个位
    bai = Stepping__tmp / 100; //将步进值除以100得到百位，也就是频率值的十位，因为有一个小数位
    shi = Stepping__tmp % 100 / 10; //将步进值除以100的余数除以十得到十位
    ge = Stepping__tmp % 100 % 10; //取余10后得到个位，也就是频率步进值的小数点后一位
    xie_com(0x80 + 11); //选中液晶第一行第十一列
    if (bai == 0) //百位是否为0
        xie_date(' '); //百位不显示
    else //百位不为0
        xie_date(numbers[bai]); //显示百位数据
    xie_date(numbers[shi]); //显示十位数据
    xie_date('.'); //显示小数点
    xie_date(numbers[ge]); //显示个位，也就是小数点后一位
}

void Stepping_jiance() //步进值设置键盘程序
{
    if (StepSet == 0) //步进设置按键按下
    {
        yanshi_time(5); //延时去抖
        if (StepSet == 0) //再次判断按键
        {
            while (!StepSet); //按键释放，按键松开才继续向下执行
            zhuangtai++; //变量加
            if (zhuangtai == 1) //进入设置状态时
            {
                xie_com(0x01); //清屏
                xie_com(0x80); //初始化显示步进设置界面
                xie_date('S');
                yanshi_time(1); //step value
                xie_date('t');
                yanshi_time(1);
                xie_date('e');
                yanshi_time(1);
                xie_date('p');
                yanshi_time(1);
                xie_date(' ');
                yanshi_time(1);
                xie_date('v');
                yanshi_time(1);
                xie_date('a');
                yanshi_time(1);
                xie_date('l');
                yanshi_time(1);
                xie_date('u');
                yanshi_time(1);
                xie_date('e');
                yanshi_time(1);
                xie_date(':');
                yanshi_time(1);
                Stepping__tmp = Stepping_; //步进值赋值给临时变量

                Stepping_display(); //显示步进值
            }
            if (zhuangtai == 2) //退出设置
            {
                zhuangtai = 0; //清零
                Stepping_ = Stepping__tmp; //设置好的临时步进值赋值给步进变量

                init_lcd(); //初始化液晶显示
                initclock(); //定时器初始化
                display(); //调用显示程序
            }
        }
    }
    if (zhuangtai == 1) //设置步进值时
    {
        if (Button_To_Add == 0) //加按键按下
        {
            yanshi_time(5); //延时去抖
            if (Button_To_Add == 0) //再次判断
            {
                while (!Button_To_Add); //按键释放
                Stepping__tmp++; //步进值加1
                if (Stepping__tmp > 100) //步进值最大100，也就是10.0Hz
                {
                    Stepping__tmp = 1; //超过最大值就恢复到0.1Hz
                }
                Stepping_display(); //步进显示
            }
        }
        if (KeysToReduce == 0) //减按键，注释同上
        {
            yanshi_time(5);
            if (KeysToReduce == 0)
            {
                while (!KeysToReduce);
                Stepping__tmp--; //步进减
                if (Stepping__tmp <= 0)
                {
                    Stepping__tmp = 100;
                }
                Stepping_display();
            }
        }
    }
}

void main() //主函数
{
    init_lcd(); //调用初始化程序
    TimerLoadsVariables = 65536 - (TIMER_FACTOR / frequency_); //定时器初值
    Counter_H = TimerLoadsVariables / 256;
    Counter_L = TimerLoadsVariables % 256;
    initclock(); //定时器初始化
    Light_emittingDiode_0 = 0; //点亮第一个波形指示灯
    while (1) //进入while循环，括号内为1，一直成立，所以也叫死循环，程序不会跳出，一直在内执行
    {
        if (zhuangtai == 0) //正常模式不是步进调节
        {
            keyscan(); //扫描按键
            //	display();
        }

        Stepping_jiance(); //扫描步进调节程序

        switch (waveform_) //选择波形
        {
            case 0: P1 = SineWave[u];
                break; //正弦波
            case 1: P1 = RectangularWave[u];
                break; //矩形波
            case 2: P1 = TriangleWave[u];
                break; //三角波
            case 3: P1 = SawtoothWave[u];
                break; //锯齿波
        }
    }
}

void T0_time()interrupt 1 //定时器
{
    TH0 = Counter_H;
    TL0 = Counter_L; //根据不同的初值，定时器定时时间不同，达到不同频率的目的
    u++; //变量加
    if (u >= 64) //一个周期采样64个点， 所以加到64就清零
        u = 0; //u清零
    TF0 = 0;
    // 不用清除标志位吗？
}
