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
//#include <datacommsimlib.h>

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

	state = NONE;

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
			// +++ add code here and to the predefined function void l1_send(unsigned long l2frame, int framelen) below

			// ---
			break;

		case L1_RECEIVE:
			Serial.println("[State] L1_RECEIVE");
			// +++ add code here and to the predifend function boolean l1_receive(int timeout) below

			// ---
			break;

		case L2_DATA_SEND:
			Serial.println("[State] L2_DATA_SEND"); 
			// +++ add code here 

			// ---
			break;

		case L2_RETRANSMIT:
			Serial.println("[State] L2_RETRANSMIT");
			// +++ add code here 

			// ---
			break;

		case L2_FRAME_REC:
			Serial.println("[State] L2_FRAME_REC");
			// +++ add code here 

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
			// +++ add code here

			// ---
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

}

boolean l1_receive(int timeout) {
	
	return true;
}

//////////////////////////////////////////////////////////
//
// Add your functions here
//
