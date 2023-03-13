# DC Motor Demo

DC motors and some available drive circuits in proteus (without CPU).

## Pin connection
TB6612FNG module logic control table
| AIN1/BIN1 | AIN2/BIN2 | PWMA/PWMB | AO1/AO2 |
| :-----: | :-----: | :-----: | :-----: |
| 1 | 0 | 1 | Forward |
| 0 | 1 | 1 | Reverse |
| 1 | 1 | 1 | Stop🚫 |
| 0 | 0 | 1 | Stop🚫 |
| X | X | 0 | Stop🚫 |
