<!-- Please do not change this html logo with link -->

<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# CPU Interrupt Priorities Using the AVR64DD32 Microcontroller Generated with MCC Melody

This project shows the interrupt handling features of the AVR® CPU, highlighting the round robin feature and the high-priority (level 1) interrupt feature using the MCC Melody. Three interrupts will be enabled: capture interrupt for the Time/Counter Type 0 (TCB0), capture interrupt for the TCB1, and the receive interrupt for the Universal Synchronous and Asynchronous Receiver-Transmitter (USART). The capture interrupt is triggered each time the timer reaches the TOP value.

## Related Documentation

More details and code examples on the AVR64DD32 can be found at the following links:

- [AVR64DD32 Product Page](https://www.microchip.com/wwwproducts/en/AVR64DD32)
- [AVR64DD32 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=AVR64DD32)
- [AVR64DD32 Project Examples in START](https://start.atmel.com/#examples/AVR64DD32CuriosityNano)

## Software Used

- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) v6.00 or newer
- [MPLAB® XC8](http://www.microchip.com/mplab/compilers) v2.36 or newer
- [AVR-Dx Series Device Pack](https://packs.download.microchip.com/) v2.1.152 or newer
- [MPLAB® Code Configurator Melody](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator/melody) core 2.1.11 or newer

## Hardware Used

- The AVR64DD32 Curiosity Nano Development Board is used as a test platform.
  <br><img src="images/AVR64DD32.PNG" width="640">

## Operation

To program the Curiosity Nano board with this MPLAB® X project, follow the steps provided in the [How to Program the Curiosity Nano board](#how-to-the-program-curiosity-nano-board) chapter.<br><br>

## Setup

The following configurations must be made for this project:

- System clock is 4 MHz.
- TCB0
  - Compare value (CCMP) - 10 (2.75 us)
  - Timer: enabled
  - Capture interrupt: enabled
- TCB1
  - Compare value (CCMP) - 20 (5.25 us)
  - Timer: enabled
  - Capture interrupt: enabled
- USART0
  - Baud Rate: 115200
  - RX and TX: enabled
  - RX interrupt: enabled
  - PD4 (TX pin) configured as output, PD5 (RX pin) as input
- CPUINT
  - Round robin convention for interrupt priorities: enabled
  - Priority level 1 configured for USART0
- Global interrupts are enabled.

| Pin |       Configuration        |
| :-: | :------------------------: |
| PF5 |   LED0 - Digital Output    |
| PD4 | USART0 TX - Digital Output |
| PD5 | USART0 RX - Digital Input  |

## Demo

Using the RXC interrupt, when the TCB0/1 Interrupt Service Routine (ISR) is executed, the on-board LED will be turned ON/OFF, with a 1s delay. The USART0 RXC ISR implements an echo response - it transmits the received character through USART0.

The static scheduling may prevent some interrupt requests from being serviced, as they will always be serviced according to their vector number.
The vector numbers for TCB0, TCB1, and USART0 are provided below.

| Vector Number |     Peripheral Source     |
| :-----------: | :-----------------------: |
|      14       |      TCB0 - Capture       |
|      15       |      TCB1 - Capture       |
|      21       | USART0 - Receive Complete |

This means that, without the round robin enabled, only the interrupt with the lowest vector number will be serviced, as presented below.

<br><img src="images/round-robin-scheduling-without-rr.png" width="600">

To avoid this, the CPUINT offers the round robin scheduling for normal-priority (level 0) interrupts. In the round robin scheduling, a register is used to store the last acknowledged interrupt vector number. This register ensures that the last acknowledged interrupt vector gets the lowest priority, and is automatically updated by the hardware.

In this application, the round robin scheduling is enabled to service both of the TCB0 and TCB1 capture interrupts.

<br><img src="images/round-robin-scheduling-with-rr.png" width="600">

Additionally, the USART0 RXC interrupt is provided with a level 1 priority - this makes it able to interrupt any level 0 interrupt. This is needed in some cases in which other interrupt routines are complex. The user needs to make sure that one important interrupt is not postponed and that important data are not lost. The result is explained in the image below.

<br><img src="images/round-robin-scheduling-all-isrs.png" width="600">

Four test messages are transmitted through the USART0 to the microcontroller (MCU) and transmitted back by the MCU via echo. The messages are provided in the image below.

- USART0 Echo Messages - Terminal Window
  <br><img src="images/usart-echo.jpg" width="600">

The USART0 characters are correctly transmitted back by the MCU, and the LED is continuously turning ON and OFF.

The round robin feature is shown by the LED blinky sequence (both level 0 priority ISRs are executed). The USART0 RXC interrupt being assigned with a level 1 priority is shown by the fact that all characters are received and transmitted (there is no data loss).

<br><img src="images/demo.gif">

## Summary

This code example shows the usage of the CPU interrupt scheduling features - round robin and interrupt level 1 priority.

## How to the Program Curiosity Nano board

This chapter shows how to use the MPLAB® X IDE to program an AVR® device with an Example_Project.X. This can be applied for any other projects.

- Connect the board to the PC.

- Open the Example_Project.X project in MPLAB® X IDE.

- Set the Example_Project.X project as main project.

  - Right click the project in the **Projects** tab and click **Set as Main Project**.
    <br><img src="images/Program_Set_as_Main_Project.PNG" width="600">

- Clean and build the Example_Project.X project.

  - Right click the **Example_Project.X** project and select **Clean and Build**.
    <br><img src="images/Program_Clean_and_Build.PNG" width="600">

- Select **AVRxxxxx Curiosity Nano** in the Connected Hardware Tool section of the project settings:

  - Right click the project and click **Properties**.
  - Click the arrow under the Connected Hardware Tool.
  - Select **AVRxxxxx Curiosity Nano** (click the **SN**), click **Apply** and then **OK**.
    <br><img src="images/Program_Tool_Selection.PNG" width="600">

- Program the project to the board.
  - Right click the project and click **Make and Program Device**.
    <br><img src="images/Program_Make_and_Program_Device.PNG" width="600">

<br>

- [Back to Setup](#setup)
- [Back to Demo](#demo)
- [Back to Summary](#summary)
- [Back to top](#cpu-interrupt-priorities-using-the-avr64dd32-microcontroller-generated-with-mcc-melody)
