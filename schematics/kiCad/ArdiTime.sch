EESchema Schematic File Version 2
LIBS:V_adc_dac
LIBS:V_Battery
LIBS:V_Connector
LIBS:V_Diode
LIBS:V_Linear
LIBS:V_Logic
LIBS:V_Microcontroller
LIBS:V_Passive
LIBS:V_Regulator
LIBS:V_Relay
LIBS:V_Transistor
LIBS:power
LIBS:device
LIBS:transistors
LIBS:switches
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Arduino_Mini-cache
LIBS:ArdiTime-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ArdiTime"
Date "sam. 04 avril 2015"
Rev "1"
Comp "David"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +9V #PWR01
U 1 1 58AB59FE
P 900 850
F 0 "#PWR01" H 900 700 50  0001 C CNN
F 1 "+9V" H 900 990 50  0000 C CNN
F 2 "" H 900 850 50  0000 C CNN
F 3 "" H 900 850 50  0000 C CNN
	1    900  850 
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 58AB5A95
P 1800 4750
F 0 "R1" V 1880 4750 50  0000 C CNN
F 1 "1k" V 1800 4750 50  0000 C CNN
F 2 "" V 1730 4750 50  0000 C CNN
F 3 "" H 1800 4750 50  0000 C CNN
	1    1800 4750
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 58AB5B9E
P 4900 5650
F 0 "D1" H 4900 5750 50  0000 C CNN
F 1 "LED Amber" V 5050 5600 50  0000 C CNN
F 2 "" H 4900 5650 50  0000 C CNN
F 3 "" H 4900 5650 50  0000 C CNN
	1    4900 5650
	-1   0    0    1   
$EndComp
$Comp
L LED D2
U 1 1 58AB5C09
P 5350 5650
F 0 "D2" H 5350 5750 50  0000 C CNN
F 1 "LED alarm" V 5500 5600 50  0000 C CNN
F 2 "" H 5350 5650 50  0000 C CNN
F 3 "" H 5350 5650 50  0000 C CNN
	1    5350 5650
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 58AB5C5A
P 5400 4800
F 0 "R4" V 5480 4800 50  0000 C CNN
F 1 "150" V 5400 4800 50  0000 C CNN
F 2 "" V 5330 4800 50  0000 C CNN
F 3 "" H 5400 4800 50  0000 C CNN
	1    5400 4800
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 58AB5CB1
P 4950 4800
F 0 "R3" V 5030 4800 50  0000 C CNN
F 1 "150" V 4950 4800 50  0000 C CNN
F 2 "" V 4880 4800 50  0000 C CNN
F 3 "" H 4950 4800 50  0000 C CNN
	1    4950 4800
	1    0    0    -1  
$EndComp
$Comp
L Speaker LS1
U 1 1 58AB5D02
P 10550 2650
F 0 "LS1" H 10850 2450 50  0000 R CNN
F 1 "Speaker (8ohm)" H 11050 2350 50  0000 R CNN
F 2 "" H 10550 2450 50  0000 C CNN
F 3 "" H 10540 2600 50  0000 C CNN
	1    10550 2650
	1    0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 58AB5D55
P 9750 2700
F 0 "RV1" V 9650 2700 50  0000 C CNN
F 1 "10k" V 9750 2700 50  0000 C CNN
F 2 "" H 9750 2700 50  0000 C CNN
F 3 "" H 9750 2700 50  0000 C CNN
	1    9750 2700
	-1   0    0    1   
$EndComp
$Comp
L Voltmeter_DC MES1
U 1 1 58AB5F36
P 4500 5050
F 0 "MES1" H 4370 5090 50  0000 R CNN
F 1 "VUmetre" H 4370 5020 50  0000 R CNN
F 2 "" V 4500 5150 50  0000 C CNN
F 3 "" V 4500 5150 50  0000 C CNN
	1    4500 5050
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW1
U 1 1 58ABF7E8
P 900 2150
F 0 "SW1" H 950 2250 50  0000 L CNN
F 1 "SW_Push" H 900 2090 50  0000 C CNN
F 2 "" H 900 2350 50  0000 C CNN
F 3 "" H 900 2350 50  0000 C CNN
	1    900  2150
	0    1    1    0   
$EndComp
Text Label 8000 2200 1    60   ~ 0
RAW
Text Label 7200 1700 1    60   ~ 0
DTR
Text Label 7400 1700 1    60   ~ 0
0(Rx)
Text Label 6650 2300 0    60   ~ 0
1(Tx)
Text Label 6650 2400 0    60   ~ 0
0(Rx)
Text Label 6650 2500 0    60   ~ 0
Reset
Text Label 6650 2800 0    60   ~ 0
3(**)
Text Label 6650 2600 0    60   ~ 0
GND
Text Label 6650 3000 0    60   ~ 0
5(**)
Text Label 6650 3100 0    60   ~ 0
6(**)
Text Label 6650 3200 0    60   ~ 0
7
Text Label 6650 3300 0    60   ~ 0
8
Text Label 6650 3400 0    60   ~ 0
9(**)
Text Label 8150 3400 0    60   ~ 0
10(**/SS)
Text Label 8150 3300 0    60   ~ 0
11(**/MOSI)
Text Label 8150 3200 0    60   ~ 0
12(MISO)
Text Label 8150 3100 0    60   ~ 0
13(SCK)
Text Label 8150 3000 0    60   ~ 0
A0
Text Label 8150 2900 0    60   ~ 0
A1
Text Label 8150 2800 0    60   ~ 0
A2
Text Label 8150 2700 0    60   ~ 0
A3
Text Label 7300 3900 3    60   ~ 0
A4
Text Label 7200 3900 3    60   ~ 0
A5
Text Notes 6200 1275 0    60   ~ 0
Shield Arduino Pro Mini \n
Wire Notes Line
	6175 1350 7350 1350
Wire Notes Line
	7350 1350 7350 1175
Text Label 7600 3900 3    60   ~ 0
A7
Text Label 7700 3900 3    60   ~ 0
A6
$Comp
L CONN_01X02 P2
U 1 1 58ACAF59
P 7250 3700
F 0 "P2" H 7250 3850 50  0000 C CNN
F 1 "ADC" V 7350 3700 50  0000 C CNN
F 2 "Socket_Arduino_Pro_Mini:Socket_Strip_Arduino_1x02" H 7250 3700 50  0001 C CNN
F 3 "" H 7250 3700 50  0000 C CNN
	1    7250 3700
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 P4
U 1 1 58ACAF5A
P 7650 3700
F 0 "P4" H 7650 3850 50  0000 C CNN
F 1 "ADC" V 7750 3700 50  0000 C CNN
F 2 "Socket_Arduino_Pro_Mini:Socket_Strip_Arduino_1x02" H 7650 3700 50  0001 C CNN
F 3 "" H 7650 3700 50  0000 C CNN
	1    7650 3700
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X06 P3
U 1 1 58ACAF5B
P 7450 1900
F 0 "P3" H 7450 2250 50  0000 C CNN
F 1 "COM" V 7550 1900 50  0000 C CNN
F 2 "Socket_Arduino_Pro_Mini:Socket_Strip_Arduino_1x06" H 7450 1900 50  0001 C CNN
F 3 "" H 7450 1900 50  0000 C CNN
	1    7450 1900
	0    -1   1    0   
$EndComp
Text Label 7300 1700 1    60   ~ 0
1(Tx)
$Comp
L GND #PWR02
U 1 1 58ACAF5C
P 7850 1700
F 0 "#PWR02" H 7850 1450 50  0001 C CNN
F 1 "GND" H 7850 1550 50  0000 C CNN
F 2 "" H 7850 1700 50  0000 C CNN
F 3 "" H 7850 1700 50  0000 C CNN
	1    7850 1700
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 58ACAF5D
P 7500 1700
F 0 "#PWR03" H 7500 1550 50  0001 C CNN
F 1 "VCC" H 7500 1850 50  0000 C CNN
F 2 "" H 7500 1700 50  0000 C CNN
F 3 "" H 7500 1700 50  0000 C CNN
	1    7500 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 1700 7850 1700
Connection ~ 7700 1700
$Comp
L CONN_01X12 P1
U 1 1 58ACAF5E
P 7200 2850
F 0 "P1" H 7200 3500 50  0000 C CNN
F 1 "Digital" V 7300 2850 50  0000 C CNN
F 2 "Socket_Arduino_Pro_Mini:Socket_Strip_Arduino_1x12" H 7200 2850 50  0001 C CNN
F 3 "" H 7200 2850 50  0000 C CNN
	1    7200 2850
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X12 P5
U 1 1 58ACAF5F
P 7700 2850
F 0 "P5" H 7700 3500 50  0000 C CNN
F 1 "Analog" V 7800 2850 50  0000 C CNN
F 2 "Socket_Arduino_Pro_Mini:Socket_Strip_Arduino_1x12" H 7700 2850 50  0001 C CNN
F 3 "" H 7700 2850 50  0000 C CNN
	1    7700 2850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4050 2600 7000 2600
Wire Wire Line
	7000 2300 6650 2300
Wire Wire Line
	6650 2400 7000 2400
Wire Wire Line
	7000 2500 6650 2500
Wire Wire Line
	8000 900  8000 2300
Wire Wire Line
	8000 2300 7900 2300
Wire Wire Line
	7900 2400 8000 2400
Wire Wire Line
	8000 2400 8000 3500
$Comp
L GND #PWR05
U 1 1 58ACAF61
P 8000 3500
F 0 "#PWR05" H 8000 3250 50  0001 C CNN
F 1 "GND" H 8000 3350 50  0000 C CNN
F 2 "" H 8000 3500 50  0000 C CNN
F 3 "" H 8000 3500 50  0000 C CNN
	1    8000 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 2600 7900 2600
$Comp
L VCC #PWR06
U 1 1 58ACAF62
P 8100 1550
F 0 "#PWR06" H 8100 1400 50  0001 C CNN
F 1 "VCC" H 8100 1700 50  0000 C CNN
F 2 "" H 8100 1550 50  0000 C CNN
F 3 "" H 8100 1550 50  0000 C CNN
	1    8100 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 3100 9000 3100
Wire Notes Line
	8850 4100 6150 4100
Wire Notes Line
	6150 4100 6150 1200
Text Notes 7300 2300 0    60   ~ 0
1
Wire Notes Line
	8850 4100 8850 1200
Wire Notes Line
	8850 1200 6150 1200
$Comp
L GND #PWR07
U 1 1 58ACC0F6
P 4500 6300
F 0 "#PWR07" H 4500 6050 50  0001 C CNN
F 1 "GND" H 4500 6150 50  0000 C CNN
F 2 "" H 4500 6300 50  0000 C CNN
F 3 "" H 4500 6300 50  0000 C CNN
	1    4500 6300
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 58ACC58D
P 4500 5550
F 0 "R6" V 4580 5550 50  0000 C CNN
F 1 "18k" V 4500 5550 50  0000 C CNN
F 2 "" V 4430 5550 50  0000 C CNN
F 3 "" H 4500 5550 50  0000 C CNN
	1    4500 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 58ACCBA7
P 5400 6300
F 0 "#PWR08" H 5400 6050 50  0001 C CNN
F 1 "GND" H 5400 6150 50  0000 C CNN
F 2 "" H 5400 6300 50  0000 C CNN
F 3 "" H 5400 6300 50  0000 C CNN
	1    5400 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 58ACCBDD
P 4950 6300
F 0 "#PWR09" H 4950 6050 50  0001 C CNN
F 1 "GND" H 4950 6150 50  0000 C CNN
F 2 "" H 4950 6300 50  0000 C CNN
F 3 "" H 4950 6300 50  0000 C CNN
	1    4950 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 58ACDFE3
P 10350 4000
F 0 "#PWR011" H 10350 3750 50  0001 C CNN
F 1 "GND" H 10350 3850 50  0000 C CNN
F 2 "" H 10350 4000 50  0000 C CNN
F 3 "" H 10350 4000 50  0000 C CNN
	1    10350 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 58ACE78A
P 9750 2950
F 0 "#PWR012" H 9750 2700 50  0001 C CNN
F 1 "GND" H 9750 2800 50  0000 C CNN
F 2 "" H 9750 2950 50  0000 C CNN
F 3 "" H 9750 2950 50  0000 C CNN
	1    9750 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 1850 9750 2550
Wire Wire Line
	9000 3100 9000 4250
$Comp
L R R8
U 1 1 58AE1028
P 9400 3300
F 0 "R8" V 9480 3300 50  0000 C CNN
F 1 "1k" V 9400 3300 50  0000 C CNN
F 2 "" V 9330 3300 50  0000 C CNN
F 3 "" H 9400 3300 50  0000 C CNN
	1    9400 3300
	0    1    1    0   
$EndComp
Text Label 6650 2700 0    60   ~ 0
2
Wire Wire Line
	4500 2800 4500 4850
Wire Wire Line
	4500 5800 4500 6300
Wire Wire Line
	4500 5250 4500 5300
Wire Wire Line
	4950 5050 4950 5300
Wire Wire Line
	4950 6000 4950 6300
Wire Wire Line
	4950 3000 4950 4550
$Comp
L R R5
U 1 1 58CD5F48
P 5850 4800
F 0 "R5" V 5930 4800 50  0000 C CNN
F 1 "150" V 5850 4800 50  0000 C CNN
F 2 "" V 5780 4800 50  0000 C CNN
F 3 "" H 5850 4800 50  0000 C CNN
	1    5850 4800
	1    0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 58CD5FA1
P 5800 5650
F 0 "D3" H 5800 5750 50  0000 C CNN
F 1 "LED Deco" V 5950 5600 50  0000 C CNN
F 2 "" H 5800 5650 50  0000 C CNN
F 3 "" H 5800 5650 50  0000 C CNN
	1    5800 5650
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 58CD60A5
P 5850 6300
F 0 "#PWR?" H 5850 6050 50  0001 C CNN
F 1 "GND" H 5850 6150 50  0000 C CNN
F 2 "" H 5850 6300 50  0000 C CNN
F 3 "" H 5850 6300 50  0000 C CNN
	1    5850 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 5050 5400 5300
Wire Wire Line
	5400 6000 5400 6300
Wire Wire Line
	5400 3100 5400 4550
Wire Wire Line
	5850 5050 5850 5300
$Comp
L GND #PWR?
U 1 1 58CD7DC8
P 4050 6300
F 0 "#PWR?" H 4050 6050 50  0001 C CNN
F 1 "GND" H 4050 6150 50  0000 C CNN
F 2 "" H 4050 6300 50  0000 C CNN
F 3 "" H 4050 6300 50  0000 C CNN
	1    4050 6300
	1    0    0    -1  
$EndComp
$Comp
L 2N2222 Q1
U 1 1 58CD84B5
P 10200 3300
F 0 "Q1" H 10200 3650 50  0000 L CNN
F 1 "2N2222" H 10100 3550 50  0000 L CNN
F 2 "TO92" H 10200 3300 50  0001 C CNN
F 3 "" H 10200 3300 60  0001 C CNN
	1    10200 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	7900 2700 9600 2700
Wire Wire Line
	10350 3600 10350 4000
Wire Wire Line
	9650 3300 10100 3300
$Comp
L R R7
U 1 1 58CD9581
P 10350 2100
F 0 "R7" V 10430 2100 50  0000 C CNN
F 1 "10" V 10350 2100 50  0000 C CNN
F 2 "" V 10280 2100 50  0000 C CNN
F 3 "" H 10350 2100 50  0000 C CNN
	1    10350 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	8100 1850 10350 1850
Connection ~ 8100 1850
Connection ~ 9750 1850
Wire Wire Line
	8100 1550 8100 2600
Wire Wire Line
	10350 2350 10350 2650
Text Notes 10500 2250 1    60   ~ 0
volume
Wire Wire Line
	10350 2750 10350 3000
Wire Wire Line
	9750 2850 9750 2950
Wire Wire Line
	9150 3300 7900 3300
Wire Wire Line
	5850 6000 5850 6300
Wire Wire Line
	5850 3200 5850 4550
Wire Wire Line
	5850 3200 7000 3200
Wire Wire Line
	5400 3100 7000 3100
Wire Wire Line
	4950 3000 7000 3000
$Comp
L 2N2222 Q2
U 1 1 58D7C1AD
P 2500 4750
F 0 "Q2" H 2450 5100 50  0000 L CNN
F 1 "2N2222" H 2350 5000 50  0000 L CNN
F 2 "TO92" H 2500 4750 50  0001 C CNN
F 3 "" H 2500 4750 60  0001 C CNN
	1    2500 4750
	0    1    1    0   
$EndComp
$Comp
L GNDPWR #PWR010
U 1 1 58ACCDF9
P 2650 5800
F 0 "#PWR010" H 2650 5600 50  0001 C CNN
F 1 "GNDPWR" H 2650 5670 50  0000 C CNN
F 2 "" H 2650 5750 50  0000 C CNN
F 3 "" H 2650 5750 50  0000 C CNN
	1    2650 5800
	1    0    0    -1  
$EndComp
$Comp
L 1N400X D1
U 1 1 58D7D396
P 2650 2250
F 0 "D1" H 2800 2300 50  0000 L CNN
F 1 "1N4004" H 2800 2200 50  0000 L CNN
F 2 "AX3_1" H 2650 2250 50  0001 C CNN
F 3 "" H 2650 2250 60  0001 C CNN
	1    2650 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4050 2600 4050 6300
Wire Wire Line
	3700 900  8000 900 
$Comp
L DPDT K1
U 1 1 58D7E786
P 1800 3400
F 0 "K1" V 1100 3400 50  0000 L CNN
F 1 "DPDT" V 1200 3350 50  0000 L CNN
F 2 "??" H 1800 3400 50  0001 C CNN
F 3 "" H 1800 3400 60  0001 C CNN
	1    1800 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	3700 3450 3700 900 
Wire Wire Line
	1550 3400 1350 3400
Wire Wire Line
	4500 2800 7000 2800
Connection ~ 4050 3850
Wire Wire Line
	2100 3850 4050 3850
Wire Wire Line
	2100 3450 3700 3450
Wire Wire Line
	900  2350 900  4750
Wire Wire Line
	900  850  900  1950
Wire Wire Line
	2650 5050 2650 5800
Wire Notes Line
	3550 6500 3550 1000
Wire Notes Line
	3550 1000 650  1000
Wire Notes Line
	650  1000 650  6500
Text Notes 2600 6100 0    60   ~ 0
0v
Wire Wire Line
	900  4250 9000 4250
Wire Notes Line
	1550 2650 1550 3950
Wire Notes Line
	1550 3950 2100 3950
Wire Notes Line
	2100 3950 2100 2650
Wire Notes Line
	2100 2650 1550 2650
Text Notes 1600 2550 0    60   Italic 0
attention \nau sens
Connection ~ 900  1150
Wire Wire Line
	1350 3400 1350 1150
Connection ~ 1350 1150
Wire Wire Line
	1450 1150 1450 3050
Wire Wire Line
	1450 3050 1550 3050
Connection ~ 1450 1150
Wire Wire Line
	900  1150 2650 1150
Wire Wire Line
	2650 1150 2650 2050
Wire Wire Line
	2100 3050 2650 3050
Connection ~ 2650 3050
Wire Wire Line
	2650 2500 2650 4450
Wire Notes Line
	650  6500 3550 6500
Wire Wire Line
	2050 4750 2400 4750
Wire Wire Line
	900  4750 1550 4750
Connection ~ 900  4250
$EndSCHEMATC
