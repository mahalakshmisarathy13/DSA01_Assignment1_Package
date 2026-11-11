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
