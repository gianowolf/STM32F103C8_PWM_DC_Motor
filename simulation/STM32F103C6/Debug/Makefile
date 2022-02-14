###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = STM32F103C6
COMPILER = "Keil for ARM"
TARGET = Debug
SHELL = C:\Windows\system32\cmd.exe

## Tools general options
ASMFLAGS=--cpu=cortex-m3 --thumb -g
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -IC:/Keil_v5/ARM/CMSIS/Include -g
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/main.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/main.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/system_stm32f1xx.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/system_stm32f1xx.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/startup_stm32f103.o: TOOL=ASM
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/startup_stm32f103.s
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/Controller.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Controller.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/Leds.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Leds.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/LCD.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/LCD.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/WaterBomb.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/WaterBomb.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/WaterLevelSensor.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/WaterLevelSensor.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/Seos.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Seos.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/CatProximitySensor.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/CatProximitySensor.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/utils.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/utils.c
#     E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/Debug/file_manager.o: TOOL=CC
#        E:/My Drive/4_TPI/TP4/simulation/STM32F103C6/file_manager.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o system_stm32f1xx.o startup_stm32f103.o Controller.o Leds.o LCD.o WaterBomb.o WaterLevelSensor.o Seos.o CatProximitySensor.o utils.o file_manager.o 
	$(LD)  $(LDFLAGS)  "main.o" "system_stm32f1xx.o" "startup_stm32f103.o" "Controller.o" "Leds.o" "LCD.o" "WaterBomb.o" "WaterLevelSensor.o" "Seos.o" "CatProximitySensor.o" "utils.o" "file_manager.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

system_stm32f1xx.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "system_stm32f1xx.o"

startup_stm32f103.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "startup_stm32f103.o"

Controller.o:	../Controller.c 
	$(CC) $(CCFLAGS)  "../Controller.c" -c -o "Controller.o"

Leds.o:	../Leds.c 
	$(CC) $(CCFLAGS)  "../Leds.c" -c -o "Leds.o"

LCD.o:	../LCD.c 
	$(CC) $(CCFLAGS)  "../LCD.c" -c -o "LCD.o"

WaterBomb.o:	../WaterBomb.c 
	$(CC) $(CCFLAGS)  "../WaterBomb.c" -c -o "WaterBomb.o"

WaterLevelSensor.o:	../WaterLevelSensor.c 
	$(CC) $(CCFLAGS)  "../WaterLevelSensor.c" -c -o "WaterLevelSensor.o"

Seos.o:	../Seos.c 
	$(CC) $(CCFLAGS)  "../Seos.c" -c -o "Seos.o"

CatProximitySensor.o:	../CatProximitySensor.c 
	$(CC) $(CCFLAGS)  "../CatProximitySensor.c" -c -o "CatProximitySensor.o"

utils.o:	../utils.c 
	$(CC) $(CCFLAGS)  "../utils.c" -c -o "utils.o"

file_manager.o:	../file_manager.c 
	$(CC) $(CCFLAGS)  "../file_manager.c" -c -o "file_manager.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf system_stm32f1xx.o
	rm -rf startup_stm32f103.o
	rm -rf Controller.o
	rm -rf Leds.o
	rm -rf LCD.o
	rm -rf WaterBomb.o
	rm -rf WaterLevelSensor.o
	rm -rf Seos.o
	rm -rf CatProximitySensor.o
	rm -rf utils.o
	rm -rf file_manager.o
