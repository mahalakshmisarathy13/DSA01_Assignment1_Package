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
