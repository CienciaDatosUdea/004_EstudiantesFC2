# 1D FDTD

This repository contains a minimal but complete C++ implementation of the 1-D
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
README.md

The `src/fdtd.h` file only includes the public header to match the rubric's path
layout.

## Build

```bash
make
