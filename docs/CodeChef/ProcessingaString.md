# Processing a String - CodeChef

## Problem Statement / Goal
The goal of this program is to calculate the sum of all numerical digits ('0' to '9') present in a given string.

## Approach & Logic
1. Read the number of test cases, $T$.
2. For each test case, read the input string $S$ (up to 1000 characters).
3. Loop through each character of the string until the null-terminator `\0` is reached:
   - Check if the current character is a digit (between `'0'` and `'9'`).
   - If it is a digit, convert the character representation to its corresponding integer value by subtracting `'0'`, and add it to the running sum.
4. Print the final sum for each test case.

## Detailed Code Walkthrough
- `int main()`: The entry point of the program.
- `int T; scanf("%d", &T);`: Reads the number of test cases.
- `while (T--)`: Loops through each test case.
- `char S[1001]; scanf("%s", S);`: Allocates memory for string `S` (up to 1000 characters plus null-terminator) and reads the string.
- `int sum = 0;`: Initializes the sum of digits to 0.
- `for (int i = 0; S[i] != '\0'; i++)`: Iterates through the string characters.
- `if (S[i] >= '0' && S[i] <= '9')`: Filters out non-digit characters.
- `sum += S[i] - '0';`: Converts ASCII value of digit to integer and accumulates.
- `printf("%d\n", sum);`: Prints the final accumulated sum followed by a newline.

## Complexity Analysis
- **Time Complexity:** $O(N)$ per test case, where $N$ is the length of the string $S$, because we inspect each character exactly once. Overall time complexity is $O(T \times N)$.
- **Space Complexity:** $O(1)$ auxiliary space as we only use a fixed-size character array of length 1001 and a few integer variables.
