#include <sys/backtrace.h>
#include <sys/flash.h>
#include <sys/xip.h>
#include <fsal.h>
#include <osal.h>
#include <soc_defs.h>
#include <soc_types.h>
#include <attrs.h>

/* Littlevgl specific */
#include "lvgl.h"
#include "lvgl_driver.h"
//#include "lv_examples/lv_apps/demo/demo.h"

#include "gui_conf.h"
#include "lv_sim_eclipse_sdl/lv_gui.h"

#define M_TICK (5)
static void  lv_tick_task(void *arg) CONFIG_LVGL_ATTRIBUTE_TICK_INC;

OsTimer add_str;
static void  lv_tick_task(void *arg){
    (void) arg;
	
    lv_tick_inc(M_TICK*portTICK_RATE_MS);
}

//Creates a semaphore to handle concurrent call to lvgl stuff
//If you wish to call *any* lvgl function from other threads/tasks
//you should lock on the very same semaphore!

lv_indev_t * indev_mouse;

void g_add_string(OsTimer tmr)
{
    char buf[80];
    static int s_idx = 0;
    if (s_idx++ == 0) {
        snprintf(buf, 80, "123456789012345678901234567890\n", s_idx++);
    } else {
        snprintf(buf, 80, "%d\n", s_idx++);
    }
    //printf("%s", buf);
    terminal_add(buf);
}
//uint16_t *g_buf1;
//uint16_t *g_buf2;
//
void guiTask(void *arg) {

    lv_init();

    lvgl_driver_init();

    static LV_MEM_ATTR lv_color_t buf1[DISP_BUF_SIZE];
    static LV_MEM_ATTR lv_color_t buf2[DISP_BUF_SIZE];
    static lv_disp_buf_t disp_buf;
    //lv_disp_buf_init(&disp_buf, g_buf1 = MEM_NO_CACHE(buf1), g_buf2 = MEM_NO_CACHE(buf2), DISP_BUF_SIZE);
    lv_disp_buf_init(&disp_buf, MEM_NO_CACHE(buf1), MEM_NO_CACHE(buf2), DISP_BUF_SIZE);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

	
	static OsTimer lv_os_timer = NULL;
	if( OS_TimerCreate(&lv_os_timer, M_TICK, (u8)TRUE, NULL, (OsTimerHandler)lv_tick_task) == OS_FAILED) {
			printf("OS_TimerCreate NG\n");
			return;
	}
	OS_TimerStart(lv_os_timer);

    // demo
    //lv_demo_benchmark();
    //lv_demo_keypad_encoder();
    //lv_demo_widgets();
    //lv_demo_stress();
    //lv_obj_t * terminal_create(void);
    //terminal_create();
    lvgl_gui_init();

    //OS_TimerCreate(&add_str, 500, 1, NULL, g_add_string);
    //OS_TimerStart(add_str);

    while (1) {
        lv_task_handler();
        OS_MsDelay(M_TICK);
    }

    vTaskDelete(NULL);
}


