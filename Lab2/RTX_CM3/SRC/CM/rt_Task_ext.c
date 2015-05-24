/**
* @file: rt_Task_ext.c
*/
#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_MemBox.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_Task_ext.h"
int rt_tsk_count_get (void) {
	
	int id;
	int counter = 0;
	
	for( id = 0; id < os_maxtaskrun; id++ ) {
		if( os_active_TCB[id] != NULL ) {
			counter++;
		}
	}
	
	return counter;
	
}
/* end of file */