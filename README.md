# Traveler

A small maze-solving program written in pure C.

## Overview

Traveler finds a path through a maze from a starting point to a destination.

The project was created as a small exercise in algorithm design and low-level programming using only C.

## Build and tests

* build: `cmake -B build` and `cmake --build build`
* run tests: `ctest --test-dir build`

## Example

```text
###########
#S#       #
# # ##### #
# #     # #
# ##### # #
#       #E#
###########
```

`S` — start
`E` — destination
`#` — wall
