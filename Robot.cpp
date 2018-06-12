/*-------------------------*/
/* candyBot2018            */
/* Created by: Casey Jones */
/* controls the robot      */
/*-------------------------*/

#include <iostream>
#include <string>
#include "WPILib.h"
#include <Joystick.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Drive/DifferentialDrive.h"
#include <PWMSpeedController.h>
//#include "DifferentialDrive.h"
#include <SpeedController.h>

class Robot : public frc::IterativeRobot {

private:
	frc::Joystick stick {0};

	DifferentialDrive *robotDrive;

	SpeedControllerGroup *driveMotorsLeft;
	SpeedControllerGroup *driveMotorsRight;

	Victor *driveMotorLeftSlave1;
	Victor *driveMotorLeftSlave2;

	Victor *driveMotorRightSlave1;
	Victor *driveMotorRightSlave2;

	double stickY;
	double stickZ;
	bool quickTurn;
public:

	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

		driveMotorLeftSlave1 = new Victor(1);
		driveMotorLeftSlave2 = new Victor(2);
		driveMotorsLeft = new SpeedControllerGroup(*driveMotorLeftSlave1, *driveMotorLeftSlave2);

		driveMotorRightSlave1 = new Victor(3);
		driveMotorRightSlave2 = new Victor(4);
		driveMotorsRight = new SpeedControllerGroup(*driveMotorRightSlave1, *driveMotorRightSlave2);

		robotDrive = new DifferentialDrive(*driveMotorsLeft, *driveMotorsRight);


	}

	void AutonomousInit() override {
		m_autoSelected = m_chooser.GetSelected();
		// m_autoSelected = SmartDashboard::GetString(
		// 		"Auto Selector", kAutoNameDefault);
		std::cout << "Auto selected: " << m_autoSelected << std::endl;

		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {}

	void TeleopPeriodic() {
		stickY = stick.GetRawAxis(1);
		stickZ = stick.GetRawAxis(2);
		quickTurn = stick.GetRawButton(3);

		robotDrive->CurvatureDrive(stickY, stickZ, quickTurn);
	}

	void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;
};

START_ROBOT_CLASS(Robot)
