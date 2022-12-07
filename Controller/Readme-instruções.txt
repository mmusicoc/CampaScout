Raramente o contador em tempo real funciona, é necessário incluir a biblioteca RTClib
>> faça o download com o gerenciador de bibliotecas do Arduino IDE, caso não o tenha.

Para destacar as classes, funções e variáveis ​​de interesse, adicione essas palavras-chave em
C:/Arquivos de Programas (x86)/Arduino/lib/keywords.txt

#######################################
# PALAVRAS-CHAVE PERSONALIZADAS
#######################################

@mmusicoc	PALAVRACHAVE1

# Nome dos Objetos ########################

Core	PALAVRACHAVE1
USB	PALAVRACHAVE1
SDcard	PALAVRACHAVE1
RTClock	PALAVRACHAVE1
Switches	PALAVRACHAVE1
WaterLS	PALAVRACHAVE1
Flowmeter	PALAVRACHAVE1
LEDs	PALAVRACHAVE1
Pump	PALAVRACHAVE1

# Typedefs ############################

Event	LITERAL1
none	LITERAL1
pumpOn	LITERAL1
pumpOff	LITERAL1

level	LITERAL1
underMin	LITERAL1
midLevel	LITERAL1
overMax	LITERAL1

LEDstate	LITERAL1
off	LITERAL1
on	LITERAL1
blinky	LITERAL1

# Metodos e classes ##################

Arduino	LITERAL1
Sprint	PALAVRACHAVE2
Sprintln	PALAVRACHAVE2

ControllerCore	PALAVRACHAVE1
init	PALAVRACHAVE2
updateStatus	PALAVRACHAVE2
updateSerial	PALAVRACHAVE2
pumpCore	PALAVRACHAVE2

SerialHandler	PALAVRACHAVE1
serialWelcome	PALAVRACHAVE2
serialWatchDog	PALAVRACHAVE2
getNewChecks	PALAVRACHAVE2
getNewLimit	PALAVRACHAVE2
getNewFlow	PALAVRACHAVE2
commands	PALAVRACHAVE2
serialCountdown	PALAVRACHAVE2
updateChecks	PALAVRACHAVE2
updateLimits	PALAVRACHAVE2
updateFlow	PALAVRACHAVE2
updateFreq	PALAVRACHAVE2
resetLog	PALAVRACHAVE2

RTChandler	PALAVRACHAVE1
timer	PALAVRACHAVE2
fullTime	PALAVRACHAVE2
getFreq	PALAVRACHAVE2
setFreq	PALAVRACHAVE2

SDcardHandler	PALAVRACHAVE1
event	PALAVRACHAVE2
loadParam	PALAVRACHAVE2
saveParam	PALAVRACHAVE2
updateLogFreq	PALAVRACHAVE2
resetLogFile	PALAVRACHAVE2
printEvent	PALAVRACHAVE2
logSD	PALAVRACHAVE2

Sensor	PALAVRACHAVE1
getSensorChecks	PALAVRACHAVE2
setSensorChecks	PALAVRACHAVE2
getSensorLimit	PALAVRACHAVE2
setSensorLimit	PALAVRACHAVE2
sensorUpdate	PALAVRACHAVE2

SwitchesClass	PALAVRACHAVE1
updateSwitches	PALAVRACHAVE2
getSwitch	PALAVRACHAVE2

WaterLevelSensor	PALAVRACHAVE1
updateWaterLevel	PALAVRACHAVE2
getWaterLevel	PALAVRACHAVE2

FlowmeterClass	PALAVRACHAVE1
getWaterFlow	PALAVRACHAVE2
getFlowRate	PALAVRACHAVE2
setFlowRate	PALAVRACHAVE2
flowISR	PALAVRACHAVE2

LEDsClass	PALAVRACHAVE1
setLED	PALAVRACHAVE2
updateLEDs	PALAVRACHAVE2
LEDblink	PALAVRACHAVE2

PumpClass	PALAVRACHAVE1
getPump	PALAVRACHAVE2
pumpON	PALAVRACHAVE2
pumpOFF	PALAVRACHAVE2

#######################################
# Palavras-chave RTC Adafruit
#######################################

# Tipos de dados (PALAVRACHAVE1)

DateTime	PALAVRACHAVE1
RTC_DS1307	PALAVRACHAVE1
RTC_DS3231	PALAVRACHAVE1
RTC_Millis	PALAVRACHAVE1
Ds1307SqwPinMode	PALAVRACHAVE1
rtc	PALAVRACHAVE1

# Métodos e Funções (PALAVRACHAVE2)

year	PALAVRACHAVE2
month	PALAVRACHAVE2
day	PALAVRACHAVE2
hour	PALAVRACHAVE2
minute	PALAVRACHAVE2
second	PALAVRACHAVE2
dayOfTheWeek	PALAVRACHAVE2
secondstime	PALAVRACHAVE2
unixtime	PALAVRACHAVE2
begin	PALAVRACHAVE2
adjust	PALAVRACHAVE2
isrunning	PALAVRACHAVE2
now	PALAVRACHAVE2
readSqwPinMode	PALAVRACHAVE2
writeSqwPinMode	PALAVRACHAVE2
