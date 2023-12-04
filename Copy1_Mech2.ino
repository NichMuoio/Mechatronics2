#include<MechFunc.h>
#include<Encoder.h>

//NOT ENOUGH PINS ON TEENSY 4.0 ???
#define ARM_PWM 12 // Dig Pin 12
#define ARM_DIR1 16
#define ARM_DIR2 17
#define ARM_CHAN 0
#define ARM_E1 44
#define ARM_E2 43

#define FING1_PWM 0 //PWM on "digital Pin 0"
#define FING1_DIR1 1 // Digital Pin 1 (NEED H/L)
#define FING1_DIR2 2 // Digital Pin 2 (NEED H/L)
#define FING1_CHAN 1 //CHANNEL USED IN SET_PWM
#define FING1_E1 3 // Digital Pin 3 (NEED ENC Int)
#define FING1_E2 4 // Digital Pin 4 (NEED Enc Int)
#define FING1_SENS 23 //analog pin A9 (A_ReadIn)

#define FING2_PWM 5 //PWM on "digital Pin 5"
#define FING2_DIR1 6 // Digital Pin 6 (NEED H/L)
#define FING2_DIR2 7  // Digital Pin 7 (NEED H/L)
#define FING2_CHAN 2 //CHANNEL USED IN SET_PWM
#define FING2_E1 8 // Digital Pin 8 (NEED ENC Int)
#define FING2_E2 9 // Digital Pin 9 (NEED Enc Int)
#define FING2_SENS 22 //analog pin A8 (A_ReadIn)

#define THUMB_PWM 13 //LED PIN CANNOT BE USED FOR ENC
#define THUMB_DIR1 10 // NEED H/L PIN D10
#define THUMB_DIR2 11 // NEED H/L PIN D11
#define THUMB_CHAN 3 //CHANNEL USED IN SET PWM
#define THUMB_E1 15 //ALSO A1 but needs to be used for ENC placement
#define THUMB_E2 14 //A0 but needs to be used for ENC Placement
#define THUMB_SENS 21  //analog pin A7 (A_ReadIn)

#define POT1_PIN 20 // ANALOG Pin A6 for Pot read in
#define POT2_PIN 19 // Analog Pin A5 for POT 2 Read In
#define BUTTON_PIN  //Digital Pin

const int ARM_ER = 12; // Replace with your encoder resolution
const float ARM_GR = 380; // Replace with your gear ratio

const int FING1_ER = 12; // Replace with your encoder resolution
const float FING1_GR = 380; // Replace with your gear ratio

const int FING2_ER = 12; // Replace with your encoder resolution
const float FING2_GR = 380; // Replace with your gear ratio

const int THUMB_ER = 12; // Replace with your encoder resolution
const float THUMB_GR = 380; // Replace with your gear ratio

Encoder ARM_ENC(ARM_E1, ARM_E2);
Encoder FING1_ENC(FING1_E1, FING1_E2);
Encoder FING2_ENC(FING2_E1, FING2_E2);
Encoder THUMB_ENC(THUMB_E1, THUMB_E2);

long int ARM_ENC_VAL = 0;
long int FING1_ENC_VAL = 0;
long int FING2_ENC_VAL = 0;
long int THUMB_ENC_VAL = 0;


void pin_init();
void set_pwm();
void Arm_Control();
void enc_init();
void read_encoders();
void get_user_inputs();
void control();

int ARM_POS[2] = {0, 90}; //Degrees on the Arm Motor ALWAYS START HERE 


void setup() {
  // put your setup code here, to run once:
  pin_init();
  enc_init();
}

void loop() {
  // read positions
  read_encoders();
  //get user input
  get_user_input();
  //control motors
  control();

}
