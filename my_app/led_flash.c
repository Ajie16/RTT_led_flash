#include "led_flash.h"
//RTT 操作系统头文件和设备管理
#include <rtthread.h>
#include <rtdevice.h>

//调用包
#include <stdlib.h>


/* PIN脚编号，查看驱动文件drv_gpio.c确定 */
#define LED0_PIN    89
#define LED1_PIN    90

static void led_entry(void *prg)
{

    /* 设置PIN脚模式为输出 */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_pin_write(LED1_PIN, PIN_HIGH);

        rt_thread_mdelay(1000);

        /* 拉高PIN脚 */
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_pin_write(LED1_PIN, PIN_LOW);

        rt_thread_mdelay(1000);
    }
}

static int led_init(void)
{
    rt_thread_t tid;
    rt_err_t ret = RT_EOK;

    tid = rt_thread_create("led",
                           led_entry,
                           RT_NULL,
                           512,
                           10,
                           20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(led_init,led_init);



