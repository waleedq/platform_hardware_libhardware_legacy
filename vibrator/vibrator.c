/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <hardware_legacy/vibrator.h>
#include "qemu.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define LOG_TAG "vibration"
#include <utils/Log.h>

#define THE_DEVICE "/dev/ttyS1"

static int sendit(int timeout_ms)
{
    int nwr, ret,test;
    char value[100];
    char buf[1000];
    int fd;
  
    if (fd > 0){
     usleep(100000);
    }
    
    fd = open(THE_DEVICE, O_RDWR | O_NOCTTY);
    if(fd < 0){
	LOGE("couldn't open vdevice , error code: %d\n",errno);
        return errno;
    }
    if(timeout_ms > 0){
      if(timeout_ms != 9999999){
	nwr = sprintf(value, "at+xdrv=4,0,1,12,%d,%d\r\n",timeout_ms+1,timeout_ms);
      }else{
	nwr = sprintf(value, "at+xdrv=4,0,2,12,1000,999\r\n");
      }
    }else{
      nwr = sprintf(value, "at+xdrv=4,0,0,0,0,0\r\n");
    }
    ret = write(fd, value, nwr);
    close(fd);
    
    if (ret == nwr){
      LOGE("vibrated :) , ret: %d , nwr: %d, timeout_ms:%d , value:%s\n",ret,nwr,timeout_ms,value);
      return 0;
    }else{
      LOGE("couldn't vibrate :( , ret: %d , nwr: %d , timeout_ms:%d ,value:%s\n",ret,nwr,timeout_ms,value);
      return -1;
    }
}

int vibrator_on(int timeout_ms)
{
    return sendit(timeout_ms);
}

int vibrator_off()
{
    return sendit(0);
}
