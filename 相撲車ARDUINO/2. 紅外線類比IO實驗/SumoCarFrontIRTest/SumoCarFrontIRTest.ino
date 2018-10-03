
#define LEFT_IR A0
#define MID_IR A1
#define RIGHT_IR A2

int l;
int m;
int r;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	pinMode(LEFT_IR, INPUT);
	pinMode(MID_IR, INPUT);
	pinMode(RIGHT_IR, INPUT);
	while (!Serial);
	Serial.println("IRF150 test begin.");
	Serial.println("-------------------------------------------------");
}

// the loop function runs over and over again until power down or reset
void loop() {
	l = analogRead(LEFT_IR);
	m = analogRead(MID_IR);
	r = analogRead(RIGHT_IR);
	float volts_l = l *0.0048828125;
	float distance_l = 65 * pow(volts_l, -1.10);

	float volts_m = m*0.0048828125;
	float distance_m = 65 * pow(volts_m, -1.10);

	float volts_r = r*0.0048828125;
	float distance_r = 65 * pow(volts_r, -1.10);

	Serial.print("LEFT_IR = ");
	Serial.print(l);
	Serial.print(" ");
	Serial.print("Distance = ");
	Serial.print(distance_l);
	Serial.println(" cm");
	Serial.println(" ");

	Serial.print("MID_IR = ");
	Serial.print(m);
	Serial.print(" ");
	Serial.print("Distance = ");
	Serial.print(distance_m);
	Serial.println(" cm");
	Serial.println(" ");

	Serial.print("RIGHT_IR = ");
	Serial.print(r);
	Serial.print(" ");
	Serial.print("Distance = ");
	Serial.print(distance_r);
	Serial.println(" cm");
	Serial.println("--------------------------------------------------");
	delay(1000);
}
