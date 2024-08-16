#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


static void 	Start_task(void);//������
static 	TaskHandle_t 	StartTask_Handle;//������
static 	StackType_t		StartTask_Stack[128];//�����ջ
static	StaticTask_t 	StartTask_TCB;//������ƿ�

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
	StartTask_Handle=xTaskCreateStatic(	(TaskFunction_t) Start_task,		//������
																			(const char *	 ) "Start_task",	//��������
																			(uint32_t				) 128,						//�����ջ��С
																			(void *				 ) NULL,					//���ݸ��������Ĳ���
																			(UBaseType_t	 ) 4,							//�������ȼ�
																			(StackType_t * ) StartTask_Stack,//�����ջ
																			(StaticTask_t *) &StartTask_TCB );//������ƿ�
	if(StartTask_Handle!=NULL)
		vTaskStartScheduler();//��������
	while(1);
}

static void Start_task(void)
{
	taskENTER_CRITICAL();           //�����ٽ���
	
	Task1_Handle=xTaskCreateStatic(	(TaskFunction_t) Task1,		//������
																	(const char *	 ) "Task1",	//��������
																	(uint32_t			 ) 128,						//�����ջ��С
																	(void *				 ) NULL,					//���ݸ��������Ĳ���
																	(UBaseType_t	 ) 4,							//�������ȼ�
																	(StackType_t * ) Task1_Stack,//�����ջ
																	(StaticTask_t *) &Task1_TCB );//������ƿ�	
																			
	Task2_Handle=xTaskCreateStatic(	(TaskFunction_t) Task2,		//������
																	(const char *	 ) "Task2",	//��������
																	(uint32_t			 ) 128,						//�����ջ��С
																	(void *				 ) NULL,					//���ݸ��������Ĳ���
																	(UBaseType_t	 ) 4,							//�������ȼ�
																	(StackType_t * ) Task2_Stack,//�����ջ
																	(StaticTask_t *) &Task2_TCB );//������ƿ�		
																		
	if(Task1_Handle!=NULL&&Task2_Handle!=NULL)													
		vTaskDelete(StartTask_Handle); //ɾ��AppTaskCreate����
	
	taskEXIT_CRITICAL();      //�˳��ٽ���
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


















