//#include MIDI.h

int a = 19;
int b = 7;
int c = 7;
double PiInc = 0;
const int LEDPIN = 3;
boolean LEDSTATE = LOW;

#define trigPinA  2
#define trigPinB  3
#define trigPinC  4
#define trigPinD  5
#define trigPinE  6
#define refreshRandPin 7

void setup() {
	pinMode(trigPinA, INPUT);
	pinMode(trigPinB, INPUT);
	pinMode(trigPinC, INPUT);
	pinMode(trigPinD, INPUT);
	pinMode(trigPinE, INPUT);
	pinMode(refreshRandPin, INPUT_PULLUP);

	byte ran = analogRead(0);
	for (int i = 0; i < 10; i++) ran += analogRead(0);
	randomSeed(ran);
	pinMode(LEDPIN, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(4, OUTPUT);
	digitalWrite(4, LOW);
	DDRB = B00001111;
	Serial.begin(115200);
	//refreshrandom();
	Serial.println("123");
}
void refreshrandom() {
	int selector = 0;
	a = random(0, 20);
	b = random(0, 20);
	c = random(0, 20);
	Serial.println("a b c");
	Serial.print(a);
	Serial.print("  ");
	Serial.print(b);
	Serial.print("  ");
	Serial.println(c);

}

void toggleLed() {
	if (LEDSTATE == LOW) {
		LEDSTATE = HIGH;
		digitalWrite(LEDPIN, LEDSTATE);
	}
	else {
		LEDSTATE = LOW;
		digitalWrite(LEDPIN, LEDSTATE);
	}
}



bool trigA = false;
bool trigB = false;
bool trigC = false;
bool trigD = false;
bool trigE = false;
bool isRunningA = false;
bool isRunningB = false;
bool isRunningC = false;
bool isRunningD = false;
bool isRunningE = false;

int cycleA = 0;
int cycleB = 0;
int cycleC = 0;
int cycleD = 0;
int cycleE = 0;


void handleInputs() {
	if (digitalRead(trigPinA) && !trigA) {
		trigA = true;
		isRunningA = true;
		cycleA = 0;
	} else if (!digitalRead(trigPinA) && trigA) trigA = false;
	if (digitalRead(trigPinB) && !trigB) {
		trigB = true;
		isRunningB = true;
		cycleB = 0;
	} else if (!digitalRead(trigPinB) && trigB) trigB = false;
	if (digitalRead(trigPinC) && !trigC) {
		trigC = true;
		isRunningC = true;
		cycleC = 200;
	} else if (!digitalRead(trigPinC) && trigC) trigC = false;
	if (digitalRead(trigPinD) && !trigD) {
		trigD = true;
		isRunningD = true;
		cycleD = 0;
	} else if (!digitalRead(trigPinD) && trigD) trigD = false;
	if (digitalRead(trigPinE) && !trigE) {
		trigE = true;
		isRunningE = true;
		cycleE = 0;
	} else if (!digitalRead(trigPinE) && trigE) trigE = false;
	//Serial.print(trigA);
	//Serial.print(trigB);
	//Serial.print(trigC);
	//Serial.print(trigD);
	//Serial.println(trigE);
	if (!digitalRead(refreshRandPin)) refreshrandom();
}
#define sndLength 900
void handleOutputs() {
	byte MUX = 0;
	
	if (isRunningA) {
		if (cycleA < 1000) {
			cycleA++;
			byte drumA = (cycleA+300) >> ((cycleA + 300) | b) >> c >> (cycleA + 300);
			//byte drumA = cycleE*(cycleE >> a | cycleE >> b) >> (cycleE >> c);
			MUX = MUX + drumA;
		}
		else {
			isRunningA = false;
			//refreshrandom();
		}
	}
	if (isRunningB) {
		if (cycleB < 1000) {
			cycleB++;
			byte drumB = cycleB*(cycleB >> a | cycleB >> b) >> (cycleB >> c);
			//byte drumB = (cycleB *(cycleB >> (cycleB >> a)) % cycleB) + (cycleB * (((cycleB >> 9) & 10) | ((cycleB >> c)&a) *((cycleB >> a)&b&(cycleB >> 15))));

		
			MUX = MUX + drumB;
		}
		else {
			isRunningB = false;
			//refreshrandom();
		}
	}
	if (isRunningC) {
		if (cycleC < 1000) {
			
			cycleC++;
			byte drumC = (cycleC *(cycleC >> (cycleC >> a)) % cycleC) + (cycleC * (((cycleC >> 9) & 10) | ((cycleC >> c)&a) *((cycleC >> a)&b&(cycleC >> 15))));
			MUX = MUX + drumC;
		}
		else {
			isRunningC = false;
			//refreshrandom();
		}
	}
	if (isRunningD) {
		if (cycleD < 1000) {
			cycleD++;
			byte drumD = ((cycleD * 2)&(cycleD >> (cycleD >> a))) + ((cycleD * 1)&(cycleD >> c) & 31);
			MUX = MUX + drumD;
		}
		else {
			isRunningD = false;
			//refreshrandom();
		}
	}
	if (isRunningE) {
		if (cycleE < 2000) {
			cycleE++;
			byte drumE = cycleE*(cycleE >> a | cycleE >> b) >> (cycleE >> c);
			MUX = MUX + drumE;
		}
		else {
			isRunningE = false;
			//refreshrandom();
		}
	}

	//OUTPUT
	PORTB = MUX;
}

void loop() {
	handleOutputs();
	handleInputs();
}
	//refreshrandom();
	//Serial.println(a);
	//Serial.println(b);
	//Serial.println(c);


	//Serial.println();

	/*
		PORTB = i >> (i | b) >> c >> i;

		PORTB = i*(i >> a | i >> b) >> (i >> c);

		PORTB = (i*(i >> (i >> a)) % i) + (i * (((i >> 9) & 10) | ((i >> c)&a) *((i >> a)&b&(i >> 15))));

		PORTB = ((i * 2)&(i >> (i >> a))) + ((i * 1)&(i >> c) & 31);

		PORTB = ((i >> a | i%b)&(i >> c | i % 19));

		PORTB = i >> (i | b) >> c >> i; }

		PORTB = i*(i >> a | i >> b) >> (i >> c); }

		PORTB = i >> a; }

		PORTB = (i >> b + i << c); }
		*/
