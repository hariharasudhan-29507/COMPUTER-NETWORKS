# Byte Stuffing Protocol (Character-Oriented Framing)

## Problem Statement / Goal
Byte stuffing (or character stuffing) is a framing method in the Data Link Layer. It allows arbitrary binary data to be sent across a network by reserving specific bytes as "Flag" and "Escape" characters. If a Flag or Escape byte appears in the payload, an Escape byte is stuffed before it so that it is not misidentified as a frame boundary. This program implements byte stuffing and destuffing in binary blocks.

## Approach & Logic
- **Flag Byte:** Represented in binary as `"01111110"`.
- **Escape (ESC) Byte:** Represented in binary as `"01111101"`.
- **Byte Stuffing:**
  1. Convert the user input string into 8-bit binary blocks.
  2. Prepend a Flag byte to indicate the start of the frame.
  3. Iterate through each binary block:
     - If the block is identical to Flag `"01111110"` or Escape `"01111101"`, prepend (insert) an Escape block `"01111101"` before it.
     - Copy the block to the output.
  4. Append a Flag byte to indicate the end of the frame.
- **Byte Destuffing:**
  1. Take the stuffed binary block stream.
  2. Skip the starting Flag.
  3. Iterate through the blocks:
     - If an Escape block is encountered, skip it and directly copy the next block (which was stuffed).
     - Otherwise, copy the block.
  4. Skip the ending Flag.
  5. Convert the binary blocks back to characters to restore the original text.

## Detailed Code Walkthrough
- `void charToBinaryStr(char character, char binary_str[])`: Converts a single character into an 8-character binary ASCII string.
- `char binaryStrToChar(char binary_str[])`: Converts an 8-bit binary string back into a single character.
- `void byteStuffing()`:
  - Prompts for a string.
  - Converts characters to binary blocks using `charToBinaryStr`.
  - Appends the starting Flag.
  - Checks each raw block. If it matches `FLAG_BIN` or `ESC_BIN`, inserts `ESC_BIN` block first.
  - Appends the ending Flag.
  - Prints the byte-stuffed frame in space-separated block format and as a continuous bitstream.
- `void byteDestuffing()`:
  - Takes the number of blocks and the space-separated blocks as input.
  - Traverses the blocks from index 1 to `total_blocks - 2` (skipping the outer boundary flags).
  - If a block is `ESC_BIN`, skips it and reads the next block to the destuffed output.
  - Converts destuffed binary blocks back to ASCII characters and prints the restored text.
- `int main()`: Displays an interactive command-line menu for:
  1. Byte Stuffing
  2. Byte Destuffing
  3. Exit

## Complexity Analysis
- **Time Complexity:** $O(N)$ where $N$ is the number of characters/blocks. Conversion, stuffing, and destuffing run in linear time relative to the input length.
- **Space Complexity:** $O(N)$ for local storage arrays storing binary strings and blocks.
