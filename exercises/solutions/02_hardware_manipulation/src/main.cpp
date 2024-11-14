// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Peripherals.h"
#include "Timer.h"
#include <cstdint>
#include <iostream>

// Base address for GPIO port D
constexpr uintptr_t GPIOD_BASE{0x40020C00u};

// Enum class for GPIO modes
enum class GPIO_Modes { input, output, alternate, analog };

// Pointers to GPIO registers
static volatile uint32_t *const GPIOD_moder{reinterpret_cast<uint32_t *>(GPIOD_BASE)};
static volatile uint32_t *const GPIOD_odr{reinterpret_cast<uint32_t *>(GPIOD_BASE + 0x14u)};
static volatile const uint32_t *const GPIOD_idr{reinterpret_cast<uint32_t *>(GPIOD_BASE + 0x10u)};

// Enum class for LED pins
enum class LEDPin { D6 = 8, D5, D4, D3 };

// Enum class for motor control pins
enum class MotorPin { on = 12, dir };

// Enum class for seven-segment display pins
enum class SevenSegmentPin { A = 8, B, C, D };

int main(void) 
{
  // Enable GPIO port D
  STM32F407::enable(STM32F407::AHB1_Device::GPIO_D);

  // Configure the mode of the GPIO pin for LED D6 to output
  auto moder = *GPIOD_moder;
  moder &= ~(0b11U << (int(LEDPin::D6) * 2)); // Clear the mode bits for LED D6
  moder |= 0b01U << (int(LEDPin::D6) * 2);    // Set the mode bits to output for LED D6
  *GPIOD_moder = moder;                       // Write the updated mode register value

  // Loop to toggle LED D6 and motor on/off
  for (int i = 0; i < 5; ++i) {
    puts("tick....");
    auto odr = *GPIOD_odr;                          // Read the current output register value
    odr |= 0x1U << static_cast<int>(LEDPin::D6);     // Set the bit to turn on LED D6
    *GPIOD_odr = odr;                               // Write the updated output register value
    sleep(500);                                       // Wait for 500 milliseconds
    odr &= ~(0x1U << static_cast<int>(LEDPin::D6));  // Clear the bit to turn off LED D6
    *GPIOD_odr = odr;                               // Write the updated output register value
    sleep(500);                                       // Wait for 500 milliseconds
  }

  // Configure the mode of the GPIO pins for the motor
  moder = *GPIOD_moder;
  moder &= ~(0xFU << (int(MotorPin::on) * 2));  // Clear the mode bits for the motor pins
  moder |= 0x5U << (int(MotorPin::on) * 2);     // Set the mode bits to output for the motor pins
  *GPIOD_moder = moder;                         // Write the updated mode register value

  // Loop to toggle motor on/off
  for (int i = 0; i < 5; ++i) {
    puts("spin...."); 
    auto odr = *GPIOD_odr;              // Read the current output register value
    odr ^= 0x1U << int(MotorPin::dir);   // Toggle the direction bit
    odr |= 0x1U << int(MotorPin::on);    // Set the bit to turn on the motor
    *GPIOD_odr = odr;                   // Write the updated output register value
    sleep(500);                           // Wait for 500 milliseconds
    odr &= ~(0x1U << int(MotorPin::on)); // Clear the bit to turn off the motor
    *GPIOD_odr = odr;                   // Write the updated output register value
    sleep(500);                           // Wait for 500 milliseconds
  }

  // Configure the mode of the GPIO pins for the seven-segment display
  moder = *GPIOD_moder;
  moder &= ~(0xFFU << (int(SevenSegmentPin::A) * 2)); // Clear the mode bits for the seven-segment pins
  moder |=
      0x55U << (int(SevenSegmentPin::A) * 2); // Set the mode bits to output for the seven-segment pins
  *GPIOD_moder = moder; // Write the updated mode register value

  // Loop to count from 0 to 9 on the seven-segment display
  for (unsigned i = 0; i < 10; ++i) {
    puts("count....");
    uint32_t odr = *GPIOD_odr;                // Read the current output register value
    odr &= ~(0xFU << int(SevenSegmentPin::A)); // Clear the bits corresponding
                                                // to the seven-segment pins
    odr |= i << int(SevenSegmentPin::A);       // Set the bits to display the current
                                                // count value
    *GPIOD_odr = odr;                         // Write the updated output register 
                                                // value to display the count
    sleep(500);                                 // Wait for 500 milliseconds
  }
}
