[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# final-project-skeleton

    * Team Name: iBuildSpeed
    * Team Members: Ahmed Abdellah, Ayman Tewfik, Andrew Katz
    * Github Repository URL: https://github.com/ese3500/final-project-ibuildspeed
    * Github Pages Website URL: [for final submission]
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

Don't forget to make the GitHub pages public website!
If you’ve never made a Github pages website before, you can follow this webpage (though, substitute your final project repository for the Github username one in the quickstart guide):  <https://docs.github.com/en/pages/quickstart>

### 1. Video

[Demoing electric skateboard using I2C pressure sensors](https://drive.google.com/file/d/1Hnqc6SHLUXZd8Aw96VgkGABT7wk5KBnw/view?usp=sharing)<br>
[Showing how skateboard worked with lights/pressure sensor](https://drive.google.com/file/d/1IuB5yCILuj6FcOUCSRd2ZlDpXLcBj3dS/view?usp=sharing) <br>
[Demoing collision detection](https://drive.google.com/file/d/1hczSDGDwY4ylqr7qDrfUw2X2F34fmRHp/view?usp=sharing)

### 2. Images
![Bottom of skateboard](https://github.com/ese3500/final-project-ibuildspeed/assets/68669398/472f3fc9-06fc-4a26-bac3-7e4f0c4068cf)
[Top of skateboard](https://drive.google.com/file/d/1r9hFO10wdhOQfwpBqguP-r_c5ASnazm1/view?usp=sharing)

### 3. Results
What were your results? Namely, what was the final solution/design to your problem?

We were able to create a fully hands-free electric skateboard through the use of pressure pads and an I2C pressure sensor. The skateboard has headlights and brake lights for safety purposes as well as an ultrasonic collision detection system.

#### 3.1 Software Requirements Specification (SRS) Results
Based on your quantified system performance, comment on how you achieved or fell short of your expected software requirements. You should be quantifying this, using measurement tools to collect data.

The software requirements we had included using interrupts for the ultrasonic collision detection system, creating PWM signals based on an ADC reading, and writing the read/write for the I2C pressure sensors.  
IR modulation and ADC was removed and the I2C pressure sensors were used instead. ADC was still used with the photocell to control headlights.

Headlights and VESC were controlled via PWM

#### 3.2 Hardware Requirements Specification (HRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected hardware requirements. You should be quantifying this, using measurement tools to collect data.

The hardware requirements that we had include using a linear voltage regulator, a belt drive motor that uses a brushless DC motor, and a current-limiting MOSFET in order to limit the current output of the GPIO and prevent it from damaging the ATMEGA. The linear voltage regulator was used to step down the motor driving PWM signal. This is because the motor driver (VESC) takes in a 3.3V input, but the output of the GPIO pin that controls the speed is a 5V signal. The belt drive motor is used in order to control the speed of the electric skateboard. The speed of the skateboard ranges from 0mph - 30mph. The current limiting MOSFET prevents the headlights/brake lights from drawing too much current from the GPIO pin. The limit of the output current from any GPIO pin is 20mA, but the LEDs from the headlights/brake lights draw 74mA.
### 4. Conclusion

Reflect on your project. Some questions to consider: What did you learn from it? What went well? What accomplishments are you proud of? What did you learn/gain from this experience? Did you have to change your approach? What could have been done differently? Did you encounter obstacles that you didn’t anticipate? What could be a next step for this project?

There were many things that we learned during this project. There are many issues when trying to integrate everything together. Even though everything works on its own, when everything is put together it might not completely work. We also learned how to practically implement I2C for the pressure sensor. There were changes that had to have been made to the initial design. Originally the plan was to use an optics to determine the speed of the motor. This was done by having a small enclosure and depending on how much the enclosure is stepped on, the closer the IR lights get which would then output a higher voltage. This did not seem to be practical and so we switched to a air pedal and pressure sensor to determine what the speed of the skateboard should be. There were many obstacles that we encountered. Some of these obstacles include the integration of I2C sensors breaking the whole system as well as the unpredictable behavior of the ultrasonic collision detection. The next step of this project would be to use a different form of collision detection. Either use the Time of Flight sensor for this since it has a larger range and this would allow us to have a braking curve so that it is not a hard stop, or use LIDAR-LITE (V3 or V4) depending on testing results.

Casework will need multiple additional rounds of design, due to the amount of flex in the board, the lack of water proofing, and the weird profile of the board. This would also allow better cable management, wiring, and a more robust way of connecting the electronics.

## References

Fill in your references here as you work on your proposal and final submission. Describe any libraries used here.

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
