#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <math.h>

#define uchar unsigned char

#define LedPinRed    0
#define LedPinGreen  1
#define LedPinBlue   2

#define FREQ_RED 1.0f
#define AMPLITUBE 100.0f

int g_time_ms;

void ledInit(void)
{
	softPwmCreate(LedPinRed,  0, AMPLITUBE);
	softPwmCreate(LedPinGreen,0, AMPLITUBE);
	softPwmCreate(LedPinBlue, 0, AMPLITUBE);
}

void ledColorSet(uchar r_val, uchar g_val, uchar b_val)
{
	softPwmWrite(LedPinRed,   r_val);
	softPwmWrite(LedPinGreen, g_val);
	softPwmWrite(LedPinBlue,  b_val);
}

void update_time(void)
{
	g_time_ms++;
	delay(1);
	
}

int get_time_ms(void)
{

		return g_time_ms;
	
}

int getChroma(int time_ms, float beat_freq)
{
	float time_s = time_ms/1000.0f;
	float value;
	
	value = AMPLITUBE/2.0f * ( sin(2 * M_PI * beat_freq * time_s) + 1);
	
	return (int)value;
}

int main(void)
{
	int time_ms;
	
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	ledInit();

	while(1)
	{
		
		update_time();
		time_ms = get_time_ms();
		// printf("time=%d, value=%d\n", time_ms, getR(time_ms));
		ledColorSet(getChroma(time_ms, 0.22f), getChroma(time_ms, 0.33f), getChroma(time_ms, 0.44f));
	}
	
	

	return 0;
}
