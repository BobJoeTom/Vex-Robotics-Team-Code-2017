#pragma config(Motor,  port1, null,     tmotorNormal, openLoop)
#pragma config(Motor,  port2, null,     tmotorNormal, openLoop)
#pragma config(Motor,  port3, null,     tmotorNormal, openLoop)
#pragma config(Motor,  port4, null,      tmotorNormal, openLoop)
#pragma config(Motor,  port5, null,    tmotorNormal, openLoop)
#pragma config(Motor,  port6, null,		tmotorNormal, openLoop)
#pragma config(Motor,  port7, null,   tmotorNormal, openLoop)
#pragma config(Motor,  port8, null, tmotorNormal, openLoop)

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        TODO
					Sensor
					Straifing
					autonomous
					Step down function on raiseClawa
/*                                                                           */
/*---------------------------------------------------------------------------*/


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
/*                          Utility Methods						                       */
/*---------------------------------------------------------------------------*/
/*
							Field
y	¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦
	¦															 ¦
	¦															 ¦
	¦															 ¦
	¦															 ¦
	¦															 ¦
	¦															 ¦
	¦															 ¦
	¦															 ¦
0	+------------------------------+
	0															x
Dimensions are in centimeteres and also INPUTS
*/
//Sensor Port Names
int xLS = 6;
int yLS = 4;
int yRS = 2;

void userMove()
{
		/*motor[port4] = (vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4])/2;
		motor[port6] =  (vexRT[Ch3] - vexRT[Ch1] + vexRT[Ch4])/2;
		motor[port2] = (vexRT[Ch3] + vexRT[Ch1] + vexRT[Ch4])/2;
		motor[port8] =  (vexRT[Ch3] + vexRT[Ch1] - vexRT[Ch4])/2;
		*/
		motor[port4] = (vexRT[Ch1] - vexRT[Ch3] + vexRT[Ch4])/1.5;
		motor[port6] =  (vexRT[Ch1] - vexRT[Ch3] - vexRT[Ch4])/1.5;
		motor[port2] = (vexRT[Ch1] + vexRT[Ch3] + vexRT[Ch4])/1.5;
		motor[port8] =  (vexRT[Ch1] + vexRT[Ch3] - vexRT[Ch4])/1.5;
}

void raiseClaw(float speed)
{
			motor[port1] = speed;
			motor[port3] = -speed;
			motor[port7] = speed;
			motor[port10] = speed;
}

void openClaw(float speed){
			motor[port5] = speed;
			motor[port9] = speed;
}

void moveX(int speed){
		//Spped greater than 0 moves right, less than 0 moves left
		motor[port4] = (speed);
		motor[port6] =  -(speed);
		motor[port2] = (speed);
		motor[port8] =  - (speed);

}
void moveY(int speed){
	//Speed greater than 0 moves forward, less than 0 moves backwards
		motor[port4] = -(speed);
		motor[port6] =  -(speed);
		motor[port2] = (speed);
		motor[port8] =  (speed);
}


void moveXY(int xSpeed, int ySpeed){

		motor[port4] = (vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4])/1.5;
		motor[port6] =  (vexRT[Ch3] - vexRT[Ch1] + vexRT[Ch4])/1.5;
		motor[port2] = (vexRT[Ch3] + vexRT[Ch1] + vexRT[Ch4])/1.5;
		motor[port8] =  (vexRT[Ch3] + vexRT[Ch1] - vexRT[Ch4])/1.5;
}

void moveToX(float xDisp){//Move the bot to the niputed x displacement
	bool running = true;
	while(running){
		int currDisp = SensorValue(xLS);
		if(abs(SensorValue(xLS)- xDisp) <= 1)running = false;
		else if(currDisp > xDisp){
				moveX(-127);
		}else	if(currDisp < xDisp){
				moveX(127);
		}
	}
}

void moveToY(float yDisp){//Move the bot to the niputed y displacement
	bool running = true;
	while(running){
		int currDisp =SensorValue(yLS);
		if(abs(SensorValue(yLS)- yDisp) <= 1)running = false;
		else if(currDisp > yDisp){
				moveX(-127);
		}else	if(currDisp < yDisp){
				moveX(127);
		}
	}
}

void moveDispX(float xDisp){//Takes in the amount of x displaced, will displace the current x displacement by amound inputted, forexample x currently
									//at 70 from the leftinput(30) will move 70 to the right
	float beginX = SensorValue(xLS);
	float targetX = beginX + xDisp;
	moveToX(targetX);
}

void moveDispY(float yDisp){//Takes in the amount of y displaced, will displace the current y displacement by amound inputted, forexample y currently
											//at 30 from the bottom input(70) will move 70 up
	float beginY = SensorValue(yLS);
	float targetY = beginY + yDisp;
	moveToY(targetY);
}

/*void moveToXY(int xDisp, int yDisp){//Will displace both x and y at the same time
	bool running = true;
	int beginX = SONAR SENSOR XVALUE;
	int targetX = beginX + xDisp;
	int beginY = SONAR SENSOR yVALUE;
	int targetX = beginY + yDisp;
	while(running){
		//TODO move(left or right) in which way to achieve target value
		if(current XvaluSoNAR - targetX <= 0&&current XvaluSoNAR - targetY <= 0)running = false;
	}
}
*/
/*
void moveToXY(int xDisp, int yDisp){//Will move to both xDisp and yDisp at the same time
	bool running = true;

	while(running){
		//TODO move(left or right) in which way to achieve target value
		if(current XvaluSoNAR - xDisp <= 0&&current XvaluSoNAR - yDisp <= 0)running = false;
	}
}
*/

void rotate(int deg){//Deg for degrees
		if(deg>0){//Rotate Right
			motor[port4] = (vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4])/1.5;
			motor[port6] =  (vexRT[Ch3] - vexRT[Ch1] + vexRT[Ch4])/1.5;
			motor[port2] = (vexRT[Ch3] + vexRT[Ch1] + vexRT[Ch4])/1.5;
			motor[port8] =  (vexRT[Ch3] + vexRT[Ch1] - vexRT[Ch4])/1.5;

		}else if(deg<0){//Rotate Left
			motor[port4] = (vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4])/1.5;
			motor[port6] =  (vexRT[Ch3] - vexRT[Ch1] + vexRT[Ch4])/1.5;
			motor[port2] = (vexRT[Ch3] + vexRT[Ch1] + vexRT[Ch4])/1.5;
			motor[port8] =  (vexRT[Ch3] + vexRT[Ch1] - vexRT[Ch4])/1.5;
		}
}
void align(){//Create a triangle to align the bot with rotate to have it perpendicular to the walls
	float	yLeft= SensorValue(yLS);
	float yRight= SensorValue(yRS);
	bool running = true;
	while (running){
		if(abs(yLeft - yRight)<= 1){
			running = false;
		}else if(yLeft<yRight){
			rotate(-1);
		}else if(yLeft>yRight){
			rotate(1);
		}
	}
}



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

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

task autonomous()
{
	raiseClaw(120);
	moveY(127);
	openClaw(127);
	sleep(2500);
	raiseClaw(0);
	moveY(0);
	openClaw(0);
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
  // User control code here, inside the loop

  while (true)
  {
  	userMove();

		if(vexRT[Btn5U] == 1)raiseClaw(120);
		else if(vexRT[Btn5D] == 1) raiseClaw(-120);
		else raiseClaw(0);

		if(vexRT[Btn6U] == 1)openClaw(63);
		else if(vexRT[Btn6D] == 1) openClaw(-63);
		else openClaw(0);
  }
}
