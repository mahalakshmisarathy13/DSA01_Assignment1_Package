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
