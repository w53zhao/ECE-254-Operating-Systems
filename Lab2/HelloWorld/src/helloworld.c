#include <LPC17xx.h>
#include <RTL.h>
#include <stdio.h>
#include "uart_polling.h"
#include "../../RTX_CM3/INC/RTL_ext.h"

__task void task1() {
	
	int tasks;
	
	while(1) {
			tasks = os_tsk_count_get();
			printf("Number of tasks: %d\n", tasks);
			os_dly_wait(200);
	}
	
}

__task void task2() {
	while(1) {
			printf("Task 2\n");
			os_dly_wait(200);
	}
}

__task void task3() {
	while(1) {
			printf("Task 3\n");
			os_dly_wait(200);
	}
}

__task void task4() {
	while(1) {
			printf("Task 4\n");
			os_dly_wait(200);
	}
}

__task void task5() {
	while(1) {
			printf("Task 5\n");
			os_dly_wait(200);
	}
}

__task void init(void) {
	os_tsk_create(task1, 1);
	os_tsk_create(task2, 1);
	os_tsk_create(task3, 1);
	os_tsk_create(task4, 1);
	os_tsk_create(task5, 1);
	os_tsk_delete_self();
}

int main() {
	SystemInit();
	uart0_init();
	os_sys_init(init);
}
