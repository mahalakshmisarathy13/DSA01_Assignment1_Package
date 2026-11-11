# Task 5 – Write Correct Expressions with the Right Precedence

## Objective
Use correct operators and readable expressions for peak checking and fare calculation.

## 1. Required expressions
Peak check:
`bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);`

Peak surcharge in integer paise:
`long long fare = baseFare;`
`if (peak) fare += baseFare * PEAK_SURCHARGE_PERCENT / 100;`

A concession should be a separate, documented policy step. Since the assignment does not state concession rates or combination order, state the chosen assumption before implementing it. This package's demonstration assumption is student 10% and senior 15%, applied to the base fare before a peak surcharge.

## 2. Precedence and associativity
Multiplication and division bind more tightly than addition. Relational comparisons bind more tightly than logical `&&`, and `&&` binds more tightly than `||`. Parentheses are recommended to make the peak windows obvious. Compound assignment such as `fare += amount` adds the right-hand side and stores the result. The conditional operator `condition ? value1 : value2` selects one of two expressions.

`x++` yields the old value and then increments; `++x` increments first and yields the new value. Avoid `i = i++`; it is confusing and can invoke undefined behaviour in older language standards / is not a valid way to express a controlled increment. Use `i++` or `++i` as a separate statement.

For integer division, C++ truncates toward zero. Thus `-10 / 3` is `-3`, and the remainder is `-1`, because `-10 == (-3 * 3) + (-1)`.

## 3. Predicted output (write this before running)
```text
11 16
9 6 5
6 4
3 1 -3 -1
18
```
Explanation:
- `5 + 3 * 2` is 11; `(5 + 3) * 2` is 16.
- `x++ + ++y`: old x is 5; y becomes 4; z is 9; then x is 6 and y is 4.
- `x > y ? x : y` is 6; `x % 4 * 2` is `(6 % 4) * 2 = 4`.
- Integer division and remainder follow truncation toward zero.
- The loop adds i values 0, 3, 6, 9, giving 18.

## Alternative concept and complexity analysis
A 24-element `bool peak[24]` lookup table can mark each hour as peak or off-peak. A table access is **O(1)**, as is evaluating the two-range expression. The table uses 24 bool elements (commonly 24 bytes, but `sizeof(bool)` should be checked on the target compiler). The expression uses a few comparisons and no table storage. The expression is compact and self-documenting for two intervals; a table can be easier to extend for complex calendars.
