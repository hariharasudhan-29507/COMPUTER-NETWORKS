# Bit Stuffing Protocol

## Problem Statement / Goal
Bit stuffing is a framing technique used in the Data Link Layer of computer networks. It inserts non-information bits into data to break up continuous sequences of identical bits and prevent them from being mistaken for frame delimiters (flags). This program implements bit stuffing and destuffing.

## Approach & Logic
- **Bit Stuffing:**
  1. Convert a user-entered text string into its binary ASCII equivalent.
  2. For bit stuffing, we look for five consecutive `1`s in the binary sequence.
  3. If five consecutive `1`s are encountered, a `0` is stuffed (inserted) directly after the fifth `1`.
  4. Delimiters (flags) such as `0111111` are prepended and appended to mark the start and end of the frame.
- **Bit Destuffing:**
  1. Read a stuffed binary stream.
  2. Traverse the stream and copy bits to a destuffed output buffer.
  3. When five consecutive `1`s are detected, skip the next bit (which is the stuffed `0`).
  4. Output the restored binary sequence.

## Detailed Code Walkthrough
- `void stringToBinary(char str[])`: Converts a string `str` to its binary ASCII stream and saves it in the global array `binary`.
- `void bitStuffing()`:
  - Takes a string input from the user.
  - Converts it to a binary stream using `stringToBinary`.
  - Iterates through `binary`. If `binary[i] == '1'`, it increments `count`. If `count == 5`, it inserts a stuffed `'0'` right after it, then resets the counter.
  - Prints the stuffed bitstream and the resulting stuffed frame wrapped in starting/ending flags (`0111111`).
- `void bitDestuffing()`:
  - Takes a stuffed binary stream input.
  - Reconstructs the original bit sequence by copying bits one by one.
  - Keeps track of consecutive `1`s. When `count == 5`, it increments the loop index `i` to skip the next character (the stuffed `0`).
  - Prints the destuffed original binary bitstream.
- `int main()`: Provides an interactive command-line interface with a menu to choose between:
  1. Bit Stuffing
  2. Bit Destuffing
  3. Exit

## Complexity Analysis
- **Time Complexity:** $O(L)$ where $L$ is the length of the binary string. Converting characters to binary is $O(C)$ where $C$ is string length ($L = 8 \times C$), and stuffing/destuffing traverses the bit sequence once, taking linear time.
- **Space Complexity:** $O(L)$ to store the binary representations and output frames in global and local arrays.
