[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# final-project-skeleton

    * Team Name: iBuildSpeed
    * Team Members: Ahmed Abdellah, Ayman Tewfik, Andrew Katz
    * Github Repository URL: https://github.com/ese3500/final-project-ibuildspeed
    * Github Pages Website URL: https://ese3500.github.io/final-project-ibuildspeed/
    * Description of hardware: (embedded hardware, laptop, etc) embedded hardware

## Final Project Proposal

### 1. Abstract

iBuildSpeed is building a completely hands-free electric skateboard. Featuring a modern BLDC and VESC, the team's task mainly involves creating a hands-free control system and integrating peripherals. 
The control system involves desigining an analog acceleration and deceleration pedal, whilst the peripherals include automatic headlights, LCD info display, and crash detection. 

### 2. Motivation

When it comes to micromobility, you essentially have two options: an escooter or a electric skateboard with a bluetooth controller. Either way, you're actively using your hands to control the device-- meaning they can't do other more important things. If you rely on micromobility for your daily travel, chances are you need to be able to carry groceries, or access google maps efficiently while on the go (safely of course). Current solutions don't allow for this, which is where we come in. Bluetooth controllers offer no safety benefit when it comes to steering, and if we can control our car's speed with our feet, why not a skateboard? 

### 3. Goals

1) Configure BLDC motors
2) Achieve communication between ATMega328PB and Dual FSESC4.20 100A VESC
3) Develop Robust IR Emitter / Detector Circuit
4) Convert IR Emittor / Sensor values into VESC control setting (PWM)
5) Design Hardware for pedals
6) Enable force sensors for extra safety
7) Develop Auto-detecting Headlights
8) Power supply maangement
9) Develop collision-detection emergency braking using ultrasonic sensor
10) Sleek casework 

### 4. Software Requirements Specification (SRS)
- Pulse generation for IR Emittor
- ADC for IR Sensor
- SPI / UART Communication with VESC
- ADC for Force Sensor
- Timer input capture for Ultrasonic
- Interrupts for crash detection
- Graphics code for displaying data 
  
### 5. Hardware Requirements Specification (HRS)
- Dual BLDC motor setup
- Longboard
- 12s3p LiPo
- Ultrasonic Sensor
- IR emittor and IR transistor
- ATMega 328PB
- Dual FSESC4.20 100A VESC
- Battery protection casework
- Electronic protection caseowork
- Buck converter
- LCD screen 

### 6. MVP Demo

- IR emittor and detector circuit complete
- Force sensors configured 
- Speed communication between ATMega328PB and VESC
- Crash detection system completed
- Battery critical warning sytem completed
- Automatic Headlights completted
  
### 7. Final Demo
- Casework for pedals
- Casework for electronics & LiPo
- Threadlocking mechancial components
- RTOS scheduler
- LCD stats display 
  
Overall, we expect to have the basic controls system polished with peripherals being completed depending on time restrictions. 

### 8. Methodology

Our approach is to first do as much research as we can on BLDC motor control and the VESC Architecure. Then, we will draw out a systems diagram mapping out everything we need and how they will communicate. After that, we will designate pins on the ATMega328PB. From this point on, we can define the pins in the software so we can extract away our progress. We then plan on building in parallel, making it easy to integrate our segments of the project. The major focus will be on the acceleration and deceleration pads, but after we finish that we can being working on less critical peripherals (auto-headlights, 

### 9. Components

What major components do you need and why?

#### Already have: 
- BLDC motors for driving the electric skateboard
- LiPo to provide power to the motors and electronics system
- Belt drive system to connect the motors to the whells of the skateboard
- Dual VESC for controlling the BLDC motors 

#### Need to purchase: 
- Force sensors to enact a layer of safety. We want the speed to increase ONLY if both the force sensors and IR emitters are giving non 0 values.
- Powerful Dimmable Headlights (PWM?). We want headlights that automatically turn on during nighttime to improve rider visibility.  
- LCD to display critical information such as speed, battery percentage, and internal temperature
- High quality ultrasonic sensor to robustly determine the distance of nearby objects 
  
### 10. Evaluation

What is your metric for evaluating how well your product/solution solves the problem? Think critically on this section. Having a boolean metric such as “it works” is not very useful. This is akin to making a speaker and if it emits sound, albeit however terrible and ear wrenching, declare this a success.
It is recommended that your project be something that you can take pride in. Oftentimes in interviews, you will be asked to talk about projects you have worked on.

The major evaluation metric for this project will be the throttle error rate. The throttle error rate is the percentage of times out a fixed X trials that the skateboard incorrectly accelerates or decelerates during the following conditions: displacement & force, displacement & no force, no displacement & force, no displacement & no force. Each of these 4 metrics will have their own error rates, as well as a seperate one for accleration and deceleration. Therefore, we will have a total of 8 error rates: 
- E_adf = error rate during acceleration testing with both displacement & force present
- E_ad = error rate during acceleration testing with only displacement present
- E_af = error rate during acceleration testing with only force present
- E_ddf = error rate during decceleration testing with both displacement & force present
- E_dd = error rate during decceleration testing with only displacement present
- E_df = error rate during decceleration testing with only force present 

The goal is to have each of these error rates below 5%. 


### 11. Timeline

This section is to help guide your progress over the next few weeks. Feel free to adjust and edit the table below to something that would be useful to you. Really think about what you want to accomplish by the first milestone.

| **Week**            | **Task** | **Assigned To** |
|---------------------|----------|-----------------|
| **Week 1: 3/24 - 3/31** | 1. Research VESC Architecture <br>2. Communicate a simple message between AtMega328PB and VESC<br>3. Read IR emitter and sensor docs<br>4. Design a simple circuit to pulse IR at the proper frequency according to docs so emitter receives voltage<br>5. Plot current as a function of distance<br>6. Design code architecture| (1-2) Ahmed<br> (3-4)Ayman<br>(5-6) Both |
| **Week 2: 4/1 - 4/7**   | 1. Map emitter to speed values <br> 2. Convert emitter to I2C message <br> 3. Configure Force Sensors <br> 4. Write Software for mandatin force & displaceent | (1-2) Ahmed <br> (3-4) Ayman |
| **Week 3: 4/8 - 4/14**  | 1. Finish IR to VESC messaging <br> 2. Configure Ultrasonic Sensor Software for crash detection  | Ahmed & Ayman |
| **Week 4: 4/15 - 4/21** | 1. Finish Ultrasonic emergency braking <br> 2. Configure ADC for automatic headlights <br>  3. Implement RTOS scheduler  | (1 & 3) Ahmed <br> (2) Ayman |
| **Week 5: 4/22 - 4/26** | 1. LCD Graphics <br> 2. Finalzie casework  <3> 3. Perfboard migrations| (1) Ahmed & Ayman <br> (2) Ahmed & Ayman (3) Ahmed|

### 12. Proposal Presentation

Add your slides to the Final Project Proposal slide deck in the Google Drive.5

## Final Project Report

### 1. Video

[Demoing electric skateboard using I2C pressure sensors](https://drive.google.com/file/d/1Hnqc6SHLUXZd8Aw96VgkGABT7wk5KBnw/view?usp=sharing)<br>
[Showing how skateboard worked with lights/pressure sensor](https://drive.google.com/file/d/1IuB5yCILuj6FcOUCSRd2ZlDpXLcBj3dS/view?usp=sharing) <br>
[Demoing collision detection](https://drive.google.com/file/d/1hczSDGDwY4ylqr7qDrfUw2X2F34fmRHp/view?usp=sharing)

### 2. Images
![Original Vison](https://github.com/ese3500/final-project-ibuildspeed/assets/68669398/699e8d12-8ab5-4d23-8291-020dab630f18)
![Bottom of skateboard](https://github.com/ese3500/final-project-ibuildspeed/assets/68669398/472f3fc9-06fc-4a26-bac3-7e4f0c4068cf)
![Top of skateboard](https://github.com/ese3500/final-project-ibuildspeed/assets/68669398/b0b9893d-093c-4a9a-874c-450f50e6fd87)
### 3. Results
What were your results? Namely, what was the final solution/design to your problem?

We were able to create a fully hands-free electric skateboard through the use of pressure pads and an I2C pressure sensor. The skateboard has headlights and brake lights for safety purposes as well as an ultrasonic collision detection system. The final product is not reliably rideable, as there needs to be tuning to the acceleration and braking curves. 

#### 3.1 Software Requirements Specification (SRS) Results

3.1 Overview

The software component of the project is designed to manage the control systems of an electric skateboard, integrating various sensors and actuators to enhance functionality and safety.

3.2 Users

The primary users of this system are individuals using the electric skateboard for commuting and recreational purposes.

3.3 Definitions, Abbreviations

ADC: Analog-to-Digital Converter<br>
PWM: Pulse Width Modulation<br>
I2C: Inter-Integrated Circuit<br>
VESC: Vedder Electronic Speed Controller<br>
RTOS: Real-Time Operating System<br>
3.4 Functionality

SRS 01: The ultrasonic collision detection system shall use interrupts and input capture techniques to measure the distance to an object. When the distance is less than the predefined threshold, the system shall initiate a hard brake.
SRS 02: The system shall control the headlight brightness using a PWM signal that adjusts based on the ambient light levels detected by a photoresistor. The headlights shall be off in bright light, dim at dusk, and fully bright at night.
SRS 03: The software shall manage I2C communication with differential pressure sensors for controlling the skateboard's speed. The system shall support multi-master configuration to handle sensors with the same address on dual I2C buses.

The I2C utilizes differential pressure sensors that share the same address. To support this, we leverage both I2C buses on the ATMega328PB and alternatively send start conditions followed by two read conditions: one with ACK and the second one with NACK to obtain 2 bytes of pressure sensor readings and then terminate the communication. The pressure sensors ranged in values from 255 to 16500 and we used a linear acceleration and logistic decay braking function in speedcontroller.c file (see pressure_speed branch). These functions map pressure sensor readings to duty cycle values based on the desired sensitivity. 

The duty cycle value had to be compatible with the open source VESC project PPM signal. To do this, we found that a frequency of 50-70Hz with various duty cycles can emulate a typical RC controller. We found that 61Hz worked without having to modify our system clock. We used the VESC tool to view our mappings and make adjustments along the way. 

We fell short of integrating RTOS scheduling due to integration challenges.
Headlights and VESC were controlled via PWM

#### 3.2 Hardware Requirements Specification (HRS) Results
4.1 Overview

This project involves designing and assembling the electronic hardware necessary to control an electric skateboard, focusing on the motor, lighting, and sensor interfaces.

4.2 Definitions, Abbreviations

GPIO: General-Purpose Input/Output
MOSFET: Metal-Oxide-Semiconductor Field-Effect Transistor

4.3 Functionality

HRS 01: The skateboard shall incorporate an ATmega328PB microcontroller to manage all onboard hardware interactions.
HRS 02: An ultrasonic sensor shall be used for obstacle detection, capable of detecting obstacles up to 200 cm away.
HRS 03: A 12x6 cm LCD display shall be utilized for the user interface. The display shall connect to the microcontroller via the I2C bus.
HRS 04: A linear voltage regulator shall step down the PWM signal to 3.3V to match the input requirements of the VESC motor driver.
HRS 05: A current-limiting MOSFET shall be implemented to restrict the GPIO output current to 20mA to prevent damage to the microcontroller when driving the headlights and brake lights.

The speed of the skateboard ranges from 0mph - 30mph. The current limiting MOSFET prevents the headlights/brake lights from drawing too much current from the GPIO pin. The limit of the output current from any GPIO pin is 20mA, but the LEDs from the headlights/brake lights draw 74mA. We also had a 12s3p battery casework that successfully protected ourselves and our environment from any damage. The pressure pedals required tube adaptations in order to fit our pressure sensor modules.  

We fell short of our expected hardware requirements, mostly because integrating all moving parts resulted in errors. We were also unable to achieve dual-motor control as a result of frying the dual vesc. We also fell short of obtaining practical speed measurements and thus can only report theoretical. 


### 4. Conclusion

Reflect on your project. Some questions to consider: What did you learn from it? What went well? What accomplishments are you proud of? What did you learn/gain from this experience? Did you have to change your approach? What could have been done differently? Did you encounter obstacles that you didn’t anticipate? What could be a next step for this project?

This project allowed us to struggle a lot, and in turn-- learn a lot. Learning about VESC architecture and reading through complicated specifications gave us a glimpse into the complicated world of BLDC motor control. We learned how to analyze the open source documentation and schematics to understand the differences between constant torque, duty cycle, and PWM. We also learned how the VESC handles power management-- controlling motors with the 50V battery input whilst completing computations at a 3.3V level. Obtaining successful communication with the VESC took much longer than anticipated, but resulted in newfound knowledge across several domains. We also learned how to practically implement I2C for the pressure sensor and how to use the logic-level analyzer. 

Even though everything works on its own, when everything is put together it suffered from glithces and non-deterministic behavior.  Throughout the course of the project, we made many changes to our design. Originally, the plan was to use an optics-based controlle to determine the speed of the motor. This was done by having a small enclosure and depending on how much the enclosure is stepped on, the closer the IR lights get which would then output a higher voltage. After two weeks of testing and debugging, we decided to research alternative measures and switched to a air pedal and pressure sensor to determine what the speed of the skateboard should be. There were many obstacles that we encountered. Some of these obstacles include the integration of I2C sensors breaking the whole system as well as the unpredictable behavior of the ultrasonic collision detection and delayed parts. 

The next step of this project would be to use a different form of collision detection. Either use the Time of Flight sensor for this since it has a larger range and this would allow us to have a braking curve so that it is not a hard stop, or use LIDAR-LITE (V3 or V4) depending on testing results. We also plan on integrating load cells in order to stop the skateboard whenever there is no weight (person standing) on it. 

Casework will need multiple additional rounds of design, due to the amount of flex in the board, the lack of water proofing, and the unusual profile of the board. This would also allow better cable management, wiring, and a more robust way of connecting the electronics.

## References

[VESC Docs](https://vesc-project.com/documentation)
[EV braking] (https://www.researchgate.net/figure/braking-force-distribution-curve-of-an-EVs_fig3_290628276)

<!--## Github Repo Submission Resources

You can remove this section if you don't need these references. 

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
-->
