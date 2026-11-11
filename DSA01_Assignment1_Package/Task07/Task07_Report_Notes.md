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
