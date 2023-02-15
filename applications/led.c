#include "led.h"



/*-------------------------------   线程2：快闪   -------------------------------*/
static rt_thread_t led_fast_flash = RT_NULL;

static void led_fast_flash_thread(void *parameter)
{
    rt_pin_mode(LED9_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED9_PIN, PIN_HIGH);

    while (1)
    {
      rt_pin_write(LED9_PIN, PIN_LOW);
      rt_thread_mdelay(100);

      rt_pin_write(LED9_PIN, PIN_HIGH);
      rt_thread_mdelay(200);
    }
}

int led_fast_start(void)
{
    led_fast_flash = rt_thread_create("led_fast",
                                      led_fast_flash_thread, 
                                      RT_NULL,
                                      LED_FAST_STACK_SIZE,
                                      LED_FAST_PRIORITY, 
                                      LED_FAST_TIMESLICE);

    if (led_fast_flash != RT_NULL)
        rt_thread_startup(led_fast_flash);
    
    return 0;
}

//MSH_CMD_EXPORT(led_fast_start, led fast flash start);
INIT_APP_EXPORT(led_fast_start);




