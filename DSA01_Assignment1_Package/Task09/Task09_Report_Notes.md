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
