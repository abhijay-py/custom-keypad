# custom-keypad
Utilized KiCAD and STM32Cube to design a customizable keypad with 6 keys and a volume knob. <br>
Powered by a STM32H7A3RGT6 microcontroller with Cherry MX Brown Switches and a knurled metal volume knob. <br>
Boasts a 6-key keypad pre-programmed with requested keys, with a custom black 3D printed case to enclose the PCB and improve the appearance and stabliity of the device. <br>
Used consumer and keypad hardware interface device reports to create a custom HID report that was able to send both media and regular keyboard commands to PCs. <br>
Created a decoder + EXTI interrupt system to properly debounce and evaluate transistions in the rotary encoder to effectively adjust volume corresponding to the end user's turning of the dial. <br>
