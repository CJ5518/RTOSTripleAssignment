#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <Wire.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "Stepper.h"

#include "ClosedCube_HDC1080.h"
#include "7seg.hpp"

#define BUTTON1 19
#define BUTTON2 9
#define BUTTON3 8

ClosedCube_HDC1080 hdc1080;
Stepper myStepper = Stepper(2048, 0, 12, 1, 13);
int motorPosition = 0;
const int stepsPerRevolution = 2048;

Adafruit_NeoPixel strip =
    Adafruit_NeoPixel(4, 20, NEO_GRB + NEO_KHZ800);

TaskHandle_t displayRefreshTask;
TaskHandle_t motorTask;


QueueHandle_t sevSegQueue;

int displayBase = 10;
void addToSevSegQueue(int n) {
	if (!uxQueueSpacesAvailable(sevSegQueue)) {
		xQueueReset(sevSegQueue);
		displayBase = 16;
		n=0x0F;
	}
	xQueueSend(sevSegQueue, &n, 0);
}


void sevSegDisplayRefresh(void*) {
	sevSegQueue = xQueueCreate(10, sizeof(int));
	int sevSegDisplayDigit = 0;
	while (1) {
		if (xQueueReceive(sevSegQueue, &sevSegDisplayDigit, portMAX_DELAY) == pdTRUE) {
			//If there is a thing to display, do so for about 2 seconds
			for (int q = 0; q < 100; q++) {
				int leftDigit = sevSegDisplayDigit / displayBase;
				int rightDigit = sevSegDisplayDigit % displayBase;
				sevSegLeftDigit(0);
				sevSegRightDigit(0);
				writeDigit(leftDigit);
				sevSegLeftDigit(1);
				vTaskDelay(4 / portTICK_PERIOD_MS);
				sevSegLeftDigit(0);

				writeDigit(rightDigit);
				sevSegRightDigit(1);
				vTaskDelay(4 / portTICK_PERIOD_MS);
				sevSegRightDigit(0);

				vTaskDelay(10 / portTICK_PERIOD_MS);
			}
		}
	}
}

double temp;
double humidity;
int sensorMode = 0;

int motorMode = 0;

void sensorTask(void*) {
	temp = 0;
	humidity = 0;
	while (1) {
		temp = hdc1080.readTemperature();
		humidity = hdc1080.readHumidity();
		if (sensorMode == 0) {
			addToSevSegQueue((int)temp);
		} else if (sensorMode == 1) {
			addToSevSegQueue((int)humidity);
		} else if (sensorMode == 2) {
			addToSevSegQueue((int)(((float) motorPosition / (float)stepsPerRevolution) * 100));
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

int countButtonPresses(int pin) {
	int ret = 1;
	int waitingForRelease = 1;
	for (int q = 0; q < 100; q++) {
		//It is incredibly difficult (impossible probably) to repeatedly tap a button in 20 milliseconds, and this avoids bouncing
		busy_wait_ms(20);
		if (waitingForRelease && !digitalRead(pin)) {
			waitingForRelease = 0;
		}
		if (!waitingForRelease && digitalRead(pin)) {
			ret++;
			waitingForRelease = 1;
		}
	}
	return ret;
}

void inputPollingTask(void*) {
	while (1) {
		int button1State = digitalRead(BUTTON1);
		int button2State = digitalRead(BUTTON2);
		int button3State = digitalRead(BUTTON3);
		

		if (button1State || button2State || button3State) {
			//Button pressed, now we wait the next 2 seconds and check for other presses
			if (button1State) {
				switch (countButtonPresses(BUTTON1)) {
					case 1: {
						motorMode = 3;
						motorPosition = 0;
					} break;
					case 2: {
						motorMode = 4;
						motorPosition = 0;
					} break;
					case 3: {
						Serial.printf("Pressed thrice\n");
						vTaskSuspend(motorTask);
						vTaskSuspend(displayRefreshTask);
						sevSegLeftDigit(1);
						sevSegRightDigit(1);
						writeDigit(0xE);
						while (1) {
							//This is the 'stop everything' part
							button1State = digitalRead(BUTTON1);
							button2State = digitalRead(BUTTON2);
							button3State = digitalRead(BUTTON3);

							if (!(button1State || button2State || button3State)) {
								busy_wait_ms(10);
							} else {
								Serial.printf("%d%d%d\n", button1State, button2State, button3State);
								break;
							}
						}
						vTaskResume(motorTask);
						vTaskResume(displayRefreshTask);
					} break;
					case 4: {
						if (displayBase == 16) {
							displayBase = 10;
						} else {
							displayBase = 16;
						}
					} break;
					default: break;
				}
			} else if (button2State) {
				switch (countButtonPresses(BUTTON2)) {
					case 1: {
						Serial.printf("Set motor mode to 0\n");
						motorMode = 0;
					} break;
					case 2: {
						motorMode = 1;
						Serial.printf("Set motor mode to 1\n");
					} break;
					case 3: {
						motorMode = 2;
						motorPosition = 0;
					} break;
					default: break;
				}
			} else if (button3State) {
				switch (countButtonPresses(BUTTON3)) {
					case 1: {
						sensorMode = 0;
					} break;
					case 2: {
						sensorMode = 1;
					} break;
					case 3: {
						sensorMode = 2;
					} break;
					default: break;
				}
			}
		}
		vTaskDelay(20 / portTICK_PERIOD_MS);
	}
}


void stepperMotorTask(void*) {
	myStepper.setSpeed(10);
	while (1) {
		if (motorMode == 0) {
			myStepper.step(1);
			motorPosition++;
		} else if (motorMode == 1) {
			myStepper.step(-1);
			motorPosition--;
		} else if (motorMode == 2) {
			if (motorPosition >= 0 && motorPosition < stepsPerRevolution) {
				myStepper.step(1);
				motorPosition++;
			} else if (motorPosition >= stepsPerRevolution) {
				motorPosition = -stepsPerRevolution;
			} else if (motorPosition < 0) {
				myStepper.step(-1);
				motorPosition++;
			}
		} else if (motorMode == 3) {
			float percentageTarget = (float)humidity / 100.0f;
			int intTarget = percentageTarget * stepsPerRevolution;
			if (motorPosition < intTarget) {
				myStepper.step(1);
				motorPosition++;
			} else if (motorPosition > intTarget) {
				myStepper.step(-1);
				motorPosition--;
			}
		} else if (motorMode == 4) {
			float percentageTarget = (float)temp / 100.0f;
			int intTarget = percentageTarget * stepsPerRevolution;
			if (motorPosition < intTarget) {
				myStepper.step(1);
				motorPosition++;
			} else if (motorPosition > intTarget) {
				myStepper.step(-1);
				motorPosition--;
			}
		}
		vTaskDelay(5 / portTICK_PERIOD_MS);
	}
}

void stripTask(void*) {
	while (1) {
		strip.setPixelColor(0, strip.Color(255,0,0));
		strip.setPixelColor(1, strip.Color(255,0,0));
		strip.setPixelColor(2, strip.Color(255,0,0));
		strip.setPixelColor(3, strip.Color(255,0,0));
		strip.show();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}


void setup() {
	Wire.begin();

	Serial.begin(MONITOR_SPEED);

	hdc1080.begin(0x40);
	strip.begin();
	strip.setBrightness(20);
	strip.show();  // Initialize all pixels to 'off'
	pinMode(BUTTON1, INPUT);
	pinMode(BUTTON2, INPUT);
	pinMode(BUTTON3, INPUT);
	
	init7Seg();

	xTaskCreate(sensorTask, "SensorTask", 256, NULL, 4, NULL);
	xTaskCreate(sevSegDisplayRefresh, "SevSegDisplayRefresh", 256, NULL, 5, &displayRefreshTask);
	xTaskCreate(inputPollingTask, "inputPollingTask", 256, NULL, 7, NULL);
	xTaskCreate(stepperMotorTask, "stepperMotorTask", 256, NULL, 4, &motorTask);
	xTaskCreate(stripTask, "stripTask", 256, NULL, 6, NULL);
}

void loop() {
	
}
