# Project Title

Safe-deposit Box Security Using Google Assistant as an Advanced Authentication System


## Overview

The "Safe-deposit Box Security Using Google Assistant" project demonstrates a comprehensive security solution that combines RFID authentication and Google Assistant voice commands for advanced access control. By integrating these two authentication methods, the project ensures robust security for accessing a safe-deposit box. 
The heart of the project lies in an Arduino microcontroller, which orchestrates the interactions between an RFID module, a relay shield, Blynk platform, and Google Assistant through IFTTT integration. The relay shield is employed for efficient power supply management, reducing clutter and improving the overall organization of components.
Upon successful integration, users can access the safe-deposit box using either RFID cards and Google Assistant voice commands Sequentially. The RFID authentication provides a traditional method for accessing the box, while the Google Assistant integration offers a more advanced and convenient method, enhancing the security features of the system.
With this project, you can explore the seamless integration of multiple authentication methods and create a secure environment for accessing your valuable possessions. The integration of both traditional and modern authentication methods ensures convenience without compromising on security.


## Table of Contents

- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Uploading Arduino Code](#uploading-arduino-code)
- [RFID Integration](#rfid-integration)
- [Google Assistant and IFTTT Integration](#google-assistant-and-ifttt-integration)
- [Testing](#testing)
- [Code Implementation](#code-implementation)
- [Project Flowchart](#project-flowchart)
- [Images](#images)
- [How to Use](#how-to-use)
- [Contributors](#contributors)


## Prerequisites

Before you begin, ensure you have met the following requirements:
- Arduino IDE installed on your computer.
- A compatible microcontroller (e.g., Arduino Uno).
- RFID module (e.g., MFRC522).
- Blynk account.
- IFTTT account.

## Hardware Setup

Follow these steps to set up the hardware components:
1. Utilize a relay shield [Circuit Diagram](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Circuit%20Diagram.jpg) equipped with a relay to enhance component organization and enable streamlined power supply distribution, using a single power source for all components.
2. Connect the [sensors, actuators, and other components](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Wiring%20Diagram.jpg) to your microcontroller according to the provided circuit diagram.

## Uploading Arduino Code

1. Open the Arduino IDE.
2. Open the [Safe-deposit Box Security Using Google Assistant as an Advanced Authentication System.ino](Project_2/Safe-deposit%20Box%20Security%20Using%20Google%20Assistant%20as%20an%20Advanced%20Authentication%20System.ino) file.
3. Select the appropriate board and port from the Tools menu.
4. Click the "Upload" button to upload the code to your microcontroller.

## RFID Integration

1. Integrate the RFID module into the hardware setup following the specifications in its datasheet.
2. By replacing the unique RFID code registered in the system, modify the code to incorporate RFID functionality

## Google Assistant, Blynk, and IFTTT Integration

For a seamless interaction between the project and Google Assistant, Blynk, and IFTTT, follow these steps:

1. **Blynk Integration**:
   - Begin by setting up a Blynk account and creating a new project.
   - Add a device to your Blynk project. You can use a predefined hardware model or create a custom template.
   - Configure Blynk datastreams to serve as triggers for specific actions. For example, create a datastream named "UnlockTrigger" to activate actions based on Google Assistant voice commands.
   - Configure the event to allow Push Notification Activation on blynk
   ![Blynk Device Template](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Blynk%20device.png)
   ![Blynk Datastream](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Datastream%20Blynk.png)
   ![Blynk Event](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Push%20Notification%20And%20Events%20.png)

2. **Code Implementation for Blynk**:
   - Modify the Arduino code [Safe-deposit Box Security Using Google Assistant as an Advanced Authentication System.ino](Project_2/Safe-deposit%20Box%20Security%20Using%20Google%20Assistant%20as%20an%20Advanced%20Authentication%20System.ino) to include the Blynk library and handle communication with Blynk.
   - Use your Blynk device template, including the Auth Token, to interact with Blynk. When the "UnlockTrigger" datastream is triggered, activate the appropriate action in your code to unlock the safe-deposit box.

3. **Google Assistant Voice Commands**:
   - Configure IFTTT applets using the Webhooks service to connect Google Assistant voice commands to Blynk actions.
   - Set up IFTTT applets to trigger when specific phrases are spoken to Google Assistant. For example, set a phrase like "Activate unlock sequence" to trigger a Webhooks GET request to your Blynk project, activating the "UnlockTrigger" datastream using the Blynk Auth Token as a parameter.

   ![IFTTT Applet](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/IFTTT%20Interface%20.jpg)

By combining Google Assistant, Blynk, and IFTTT, the project provides a two-step verification process for accessing the safe-deposit box. 
Users must first use RFID authentication and then activate certain actions through Google Assistant voice commands. 
This integration enhances security while maintaining user convenience. 

## Testing

1. Ensure the hardware components are connected correctly.
2. Test the RFID integration by using the appropriate RFID cards/tags for authentication.
3. Test the Google Assistant integration by using voice commands to trigger Blynk actions.

## Code Implementation

The Arduino code for this project can be found in the file [Safe-deposit Box Security Using Google Assistant as an Advanced Authentication System.ino](Project_2/Safe-deposit%20Box%20Security%20Using%20Google%20Assistant%20as%20an%20Advanced%20Authentication%20System.ino).

## Project Flowchart

![Project Flowchart](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Project%20Flowchart.jpeg)

The flowchart provides an overview of the authentication process, highlighting interactions between components.

## Images

- Safe-deposit Box Setup:
  ![Safe-deposit Box Setup](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Safe%20Deposit%20Box%20Full%20Project%20Pitcure.jpg)

- RFID Integration:
  ![RFID Integration](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/RFID%20Readings.png)

- Google Assistant Integration:
  ![Google Assistant Integration](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Google%20Assistant.jpg)
  ![Google Assistant Integration](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Google%20Assistant%202.jpg)
- Blynk Integration:
  ![Blynk Integration](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Blynk%20Push%20Notifications.jpg)
## How to Use

This project offers a sophisticated security system for a safe-deposit box, combining RFID and Google Assistant interactions that are intelligently linked through specific parameters. The system revolves around four distinct sequences of interaction:

1. **Successful RFID Authentication and Google Assistant Interaction**:
   - When RFID authentication succeeds, a push notification is triggered to prompt the user to authenticate using Google Assistant.
   - The user needs to provide a voice command to unlock the safe-deposit box, and a subsequent push notification confirms the successful unlock.

![Sequence 1](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Sequence%201.jpg)

2. **RFID Authentication Failure**:
   - If RFID authentication fails, the system will notify the user about the detection of failed attempts.
   - After three unsuccessful attempts, the RFID authentication will be blocked, accompanied by a push notification and an audible alarm on the safe-deposit box, alerting the owner.

![Sequence 2](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Sequence%202.jpg)

3. **Unlocking RFID Authentication Through Google Assistant**:
   - If the RFID authentication becomes blocked, users can reactivate it using Google Assistant.
   - The system sends a push notification to indicate that RFID authentication has been reactivated.

![Sequence 3](https://github.com/Ibnulfaiq/Embedded-Systems-Playground/blob/main/Project_2/Sequence%203.jpg)

4. **Resetting the System**:
   - When both RFID and Google Assistant authentications are active, the system includes a reset sequence that triggers after a specific time interval.
   - This sequence resets the system to its normal state before any authentication was attempted.

For detailed implementation, refer to the [Safe-deposit Box Security Using Google Assistant as an Advanced Authentication System.ino](Project_2/Safe-deposit%20Box%20Security%20Using%20Google%20Assistant%20as%20an%20Advanced%20Authentication%20System.ino) code and the [Project Flowchart](Project_2/Project%20Flowchart.jpeg) for a visual representation of the interaction flow.
This versatile security system not only combines RFID and Google Assistant authentication but also adapts to various scenarios to ensure the safety of your valuable items.


## Contributors

- Your Name [@Ibnulfaiq](https://github.com/Ibnulfaiq)

Contributions to this project are welcome. Feel free to open issues and submit pull requests to improve the project.

