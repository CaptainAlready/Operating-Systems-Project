# Operating-Systems-Project

This repo contains code written in c for the undergraduate course of CEID "Operating Systems".
The .c files contain code which is parellized through the use of processes in favour of performance.

You can find what each .c file does below:

* <h2 style ="font-size: 0.5em">Bakery.c</h2>
An implementation of the Lamport - Bakery algorithm using c-processes to achieve mutual exclusion of those processes.
More on that algorithm : https://www.geeksforgeeks.org/bakery-algorithm-in-process-synchronization/

* <h2 style ="font-size: 0.5em">B+treeshared.c</h2>
An implementation of a B+ tree which is shared among the processes using shared memory segments to achieve inter-processes communication without the loss of information.

* <h2 style ="font-size: 0.5em">Smokers.c</h2>
The famous Cigrarettes Smoker's Problem solved through inter-proccess communication and semaphores.
More on that akgorithm : https://www.cs.umd.edu/~hollings/cs412/s96/synch/smokers.html

<p align="center">
<a>
  <img src="https://github.com/CaptainAlready/Operating-Systems-Project/blob/main/exampleB%2BTreeShared.png" width="300" height="250">
</a> 
  <br>
  Example of Shared B+ Tree function <br>
  which adds all the leaf-values and <br>
  stores them in a pointer *p
  </p> 

