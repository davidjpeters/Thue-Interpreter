### Thue Interpreter
A simple Thue interpreter written in C++

---
You can find more information on Thue here:
https://esolangs.org/wiki/Thue

---
Thue consists of a set of rules at the start of your program of the form

lhs::=rhs

The ::= symbol on a line by itself indicates the end of the ruleset

Followed by some string, which will be used as the input string

---
```
a::=Hello, World!
::=
a
```
Would output "Hello, World!"

---
Rules are applied non-deterministically, meaning given the following code:
```
x::=1
x::=0
::=
xxx
```
Any of the valid rules may be applied to the input string, to anywhere the lhs of the rule is found. That is:

1xx, x1x, xx1, 0xx, x0x, and xx0 are all equally likely to be the first change made


---
Compile the program and run with:
```
./<executable name> <filename>
```
