Rara que funcione el contador en tiempo real, es necesario incluir la librería RTClib
>> descargar con el gestor de librerías de Arduino IDE si no se tiene.

Para resaltar las clases, funciones y variables de interés, añadir estas keywords en
C:/Program Files (x86)/Arduino/lib/keywords.txt

#######################################
# CUSTOM KEYWORDS
#######################################

@mmusicoc	KEYWORD1

# Object names ########################

Core	KEYWORD1
USB	KEYWORD1
SDcard	KEYWORD1
RTClock	KEYWORD1
Switches	KEYWORD1
WaterLS	KEYWORD1
Flowmeter	KEYWORD1
LEDs	KEYWORD1
Pump	KEYWORD1

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

# Classes and methods ##################

Arduino	LITERAL1
Sprint	KEYWORD2
Sprintln	KEYWORD2

ControllerCore	KEYWORD1
init	KEYWORD2
updateStatus	KEYWORD2
updateSerial	KEYWORD2
pumpCore	KEYWORD2

SerialHandler	KEYWORD1
serialWelcome	KEYWORD2
serialWatchDog	KEYWORD2
getNewChecks	KEYWORD2
getNewLimit	KEYWORD2
getNewFlow	KEYWORD2
commands	KEYWORD2
serialCountdown	KEYWORD2
updateChecks	KEYWORD2
updateLimits	KEYWORD2
updateFlow	KEYWORD2
updateFreq	KEYWORD2
resetLog	KEYWORD2

RTChandler	KEYWORD1
timer	KEYWORD2
fullTime	KEYWORD2
getFreq	KEYWORD2
setFreq	KEYWORD2

SDcardHandler	KEYWORD1
event	KEYWORD2
loadParam	KEYWORD2
saveParam	KEYWORD2
updateLogFreq	KEYWORD2
resetLogFile	KEYWORD2
printEvent	KEYWORD2
logSD	KEYWORD2

Sensor	KEYWORD1
getSensorChecks	KEYWORD2
setSensorChecks	KEYWORD2
getSensorLimit	KEYWORD2
setSensorLimit	KEYWORD2
sensorUpdate	KEYWORD2

SwitchesClass	KEYWORD1
updateSwitches	KEYWORD2
getSwitch	KEYWORD2

WaterLevelSensor	KEYWORD1
updateWaterLevel	KEYWORD2
getWaterLevel	KEYWORD2

FlowmeterClass	KEYWORD1
getWaterFlow	KEYWORD2
getFlowRate	KEYWORD2
setFlowRate	KEYWORD2
flowISR	KEYWORD2

LEDsClass	KEYWORD1
setLED	KEYWORD2
updateLEDs	KEYWORD2
LEDblink	KEYWORD2

PumpClass	KEYWORD1
getPump	KEYWORD2
pumpON	KEYWORD2
pumpOFF	KEYWORD2

#######################################
# RTC Adafruit keywords
#######################################

# Datatypes (KEYWORD1)

DateTime	KEYWORD1
RTC_DS1307	KEYWORD1
RTC_DS3231	KEYWORD1
RTC_Millis	KEYWORD1
Ds1307SqwPinMode	KEYWORD1
rtc	KEYWORD1

# Methods and Functions (KEYWORD2)

year	KEYWORD2
month	KEYWORD2
day	KEYWORD2
hour	KEYWORD2
minute	KEYWORD2
second	KEYWORD2
dayOfTheWeek	KEYWORD2
secondstime	KEYWORD2
unixtime	KEYWORD2
begin	KEYWORD2
adjust	KEYWORD2
isrunning	KEYWORD2
now	KEYWORD2
readSqwPinMode	KEYWORD2
writeSqwPinMode	KEYWORD2
