# 1D FDTD

This repository contains a C++ implementation of the 1-D
FDTD scheme requested in the exam, plus a Python visualizer.

## Layout
include/
  fdtd.hpp
src/
  fdtd.cpp
  fdtd.h
Makefile
main.cpp
python/
  sim_fdtd.py
docs/
  method.pdf
trials/
  (directories containing trials for different parameters, and testing vanishing boundary conditions)
README.md

The `src/fdtd.h` file only includes the public header to match the rubric's path
layout.

## Build

```bash
make clean && make

## Execution

The compiled binary accepts three positional arguments. In order:
Nz, time steps, boundary conditions (periodic, which is the default or pec,
perfect electric conductor).

Make sure to delete all previously generated csv files before running the code again.

## Trials

All the trials presented in this work were obtained by fixing the number of
spatial divisions as 200, and varying dt to obtained the desired beta ratio. The trial marked as pec is executed with vanishing boundary conditions.
