#ifndef DAY1_CPP
#define DAY1_CPP

/**
 * @file Day1.cpp
 * @brief Implementation for Day1 puzzle runner.
 * @author Devon F.
 *
 * This translation unit implements the `Day1::run` method which:
 *  - Reads movement instructions from the file "dayone.txt".
 *  - Interprets each line as a direction ('R' or 'L') followed by a distance value.
 *  - Updates a circular position on a 0..99 range (wraps at 100).
 *  - Tracks how many times position becomes 0 and how many full 0-wraps occurred.
 *
 * Notes:
 *  - The function prints diagnostic messages to stdout.
 *  - The behavior and algorithm are preserved from the original implementation;
 *    only documentation has been added to explain the logic.
 */

#include "Day1.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;

/**
 * @brief Execute Day 1 puzzle logic.
 *
 * Reads movement instructions from the file "dayone.txt". Each non-empty
 * line is expected to contain a direction character as the first character:
 *  - 'R' for right (increase position)
 *  - 'L' for left  (decrease position)
 * followed by an integer amount (e.g. "R12", "L4").
 *
 * The method maintains a circular position on a 0..99 range (wrap at 100).
 * It tracks:
 *  - final position after processing all instructions,
 *  - how many times the position was exactly 0 (zeroCount),
 *  - how many times the movement caused a wrap across 0 (zeroWrap).
 *
 * Counters:
 *  - zeroWrap increments for:
 *      * any full 100-unit increments included in a single instruction
 *        (value / 100), and
 *      * when a single instruction crosses the 0 boundary compared to the
 *        previous position (oldStart -> start).
 *
 * Side effects:
 *  - Prints status messages to stdout.
 *  - Returns void.
 */
void Day1::run() {
    cout << "Day 1: Hello, World!" << endl;

    // Open input file containing movement instructions.
    std::fstream file("dayone.txt");
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    // Current position on a 0..99 circular range. Start at 50 by default.
    int start = 50;
    // Preserve previous position to detect boundary crossings.
    int oldStart = start;
    // Count of times the position was exactly zero after applying an instruction.
    int zeroCount = 0;
    // Count of times we've wrapped across zero (including full 100-unit chunks).
    int zeroWrap = 0;

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines.
        if (line.empty()) continue;

        // First character is the direction; remaining substring is the integer value.
        char direction = line[0];
        int value = std::stoi(line.substr(1));

        // Account for any complete 100-unit wraps contained within the movement value.
        // Example: a move of 250 contains two full 100-unit wraps.
        zeroWrap += value / 100; // Count full wraps

        // Apply movement to the linear position (may go beyond [0,99] temporarily).
        if (direction == 'R') start += value;
        else if (direction == 'L') start -= value;
        else {
            // Invalid instruction format: report and exit early.
            cout << "Invalid direction: " << direction << endl;
            return;
        }

        // Normalize position into the [0,99] range using a safe modulo for negatives.
        start = (start % 100 + 100) % 100;

        // Detect boundary crossing relative to previous position.
        // - If oldStart != 0 and new start == 0, we crossed onto zero.
        // - If moving right and the wrapped result is numerically less than oldStart,
        //   or moving left and wrapped result is numerically greater than oldStart,
        //   we crossed the 0 boundary.
        if (oldStart != 0 && (start == 0
            || (direction == 'R' && start < oldStart)
            || (direction == 'L' && start > oldStart))) {
            zeroWrap++;
        }

        // If the new position is exactly zero, increment the zero occurrence counter.
        if (start == 0) zeroCount++;

        // Update previous position for next iteration's comparison.
        oldStart = start;
    }

    file.close();

    // Print final results.
    cout << "Final Position: " << start << endl;
    cout << "Final 0 Count: " << zeroCount << endl;
    cout << "Total 0 Wraps: " << zeroWrap << endl;
}

#endif // DAY1_CPP