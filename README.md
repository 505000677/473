# CMPSC473 PA1

Only prog3/Makefile and prog4/prog4.c are modified.

In prog3/Makefile, it didn't build seperate programs for 32/64 bits, so it is modified similarly to prog2/Makefile.
In prog4/prog4.c, we are asked to use `getrusage` to retreive some runtime information. We calculated the system and user CPU time by a subtraction.

To clean all executables, run `./clean.sh` at the root directory of the project.
