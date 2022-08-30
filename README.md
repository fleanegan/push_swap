# push_swap 
This is a project of the cursus of ecole 42. 
The goal is to write an algorithm which sorts a list of numbers on two stacks with the operations rotate(ra for first stack, rb for second stack, rr for both), reverse_rotate(rra, rrb, rrr), push(pa, pb) and swap (sa, sb, ss for both). 
Build it like so:
```
make all
```
And run it like this:
```
./src/push_swap 0 1 2 3 5 6 4
```
The program will output the performed actions

# Tests
The code is unit tested using the test framework criterion (https://github.com/Snaipe/Criterion). A minimal installation can be done by:
```
wget https://github.com/Snaipe/Criterion/releases/download/v2.3.3/criterion-v2.3.3-linux-x86_64.tar.bz2
tar -xf criterion-v2.3.3-linux-x86_64.tar.bz2
rm criterion-v2.3.3-linux-x86_64.tar.bz2
```
Then, the test suite can be run with 
```
make run_tests
```
