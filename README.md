# CSC 452/552 Operations Systems
# Project 2 The Classic Bounded Buffer Problem
## Name: Caitlyn Nelson
## Bronco ID: 114108964
## Date:10/19/2024

# 1. Project Overview

We implemented a FIFO queue as a monitor that can be used to solve the bounded buffer problem. My queue will has a fixed capacity and blocks calling threads when it is full or empty. 

The Learning Outcomes that applly are below:

Apply computer science theory and software development fundamentals to produce computing-based solutions (ABET Outcome 6).
Use pthreads to implement monitor.

# 2. Project Management Plan
    a. Task 1 - Setup and Prepare the Repository: Initialize the repository that was to be used. I had to copy and clone the repository for myself and then intialize all the starter code that was needed by copying the documentation and code from the given lab.h and main.c and test-lab.c.
    b. Task 2 - Implement the header file lab.h in lab.c: Before I began writing any code, I wrote out all the psuedocode for my project. This took me a couple hours however, I found that this solidified my understanding of how main.c was working with the lab.h and lab.c. It also gave me a deeper understanding of what I was expected to create behind the scenes to make this code work. 
    c. Task 3 - Read the pthread documentation: Took a deep dive into the documentation to make sure that I understood what each function call was doing and how it was doing what its preposed purpose is.
    d. Task 4 - Coded Queue Struct: Here I initialized my struct. I created the components consisting of an array of pointers, max capacity, size, two queue conditional variables, queue lock, and a shutdown flag.
    e. Task 5 - Implemented queue_init function: Here I was able to create the new queue and allocate the memory that was needed. Afterwards, I instantiated and initialized all variables to their starting values.
    f. Task 6 - Implemented queue_destroy: All that was necessary here was to free the allocated memory for the array of pointers and the queue struct itself.
    g. Task 7 - Implemented enqueue: For the start of this, I locked and unlocked the queue lock so that I wouldn't forget this step. Then I wrote the conditional if statements, one -> (if size = capacity and shutdown = false) and two -> (if shutdown = true). Then, the rest is just adding the data to the queue. Also, broadcasting at the end making sure if anything waiting would be woken up.
    h. Task 8 - Implemented dequeue: For the start of this, I locked and unlocked the queue lock so that I wouldn't forget this step. Then I wrote the conditional if statements, one -> (if size = 0 and shutdown = false) and two -> (if shutdown = true and size = 0). Then, the rest is just removing from the queue and sending the removed data variable back.Also, broadcasting at the end making sure if anything waiting would be woken up.
    i. Task 9 - Implemented shutdown: For the start of this, I locked and unlocked the queue lock so that I wouldn't forget this step. Then change the shutdown variable to true and broadcast to both consumers and producers.
    j. Task 10 - Implemented is_empty: For the start of this, I locked and unlocked the queue lock so that I wouldn't forget this step. Then I check if the queue is empty and change the variable based on what I find and then return.
    k. Task 11 - Implemented is_shutdown: Implemented is_empty: For the start of this, I locked and unlocked the queue lock so that I wouldn't forget this step. Then I check if the shutdown flag is true and then return based upon what I find.
    l. Task 12 - Fix bugs and make sure that the code works as expected.
    
# 3. Project Deliveries
    a. How to compile and use my code?
    To compile this code run the command 'make clean' -> 'make'
    To run the first program after make has been run -> './myprogram' (Program runs and passes)
    To run the second program after the make has been run -> './myprogram (Program runs and passes)
    To run the test-lab file after make has been run -> './test-lab' (All tests pass)

    b. Any self-modification?
    There are no self-modifications present within this code except print statements utilized when I was debugging to figure out why my program was hanging itself.

    c. Summary of Results.
    When the test-lab.c is run my code runs all the neccessary tests for the queue and passes all 4 with no memory leaks or issues.z
    Results copied from terminal below:
        tests/test-lab.c:100:test_create_destroy:PASS
        tests/test-lab.c:101:test_queue_dequeue:PASS
        tests/test-lab.c:102:test_queue_dequeue_multiple:PASS
        tests/test-lab.c:103:test_queue_dequeue_shutdown:PASS

        -----------------------
        4 Tests 0 Failures 0 Ignored 
        OK

    When the ./myprogram is run my code runs completely and returns the expected output.
    Results copied from terminal below:
        Simulating 1 producers 1 consumers with 10 items per thread and a queue size of 5
        Creating 1 consumer threads
        Producer thread: 132775999960832 - producing 10 items
        Consumer thread: 132775991568128
        Producer thread: 132775999960832 - Done producing!
        Consumer Thread: 132775991568128 - Done consuming!
        Queue is empty:true
        Total produced:10
        Total consumed:10
        2.300049 10

    When the ./myprogram -c 3 -p 7 -i 100 -s 20 my code runs completely and returns the expected output.
    Results copied from terminal below:
        Simulating 7 producers 3 consumers with 14 items per thread and a queue size of 20
        Producer thread: 137023235028736 - producing 14 items
        Producer thread: 137023226636032 - producing 14 items
        Producer thread: 137023218243328 - producing 14 items
        Producer thread: 137023209850624 - producing 14 items
        Producer thread: 137023201457920 - producing 14 items
        Producer thread: 137023193065216 - producing 14 items
        Creating 3 consumer threads
        Producer thread: 137023184672512 - producing 14 items
        Consumer thread: 137023176279808
        Consumer thread: 137023167887104
        Producer thread: 137023235028736 - Done producing!
        Consumer thread: 137023159494400
        Producer thread: 137023218243328 - Done producing!
        Producer thread: 137023226636032 - Done producing!
        Producer thread: 137023209850624 - Done producing!
        Producer thread: 137023193065216 - Done producing!
        Producer thread: 137023184672512 - Done producing!
        Producer thread: 137023201457920 - Done producing!
        Consumer Thread: 137023159494400 - Done consuming!
        Consumer Thread: 137023167887104 - Done consuming!
        Consumer Thread: 137023176279808 - Done consuming!
        Queue is empty:true
        Total produced:98
        Total consumed:98
        7.251953 98

# 4. Self-Reflection of Project 2
Overall, I felt that this project went fairly smoothly and well for me this time around. I found that the concepts for this were clear and I had a pretty good baseline understanding of what was expected of me to create with this project. I also took a different approach in which I wrote the psuedocode first making sure that I understood its logic and what I was trying to do. This also let me dig into the documentation and figure out what each files purpose was before ever implementing a single line of code. Then I went from the psuedo code to writing out the lab.c which didn't take nearly as long as the first project since I understood it. I realized I have to create the struct for the queue and upon figuring out how to deal with the data pointers in order to store that data and return it later without type differences, I was able to implement most other components easily and without difficultly. Once I got the code completed I found that it worked, but would at time hang itself and other times get all the way through without problems. This took me a few days to resolve as one I had to figure out how to debug my code (lots of print statements) and then recognize what the true problem is. I did find that I hadn't deadlocked my code instead I wasn't broadcasting to producers and consumers in my shutdown call. I initially was only broadcasting to consumers. Afterwards, my code compiles and runs to fruision every time and works as expected. Overall, I am very proud of this project. My new approach worked very well and I am coming off of this project with a renewed sense of can do rather than unsure of what I learned. I am going to continue utilizing this strategy for the future projects and hope to do as well on those as this one!

# 5. Comments for Project 2 (optional)
This project went exceedingly better than project one. The hands on assistance at the beginning was really helpful as was the lectures that went along with teaching these concepts in detail and with coding examples.

# 6. Use of AI for debugging (optional)
None

# Makefile Project Template

Steps to configure, build, run, and test the project.

## Building

```bash
make
```

## Testing

```bash
make check
```

## Clean

```bash
make clean
```

## Install Dependencies

In order to use git send-mail you need to run the following command:

```bash
make install-deps
```

At first build all compiles and runs.
