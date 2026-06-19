# SpectrumAnalyzer_STM32

Bare metal spectrum analyzer implemented on STM32F446xx microcontroller family. Developed using pure C and CMSIS registers without HAL(Hardware Abstraction Layer) for maximum efficiency and low level control.

Physically implemented on a NUCLEO-F446RE board, which uses CORTEX-M4 microcontroller.

Building done via a custom GNU Makefile that is lightweight and extension independent on top of compilation toolchain being streamlined. Compiler used is 

```text
arm-none-eabi-gcc (std=gnu2x)
```

## Tools required

1. **Make**
2. **gcc-arm-embedded**

For installation of both use [Chocolatey](https://chocolatey.org/) (if youre on windows)

To install **Choco** open powershell as Administrator and paste in this command

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

Then in that same powershell window type in:

```cmd
choco install gcc-arm-embedded
```

After installing gcc install Make by pasting in this command:

```cmd
choco install make
```

If you couldn't install **Chocolately** check out this [site](https://chocolatey.org/install).

## How to

To build a program open a new terminal in a workfolder and type in:

```cmd
make
```

After that go to ./Build and copy **SpectrumAnalyzer.bin**, paste the file into the board memory(in file explorer).

## Development Log

Done:

* [x] Delay
* [x] Makefile
* [x] UART TX

To do:

* [ ] UART RX
* [ ] I2S
* [ ] DMA
* [ ] FFT (gonna use RFFT, cause signals are real)
* [ ] I2C / SPI (possibly)
* [ ] Wi-Fi connection(via external ESP32)
* [ ] Python server(for data visualization)

## Development Timeline

June 16th: Installed stmcube vscode extension, created environment and got it working
June 17th: Wrote simple delay and built-in LED blinking program, no HAL - pure C with CMSIS, first struggles with bloated file structure of stmcube extension
June 18th: Wrote UART transmission library and grew tired of stmbcube vscode extension
June 19th: Successfully migrated from stmcube extension to a custom makefile, cleared up remains of the stm generated files and made the repo as well as the code nice and tidy
