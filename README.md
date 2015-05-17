## Synopsis
As per wikipedia , in probability theory, the birthday problem or birthday paradox concerns the probability that, 
in a set of n randomly chosen people, some pair of them will have the same birthday. 
By the pigeonhole principle, the probability reaches 100% when the number of people reaches 367
(since there are 366 possible birthdays, including February 29). However, 99.9% probability is reached with 
just 70 people, and 50% probability with 23 people.

## Motivation
While studying Think Python - an excellent book by Allen B. Downey , I came across this problem in one of the exercises. I thought it will be a good reason to learn up gnuplot and threadpools.

##Code
There a four classes

BirthdayParadox 
- Takes a set of population with their sample size , generates random numbers and checks how many duplicates are present in each sample.
- The code that does this is passed as a Work object and added to the ThreadPool queue. 

ThreadPool 
- Has multiple threads pick up Work from queue and execute them

Work
- A piece of code that is pushed into ThreadPool queue and uses a callback function to update the output.

GnuPlotter
- writes plot commands and csv input


##Tests
Tests were done with Google test.

To run
```bash
mkdir build
cmake ..
make clean && make
./test
```
