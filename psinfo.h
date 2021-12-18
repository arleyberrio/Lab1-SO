#ifndef __PSINFO_H_
#include<stdbool.h>
#define __PSINFO_H_

int errno;
void invalidCommand();
void getInfoProc(char* currentPid);
#endif