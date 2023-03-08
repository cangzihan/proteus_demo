# A/D conversion using PCF8591

AT89C52 sends and receives data with PCF8591 through I2C protocol, and displays digital quantity through 4×16 LCD.

## Pin connection
PCF8591
| Name | Connect | Function |
| :-----: | :-----: | :-----: |
| AIN0 | Input signal | A/D Channel 1 |
| AIN1 | NC | A/D Channel 2 |
| AIN2 | NC | A/D Channel 3 |
| AIN3 | NC | A/D Channel 4 |
| A0 | GND | Address bit |
| A1 | GND | Address bit |
| A2 | GND | Address bit |
| AGND | GND | Analog signal ground |
| VREF | 5V | D/A conversion reference voltage |
| SCL | C52-P2.1 | I2C Clock(I2C2) |
| SDA | C52-P2.0 | I2C Data(I2C2) |

LCD4
| Name | Connect | Function |
| :-----: | :-----: | :-----: |
| VSS | GND | Power - |
| VDD | 5V | Power + |
| VEE | Voltage input(0-5V) | LCD bias voltage |
| LCD_RS | C52-P2.3 | Data/command |
| LCD_RW | C52-P2.4 | Read/write |
| LCD_E | C52-P2.5 | Enable signal |
| D0 - D7 | C52-P0 | Data bit |
