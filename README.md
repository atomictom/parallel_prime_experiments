parallel_prime_experiments
==========================

A repository for me to play around with making a fast parallel prime finding program

What it does
------------

The program can find primes up to 10^9, and can do so in just a few seconds. Currently, I'm working to improve the speed and eventually unbound it (using segmented sieving). It started as a homework assignment to find all the primes up to 10^8 using 8 threads and sharing the work as equally as possible between threads.

It works using the Sieve of Eratosthenes with a number of optimizations. Currently it tests not with primes, but with numbers co-prime to a given "wheel" (wheel optimization). This is something I want to change.

Currently it only finds the number and sum of the primes, and prints the last 10. Though, it is trivially simple to have it print all the primes found.

Compiling
---------

Just use the Makefile to compile (you need gcc and pthreads).

Current Optimizations
---------------------

It currently uses the following optimizations:

  * Uses any number of threads (configurable using a #define)
  * Wheel optimization (skip numbers not co-prime to the first 'n' primes, with n up to 7, using a static array)
  * An cache for skipping through the wheel multiple times (since each thread skips through NUM_THREAD times)
  * Bitset (a custom, thread safe, bit set to reduce memory usage by a factor of 8)
  * Sieving from the square of the candidate number to the square root of the upper bound

At the time of writing, all of these optimizations are customizable using #defines at the top of the parallel_primes_with_options.c file. I've removed some of the switches from the main .c file to reduce clutter.

Planned Optimizations
---------------------

These are some of the optimizations I plan on doing in the future:
  
  * Make the sieve segmented (each thread works on a different segment)
  * Work to keep the wheel and the segments for each thread inside either the L1 or at least L2-3 caches
  * Only store the values that are being tested (co-prime to the wheel) (or at least the odd numbers only)
  * Only use primes for the sieving
  * Allow threads that finish sieving to start counting/summing before all threads finish (not using a barrier)
  * Making a list of the primes in parallel (might not be useful if printing is the bottleneck here)
  * A way to skip sieving with primes in a segment where they have no multiples
   
Using cachegrind (part of valgrind), I know that currently a large chunk of all reads and writes are L1 cache misses, and a good chunk of those miss even the L3 cache. I hope to keep each segment being sieved inside the L1 cache as is done with [primesieve](http://primesieve.org/).

I'm not sure if there's an easy way to only store values that are coprime to a wheel of arbitrary length (it's not too hard if you're only storing odd numbers, but I'm not sure it scales), but if so, that should cut storage by anywhere from 50% to 90% depending on the wheel size.

Other
-----
There's also a file, 'wheel_gen.c', that can be compiled and used to create static arrays for the wheel optimization used in the main program (arrays where if you start with the first prime after the last prime in the wheel, and add each number in the wheel array in order, looping back when you get to the end, allow you to skip all numbers co-prime to the primes in the wheel). I've already added static arrays for wheels up to length 7 (which is why the program is around 6000 lines long), but you can use it to make longer wheels for fun, or just to see how it works.
