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

## Building project 

Use `make build` to build the project with ccplinter check. Note that any warning genrated by cppling will result in Makefile finishing with Error 1

Use `make debug` to build the project with debugging support (debug loging and generating binary with debug symbols)

The executable should be created as `build/osh`

## Project's status

As of 22th July 2024
- Finished the part supported by the tutorial, now the advneture begins
- Currently thinking about following non-functional improvements:
  * Improving Makefile to introduce compiling to objects and then linking to shorten compilation (it doesn't take long yet though)
  * Implementing unit tests
  * Refractoring parts of the code to implement more debug messages and fixing functions names
- Currently thinking about following functional improvements:
  * Correctly recognizing parentheses for whitespace termination
  * Implementing detection of special keys (arrows, TAB, CTRL+C, CTRL+D)
  * Adding commands history
  * Playing with ASCII control characters
