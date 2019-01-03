#include <rtthread.h>
#include <rtdevice.h>
#include "key.h"
#include "led.h"

int key_init(void)
{
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT);
		return 0;
}
int key_scan1()
{
		rt_tick_t tick;
		if(rt_pin_read(KEY_PIN) == 0)//�����������
		{
				rt_thread_mdelay(20);//����
				if(rt_pin_read(KEY_PIN) == 0)//ȷ�ϰ�������
				{
						tick = rt_tick_get(); //��ȡ��ǰtick
						while (rt_tick_get() - tick < (RT_TICK_PER_SECOND / 3))//333ms��  //�����ʵ����������ʱ�����Կ�һ��ȷ������
						{
								if(rt_pin_read(KEY_PIN) == 1)//�����ɿ�
								{
										tick = rt_tick_get();
										while (rt_tick_get() - tick < (RT_TICK_PER_SECOND / 2))//333ms��
										{
												if(rt_pin_read(KEY_PIN) == 0)//��������ٴΰ���
												{
														rt_thread_mdelay(20);//����
														if(rt_pin_read(KEY_PIN) == 0)//�ٴ�ȷ�ϰ�������
														{
																while(rt_pin_read(KEY_PIN) == 0);//�ȵ�������return������Ӱ����һ��
																return 2;//˫��
														}
												}
										}
										return 1;
								}
						}
						return 1;//����
				}
		}
		return 0;
}
rt_uint32_t key_scan2()
{
		rt_tick_t tick;
		if(rt_pin_read(KEY_PIN) == 0)//�����������
		{
				rt_thread_mdelay(20);//����
				if(rt_pin_read(KEY_PIN) == 0)//ȷ�ϰ�������
				{
						tick = rt_tick_get();
						while(rt_pin_read(KEY_PIN) == 0)
						{
								led_on();
								if(rt_tick_get()-tick >= 5) //����50ms�򷵻�
									return rt_tick_get()-tick;
						};					
						return rt_tick_get()-tick;
				}
		}
		led_off();
		return 0;
}
