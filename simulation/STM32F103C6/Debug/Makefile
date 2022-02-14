###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = STM32F103C6
COMPILER = "Keil for ARM"
TARGET = Debug
SHELL = C:\WINDOWS\system32\cmd.exe

## Tools general options
ASMFLAGS=--cpu=cortex-m3 --thumb -g
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -I../../../../../../../../../../Keil_v5/ARM/CMSIS/Include -g
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/main.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/main.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/SYSTEM~1.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/system_stm32f1xx.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/STARTU~1.o: TOOL=ASM
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/startup_stm32f103.s
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/CONTRO~1.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Controller.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/Leds.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Leds.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/LCD.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/LCD.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/WATERB~1.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/WaterBomb.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/WATERL~1.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/WaterLevelSensor.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/Seos.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Seos.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/CATPRO~1.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/CatProximitySensor.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/utils.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/utils.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/rtc.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/rtc.c
#     C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/Debug/buttons.o: TOOL=CC
#        C:/Users/Edelmiro/Desktop/Taller de proyecto I/Proyectos/TP4-git/STM32F103C8_PWM_DC_Motor/simulation/STM32F103C6/buttons.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o SYSTEM~1.o STARTU~1.o CONTRO~1.o Leds.o LCD.o WATERB~1.o WATERL~1.o Seos.o CATPRO~1.o utils.o rtc.o buttons.o 
	$(LD)  $(LDFLAGS)  "main.o" "SYSTEM~1.o" "STARTU~1.o" "CONTRO~1.o" "Leds.o" "LCD.o" "WATERB~1.o" "WATERL~1.o" "Seos.o" "CATPRO~1.o" "utils.o" "rtc.o" "buttons.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

SYSTEM~1.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "SYSTEM~1.o"

STARTU~1.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "STARTU~1.o"

CONTRO~1.o:	../Controller.c 
	$(CC) $(CCFLAGS)  "../Controller.c" -c -o "CONTRO~1.o"

Leds.o:	../Leds.c 
	$(CC) $(CCFLAGS)  "../Leds.c" -c -o "Leds.o"

LCD.o:	../LCD.c 
	$(CC) $(CCFLAGS)  "../LCD.c" -c -o "LCD.o"

WATERB~1.o:	../WaterBomb.c 
	$(CC) $(CCFLAGS)  "../WaterBomb.c" -c -o "WATERB~1.o"

WATERL~1.o:	../WaterLevelSensor.c 
	$(CC) $(CCFLAGS)  "../WaterLevelSensor.c" -c -o "WATERL~1.o"

Seos.o:	../Seos.c 
	$(CC) $(CCFLAGS)  "../Seos.c" -c -o "Seos.o"

CATPRO~1.o:	../CatProximitySensor.c 
	$(CC) $(CCFLAGS)  "../CatProximitySensor.c" -c -o "CATPRO~1.o"

utils.o:	../utils.c 
	$(CC) $(CCFLAGS)  "../utils.c" -c -o "utils.o"

rtc.o:	../rtc.c 
	$(CC) $(CCFLAGS)  "../rtc.c" -c -o "rtc.o"

buttons.o:	../buttons.c 
	$(CC) $(CCFLAGS)  "../buttons.c" -c -o "buttons.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf SYSTEM~1.o
	rm -rf STARTU~1.o
	rm -rf CONTRO~1.o
	rm -rf Leds.o
	rm -rf LCD.o
	rm -rf WATERB~1.o
	rm -rf WATERL~1.o
	rm -rf Seos.o
	rm -rf CATPRO~1.o
	rm -rf utils.o
	rm -rf rtc.o
	rm -rf buttons.o
