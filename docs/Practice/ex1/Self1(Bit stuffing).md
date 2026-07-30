# Bit Stuffing Protocol with Parity & Error Injection

## Problem Statement / Goal
This program is an advanced custom implementation of the bit stuffing protocol. Beyond standard bit stuffing and destuffing, it integrates:
1. **Parity Bit Computation:** Adds an even parity bit to the stuffed frame before transmission.
2. **Error Injection:** Allows the user to manually introduce bit flips (errors) at specified indices of the transmitted frame.
3. **Error Detection at Receiver:** Re-computes parity at the receiver to detect if any transmission errors occurred.

## Approach & Logic
- **Stuffer / Transmitter:**
  1. Reads original data length and bitstream.
  2. Stuffs a `'0'` after five consecutive `'1'` bits.
  3. Computes the even parity of the stuffed frame (XOR sum of all bits).
  4. Appends the parity bit to form the transmitted frame.
- **Channel / Noise Simulator:**
  1. Asks user how many bit errors to introduce.
  2. For each error, flips the bit value (`0` to `1` or `1` to `0`) at the user-specified index in the transmitted frame, producing the received frame.
- **Receiver / Destuffer:**
  1. Re-computes the parity bit from the received frame (excluding the last parity bit).
  2. Destuffs the frame (skipping `'0'`s that follow five consecutive `'1'`s) to reconstruct the original bits.
  3. Compares the received parity bit with the computed parity. If they mismatch, an error is detected.

## Detailed Code Walkthrough
- `void printbits(int arr[], int len)`: Helper utility that prints an integer array of bits sequentially.
- `int main()`:
  - Prompts user for original bit size and elements (0 or 1).
  - Performs standard bit stuffing on array `a` to produce array `b`.
  - Computes XOR sum parity of array `b`: `parity = parity ^ b[i]`.
  - Copies array `b` into array `c` and appends the computed parity bit to the end: `c[stufflen] = parity`.
  - Simulates the transmission channel by copying `c` to `d`.
  - Prompts for error count and index positions. For each specified position `pos`, inverts the bit in `d` via `d[pos] = 1 - d[pos]`.
  - Performs recomputation of receiver-side parity `rparity` over `d` from index 0 to `stufflen - 1`.
  - Destuffs received frame `d` into array `e` by skipping bits when five consecutive `1`s are encountered.
  - Compares `rparity` with the received parity bit `d[stufflen]`.
  - Outputs the results of the parity check and the final destuffed data.

## Complexity Analysis
- **Time Complexity:** $O(N)$ where $N$ is the number of bits. The stuffing, parity calculation, error injection, parity verification, and destuffing loops each run in linear time with respect to the input size.
- **Space Complexity:** $O(N)$ as fixed-size arrays (`a`, `b`, `c`, `d`, `e`) are used to hold the bit patterns at different phases of transmission.
