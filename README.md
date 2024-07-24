# osh - Obnoxious SHell

A hobbyist project for practice of C and practical accustomization with inner workings of shells, terminal and potentially other aspects of Linux OS. Inspired by [Stephen Brennan's Tutorial](https://brennan.io/2015/01/16/write-a-shell-in-c/). As creating a shell even comparably useful to mainstream programs is way above the skills of the repo's owner, the goal is instead to have fun with creating as obnoxious shell as possible while still keeping it useable.

## Table of Content
- [Requirements](#requirements)
- [Building project](#building-project)
- [Project's status](#project-s-status)

## Requirements
- Linux environment
- GCC (developed with version 13.3.1, minmal supported version not tested)
- Make (developed with version 3.3.1, minimal supported version not tested)
### Optional
- Cpplint (developed with 1.6.1) 

## Building project 

Use `make build` to build the project with ccplinter check. Note that any warning genrated by cppling will result in Makefile finishing with Error 1

Use `make debug` to build the project with debugging support (debug loging and generating binary with debug symbols)

The executable should be created as `build/osh`

## Project's status

As of 24th July 2024
- Implemented basic history features, hooray!  
- Added bunch of issues, mostly as my own notes and ideas, as it's helpful to put your thoughts in words like you were trying to explain it to someone else. May add contribution rules if there will be any interest with the issues, but not anticipating such.
- Currently thinking about following non-functional improvements:
  * Improving Makefile to introduce compiling to objects and then linking to shorten compilation (it doesn't take long yet though)
  * Implementing unit tests
  * Refractoring parts of the code to implement more debug messages and fixing functions names
- Currently thinking about following functional improvements:
  * Correctly recognizing parentheses for whitespace termination
  * Globbing
  * Implementing detection of special keys (arrows, TAB, CTRL+C, CTRL+D)
  * Playing with ASCII control characters
