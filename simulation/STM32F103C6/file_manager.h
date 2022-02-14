#ifndef _FILEMANAGER_H
#define _FILEMANAGER_H

#include <stdint.h>

void FileManager_Init(void);
void FileManager_AddWater(uint16_t ml);
void FileManager_FinishDay(void);
void FileManager_GenerateOutput(void);

#endif
