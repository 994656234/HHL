#ifndef C_IO_H
#define C_IO_H
//
#define IO_EXPORT "/sys/class/gpio/export"
//GPS Reset
#define IO_GPSReset_dir "/sys/class/gpio/gpio4/direction"
#define IO_GPSReset_value "/sys/class/gpio/gpio4/value"
//Buzzer
#define IO_Buzzer_dir "/sys/class/gpio/gpio101/direction"
#define IO_Buzzer_value "/sys/class/gpio/gpio101/value"
//ADC
#define ADC_IN0_value "/sys/bus/i2c/drivers/ads1015/0-0048/in0_input"
#define ADC_IN1_value "/sys/bus/i2c/drivers/ads1015/0-0048/in1_input"
#define ADC_IN2_value "/sys/bus/i2c/drivers/ads1015/0-0048/in2_input"
//
#define IO_485DE_dir "/sys/class/gpio/gpio37/direction"
#define IO_485DE_value "/sys/class/gpio/gpio37/value"
enum{
    IO_GPS_Reset = 0,
    IO_Buzzer,
    ADC_IN0,
    ADC_IN1,
    ADC_IN2,
    IO_485DE
};
enum{
    IN = 1,
    OUT = 0
};
class C_io
{
public:
    C_io();
    bool IO_Open_Gpio(int iGpio, int iNo);
    int IO_SetDriection(int Type, bool direction);
    int IO_Write(int Type, bool value);
    int IO_Read(int Type);
    int ADC_Read(int Type);
    void IO_Init();
    char AsciitoHex(char data);
    void IO_Init_1709();
    void IO_Init_1708();
    void IO_Init_GZB01();
};

#endif // C_IO_H
