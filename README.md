# IR_Servo_serial_control
IR-Receive and Servo shield for Arduino Pro Mini  
https://thousandiy.wordpress.com/2017/05/28/arduino-pro-mini-servo-shield/

## IR receive and Servo Control demo  
baudrate: 115200  
1.Output received IR code to Serial port  
2.Control servo angle from serial port  
- {CH}_{Command}  
    - CH: Servo No. (1-6)  
    - Command:  
        - at: attach servo  
        - dt: detach servo  
        - 000-180: servo angle (need 3 digit)  
    - Finally the terminal character ";" is needed.
