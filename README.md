[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2TmiRqwI)
# final-project-skeleton

    * Team Name: iBuildSpeed
    * Team Members: Ahmed Abdellah, Ayman Tewfik
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
- 
### 6. MVP Demo

* IR emittor and detector circuit complete
* Speed communication between ATMega328PB and VESC
  
### 7. Final Demo

What do you expect to achieve by the final demonstration or after milestone 1?

### 8. Methodology

What is your approach to the problem?

### 9. Components

What major components do you need and why?

### 10. Evaluation

What is your metric for evaluating how well your product/solution solves the problem? Think critically on this section. Having a boolean metric such as “it works” is not very useful. This is akin to making a speaker and if it emits sound, albeit however terrible and ear wrenching, declare this a success.
It is recommended that your project be something that you can take pride in. Oftentimes in interviews, you will be asked to talk about projects you have worked on.

### 11. Timeline

This section is to help guide your progress over the next few weeks. Feel free to adjust and edit the table below to something that would be useful to you. Really think about what you want to accomplish by the first milestone.

| **Week**            | **Task** | **Assigned To**    |
|----------           |--------- |------------------- |
| Week 1: 3/24 - 3/31 |          |                    |
| Week 2: 4/1 - 4/7   |          |                    |
| Week 3: 4/8 - 4/14  |          |                    |
| Week 4: 4/15 - 4/21 |          |                    |
| Week 5: 4/22 - 4/26 |          |                    |

### 12. Proposal Presentation

Add your slides to the Final Project Proposal slide deck in the Google Drive.

## Final Project Report

Don't forget to make the GitHub pages public website!
If you’ve never made a Github pages website before, you can follow this webpage (though, substitute your final project repository for the Github username one in the quickstart guide):  <https://docs.github.com/en/pages/quickstart>

### 1. Video

[Insert final project video here]

### 2. Images

[Insert final project images here]

### 3. Results

What were your results? Namely, what was the final solution/design to your problem?

#### 3.1 Software Requirements Specification (SRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected software requirements. You should be quantifying this, using measurement tools to collect data.

#### 3.2 Hardware Requirements Specification (HRS) Results

Based on your quantified system performance, comment on how you achieved or fell short of your expected hardware requirements. You should be quantifying this, using measurement tools to collect data.

### 4. Conclusion

Reflect on your project. Some questions to consider: What did you learn from it? What went well? What accomplishments are you proud of? What did you learn/gain from this experience? Did you have to change your approach? What could have been done differently? Did you encounter obstacles that you didn’t anticipate? What could be a next step for this project?

## References

Fill in your references here as you work on your proposal and final submission. Describe any libraries used here.

## Github Repo Submission Resources

You can remove this section if you don't need these references.

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
