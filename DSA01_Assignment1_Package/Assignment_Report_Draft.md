# ASSIGNMENT 1 – CO1

## Design, Implement and Validate the Fare Logic of a City Metro Smart-Card System

**Student Name:** [Your Name]  
**Register Number:** [Your Register Number]  
**GitHub Repository:** [Paste your repository link]

## General assumptions and scope

The source brief specifies the three original zones, fares, peak windows, 20% peak surcharge and minimum post-journey balance of ₹50. It mentions student and senior-citizen concessions but does not provide their rates or combination rules. This report identifies that gap rather than treating an unstated rate as a source fact. For any demonstration concession extension, an explicit assumption must be approved or replaced with the faculty's rule. The Task 6 program follows the PDF's exact expected output.


# Task 1 – Understand the Problem and Identify the Objects

## Objective
Analyse the Namma Metro smart-card fare problem using object-oriented concepts and identify the objects, their data, behaviour and journey rules.

## 1. Objects, attributes and behaviours
| Object | Important data (attributes) | Behaviour (methods) | Why it is needed |
|---|---|---|---|
| SmartCard | cardId, balancePaise | canTravel(fare), deduct(fare), recharge(amount) | Owns the stored value and protects the balance rule. |
| Passenger | passengerId, name, category | getConcessionType() | Represents the traveller and the eligibility information used by fare policy. |
| Journey | source, destination/zone, hour, date, farePaise | calculateFare(), isPeakHour() | Represents one trip and the facts needed to calculate its fare. |
| Zone | zone name / zone identifier | identifyZone() | Represents Inner, Middle and Outer fare categories. |
| FareTable | base fares, surcharge percentage, minimum balance | baseFare(zone), calculateFare(journey) | Keeps fare rules in one place rather than repeating values. |

A zone can be represented as an `enum class` in C++. FareTable can be a class or a group of named constants and functions. For a small assignment, the zone enum plus a fare calculation function is sufficient; a class becomes more useful as the policy grows.

## 2. Procedural style versus OOP
In a procedural solution, card balances, zone values and fare rates may be separate variables, while free functions calculate fares and deduct balances. Every function must receive the relevant values. If the balance is public global data, any function can accidentally change it.

In an object-oriented solution, a `SmartCard` object owns its balance and exposes controlled operations such as `canTravel()` and `deduct()`. A `Journey` object holds journey information, and a `FareTable` or fare-policy class owns the fare rules. Data and the operations that protect it are grouped together. This improves organization and makes changes easier to localize.

## 3. Four OOP principles in this system
- **Encapsulation:** Keep `SmartCard::balancePaise` private. Only validated methods can deduct or recharge money. This prevents unrelated code from creating a negative balance.
- **Abstraction:** A caller asks `card.canTravel(fare)` without needing to know the internal balance-validation steps.
- **Inheritance:** A common `Passenger` base class could be extended by `StudentPassenger` and `SeniorPassenger` if those categories have different concession rules. Inheritance is justified only if they share common passenger data and behaviour.
- **Polymorphism:** A virtual `concessionPercent()` method in `Passenger` could return a category-specific concession. The fare system can call the same method through a base-class reference. This is useful when concession categories grow.

## 4. Correct-journey rules and assumptions
1. The base fare is ₹10 for Inner, ₹20 for Middle and ₹30 for Outer.
2. Peak hours are 08:00–09:59 and 17:00–19:59. Therefore 08:00 and 17:00 are peak; 10:00 and 20:00 are off-peak.
3. A peak journey receives a 20% surcharge.
4. After fare deduction, the card must retain at least ₹50. A journey is permitted only when `balance - fare >= 5000` paise.
5. A denied journey must not change the balance.
6. Money is stored as integer paise to avoid floating-point currency rounding.
7. The brief mentions student and senior-citizen concessions but does not specify rates or whether concessions combine with the peak surcharge. The implementation should make these policy values configurable. For demonstration only, this package uses a stated assumption of 10% student and 15% senior concession, applied to the base fare before any peak surcharge. The core Task 6 program follows the exact provided expected output and does not apply passenger concessions.

## 5. UML class diagram (text specification)
- `Passenger` — passengerId, name, category; `concessionPercent()`.
- `Journey` — zone, hour, weekend; `isPeakHour()`.
- `FareTable` — baseFare(zone), calculateFare(journey).
- `SmartCard` — private balancePaise; `canTravel(fare)`, `deduct(fare)`, `getBalance()`.
- `Pass` (introduced in Task 12) — selectedZoneA, selectedZoneB, active; `covers(zone)`, `allows(journey)`.

Relationships: Passenger makes Journey; Journey is evaluated by FareTable; Passenger uses SmartCard; SmartCard pays the fare for an accepted Journey.

## Alternative concept and complexity analysis
A procedural design would store the balance and fare values in variables and use free functions such as `calculateFare(zone, hour)` and `canTravel(balance, fare)`. For each journey, the fare lookup and balance check take constant time: **O(1)**. Memory for one card balance is **O(1)** in either design. The main difference is maintenance: a changed rule may require edits in several free functions and call sites in a procedural design, while OOP can localize the rule in FareTable or SmartCard. OOP does not automatically make the calculation faster; its advantage here is data protection and maintainability.


# Task 2 – Use Tokens, Keywords, Identifiers and Constants Correctly

## Objective
Define fare values and limits in one place and use C++ tokens and constants safely.

## 1. Five kinds of tokens
| Token kind | Meaning | Examples in this assignment |
|---|---|---|
| Keywords | Reserved words with language meaning | `int`, `class`, `if`, `return`, `switch`, `enum` |
| Identifiers | Programmer-defined names | `SmartCard`, `balancePaise`, `calculateFare` |
| Constants / literals | Fixed values written in code | `20`, `5000`, `'A'`, `true` |
| Operators | Symbols that perform operations | `+`, `-`, `*`, `/`, `>=`, `&&`, `+=` |
| Punctuators | Symbols that structure code | `{ } ( ) ; , [ ]` |

## 2. `#define`, `const` and `constexpr`
- `#define` is a preprocessor substitution. It has no C++ type and does not obey normal C++ scope in the same way as a variable.
- `const` declares a typed object that cannot be modified after initialization. Its value need not always be known at compile time.
- `constexpr` declares a value or function that can be evaluated at compile time when its inputs permit it. It is typed and participates in normal C++ scope and type checking.

`constexpr` is preferred for fixed fare values because it is typed, scoped, checked by the compiler and suitable for compile-time expressions.

## 3. Zones: `enum` and `enum class`
An unscoped `enum` exposes enumerator names into the surrounding scope and can convert to an integer more freely. `enum class Zone { Inner, Middle, Outer };` scopes names under `Zone` and does not implicitly convert to `int`. This reduces accidental mixing of zone values with unrelated integers.

## 4. Identifier naming conventions
Identifiers must not be C++ keywords, must not begin with a digit, and should use meaningful names. This package uses `PascalCase` for class and enum names (`SmartCard`, `Zone`) and `camelCase` for variables and functions (`balancePaise`, `calculateFare`). Constants use uppercase words separated by underscores (`MIN_BALANCE_PAISE`).

## Example constants
`constexpr long long INNER_FARE_PAISE = 1000;`
`constexpr long long MIDDLE_FARE_PAISE = 2000;`
`constexpr long long OUTER_FARE_PAISE = 3000;`
`constexpr int PEAK_SURCHARGE_PERCENT = 20;`
`constexpr long long MIN_BALANCE_PAISE = 5000;`

## Alternative concept and complexity analysis
If `#define` macros were used, fare values could be substituted textually, for example `#define INNER_FARE_PAISE 1000`. A macro has no declared C++ type and does not provide normal variable scope or type checking. A `constexpr` value has a type and scope. In simple use, both normally require no separate runtime storage, and neither changes the fare calculation's **O(1)** running time. `constexpr` is safer and easier to debug; macros are more prone to precedence and naming mistakes.


# Task 3 – Choose Data Types and Check Type Compatibility

## Objective
Choose suitable C++ types, examine their sizes and ranges, and justify exact currency storage.

## 1. Data type selection
| Value | Recommended type | Reason |
|---|---|---|
| Fare in paise | `long long` | Exact integer currency and safe totals |
| Card balance in paise | `long long` | Must not become negative and may grow after recharge |
| Hour | `int` | Values are 0–23 |
| Zone | `enum class Zone` | Represents a fixed set of named choices |
| Peak status | `bool` | True or false |
| Passenger initial | `char` | One character |
| Journey count | `long long` | Large network counts |
| Percentage | `int` | Whole-number percentage in this specification |
| Measurement/experimental rupees | `double` | Used only to demonstrate floating-point behaviour |
| Inferred local value | `auto` | Use only when the inferred type is clear |

The exact sizes are implementation-dependent. Run the supplied `task03_datatypes.cpp` on the target compiler and record its `sizeof` output. On many common 64-bit g++ systems, `int` is 4 bytes, `long long` is 8 bytes and `double` is 8 bytes, but your own result is the evidence to report.

## 2. Why integer paise instead of double rupees?
₹10.25 is represented as 1025 paise. Integer addition and multiplication by integer percentages avoid binary floating-point representation error. For a 20% surcharge, calculate `basePaise * 20 / 100`. The given fares are whole rupees, so the percentage result is exact in paise.

## 3. Type compatibility
In an expression containing `int` and `double`, the integer is usually converted to `double` before the arithmetic. In `7 / 2`, both operands are integers, so integer division gives 3; assigning that result to `double` produces 3.0, not 3.5. A `bool` used in arithmetic is promoted to an integer value of 0 or 1. Avoid relying on surprising implicit conversions.

## 4. Integer limits and network collection
`<climits>` provides `INT_MAX`, `INT_MIN`, `LLONG_MAX` and related limits. For a simple upper-bound example using ₹30 per journey:
- 20,000 journeys: ₹600,000.
- 500,000 journeys: ₹15,000,000.
- 3,000,000 journeys: ₹90,000,000.

In paise, these are 60,000,000; 1,500,000,000; and 9,000,000,000 respectively. The last total exceeds the usual 32-bit signed `int` maximum (2,147,483,647), so `long long` is appropriate. Use the actual `INT_MAX` printed by your compiler when explaining your result.

## 5. Precision experiment
The supplied program adds a decimal value repeatedly using `double` and the equivalent integer number of paise using `long long`. Record the displayed difference. Floating-point error depends on the exact value and number of additions; do not claim a fixed error without running the experiment.

## Alternative concept and complexity analysis
With `double` rupees, each addition is **O(1)** and each `double` commonly occupies 8 bytes. With `long long` paise, each addition is also **O(1)** and `long long` commonly occupies 8 bytes. The space per value is therefore commonly equal, but integer paise provides exact arithmetic for the specified currency amounts. A repeated-addition experiment demonstrates any floating-point deviation for the chosen input and n.


# Task 4 – Control Implicit Conversions

## Objective
Identify implicit conversions and understand how explicit casts and brace initialization make conversions safer.

## Important conversion points
- `double c = a / b;`: `a` and `b` are both `int`, so integer division occurs first. With 7 and 2 the result is 3, then converted to `double` as 3.0.
- `static_cast<double>(a) / b`: `a` becomes 7.0 before division, so the result is 3.5.
- `char ch = 'A' + 2;`: the character literal is promoted to `int` for addition; the result is converted back to `char`, producing `C` on the usual execution character set.
- `ch + 1`: `ch` is promoted to `int`, so the numeric result is 68 on ASCII-compatible systems.
- `bool flag = 5;`: non-zero integer converts to `true`. `boolalpha` prints `true`; before it is enabled, bool normally prints `1`.
- `s < u`: the signed `int` is converted to unsigned for the comparison because the usual arithmetic conversions apply. `-1` becomes a large unsigned value, so the comparison is false for this example and the program prints `s >= u`.

## Predicted output (write this before running)
```text
3 3.5
C 68
1 true
s >= u
```
The exact character result assumes the common ASCII-compatible execution character set used by typical g++ environments.

## Safer code practices
Use `static_cast<double>(a)` when floating-point division is intended. Use brace initialization such as `int count{3};` to reject narrowing conversions like `int x{3.7};`. Validate signed values before converting them to unsigned values. Compile with `-Wall -Wextra` and address warnings rather than suppressing them.

## Alternative concept and complexity analysis
If every conversion were explicit, the program would state the intended type changes using `static_cast`, and brace initialization would reject many narrowing conversions at compile time. Runtime time and memory are normally unchanged: the cast itself does not add a meaningful algorithmic step, so the operations remain **O(1)** with **O(1)** storage. The main benefit is earlier detection of mistakes by the compiler and clearer intent.


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


# Task 6 – Design the Control Structures

## Objective
Design fare and daily-journey logic using decisions and loops, write pseudocode, and complete the supplied TODO program.

## Control structure choices
- Use `switch` when selecting one base fare from a fixed set of zones.
- Use `if-else` for conditions such as peak surcharge, invalid input and minimum-balance validation.
- Use the conditional operator for a short value selection, not for complex business logic.
- A counted `for` loop is suitable when the number of journeys is known. A range-based `for` loop is suitable for processing every item in a collection. A `while` loop is suitable when input continues until a stop condition is entered.
- Use `continue` to skip an invalid journey and `break` to stop processing when required.
- If no `switch` case matches and there is no `default`, no case body executes. Include a `default` branch when invalid values must be handled.

## Algorithmic pseudocode
```text
START
  READ zone, hour, balance
  IF zone is invalid OR hour is outside 0..23
      DISPLAY invalid journey
      STOP this journey
  ENDIF

  SET peak = (8 <= hour < 10) OR (17 <= hour < 20)

  SELECT zone
      Inner: baseFare = 1000 paise
      Middle: baseFare = 2000 paise
      Outer: baseFare = 3000 paise
      OTHERWISE: reject journey
  ENDSELECT

  SET fare = baseFare
  IF peak
      SET fare = fare + (baseFare * 20 / 100)
  ENDIF

  IF balance - fare >= 5000
      balance = balance - fare
      DISPLAY fare and balance
  ELSE
      DISPLAY denied and unchanged balance
  ENDIF
END
```

## Completed TODO logic
TODO 1 uses a switch to select the base fare and integer arithmetic for the 20% surcharge. TODO 2 returns true only if the remaining balance is at least 5000 paise. The complete source is `task06_completed.cpp`.

## Expected output from the supplied assignment
```text
Fare Rs 10.00 balance Rs 90
Fare Rs 36.00 balance Rs 54
Denied (low balance) balance Rs 54
```

## Alternative concept and complexity analysis
An array such as `constexpr long long FARE[] = {1000, 2000, 3000};` could replace the switch if zone values map safely to array indices. Both switch selection and indexed lookup are **O(1)**. The array stores three fare values, which is **O(1)** space for a fixed number of zones. Adding a fourth zone requires adding a fare entry and a new enum value; a switch design requires adding another case. A switch with a default case can be safer when enum values may be invalid.


# Task 7 – From Procedural to Object-Oriented

## Objective
Implement the same fare and balance rules using procedural and object-oriented designs.

## Procedural version
A procedural design uses a balance variable and free functions such as `canTravel(balance, fare)` and `deduct(balance, fare)`. The caller must pass the correct balance to each function and update it correctly. If the balance is shared or public, unrelated code can bypass the validation.

## Object-oriented version
The OOP version uses `SmartCard`, stores `balancePaise` privately and exposes methods such as `canTravel(fare)`, `deduct(fare)` and `getBalance()`. `deduct()` checks the minimum-balance condition before changing the balance. The caller cannot directly assign a negative balance through the public interface.

## Comparison
Both approaches perform a constant number of arithmetic and comparison operations per journey: **O(1)** time. Each stores a constant number of values per card: **O(1)** space. The OOP version better protects the invariant and localizes future changes to the minimum-balance rule.

## Alternative concept and complexity analysis
If the balance were public, time and space would not materially change: access and assignment remain **O(1)**. However, any code could write `card.balancePaise = -100;` or deduct without checking the minimum balance. Encapsulation protects correctness, not speed.


# Task 8 – Read and Print Data Safely

## Objective
Read operator input safely, recover from invalid numeric input and print a readable fare report.

## Safe input handling
When `cin >> value` receives letters where a number is expected, the stream enters a failure state. Check `cin.fail()`. Call `cin.clear()` to reset the state flags, then `cin.ignore(numeric_limits<streamsize>::max(), '\\n')` to discard the invalid line. Ask again. Include `<limits>` for `numeric_limits`.

## Formatting
- `setw(n)` sets the width for the next formatted field.
- `setfill(ch)` changes the padding character.
- `fixed` selects fixed-point floating display.
- `setprecision(2)` prints two digits after the decimal point when used with `fixed`.
For exact currency, the program formats integer paise as rupees and two-digit paise rather than converting the stored value to double.

## Input and output design
The example program reads passenger name, balance in rupees, zone and hour. It validates each numeric entry and displays the fare, decision and remaining balance. In a production system, validate the zone against the supported choices and reject negative recharge values.

## Alternative concept and complexity analysis
An alternative is to read each input line with `getline()` and convert numeric text with `stoi()` inside `try/catch`. Reading and converting a line of length L takes **O(L)** time and requires **O(L)** buffer space. Direct formatted extraction is also proportional to the number of characters parsed, and avoids a separate string conversion buffer in simple cases. `getline` plus `stoi` gives explicit line-level control and exceptions for invalid input; `cin` requires clearing the stream state and discarding the bad input before retrying.


# Task 9 – Implement and Test the Fare Logic

## Objective
Build and test a complete metro fare application against normal, boundary and invalid cases.

## Implementation design
The complete program is `task09_fare_application.cpp`. It stores money in integer paise, checks hour values from 0 to 23, uses the three specified zones, applies the 20% peak surcharge, rejects negative recharge amounts and enforces the minimum post-journey balance of ₹50. A denied journey does not change the balance.

The assignment does not specify student or senior-citizen concession rates. The main Task 9 executable therefore keeps the core specified fare rules separate; any concession extension must state its assumed rates and combination order.

## Test plan
| Test | Input / condition | Expected result |
|---|---|---|
| 1 | Inner at 12:00 | ₹10.00 |
| 2 | Middle at 12:00 | ₹20.00 |
| 3 | Outer at 12:00 | ₹30.00 |
| 4 | Outer at 08:00 | ₹36.00 |
| 5 | Inner at 17:00 | ₹12.00 |
| 6 | 10:00 | Off-peak |
| 7 | 20:00 | Off-peak |
| 8 | Remaining balance exactly ₹50 | Allowed |
| 9 | Remaining balance below ₹50 | Denied; balance unchanged |
| 10 | Unknown zone | Rejected |
| 11 | Negative recharge | Rejected |
| 12 | Letters entered for hour | Re-prompt / invalid input handled |

For the five-journey hand calculation, use Inner off-peak ₹10 + Middle off-peak ₹20 + Outer off-peak ₹30 + Inner peak ₹12 + Outer peak ₹36 = **₹108.00**. This is the total fare, before applying the card minimum-balance rule to an individual card.

## Alternative concept and complexity analysis
A table of test cases can store inputs and expected fares, then run them in a loop. For t tests, the total test execution is **O(t)** if each fare calculation is **O(1)**. The test table requires **O(t)** storage. Adding a boundary test is easier because a new row can be added without writing another separate test block.


# Task 10 – Compare Expectations with Execution

## Objective
Compare floating-point and integer-paise totals, test integer overflow and record compiler warnings.

## Calculation using ₹10 per journey (illustrative fixed-fare experiment)
| Journeys | Total in rupees | Total in paise |
|---:|---:|---:|
| 20,000 | ₹200,000 | 20,000,000 |
| 500,000 | ₹5,000,000 | 500,000,000 |
| 3,000,000 | ₹30,000,000 | 3,000,000,000 |

The ₹10 fare is an explicit experimental assumption for this comparison, not the maximum possible fare. At 3,000,000 journeys, 3,000,000,000 paise exceeds the usual signed 32-bit `int` maximum of 2,147,483,647. `long long` can safely hold this total on standard implementations with at least 64-bit range. The rupee total of 30,000,000 fits a 32-bit signed int, but using `int` for paise does not.

## What to record
Run `task10_totals.cpp` and record its integer-paise and double-rupee output. The program also prints the compiler's `INT_MAX` and `LLONG_MAX`. Do not claim a measured rounding difference unless the output shows one. `double` has finite binary precision and can represent many decimal fractions only approximately.

## Compiler warnings
Compile each program with `-std=c++17 -Wall -Wextra`. Record the exact warning text and the source line. A warning is compiler-specific; do not invent warnings. Fix unused variables, suspicious conversions or missing returns where applicable.

## Alternative concept and complexity analysis
For n journeys, accumulating into `int`, `long long` or `double` takes **O(n)** total time and **O(1)** extra space. Each addition is **O(1)**. `int` can overflow when the total exceeds its range; signed overflow is undefined behaviour in C++. `long long` provides a much larger integer range. `double` avoids integer overflow for these values but can introduce rounding representation error. The variable sizes should be measured with `sizeof` on the target compiler.


# Task 11 – Recommend and Defend the Final Design

## Objective
Recommend a maintainable and accurate design for the current metro network using evidence from earlier tasks.

## Recommended design
1. Store fares, balances and collections in integer paise using `long long`.
2. Use `enum class Zone` for the supported zones.
3. Use named `constexpr` constants for the fixed base fares, surcharge percentage and minimum balance.
4. Use `SmartCard` with a private balance and validated operations.
5. Keep peak-hour detection and fare calculation in separate functions or a fare-policy class.
6. Validate hour, zone and recharge input before calculation.
7. Use a loop over journeys and a repeatable test table for boundary cases.

## Fare revision
For the original three-zone design, change the fare constants in one location, rebuild and rerun all tests. A larger system may load a validated configuration file at startup so authorized fare changes do not require recompilation. The configuration must be checked for missing zones, negative fares and invalid percentages.

## Limitations
The original specification does not provide student/senior concession percentages, concession eligibility verification, refund rules or fare rounding rules for fractional paise. Those require policy decisions before production deployment. A fixed three-zone switch is also less flexible when zones are added frequently.

## Whole-network suitability
The arithmetic per journey remains constant time, and `long long` is suitable for the sample network totals. A production system would also need transaction safety, concurrency handling, durable card storage, audit logs, security and central fare configuration; these are beyond this assignment's small C++ console model.

## Alternative concept and complexity analysis
Loading z fares from a configuration file takes **O(z)** startup time and **O(z)** storage. After loading, a fare lookup is **O(1)** with a suitable indexed table. Compiled-in `constexpr` fares avoid file parsing at startup but require recompilation and redeployment after changes. For a small fixed assignment, `constexpr` is simple and safe; for frequent policy updates, a validated configuration file is more maintainable.


# Task 12 – Re-evaluate and Adapt the Design

## Objective
Evaluate the original fare design against the new fourth zone, weekend discount and monthly-pass requirements, then implement and defend an adapted design.

## A. Impact analysis (2 marks)
- Add `Airport` to the zone enum and add a ₹60.00 fare (6000 paise).
- Update the fare table from three entries to four.
- Update zone validation and all tests.
- Update any switch statement or replace it with a zone-indexed table.
- Add a weekend indicator and a weekend discount rule.
- Ensure weekend discount and peak surcharge do not combine.
- Add a `Pass` class that stores two selected zones and permits unlimited journeys only in those zones while the pass is active.
- Review SmartCard payment logic: a valid pass-covered journey should not deduct a fare; journeys outside the two covered zones use normal fare logic.

## B. Evaluation of original design (2 marks)
A three-case switch can be extended with an Airport case, but each additional zone requires another case and coordinated changes. A fare table indexed by a validated zone is easier to extend. The original SmartCard can still protect balance, but it needs integration with pass eligibility so that a covered journey is not charged.

Worked examples:
- Airport weekday off-peak: ₹60.00.
- Airport weekday peak: ₹60 + 20% = ₹72.00.
- Airport weekend: ₹60 − 10% = ₹54.00.
- Airport weekend during a peak clock hour: ₹54.00, because the weekend discount replaces, rather than combines with, the peak surcharge.

## C. Adaptation / redesign (2 marks)
The implementation `task12_revised_design.cpp` uses an enum with four zones, a fare table, a weekend rule and a `Pass` class. It demonstrates a monthly pass covering two selected zones. For this assignment model, the pass is represented by an active boolean; a real monthly pass would also require start/end dates, renewal and expiry validation.

## D. Evidence-based defence (2 marks)
The design is **modified**, not completely discarded. The SmartCard remains useful for stored-value journeys, while the fare lookup is changed to a table and a separate pass object handles unlimited travel in two selected zones. Tests verify all four zones, weekend discount precedence, peak surcharge and pass-covered versus uncovered zones. The table makes a new zone a data update, while the separate discount and pass rules prevent the fare function from becoming one large conditional block.

## Alternative concept and complexity analysis
A switch can still handle four zones in **O(1)** time, and a four-entry table also provides **O(1)** lookup. The table uses **O(z)** space for z zones; for four zones this is constant-sized in this assignment. Checking whether a pass covers either of two zones is **O(1)**. A larger pass with many zones could use a set, with average **O(1)** membership lookup. The modified design is easier to extend and separates fare policy from pass eligibility.


# Conclusion

The recommended implementation stores currency in integer paise, validates all input, uses a private SmartCard balance, keeps fare rules centralized and tests boundary conditions. The revised design adds a fourth zone, a weekend discount that replaces the peak surcharge, and a separate monthly-pass abstraction. Before final submission, execute the source files on the assigned compiler, paste actual output screenshots, fill student details and add the live GitHub link.
