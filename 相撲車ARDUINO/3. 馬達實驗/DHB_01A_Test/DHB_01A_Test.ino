#define ENL 11   //EN_A
#define ML1 10   //IN1_A
#define ML2  9   //IN2_A
#define ENR  7   //EN_B
#define MR1  5   //IN1_B
#define MR2  6   //IN2_B

int speed = 0;

//DeadZone is 50.
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	pinMode(ML1, OUTPUT);
	pinMode(ML2, OUTPUT);
	pinMode(ENL, OUTPUT);
	pinMode(MR1, OUTPUT);
	pinMode(MR2, OUTPUT);
	pinMode(ENR, OUTPUT);

	while (!Serial);
	Serial.println("Motor test START");
	Serial.println("Enter the word. w:formwod, s:backword");
	Serial.println("a:turnLeft, d:turnRight, r:brake, t:DZtest, q:Stop");
	Serial.println("-----------------------------------------------------");
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (Serial.available() > 0) {
		int SRR = Serial.read();
		switch (SRR)
		{
		case 119://w
			delay(5);
			forword();
			Serial.println("Forword");
			break;

		case 115://s
			delay(5);
			backword();
			Serial.println("Backword");
			break;

		case 97://a
			turnLeft();
			Serial.println("turnLeft");
			break;

		case 100://d
			turnRight();
			Serial.println("turnRight");
			break;

		case 116://t
			dztest();
			break;

		case 113://q
			stop();
			Serial.println("Stop");
			break;
		case 'r':
			brake();
			Serial.println("Brake");
			break;
		}//switch
	}//if
}

void forword() {
	digitalWrite(ML1, HIGH);
	digitalWrite(ML2, LOW);
	digitalWrite(ENL, HIGH);
	digitalWrite(MR1, HIGH);
	digitalWrite(MR2, LOW);
	digitalWrite(ENR, HIGH);
}

void backword() {
	digitalWrite(ML1, LOW);
	digitalWrite(ML2, HIGH);
	digitalWrite(ENL, HIGH);
	digitalWrite(MR1, LOW);
	digitalWrite(MR2, HIGH);
	digitalWrite(ENR, HIGH);
}

void turnLeft() {
	digitalWrite(ML1, LOW);
	digitalWrite(ML2, LOW);
	digitalWrite(MR1, HIGH);
	digitalWrite(MR2, LOW);
	digitalWrite(ENR, HIGH);
}

void turnRight() {
	digitalWrite(ML1, HIGH);
	digitalWrite(ML2, LOW);
	digitalWrite(MR1, LOW);
	digitalWrite(MR2, LOW);
}

void dztest() {
	Serial.println("DeadZone find START");
	for (speed = 50; speed <= 255; speed++) {
		Serial.print("Now speed : ");
		Serial.println(speed);
		analogWrite(ML1, speed);
		analogWrite(ML2, 0);
		digitalWrite(ENL, HIGH);
		analogWrite(MR1, speed);
		analogWrite(MR2, 0);
		digitalWrite(ENR, HIGH);
		delay(1000);
		if (Serial.available() > 0)
			break;
	}
}

void stop() {
	digitalWrite(ML1, LOW);
	digitalWrite(ML2, LOW);
	digitalWrite(ENL, HIGH);
	digitalWrite(MR1, LOW);
	digitalWrite(MR2, LOW);
	digitalWrite(ENR, HIGH);
}

void brake() {
	digitalWrite(ML1, HIGH);
	digitalWrite(ML2, HIGH);
	digitalWrite(ENL, HIGH);
	digitalWrite(MR1, HIGH);
	digitalWrite(MR2, HIGH);
	digitalWrite(ENR, HIGH);
}

void situTurnleft() {

}

void situTurnright() {

}

void backTurnleft() {

}

void backTurnright() {

}