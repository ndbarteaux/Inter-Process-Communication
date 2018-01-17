# Inter-Process-Communication 
Project for my Operating Systems class.

README
======

This package includes the following files.

|-- Coordinator.c [Parent process (takes 5 arguments), sets up pipe and shared memory, uses fork() and execlp() to spawn child processes. Waits for all process before continuing and reads result from shared memory] The Coordinator will take a total of five command line arguments and selectively pass them on to the Checker. The first argument is the divisor, followed by the dividends.

|-- Checker.c [Child process (recieves 3 arguments from Coordinator, including read end of pipe), reads shared memory ID from pipe, determines if two args are divisble, writes result to shared memory]

|-- README.txt [This file]

|-- Makefile [Used to compile and produce an executable]

To compile:
    make

To clean:
    make clean
    
To run:
    ./Coordinator [args]

For example;
    ./Coordinator 3 3 20 49 102
