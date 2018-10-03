//#include <ozone.h>

//MR2X5A myMotor(0);

//Motor
#define ENL 11   //EN_A
#define ML1 10   //IN1_A
#define ML2  9   //IN2_A
#define ENR  7   //EN_B
#define MR1  5   //IN1_B
#define MR2  6   //IN2_B

//Sensor
#define B_L_IR 13
#define B_R_IR 12
/*#define B_ECHO_PIN 8
#define B_TRIGGER_PIN 9
#define F_ECHO_PIN 4
#define F_TRIGGER_PIN 3*/
#define F_L_IR A0
#define F_M_IR A1
#define F_R_IR A2

/*Ultrasonic f_ultrasonic(F_TRIGGER_PIN, F_ECHO_PIN);
Ultrasonic b_ultrasonic(B_TRIGGER_PIN, B_ECHO_PIN);*/

int norSpeed = 300;  //200~1024
int fastSpeed = 180; //200~1024
//DeadZone is 400.

int b_l = digitalRead(B_L_IR);
int b_r = digitalRead(B_R_IR);
/*float f_cmMsec, b_cmMsec,f_inMsec,b_inMsec;
long f_microsec = f_ultrasonic.timing(), b_microsec = b_ultrasonic.timing();*/

/*int frontSonarread = 25; //cm
int backSonarread = 10;  //cm*/
int f_l_Read = 300;  //0~1024
int f_m_Read = 300;  //0~1024
int f_r_read = 300;  //0~1024
int duration = 5;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	pinMode(ENL, OUTPUT);
	pinMode(ML1, OUTPUT);
	pinMode(ML2, OUTPUT);
	pinMode(ENR, OUTPUT);
	pinMode(MR1, OUTPUT);
	pinMode(MR2, OUTPUT);

	pinMode(B_L_IR, INPUT);
	pinMode(B_R_IR, INPUT);
	pinMode(F_L_IR, INPUT);
	pinMode(F_M_IR, INPUT);
	pinMode(F_R_IR, INPUT);


}

// the loop function runs over and over again until power down or reset
void loop() {
	int b_l = digitalRead(B_L_IR);
	int b_r = digitalRead(B_R_IR);
	/*Serial.println("Buttom IR Status: ");
	Serial.print("B_L_IR = ");
	Serial.print(b_l);
	Serial.print(", ");
	Serial.print("B_L_IR = ");
	Serial.println(b_r);*/
	if (b_l == 0 && b_r == 0) {
		brake();
		f_backword();
		delay(750);
		stop();
		delay(100);
		situTurnRight();
		delay(750);
		//Serial.println("STOP1");
		return;
	}//if(b_l)
	else;
	if (b_l==1 && b_r == 0) {
		brake();
		f_backword();
		delay(750);
		stop();
		delay(100);
		turnRight();
		delay(750);
		//Serial.println("STOP2");
		return;
	}//if(b_r)
	else;
	if (b_l == 0 && b_r == 1) {
		brake();
		f_backword();
		delay(750);
		stop();
		delay(100);
		turnLeft();
		delay(750);
		return;
		//Serial.println("STOP3");
	}//if(b_l && b_r)
	else;
	find();
}

void find() {
	//IRF150 change
	int f_l = analogRead(F_L_IR);
	int f_m = analogRead(F_M_IR);
	int f_r = analogRead(F_R_IR);
	/*float volts_f_l = f_l * 0.0048828125;
	float volts_f_m = f_m * 0.0048828125;
	float volts_f_r = f_r * 0.0048828125;
	float distance_f_l = 65 * pow(volts_f_l, -1.10);
	float distance_f_m = 65 * pow(volts_f_m, -1.10);
	float distance_f_r = 65 * pow(volts_f_r, -1.10);*/
	//Sonar
	/*f_cmMsec = f_ultrasonic.convert(f_microsec, Ultrasonic::CM);
	b_cmMsec = b_ultrasonic.convert(b_microsec, Ultrasonic::CM);*/
	/*Serial.print("Front Left : ");
	Serial.print(f_l);
	Serial.print(" ");
	Serial.print("Front mid : ");
	Serial.print(f_m);
	Serial.print(" ");
	Serial.print("Front Right : ");
	Serial.print(f_r);
	Serial.println(" ");*/
	/*Serial.print("Front Sonar : ");
	Serial.print(f_cmMsec);
	Serial.print(" cm, ");
	Serial.print("Back Sonar : ");
	Serial.print(b_cmMsec);
	Serial.print(" ,cm ");
	Serial.println(" ");*/
	//delay(1000);
	if (f_l > f_l_Read) {
		f_turnLeft();
		delay(100);
		return;
	}//if (f_l > f_l_Read)
	else;
	if (f_m > f_m_Read) {
		for (int i = 1; i <= duration; i++) {
			b_l = digitalRead(B_L_IR);
			b_r = digitalRead(B_R_IR);
			f_m = analogRead(F_M_IR);
			f_forword();
			delay(1000);
			Serial.println(i);
			Serial.println(f_m);
			if (i == duration || f_m < f_m_Read || b_l == 0 || b_r == 0) {
				f_backword();
				delay(500);
				f_backTurnLeft();
				delay(300);
				break;
			}//if (i == count || f_m < f_m_Read)
		}//(f_m > f_m_Read)
		return;
	}
	else;
	if (f_r > f_r_read) {
		f_turnRight();
		delay(100);
		return;
	}//(f_r > f_r_read)
	else;
	/*if (b_cmMsec < backSonarread && b_l == 1 && b_r == 1) {
	brake();
	delay(50);
	f_backword();
	return;
	}
	else;*/
	forword();
	return;
}

void forword() {
	analogWrite(ML1, norSpeed);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, norSpeed);
	analogWrite(MR2, 0);
	digitalWrite(ENR, HIGH);
	/*myMotor.ForwardA(norSpeed);
	myMotor.ForwardB(norSpeed);*/
}

void backword() {
	analogWrite(ML1, 0);
	analogWrite(ML2, norSpeed);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, norSpeed);
	digitalWrite(ENR, HIGH);
	/*myMotor.BackwardA(norSpeed);
	myMotor.BackwardB(norSpeed);*/
}

void turnLeft() {
	analogWrite(ML1, 0);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, norSpeed);
	analogWrite(MR2, 0);
	digitalWrite(ENR,HIGH);
	/*myMotor.ForwardA(norSpeed);
	myMotor.StopB();*/
}

void turnRight() {
	analogWrite(ML1, norSpeed);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, 0);
	digitalWrite(ENR,HIGH);
	/*myMotor.StopA();
	myMotor.ForwardB(norSpeed);*/
}


void stop() {
	digitalWrite(ML1, LOW);
	digitalWrite(ML2, LOW);
	digitalWrite(ENL,HIGH);
	digitalWrite(MR1, LOW);
	digitalWrite(MR2, LOW);
	digitalWrite(ENR,HIGH);
	/*myMotor.StopA();
	myMotor.StopB();*/
}

void brake() {
	digitalWrite(ML1, HIGH);
	digitalWrite(ML2, HIGH);
	digitalWrite(ENL,HIGH);
	digitalWrite(MR1, HIGH);
	digitalWrite(MR2, HIGH);
	digitalWrite(ENR,HIGH);
	/*myMotor.BrakeA();
	myMotor.BrakeB();*/
}

void situTurnLeft() {
	analogWrite(ML1, 0);
	analogWrite(ML2, norSpeed);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, norSpeed);
	analogWrite(MR2, 0);
	digitalWrite(ENR,HIGH);
	/*myMotor.ForwardA(norSpeed);
	myMotor.BackwardB(norSpeed);*/
}

void situTurnRight() {
	analogWrite(ML1, norSpeed);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, norSpeed);
	digitalWrite(ENR,HIGH);
	/*myMotor.BackwardA(norSpeed);
	myMotor.ForwardB(norSpeed);*/
}

void f_forword() {
	analogWrite(ML1, fastSpeed);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, fastSpeed);
	analogWrite(MR2, 0);
	digitalWrite(ENR,HIGH);
	/*myMotor.ForwardA(fastSpeed);
	myMotor.ForwardB(fastSpeed);*/
}

void f_backword() {
	analogWrite(ML1, 0);
	analogWrite(ML2, fastSpeed);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, fastSpeed);
	digitalWrite(ENR,HIGH);
	/*myMotor.BackwardA(fastSpeed);
	myMotor.BackwardB(fastSpeed);*/
}

void f_turnLeft() {
	analogWrite(ML1, 0);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, fastSpeed);
	analogWrite(MR2, 0);
	digitalWrite(ENR,HIGH);
	/*myMotor.ForwardA(fastSpeed);
	myMotor.StopB();*/
}

void f_turnRight() {
	analogWrite(ML1, fastSpeed);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, 0);
	digitalWrite(ENR,HIGH);
	/*myMotor.StopA();
	myMotor.ForwardB(fastSpeed);*/
}

void f_situTurnLeft() {
	analogWrite(ML1, 0);
	analogWrite(ML2, fastSpeed);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, fastSpeed);
	analogWrite(MR2, 0);
	digitalWrite(ENR,HIGH);
	/*myMotor.ForwardA(fastSpeed);
	myMotor.BackwardB(fastSpeed);*/
}

void f_situTurnRight() {
	analogWrite(ML1, fastSpeed);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, fastSpeed);
	digitalWrite(ENR,HIGH);
	/*myMotor.BackwardA(fastSpeed);
	myMotor.ForwardB(fastSpeed);*/
}

void backTurnLeft() {
	analogWrite(ML1, 0);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, norSpeed);
	digitalWrite(ENR,HIGH);
	/*myMotor.BackwardA(norSpeed);
	myMotor.StopB();*/
}

void backTurnRight() {
	analogWrite(ML1, 0);
	analogWrite(ML2, norSpeed);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, 0);
	digitalWrite(ENR,HIGH);
	/*myMotor.StopA();
	myMotor.BackwardB(norSpeed);*/
}

void f_backTurnLeft() {
	analogWrite(ML1, 0);
	analogWrite(ML2, 0);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, fastSpeed);
	digitalWrite(ENR,HIGH);
	/*myMotor.BackwardA(fastSpeed);
	myMotor.StopB();*/
}

void f_backTurnRight() {
	analogWrite(ML1, 0);
	analogWrite(ML2, fastSpeed);
	digitalWrite(ENL,HIGH);
	analogWrite(MR1, 0);
	analogWrite(MR2, 0);
	digitalWrite(ENR,HIGH);
	/*myMotor.StopA();
	myMotor.BackwardB(fastSpeed);*/
}
