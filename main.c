

//***********************************************************************
// One leg lift mode
// also can set z step height using capture offsets
//***********************************************************************
void one_leg_lift()
{
    //read current leg servo 1 positions the first time
    if(leg1_IK_control == true)
    {
        leg1_coxa  = coxa1_servo.read();
        leg1_femur = femur1_servo.read();
        leg1_tibia = tibia1_servo.read();
        leg1_IK_control = false;
    }

    //read current leg servo 6 positions the first time
    if(leg6_IK_control == true)
    {
        leg6_coxa  = coxa6_servo.read();
        leg6_femur = femur6_servo.read();
        leg6_tibia = tibia6_servo.read();
        leg6_IK_control = false;
    }

    //process right joystick left/right axis
    temp = ps2x.Analog(PSS_RX);
    temp = map(temp,0,255,45,-45);
    coxa1_servo.write(constrain(int(leg1_coxa+temp),45,135));

    //process right joystick up/down axis
    temp = ps2x.Analog(PSS_RY);
    if(temp < 117)                                //if joystick moved up
    {
        temp = map(temp,116,0,0,24);                //move leg 1
        femur1_servo.write(constrain(int(leg1_femur+temp),0,170));
        tibia1_servo.write(constrain(int(leg1_tibia+4*temp),0,170));
    }
    else                                          //if joystick moved down
    {
        z_height_right = constrain(temp,140,255);   //set Z step height
        z_height_right = map(z_height_right,140,255,1,8);
    }

    //process left joystick left/right axis
    temp = ps2x.Analog(PSS_LX);
    temp = map(temp,0,255,45,-45);
    coxa6_servo.write(constrain(int(leg6_coxa+temp),45,135));

    //process left joystick up/down axis
    temp = ps2x.Analog(PSS_LY);
    if(temp < 117)                                //if joystick moved up
    {
        temp = map(temp,116,0,0,24);                //move leg 6
        femur6_servo.write(constrain(int(leg6_femur+temp),0,170));
        tibia6_servo.write(constrain(int(leg6_tibia+4*temp),0,170));
    }
    else                                          //if joystick moved down
    {
        z_height_left = constrain(temp,140,255);    //set Z step height
        z_height_left = map(z_height_left,140,255,1,8);
    }

    //process z height adjustment
    if(z_height_left>z_height_right)
        z_height_right = z_height_left;             //use max left or right value
    if(batt_LEDs > 3) z_height_LED_color=0;       //use red LEDs if battery strong
    else z_height_LED_color=1;                    //use green LEDs if battery weak
    LED_Bar(z_height_LED_color,z_height_right);   //display Z height
    if(capture_offsets == true)                   //lock in Z height if commanded
    {
        step_height_multiplier = 1.0 + ((z_height_right - 1.0) / 3.0);
        capture_offsets = false;
    }
}


//***********************************************************************
// Set all servos to 90 degrees
// Note: this is useful for calibration/alignment of the servos
// i.e: set COXA_CAL[6], FEMUR_CAL[6], and TIBIA_CAL[6] values in
//      constants section above so all angles appear as 90 degrees
//***********************************************************************
void set_all_90()
{
    coxa1_servo.write(90+COXA_CAL[0]);
    femur1_servo.write(90+FEMUR_CAL[0]);
    tibia1_servo.write(90+TIBIA_CAL[0]);

    coxa2_servo.write(90+COXA_CAL[1]);
    femur2_servo.write(90+FEMUR_CAL[1]);
    tibia2_servo.write(90+TIBIA_CAL[1]);

    coxa3_servo.write(90+COXA_CAL[2]);
    femur3_servo.write(90+FEMUR_CAL[2]);
    tibia3_servo.write(90+TIBIA_CAL[2]);

    coxa4_servo.write(90+COXA_CAL[3]);
    femur4_servo.write(90+FEMUR_CAL[3]);
    tibia4_servo.write(90+TIBIA_CAL[3]);

    coxa5_servo.write(90+COXA_CAL[4]);
    femur5_servo.write(90+FEMUR_CAL[4]);
    tibia5_servo.write(90+TIBIA_CAL[4]);

    coxa6_servo.write(90+COXA_CAL[5]);
    femur6_servo.write(90+FEMUR_CAL[5]);
    tibia6_servo.write(90+TIBIA_CAL[5]);
}


//***********************************************************************
// Battery monitor routine
// Note: my hexapod uses a 3S LiPo battery
// (fully charged = 12.6V, nominal = 11.4V, discharged = 10.2V)
//***********************************************************************
void battery_monitor()
{
    //update voltage sum (remove oldest value and insert new value into array)
    batt_voltage_sum = batt_voltage_sum - batt_voltage_array[batt_voltage_index];
    //scale voltage reading to 0 to 14.97V (slight recalibration due to resistor tolerances)
    batt_voltage_array[batt_voltage_index] = map(analogRead(BATT_VOLTAGE),0,1023,0,1497);
    batt_voltage_sum = batt_voltage_sum + batt_voltage_array[batt_voltage_index];
    batt_voltage_index = batt_voltage_index + 1;
    if(batt_voltage_index > 49) batt_voltage_index = 0;

    //compute average battery voltage over the 50 samples
    batt_voltage = batt_voltage_sum / 50;

    //remap battery voltage for display on the LEDs
    //minimum = 10.2V, maximum (full) = 12.3V
    batt_LEDs = map(constrain(batt_voltage,1020,1230),1020,1230,1,8);
    if(batt_LEDs > 3) LED_Bar(1,batt_LEDs); //display green if voltage >= 11.40V
    else LED_Bar(0,batt_LEDs);              //display red if voltage < 11.40V
}


//***********************************************************************
// LED Bar Graph Routine
// Note: 8 dual-color red/green LEDs in a row
// LED_color: 0=Red, 1=Green
// LED_count: 0 to 8
//***********************************************************************
void LED_Bar(int LED_color,int LED_count)
{
    //display a red bar
    if(LED_color == 0)
    {
        for(int i=0; i<LED_count; i++)
        {
            digitalWrite((RED_LED1+(4*i)),HIGH);
            digitalWrite((GREEN_LED1+(4*i)),LOW);
        }
        for(int i=LED_count; i<8; i++)
        {
            digitalWrite((RED_LED1+(4*i)),LOW);
            digitalWrite((GREEN_LED1+(4*i)),LOW);
        }
    }

        //display a green bar
    else
    {
        for(int i=0; i<LED_count; i++)
        {
            digitalWrite((GREEN_LED1+(4*i)),HIGH);
            digitalWrite((RED_LED1+(4*i)),LOW);
        }
        for(int i=LED_count; i<8; i++)
        {
            digitalWrite((GREEN_LED1+(4*i)),LOW);
            digitalWrite((RED_LED1+(4*i)),LOW);
        }
    }
}


//***********************************************************************
// Print Debug Data
//***********************************************************************
void print_debug()
{
    //output IK data
//  Serial.print(int(theta_coxa));
//  Serial.print(",");
//  Serial.print(int(theta_femur));
//  Serial.print(",");
//  Serial.print(int(theta_tibia));
//  Serial.print(",");

    //output XYZ coordinates for all legs
//  for(leg_num=0; leg_num<6; leg_num++)
//  {
//    Serial.print(int(current_X[leg_num]));
//    if(leg_num<5) Serial.print(",");
//  }
//  Serial.print("  ");
//  for(leg_num=0; leg_num<6; leg_num++)
//  {
//    Serial.print(int(current_Y[leg_num]));
//    if(leg_num<5) Serial.print(",");
//  }
//  Serial.print("  ");
//  for(leg_num=0; leg_num<6; leg_num++)
//  {
//    Serial.print(int(current_Z[leg_num]));
//    if(leg_num<5) Serial.print(",");
//  }
//  Serial.print("  ");

    //display elapsed frame time (ms) and battery voltage (V)
    currentTime = millis();
    Serial.print(currentTime-previousTime);
    Serial.print(",");
    Serial.print(float(batt_voltage)/100.0);
    Serial.print("\n");
}
