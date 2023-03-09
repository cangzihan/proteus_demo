# LCD Display

Display string through 2×16 LCD(Standard 1602 display) by AT89C52.

## Pin connection
LCD2
| Name | Connect | Function |
| :-----: | :-----: | :-----: |
| VSS | GND | Power - |
| VDD | 5V | Power + |
| VEE | Voltage input(0-5V) | LCD bias voltage |
| LCD_RS | C52-P2.3 | Data/command |
| LCD_RW | C52-P2.4 | Read/write |
| LCD_E | C52-P2.5 | Enable signal |
| D0 - D7 | C52-P0 | Data bit |

## More information
Tutorial for LCD1602:
https://www.bilibili.com/video/BV1tG4y1L7Um
