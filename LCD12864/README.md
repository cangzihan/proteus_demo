# LCD Display

Display string through 128*64 pixels LCD by AT89C52.

- Support self-built fonts


## Pin connection
LCD12864
| Name | Connect | Function |
| :-----: | :-----: | :-----: |
| GND | GND | Power - |
| VCC | 5V | Power + |
| $\overline{ RST} $ | 5V | Reset |
| V0 | Voltage input(0-5V) | LCD bias voltage |
| LCD_RS | C52-P2.3 | Data/command |
| LCD_RW | C52-P2.4 | Read/write |
| LCD_E | C52-P2.5 | Enable signal |
| D0 - D7 | C52-P0 | Data bit |
| $\overline{ CS1}$ | C52-P1.0 | Chip select bit 1 |
| $\overline{ CS2}$ | C52-P1.1 | Chip select bit 2 |
