#include "file_manager.h"

uint32_t months[12];
uint32_t weeks[4];
uint32_t days[7];

uint8_t p_months;
uint8_t p_weeks;
uint8_t p_days;

uint32_t total_today;

void FileManager_Init()
{
	FileManager_RecoverDataFromSD();
}

void FileManager_AddWater(uint16_t ml)
{
	total_today += ml;
}

void FileManager_FinishDay()
{	
	days[p_days++] = total_today;
	p_days = p_days % 6;
	if(p_days==0)
	{
		uint32_t total_temp,i;
		for( i = 0 ; i < 6 ; i++)
		{
			total_temp+= days[i];
		}
		weeks[p_weeks++] = total_temp;
		p_weeks = p_weeks % 29;
		if(p_weeks == 0)
		{
			total_temp = 0;
			for( i = 0 ; i < 29 ; i++ )
			{
				total_temp += weeks[i];
			}
		}
	}	
}

void FileManager_GenerateOutput()
{
	
}

void FileManager_RecoverDataFromSD()
{
	p_months = 0;
	p_weeks = 0;
	p_days = 0;
	total_today = 0;
}