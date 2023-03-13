# DC Motor Demo

DC motors and some available drive circuits in proteus (without CPU). The driver circuit uses dual H-bridge configuration chips to control the motor speed and direction. The simulation settings are configured to generate a DC input voltage and vary the motor speed and direction using the switches.

## Pin connection
TB6612FNG module logic control table
| AIN1/BIN1 | AIN2/BIN2 | PWMA/PWMB | AO1/AO2 |
| :-----: | :-----: | :-----: | :-----: |
| 1 | 0 | 1 | Forward |
| 0 | 1 | 1 | Reverse |
| 1 | 1 | 1 | Stop🚫 |
| 0 | 0 | 1 | Stop🚫 |
| X | X | 0 | Stop🚫 |

## Usage
To use these circuits, you will need to have Proteus simulation software installed on your computer. Open the project files `.pdsprj` to access the circuit diagrams and simulation settings. You can modify the circuit parameters to generate different input voltages, motor speeds, and directions.
