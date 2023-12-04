/**********************************************
 FIRST PART OF THE LOOP FUNCTION
***********************************************/

void read_encoders()
{
  //read in each encoder value
  ARM_ENC_VAL = ARM_ENC.read();
  FING1_ENC_VAL = FING1_ENC.read();
  FING2_ENC_VAL = FING2_ENC.read();
  THUMB_ENC_VAL = THUMB_ENC.read();

  // calculate the angle for each motor
  ARM_ANG = (float(ARM_ENC_VAL) / ARM_ER) * 360.0 / ARM_GR;
  FING1_ANG = (float(FING1_ENC_VAL) / FING1_ER) * 360.0 / FING1_GR;
  FING2_ANG = (float(FING2_ENC_VAL) / FING2_ER) * 360.0 / FING2_GR;
  THUMB_ANG = (float(THUMB_ENC_VAL) / THUMB_ER) * 360.0 / THUMB_GR;
}

/**********************************************
 SECOND PART OF THE LOOP FUNCTION
***********************************************/

void get_user_input()
{
  //Section for getting a user input, this is currently set up for joystick use
  POT1_VAL = analogRead(POT1_PIN);
  POT2_VAL = analogRead(POT2_PIN);
  //Button pin will set the flag
  BUTTON_VAL = digitalRead(BUTTON_PIN);
  if(BUTTON_VAL == HIGH)
  {
    flag ~= flag;
  }
}

/***************************************************
 THIRD PART OF THE MAIN LOOP 
****************************************************/

void control()
{
  // This control function will call both the control for the finger and the control for the arm
  //MAYBE implement thumb control... we have the encoder
  //get feedback
  get_feedback();

  //control appendages
  Finger_Control();
  Thumb_Control();
  Arm_Control();
}

/*******************************************
 FUNCTIONS CALLED OUTSIDE OF THE MAIN LOOP
********************************************/

// CALLED IN THE CONTROL FUNCTION

void get_feedback()
{
  FLEX1 = analogRead(FING1_SENS);
  FLEX2 = analogRead(FING2_SENS);
  FSR1 =  analogRead(THUMB_SENS);

  FING1_FB = map(FLEX1);
  FING2_FB = map(FLEX2);
  THUMB_FB = map(FSR1);
}

void Finger_Control()
{


 // FING1_VOL = Kp*()
 // FING2_VOL = 




  set_pwm(FING1_CHAN, DUTY1);
  set_pwm(FING2_CHAN, DUTY2);
}

void Thumb_Control()
{

}

void Arm_Control(int flag)
{
  static long PREV_ER = 0;
  ARM_ER = ARM_ANG - ARM_POS[flag];  // this logic is incorrect NEED TO CHANGE

  ARM_VOL = Kp*(ARM_ER) + Kd*(ARM_ER - PREV_ER); // Control calculations

  PREV_ER = ARM_ER; //save the previous error for deriv control

  //SETTING BOUNDS --- Might want to do with duty not voltage
  if(ARM_VOL > VCC_MAX)
  ARM_VOL = VCC_MAX;
  if(ARM_VOL < VCC_MIN)
  ARM_VOL = VCC_MIN;

  DUTY = (ARM_VOL/VCC_MAX)*255;
  set_pwm(ARM_CHAN, DUTY);

  if(ARM_ER <= ER_MARGIN)
  {
    flag ~= flag;
  }
}

// CALLED IN THE SETUP

void pin_init()
{
  pinMode(ARM_PWM, OUTPUT); // initialize arm as an output
  pinMode(ARM_DIR1, OUTPUT); // initialize arm direction
  pinMode(ARM_DIR2, OUTPUT); // initialize arm direction

  pinMode(FING1_PWM, OUTPUT); // initialize fing1 pin as an output
  pinMode(FING1_DIR1, OUTPUT); // initialize fing1 direction1
  pinMode(FING1_DIR2, OUTPUT); // initialize fing1 direction2
  
  pinMode(FING2_PWM, OUTPUT); // initialize fing2 pin as an output
  pinMode(FING2_DIR1, OUTPUT); // initialize fing2 direction1
  pinMode(FING2_DIR2, OUTPUT); // initialize fing2 direction2

  pinMode(THUMB_PWM, OUTPUT); // initialize arm as an output
  pinMode(THUMB_DIR1, OUTPUT); // initialize arm direction
  pinMode(THUMB_DIR2, OUTPUT); // initialize arm direction

  pinMode(POT1_PIN, INPUT); // initialize arm as an output
  pinMode(POT2_PIN, INPUT); // initialize arm direction
  pinMode(BUTTON_PIN, INPUT); // initialize arm direction
}

void enc_init()
{
  // writing each encoder to 0 to begin, this will stop spill over from test to test
  ARM_ENC.write(0);
  FING1_ENC.write(0);
  FING2_ENC.write(0);
  THUMB_ENC.write(0);
}


// CALLED IN THE INDIVIDUAL CONTROL FUNCTIONS

void set_pwm(int channel, int duty)
{
  // SWITCH statement for setting pwm, each motor has its own case
  switch channel:
  {
    case 0: // FOR THE ARM
      {
        if(duty >= 0)
        {
          digitalWrite(ARM_DIR1, HIGH);
          digitalWrite(ARM_DIR2, LOW);
        }
        else
        {
          digitalWrite(ARM_DIR1, LOW);
          digitalWrite(ARM_DIR2, HIGH);
        }
        analogWrite(ARM_PWM, abs(duty));
      }
    break;

    case 1: //FINGER 1
      {
        if(duty >= 0)
        {
          digitalWrite(FING1_DIR1, HIGH);
          digitalWrite(FING1_DIR2, LOW);
        }
        else
        {
          digitalWrite(FING1_DIR1, LOW);
          digitalWrite(FING1_DIR2, HIGH);
        }
        analogWrite(FING1_PWM, abs(duty));
      }
    break;

    case 2: //FINGER 2
      {
        if(duty >= 0)
        {
          digitalWrite(FING2_DIR1, HIGH);
          digitalWrite(FING2_DIR2, LOW);
        }
        else
        {
          digitalWrite(FING2_DIR1, LOW);
          digitalWrite(FING2_DIR2, HIGH);
        }
        analogWrite(FING2_PWM, abs(duty));
      }
    break;

    case 3: //THUMB
      {
        if(duty >= 0)
        {
          digitalWrite(THUMB_DIR1, HIGH);
          digitalWrite(THUMB_DIR2, LOW);
        }
        else
        {
          digitalWrite(THUMB_DIR1, LOW);
          digitalWrite(THUMB_DIR2, HIGH);
        }
        analogWrite(THUMB_PWM, abs(duty));
      }
    break;
  }
}




