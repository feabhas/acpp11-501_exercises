// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include "Timer.h"

// Define a scoped enum class for the washing machine steps
enum class StepType {
    invalid,  // Default value, used to identify blank entries
    empty,
    fill,
    heat,
    wash,
    rinse,
    spin,
    dry,
    complete
};

// Array of string representations for each StepType
static constexpr const char* names[] = {
    "invalid", "empty", "fill",
    "heat", "wash", "rinse",
    "spin", "dry", "complete"
};

// Function to convert StepType to its string representation
static constexpr const char* to_string(StepType step) {
    return names[static_cast<int>(step)];
}

int main()
{
    // Print "Tick..." 5 times with a 500ms delay between each print
    for(int i = 0; i < 5; ++i) {
        std::cout << "Tick..." << '\n';
        sleep(500);
    }

    // Example step declarations using auto type inference
    auto step1 = StepType::empty;
    auto step2 = StepType::fill;
    auto step3 = StepType{}; // Will be invalid

    // Print the step type and its string representation
    std::cout << "step1 " << int(step1) << " is " << to_string(step1) << '\n';
    std::cout << "step2 " << int(step2) << " is " << to_string(step2) << '\n';
    std::cout << "step3 " << int(step3) << " is " << to_string(step3) << '\n';

    // Print all steps
    std::cout << "\nAll steps:\n";
    for (int i = 0; i <= static_cast<int>(StepType::complete); ++i) {
        auto step = static_cast<StepType>(i);
        std::cout << to_string(step) << '\n';
    }
}


