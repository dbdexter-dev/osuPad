// Open source zzqProX keypad firmware
#include <Keyboard.h>
#define KEYNUM 5
#define LEDNUM 2
#define DEBOUNCE_DELAY 500

const unsigned char keys[KEYNUM] = {'z', 'x', '`', KEY_F2, KEY_LEFT_SHIFT}; // Keys to emulate
const int keyPins[KEYNUM] = {8, 15, 5, 6, 7};								// Pins corresponding to the keys above
const int ledPins[LEDNUM] = {3, 10};										// Optional LED pins

void setup()
{
	int i;

	#ifdef DEBUG
	Serial.begin(9600);
	#else
	Keyboard.begin();
	#endif

	// Initialize LEDs
	for(i=0; i<LEDNUM; i++)
	{
		pinMode(ledPins[i], OUTPUT);
		digitalWrite(ledPins[i], 0);
	}

	// Initialize keys
	for(i=0; i<KEYNUM; i++)
	{
		pinMode(keyPins[i], INPUT);
		digitalWrite(keyPins[i], HIGH);
	}
}

void loop()
{
	int i;
	int keyStatus;
	static int oldKeyStatus[KEYNUM];

	for(i=0; i<KEYNUM; i++)
	{
		keyStatus = digitalRead(keyPins[i]);
		if(keyStatus != oldKeyStatus[i])
		{
			delayMicroseconds(DEBOUNCE_DELAY);
			if(keyStatus == digitalRead(keyPins[i]))
			{
				if(!keyStatus)
				{
					#ifdef DEBUG
					Serial.print("+");
					Serial.println((int)keys[i]);
					#else
					Keyboard.press(keys[i]);
					#endif
					if(i < LEDNUM)
						digitalWrite(ledPins[i], 1);
				}
				else
				{
					#ifdef DEBUG
					Serial.print("-");
					Serial.println((int)keys[i]);
					#else
					Keyboard.release(keys[i]);
					#endif
					if(i < LEDNUM)
						digitalWrite(ledPins[i], 0);
				}
				oldKeyStatus[i] = keyStatus;
			}
		}
	}
	delayMicroseconds(500);
}
