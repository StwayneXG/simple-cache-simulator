# Simple Cache Simulator

## Overview

In this project, we explore the effectiveness of caches and the impact of different cache configurations. For this we wrote a C program that simulates the behaviour of cache. The cache simulator will be configurable.

The cache simulator will take as input a memory trace, which is essentially a list of memory accesses that occurred in a program. We will use this single memory trace to evaluate cache accesses, cache hits, cache misses, and cache hit ratio and cache miss ratio.

## Aims and Objectives

The aim of this project is to design and implement a cache simulator in C language. The objectives of this project are:

* To understand the basics of computer organization and memory hierarchy
* To learn about cache architecture and its design parameters
* To simulate a cache memory system using a C program
* To analyze cache performance based on cache hit and miss rates

## Cache Configuration

The cache configuration consists of the following design parameters:

* Number of offset bits
* Number of index bits
* Number of tag bits
* Number of cache sets
* Associativity (number of cache lines per set)

## Output

Scan the ```MemoryTrace.txt``` file and report the following:

* Number of hits
* Number of misses
* Hit rate
* Miss rate

## How to run

```bash
$ gcc -o main main.c
$ ./main
```

## License
Distributed under the MIT License. See ```LICENSE``` for more information.
