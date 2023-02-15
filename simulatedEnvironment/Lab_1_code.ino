////////////////////////////
//
// V21.1 Skeleton.ino
// 
// Adapted to the physical and simulated environments
//
// 2022-12-17 Jens Andersson
//
////////////////////////////

//
// Select library
//
// uncomment for the physical environment
//#include <datacommlib.h>
//
// uncomment for the simulated environment
#include <datacommsimlib.h>

//
// Prototypes
//

//predefined
void l1_send(unsigned long l2frame, int framelen);
boolean l1_receive(int timeout);
// your own

//
// Runtime
//

//////////////////////////////////////////////////////////
//
// Add your global constant and variabel declaretions here
//

int state = NONE;
Shield sh; // note! no () since constructor takes no arguments
Transmit tx;
Receive rx;

int selectedPin; //Pin selected by user
byte tx_bit = 0; //Bit to be transmitted
byte buffer;
boolean recOK;

const byte SFD = 0b01111110;
const byte PREAMBLE = 0b10101010;

unsigned long timeStart;
unsigned long timeDrift;
unsigned long timeout = 20000;
//////////////////////////////////////////////////////////

//
// Code
//
void setup() {
	sh.begin();

	//////////////////////////////////////////////////////////
	//
	// Add init code here
	//

	state = APP_PRODUCE;

	// Set your development node's address here

	//////////////////////////////////////////////////////////
}

void loop() {

	//////////////////////////////////////////////////////////
	//
	// State machine
	// Add code for the different states here
	//

	switch(state){

		case L1_SEND:
			Serial.println("[State] L1_SEND");

			l1_send(tx.frame, LEN_FRAME);
			state = L1_RECEIVE;
			break;

		case L1_RECEIVE:
			Serial.println("[State] L1_RECEIVE");
			recOK = l1_receive(20000);
			state = L2_FRAME_REC;  
			break;

		case L2_DATA_SEND:
			Serial.println("[State] L2_DATA_SEND"); 
			tx.frame_from = 0;
			tx.frame_to = 0;
			tx.frame_type = FRAME_TYPE_DATA;
			tx.frame_seqnum = 0;
			tx.frame_payload = selectedPin;
			tx.frame_crc = 0;
			tx.frame_generation();
			tx.print_frame();

			state = L1_SEND;
			break;

		case L2_RETRANSMIT:
			Serial.println("[State] L2_RETRANSMIT");
			// +++ add code here 

			// ---
			break;

		case L2_FRAME_REC:
			Serial.println("[State] L2_FRAME_REC");
			rx.frame_decompose();

			state = APP_PRODUCE;

			// ---
			break;

		case L2_ACK_SEND:
			Serial.println("[State] L2_ACK_SEND");
			// +++ add code here 

			// ---
			break;

		case L2_ACK_REC:
			Serial.println("[State] L2_ACK_REC");
			// +++ add code here

			// ---
			break;

		case APP_PRODUCE: 
			Serial.println("[State] APP_PRODUCE");
			selectedPin = sh.select_led();
			Serial.println(selectedPin);
			state = L2_DATA_SEND;
			break;

		case APP_ACT:
			Serial.println("[State] APP_ACT");
			// +++ add code here 

			// ---
			break;

		case HALT:  
			Serial.println("[State] HALT");
			sh.halt();
			break;

		default:
			Serial.println("UNDEFINED STATE");
			break;
	}

	//////////////////////////////////////////////////////////

}
//////////////////////////////////////////////////////////
//
// Add code to the predfined functions
//
void l1_send(unsigned long frame, int framelen) {
	Serial.println("l1 help function send");
	help_send_byte(PREAMBLE);
	help_send_byte(SFD);
	help_send_frame(frame);

}

void help_send_byte(byte toSend){
	Serial.println("send SFD and PREAMBLE");
	for (int i = 0; i<8; i++){
		tx_bit = (((toSend << i)& 0x80) == 0x80 ) ? 0x1 : 0x0;
		write_pin(PIN_TX, tx_bit);
	}}

void help_send_frame(unsigned long frame){
	for (int i = 0; i<32; i++){
		tx_bit = (((frame << i) & 0x80000000) == 0x80000000) ? 0x1 : 0x0;
		write_pin(PIN_TX, tx_bit);
	}}

boolean l1_receive(int timeout) {
	timeStart = millis();
	buffer = 0b00000000;

	while (sh.sampleRecCh(PIN_RX) == LOW){
		if (false){ // check_timeOut(timeStart)
			Serial.print("TIMEOUT");
			return false;
		}
	}

	Serial.println("Positive flank found");
	delay(50);

	while(buffer != SFD){
		timeDrift = millis();
		if (false){ // check_timeOut(timeStart)
			Serial.print("TIMEOUT");
			return false;
		}

		if (sh.sampleRecCh(PIN_RX) == HIGH){
			buffer = (buffer << 1) | 0b1; // left shift and XOR
			digitalWrite(DEB_1, HIGH);
		} else {
			buffer = buffer << 1;
			digitalWrite(DEB_1, LOW);
		}
		delay(T_S - (millis() - timeDrift)); // compensate for time taken to run code
	}
	digitalWrite(DEB_1, HIGH);
	Serial.print(buffer, BIN);

	for (int i = 0; i < LEN_FRAME; i++){
		timeDrift = millis();
		if (sh.sampleRecCh(PIN_RX) == HIGH){
			rx.frame = (rx.frame << 1) | 0b1 ; // left shift and XOR
			digitalWrite(DEB_2, HIGH);
		} else {
			rx.frame = rx.frame << 1;
			digitalWrite(DEB_2, LOW);
		} 
		delay(T_S - (millis() - timeDrift));   
	}

	Serial.print("frame received successfully");
	digitalWrite(DEB_1, LOW);
	digitalWrite(DEB_2, LOW);
	return true;

}

void write_pin(const int pin, byte result_bit){
	if(result_bit == 0x1){
		digitalWrite(pin, HIGH);
	} else {
		digitalWrite(pin, LOW);
	}
	delay(100);
}

boolean check_timeout(long start){
	return (millis() - start >= timeout);
}

