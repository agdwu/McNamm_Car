#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


static void 	Start_task(void);//任务函数
static 	TaskHandle_t 	StartTask_Handle;//任务句柄
static 	StackType_t		StartTask_Stack[128];//任务堆栈
static	StaticTask_t 	StartTask_TCB;//任务控制块

static void 	Task1(void);
static 	TaskHandle_t 	Task1_Handle;
static 	StackType_t		Task1_Stack[128];
static	StaticTask_t 	Task1_TCB;

static void 	Task2(void);
static 	TaskHandle_t 	Task2_Handle;
static 	StackType_t		Task2_Stack[128];
static	StaticTask_t 	Task2_TCB;


void MX_FREERTOS_Init(void); 


void MX_FREERTOS_Init(void)
{
	StartTask_Handle=xTaskCreateStatic(	(TaskFunction_t) Start_task,		//任务函数
																			(const char *	 ) "Start_task",	//任务名称
																			(uint32_t				) 128,						//任务堆栈大小
																			(void *				 ) NULL,					//传递给任务函数的参数
																			(UBaseType_t	 ) 4,							//任务优先级
																			(StackType_t * ) StartTask_Stack,//任务堆栈
																			(StaticTask_t *) &StartTask_TCB );//任务控制块
	if(StartTask_Handle!=NULL)
		vTaskStartScheduler();//开启调度
	while(1);
}

static void Start_task(void)
{
	taskENTER_CRITICAL();           //进入临界区
	
	Task1_Handle=xTaskCreateStatic(	(TaskFunction_t) Task1,		//任务函数
																	(const char *	 ) "Task1",	//任务名称
																	(uint32_t			 ) 128,						//任务堆栈大小
																	(void *				 ) NULL,					//传递给任务函数的参数
																	(UBaseType_t	 ) 4,							//任务优先级
																	(StackType_t * ) Task1_Stack,//任务堆栈
																	(StaticTask_t *) &Task1_TCB );//任务控制块	
																			
	Task2_Handle=xTaskCreateStatic(	(TaskFunction_t) Task2,		//任务函数
																	(const char *	 ) "Task2",	//任务名称
																	(uint32_t			 ) 128,						//任务堆栈大小
																	(void *				 ) NULL,					//传递给任务函数的参数
																	(UBaseType_t	 ) 4,							//任务优先级
																	(StackType_t * ) Task2_Stack,//任务堆栈
																	(StaticTask_t *) &Task2_TCB );//任务控制块		
																		
	if(Task1_Handle!=NULL&&Task2_Handle!=NULL)													
		vTaskDelete(StartTask_Handle); //删除AppTaskCreate任务
	
	taskEXIT_CRITICAL();      //退出临界区
}


static void Task1(void)
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_8);
		vTaskDelay(500);
	}
}


static void Task2(void)
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_9);
		vTaskDelay(1000);
	}
}


















