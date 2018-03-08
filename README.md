# Reusable C Software Library
A highly flexible, and also (relatively) high performance C of a C version of
the C++ STL. Unless otherwise stated, everything in here is for programming on a
Linux platform (it might work on Windows, but I haven't tested it even a little
bit).

## Basic Setup

Before starting, you will need a recent version of the following programs:

- cmake
- make
- gcc

### Pre-cloning
1. Set up an ssh key for password-less connection to github (this is for the
   cmake config). Yes I know that it can be done without ssh, but I set it up
   this way so I don't have to type my github password ever.

### Post-cloning
After cloning this repo, you will need to:

1. Pull in the cmake config:

        git submodule update --init --recursive

Then you can build via:

    mkdir build && cd build
    cmake ..
    make

# Modules Summary
RCSW is built around the idea of modules to help organize the code, and to
provide logical segmentation between (un)complementary areas of
functionality. Full details of modules is in the documentation, which can be
built with `make documentation`. Only a brief summary is given here.

Most modules come with at least a cursory test suite to provide sanity checks,
though many have thorough suites. Test suites also serve as example usages.

## Data Structures

A general, yet highly performant data structures library. It highly run-time
configurable, in the sense that the memory used by the data structure handle,
the elements the data structure will manage/contain, and structure metadata can
be independently provided by the calling application, or malloc()ed by the
library.

The data structures library is comprised of the following modules:

- Ringbuffer.
- Linked list.
- FIFO (built on ringbuffer).
- Raw FIFO (only handles 1, 2, or 4 byte elements). Uses only pointer math when
  adding/removing elements, instead of memcpy()/function calls, so is ISR safe.
- Dynamic array (just like std::vector; grows/shrinks as needed). Uses approach
  in *Introduction To Algorithms*.
- Binary Search Tree (uses approach in *Introduction To Algorithms*.
- Red-Black tree (uses approach in *Introduction To Algorithms*).
- Order Statistics Tree (built on RB-Tree; uses approach in *Introduction To Algorithms*).
- Interval Tree (built on RB-Tree; uses approach in *Introduction To Algorithms*).
- Hashmap (built using linked lists and dynamic arrays).
- Binary heap (built using dynamic array).
- Static Adjacency Matrix.
- Dynamic Adjacency Matrix (in progress).
- Adjacency List (in progress).
- Compressed Sparse Matrix (in progress).

## Algorithm
A general purpose, yet highly performant set of *serial* algorithms. Includes:

- String parenthesization: Can a string be parenthesized to result in another
  string under the rules of some multiplicative paradigm?
- Edit Distance: How close are two contiguous sequences of characters, numbers,
  structs, etc. to each other, according to some measure?
- Longest Common Subsequence: What is the longest common subsequence of two
  sequences of objects?
- Matrix Chain Optimization: What is the most efficient way to multiply a
  sequence of matrices?
- Binary Search (recursive and iterative).
- Quicksort (recursive and iterative).
- Mergesort (recursive and iterative).
- Insertion sort.
- Radix sort.

## Multithread
A collection of modules for programming in multithreaded environments (obviously
all thread safe). Full documentation is in. The wrappers around POSIX primitives
may seem uncessary, but I wanted to leave the ability to program on embedded
platforms where POSIX might not be available, and retain the ability to use a
single extensible interface.

- Memory pool: Used by threads to request/release memory chunks of a specified
  size. Useful in publisher-subscriber settings.
- Binary semaphore: Linux doesn't have one of these natively, so I built one out
  of a mutex and cv.
- Condition variable: Wrapper around POSIX condition variables.
- Counting semaphore: Wrapper around POSIX semaphores.
- mutex: Wrapper around POSIX mutexes.
- Condition variable/mutex pair (cvm): A single interface for using both, as
  they are frequently used together.
- Queue: Producer-consumer queue.
- Reader/Writer lock: A completely fair lock that guarantees that neither
  readers nor writers will starve.
- OpenMP implementations of 2D kernel convolution, radix sort.
- Various thread management tools like locking threads to a particular core.

## Multiprocess
A collection of modules for managing multi-process applications, as well as a
few simple-ish MPI routines I've written for various classes.

## Simple I/O
A re-implementation of the libc routines needed to make printf() work

I originally did this as a programming exercise, but have found it very useful
for debugging in bare metal/embedded environments when libc is not available
(i.e. bootstraps).

## Utils
A miscellaneous collection of functions and macros that I found useful at one
time or another, but that did not warrant their own module. Full documentation
is in utils. Includes:

- 8, 16 32 bit additive and XOR checksums
- Common hashing functions
- Memory manipulation (i.e. read-modify-write with verify)
- Timespec comparison/addition/etc.
- Random other things :-P

## PULSE
A PUbLisher SubscribEr system, in which any number of
tasks/threads/processes/etc. can send arbitrarily sized packets to each other
using a distributed FIFO system. There is no centralized controller, meaning
each publishing thread does the work of its publish().

# Style
I have tried to code this library according to google C++ style, ignoring the
C++ specific bits, and also the stuff I think is dumb.

# License
This project is licensed under GPL 2.0. See [LICENSE](LICENSE).

# Donate
If you've found this project helpful, please consider donating somewhere between
a cup of coffe and a nice meal:

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.me/jharwell1406)
