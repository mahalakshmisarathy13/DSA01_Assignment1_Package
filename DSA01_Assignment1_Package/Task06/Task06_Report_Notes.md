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
