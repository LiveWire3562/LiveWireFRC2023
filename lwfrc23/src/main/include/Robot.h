// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

// add XBOX controller
#include <frc/XboxController.h>

// add Differential Drive
#include <frc/drive/DifferentialDrive.h>

// add motor controls
#include <frc/motorcontrol/PWMSparkMax.h>

// add motor control group
#include <frc/motorcontrol/MotorControllerGroup.h>

class Robot : public frc::TimedRobot {
 public:
  
  // xbox controllor
  frc::XboxController m_driverController{0};

  // assign drive motors
  frc::PWMSparkMax m_rightFront{0};
  frc::PWMSparkMax m_rightRear{2};
  frc::PWMSparkMax m_leftFront{1};
  frc::PWMSparkMax m_leftRear{3};

  // create left and right motor groups
  frc::MotorControllerGroup rightDriveMotor{m_rightFront, m_rightRear};
  frc::MotorControllerGroup leftDriveMotor{m_leftFront, m_leftRear};

  // add arm motor
  frc::PWMSparkMax m_frontArm{4};

  // create drivetrain
  frc::DifferentialDrive m_robotDrive{leftDriveMotor, rightDriveMotor};


  void RobotInit() override{
    // invert motor on side - may need changed to other side
    // this keeps forward onpositive voltages only
    rightDriveMotor.SetInverted(true);
  };

  // run items in any mode
  void RobotPeriodic() override;

  // Autonomous Runtime 
  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  // Teleop Runtime
  void TeleopInit() override;
  void TeleopPeriodic() override{
    // Drive - Tank Style
    m_robotDrive.TankDrive(-m_driverController.GetLeftY(), -m_driverController.GetRightY());
    
  };

  // Bot Disabled Runtime
  void DisabledInit() override;
  void DisabledPeriodic() override;

  // Bot Testing Runtime
  void TestInit() override;
  void TestPeriodic() override;

 //  Bot Sim Runtime
  void SimulationInit() override;
  void SimulationPeriodic() override;


 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};
