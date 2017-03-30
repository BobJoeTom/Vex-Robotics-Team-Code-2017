#pragma config(Sensor, dgtl1,  yLS,            sensorSONAR_mm)
#pragma config(Sensor, dgtl3,  yRS,            sensorSONAR_mm)
#pragma config(Sensor, dgtl5,  xLS,            sensorSONAR_mm)
#pragma config(Sensor, dgtl7,  xRS,            sensorSONAR_mm)
#pragma config(Motor,  port1,           fLeft,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port2,          rBack,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           bLeft,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           lFront,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           Claw,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           fRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           rFront,         tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           bRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           lBack,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          sup,         tmotorServoContinuousRotation, openLoop)

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
/*---------------------------------------------------------------------------*/
/*                          Utility Methods	                       */
/*---------------------------------------------------------------------------*/
/*
*/
//Array of 14900 bytes, sample packets down below
byte auton[14900];
//CH1, Ch1, Ch3, Riase, Close
//93 times per seond(.01 times per second)
void userMove()//Called repeatedly multiple times per second to reset motor pwoer settings to controller input
{
	if(abs(vexRT[Ch1] + vexRT[Ch3] + vexRT[Ch4])>10){//COntroller dead zone
	
motor[fRight] = (vexRT[Ch1] - vexRT[Ch3] + vexRT[Ch4]);
	motor[bRight] =  (vexRT[Ch1] - vexRT[Ch3] - vexRT[Ch4]);
	motor[fLeft] = (vexRT[Ch1] + vexRT[Ch3] + vexRT[Ch4]);
	motor[bLeft] =  (vexRT[Ch1] + vexRT[Ch3] - vexRT[Ch4]);

	}else{
	motor[fRight] = 0;
	motor[bRight] =  0;
	motor[fLeft] = 0;
	motor[bLeft] =  0;
	}
}

void userMove(int index)//Called during auton, to read on a certain index
{
	if(abs(auton[index] + auton[index+1] + auton[index+2])>10){//COntroller dead zone
	motor[fRight] = (auton[index] - auton[index+1] + auton[index+2]);
	motor[bRight] =  (auton[index] - auton[index+1] - auton[index+2]);
	motor[fLeft] = (auton[index] + auton[index+1] + auton[index+2]);
	motor[bLeft] =  (auton[index] + auton[index+1] - auton[index+2]);
	}else{
	motor[fRight] = 0;
	motor[bRight] =  0;
	motor[fLeft] = 0;
	motor[bLeft] =  0;
}
}
void userMove(byte C1, byte C3, byte C4)//Called during auton, to read on a certain index
{
	if(abs(C1 + C3 + C4)>10){//COntroller dead zone
	motor[fRight] = ( C1  - C3 + C4);
	motor[bRight] = (C1 - C3  - C4);
	motor[fLeft] =  ( C1  + C3 + C4);
	motor[bLeft] =  (C1 + C3  - C4);
	}else{
	motor[fRight] = 0;
	motor[bRight] =  0;
	motor[fLeft] = 0;
	motor[bLeft] =  0;
}
}

void raiseClaw(float speed)//Sets the scissor lift motors to a certain speed/power setting
{	//Spped greater than 0 lifts scissor lift, speed less than 0 lowers lift
	motor[lBack] = speed;
	motor[rBack] = -speed;
	motor[lFront] = speed;
	motor[rFront] = -speed;
}

void openClaw(float speed){//Sets the claw motors to a certain speed/power setting
	//Speed greater than 0 closes, less than 0 opens
	motor[Claw] = speed;
}

void support(float speed){
	motor[sup]=speed;	
}

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
byte meshByte(byte raise,byte open){
	return(raise << 4) | open;//Concatinate Bytes 
}

byte meshByte(byte raise,byte open, byte supp){
	return(raise<<4)|(supp<<2)|(open);//Concatinate Bytes 
}

int res = 1000/(125);

void newMap(){
	clearDebugStream();
	int index = 0;
	while(index< 14875){
	delay(res);//5 MS delay

	//Store Values For Accuracey
	byte C1 = vexRT[Ch1];
	byte C3 = vexRT[Ch3];
	byte C4 = vexRT[Ch4];
	userMove(C1, C3, C4);//Move with Values
	//Save Values
	auton[index]=C1;
	auton[index+1]=C3;
	auton[index+2]=C4;
	//CLAW
	byte raise;
	byte close;
	byte supp;
	if(vexRT[Btn5U] == 1){raiseClaw(120);raise=1;}
	else if(vexRT[Btn5D] == 1){ raiseClaw(-120);raise=2;}
	else {raiseClaw(0);raise=0;}
	if(vexRT[Btn6U] == 1){openClaw(120);close=1;}
	else if(vexRT[Btn6D] == 1){ openClaw(-120);close=2;}
	else {openClaw(0);close=0;}
	if(vexRT[Btn8U] == 1){support(120);supp=1;}
	else if(vexRT[Btn8D] == 1) {support(-120);supp=2;}
	else {support(0);supp= 0;}
	auton[index+3]=meshByte(raise, close,supp);
	index+=4;//Packet Increase
	}
}

void newPlayMap(){
	clearDebugStream();
	int index = 0;
	while(index< 14875){
	delay(res);//5 MS delay
	//REPLAY PACKET
	userMove(index);//TODO IF STATEMENT OF CONCAT
	byte raise = auton[index+3]>>4;
	byte open = auton[index+3]&15;
	byte supp = (auton[index+3]>>2)&3;
	if((raise)==2)raise=-120;else raise *= 120;
	
	if((open)==2)open=-120;else open *= 120;
	if((supp)==2)supp=-120;else supp *= 120;

	raiseClaw(raise);
	
	openClaw(open);
	support(supp);
	index+=4;//Packet Increase
	}
}

void print(){
	clearDebugStream();
	int index = 0;
	while(index< 14875){
	delay(7);//5 MS delay
	writeDebugStreamLine("%hi, %hi, %hi, %hi, ",auton[index],auton[index+1],auton[index+2],auton[index+4]);
	index+=4;//Packet Increase
	}
}

task autonomous()
{
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	while(true){
	if(vexRT[Btn7R] ==1){
	newMap();
	motor[fRight] = 0;
	motor[bRight] =  0;
	motor[fLeft] = 0;
	motor[bLeft] =  0;
	raiseClaw(0);
	openClaw(0);
	support(0);
	delay(5000);
	}
	if(vexRT[Btn7L] == 1){
	newPlayMap();
	}
	if(vexRT[Btn7D] == 1){
		print();
	}

  	userMove();

	if(vexRT[Btn5U] == 1)raiseClaw(120);
	else if(vexRT[Btn5D] == 1) raiseClaw(-120);
	else raiseClaw(0);

	if(vexRT[Btn6U] == 1)openClaw(110);
	else if(vexRT[Btn6D] == 1) openClaw(-110);
	else openClaw(0);

	if(vexRT[Btn8U] == 1)support(110);
	else if(vexRT[Btn8D] == 1) support(-110);
	else support(0);

	}
}
