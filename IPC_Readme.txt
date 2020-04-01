Made by - Satvik Sharma
Last Modified on - 1st April 2020

                                                    IPC Mechanism

Need - (i)If a process needs to co-ordinate
       (ii)If a process nedds to communicate or syncronize


                            Form of IPC Mechanism
                                     |
                                     |
                      ----------------------------------
                      |                                |
                      |                                |
                   Conventional                   Unconventional
                   -Process to Process            -Process to Device-Driver
                   -Thread to thread              -Device-Driver to process
                                                  -Thread to Device-Driver
                                                  -Device Driver to Thread
Note: In this discussion we will omly consider Convention Mechanism.

Types of IPC Mechanism-
1.Message Queue
2.Pipes
3.Signal
4.Shared Memory 
5.Semaphpres
6.Mutex

In this repo we will be programming each of these IPC Mechanism in detail.

->Approprite system calls are used to implement each of these mechanism, 
  each IPC Mechanism has its own set of system calls.

Lets us first understand Process and threads and how these two resides in OS.

PROCESS
-------
->An active instance of of an application/program is a process in an operating system.
->Process control block or Process descriptor is the object that is used to manage process
 in the system.
->There is one process decriptor per process.
->Each process also has assigned unique process ID(pid) maintained in it's process descriptor.
->As Linux Kernel has two mode that is user-space & kernel space respectively, a process
 can also be understood in either of these perspective, we will see both in following discussion.

USER-SPACE PERSPECTIVE
->At the address space of a process there is a process layout in user-space.
->This address space is made up of logical addresses or virtual address(physical address)
[This area of discussion is out of the scope of this document as another OS concept VIRTUAL MEMORY MANGMENT is responsible for this handling]
->Address space is further divided into differnet part,
  one part manages code,
  another manages data,
  yet another manages stack.
  and another one that manages heap.

KERNAL-SPACE PERSPECTIVE
->A newly created process is added to the ready state.
  i.e state is changed to ready and process descriptor(pd) is added to ready queue.
->ready queue is the queue where processes that are ready to execute are maintained.
->Schedular scans the ready queue and selects the process on the bases of an event or time sharing.
->If a process is selected by the schedular it's state is changes to running.
->If a running process request for a logical or physical rescource and corresponding resource 
  is temporairly unavailabe then the process is changed to blocking/waiting state.
  Once the resource is again available it goes to ready state again.
->If the process terminates normally or abnormally it enters the terminated state
  where all resources allocated to the processes are freed pd and pid are also freed.
 
THREAD
------






Ideally process can not communicate with each other, they are unable to access each other's private data-segements.

1.Message Queue IPC Mechanism
->Each message queue IPC Mechanism is represneted and managed using a system object.
->This queue object maintaines a queue of messages - these are kernel buffers which contains
  process/application data to be exchanged.
->The queue object also contains a wait queue (wq) for implicit co-oridnation and
  synchronization of process, during exchange of data.
->Asynchronous mechanism is supported by message queue, meaning two or more process
  can communicate with a message queue.
->Process can send-recieve data to-from the message queue at any time independent of other process

Critical Cases in Message Queue Mechanism
1.If sender sends the message before the reciver is ready for reciving.

  In this case the messgae from the sender will be copied into the message queue object's buffer(s)
  and queued, in the message queue object

2.If receiver attempts to recive a message, before a sender has requested

  In this case reciver process will be blocked in the wait queue(wq) of the respective message
  queue and the schedular will invoked when there is new arrival of message, the reciver process
  will unlocked and added to the schedular, when scheduled the reciver will copy the message from
  the queue.

->Message queue can be uni-directional or bi-directional
  object's message queue










