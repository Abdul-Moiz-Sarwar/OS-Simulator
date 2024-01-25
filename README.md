# Operating System Simulator

This project involves the development of an operating system simulator, leveraging the concepts of operating systems studied during the course. The simulator encompasses various functionalities, including CPU scheduling, semaphore implementation for the Dining Philosopher Problem, deadlock avoidance using the Banker's Algorithm, memory management, and page replacement.

## CPU Scheduling

### Multilevel Queue Scheduling
- Three queues implementing different scheduling algorithms: Priority Scheduling, Round Robin (RR), and Shortest Remaining Job First (SRJF).
  
### Multilevel Feedback Queue Scheduling
- Dynamic movement of processes between queues with aging implementation.
- Three queues employing FCFS, Shortest Job First (SJF), and RR for scheduling.

### Additional Scheduling Algorithms
- Longest Job First
- Lowest Feedback Ratio Next Scheduling

## Dining Philosopher Problem
Implement a solution for the classic Dining Philosopher Problem using semaphores. This problem involves philosophers sitting at a round table, alternating between thinking and eating. Semaphores ensure a deadlock-free and starvation-free scenario.

## Deadlock Avoidance

### Banker's Algorithm
An algorithm designed to avoid deadlock and allocate resources safely to each process in the computer system. It simulates resource allocation similar to a banking system approving loans based on available resources.

## Memory Management

### Two-Level Page-Table Scheme
Implementation of a two-level page-table scheme for efficient memory management.

### Hashed Page Table with TLB
Utilization of hashed page table with Translation Lookaside Buffer (TLB) for improved memory access.

## Page Replacement

### Second Chance Algorithm
Implementation of the Second Chance Algorithm using a circular linked list. Calculation of page faults, page fault probability, and page fault percentage using this algorithm.

## How to Run
The project can be run on ubuntu using generic compilation command.

Feel free to explore the code.
