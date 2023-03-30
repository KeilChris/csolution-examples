/*---------------------------------------------------------------------------
 * Copyright (c) 2020 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *      Name:    Hello.c
 *      Purpose: Hello World based on RTX
 *
 *---------------------------------------------------------------------------*/

#include "main.h"
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2

#include "RTE_Components.h"
#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif

#include <stdio.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/

static int count = 0;

static void app_main (void *argument) {
  (void)argument;

  printf("Starting ...\r\n");

#ifdef RTE_Compiler_EventRecorder
  printf("... using Event Recorder\r\n");
  EventRecorderClockUpdate();
  EventStartC (0);
#endif

  printf("\r\n");

  while (1)  {
#ifdef RTE_Compiler_EventRecorder
    EventStartBv(0, count, 0);
#endif
    printf ("Hello World %d\r\n", count);
#ifdef RTE_Compiler_EventRecorder
    EventStopB(0);
#endif

    if (count > 100) break;
    count++;
    osDelay (1000);
  }

#ifdef RTE_Compiler_EventRecorder
  EventStopC(0);
#endif

  printf("\r\nFinished\r\n\x04");
  exit(0);
}

/*---------------------------------------------------------------------------
 * Application initialization
 *---------------------------------------------------------------------------*/
void app_initialize (void) {
  osThreadNew(app_main, NULL, NULL);
}
