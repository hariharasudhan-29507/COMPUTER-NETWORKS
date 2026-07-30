# Code Repository & Documentation

Welcome to the Code Repository! This project contains a collection of competitive programming solutions from CodeChef and LeetCode, as well as practical framing protocol implementations (Bit stuffing, Byte stuffing) for Networking.

## Repository Structure

Below is an overview of the directory hierarchy of this repository:

```
├── CodeChef/
│   └── ProcessingaString.c
├── LeetCode/
│   ├── 338.CountingBits.c
│   ├── 421.MaximumXORinTheArray.c
│   ├── 476.NumberComplement.cpp
│   ├── 67.AddBinary.cpp
│   └── 693.BinaryNumberWithAlternatingBits.cpp
├── Practice/
│   └── ex1/
│       ├── Bitstuffing.c
│       ├── Bytestuffing.c
│       └── Self1(Bit stuffing).c
└── docs/                             # Full documentation files
    ├── CodeChef/
    │   └── ProcessingaString.md
    ├── LeetCode/
    │   ├── 338.CountingBits.md
    │   ├── 421.MaximumXORinTheArray.md
    │   ├── 476.NumberComplement.md
    │   ├── 67.AddBinary.md
    │   └── 693.BinaryNumberWithAlternatingBits.md
    └── Practice/
        └── ex1/
            ├── Bitstuffing.md
            ├── Bytestuffing.md
            └── Self1(Bit stuffing).md
```

---

## Detailed Code Explanations & Documentation

We have provided a dedicated documentation markdown file explaining **every single code file** in this repository. Use the links below to navigate to the detailed walkthroughs:

### 1. CodeChef
* **[Processing a String](docs/CodeChef/ProcessingaString.md)** (`CodeChef/ProcessingaString.c`)
  - *Goal:* Sum all numeric digits present in a given string.

### 2. LeetCode
* **[338. Counting Bits](docs/LeetCode/338.CountingBits.md)** (`LeetCode/338.CountingBits.c`)
  - *Goal:* Generate an array with the count of set bits for all integers up to `n`.
* **[421. Maximum XOR in The Array](docs/LeetCode/421.MaximumXORinTheArray.md)** (`LeetCode/421.MaximumXORinTheArray.c`)
  - *Goal:* Use a Trie (Prefix Tree) to efficiently compute the maximum XOR of any two elements in an array.
* **[476. Number Complement](docs/LeetCode/476.NumberComplement.md)** (`LeetCode/476.NumberComplement.cpp`)
  - *Goal:* Invert/flip all bits in the binary representation of an integer and return the complement.
* **[67. Add Binary](docs/LeetCode/67.AddBinary.md)** (`LeetCode/67.AddBinary.cpp`)
  - *Goal:* Compute the binary sum of two large binary strings.
* **[693. Binary Number with Alternating Bits](docs/LeetCode/693.BinaryNumberWithAlternatingBits.md)** (`LeetCode/693.BinaryNumberWithAlternatingBits.cpp`)
  - *Goal:* Check if a positive integer has strictly alternating bits (no consecutive identical bits).

### 3. Practice (Framing Protocols & Networking)
* **[Bit Stuffing](docs/Practice/ex1/Bitstuffing.md)** (`Practice/ex1/Bitstuffing.c`)
  - *Goal:* Standard Data Link Layer bit stuffing (inserting `'0'` after five consecutive `'1'`s) and destuffing.
* **[Byte Stuffing](docs/Practice/ex1/Bytestuffing.md)** (`Practice/ex1/Bytestuffing.c`)
  - *Goal:* Character-oriented framing with Flag (`"01111110"`) and Escape (`"01111101"`) blocks.
* **[Bit Stuffing with Parity & Error Injection](docs/Practice/ex1/Self1(Bit stuffing).md)** (`Practice/ex1/Self1(Bit stuffing).c`)
  - *Goal:* Implementation of bit stuffing combined with even parity calculation, user-controlled channel error injection, and receiver error detection.

---

## How to Compile & Run the Code

### C Programs (e.g. CodeChef / LeetCode / Practice)
Use `gcc` to compile any of the C source files:
```bash
gcc -o my_program Practice/ex1/Bitstuffing.c
./my_program
```

### C++ Programs (e.g. LeetCode)
Use `g++` to compile C++ source files:
```bash
g++ -o my_program LeetCode/67.AddBinary.cpp
```
*(Note: LeetCode solution files contain class methods intended to be run in a test harness, but you can wrap them in a standard C++ driver `main` function for local testing).*
