

#define L_IR 13
#define R_IR 12
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	pinMode(L_IR, INPUT);
	pinMode(R_IR, INPUT);
}//setup

 // the loop function runs over and over again until power down or reset
void loop() {
	int L = digitalRead(L_IR);
	int R = digitalRead(R_IR);
	Serial.print("Left IR Status: ");
	Serial.print(L);
	Serial.print(" ");
	Serial.print("Right IR Status: ");
	Serial.println(R);
	delay(1000);
	if (L <1 || R <1) {
		Serial.println("Out the Space!!");
		Serial.println(" ");
	}//if
	else {
		Serial.println("Inside the Space!!");
		Serial.println(" ");
	}//else
}//loop
