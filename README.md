# Mentor Assignment Problem



This project implements and compares two approaches for assigning students to mentors based on ranked preferences.



## Implemented Approaches



- Gale–Shapley Stable Matching

- Greedy Assignment Algorithm



The goal is to match students with mentors while considering the preference lists of both sides.



## Files



- `gale_shapley.cpp` — implementation of the Gale–Shapley stable matching algorithm

- `greedy_algorithm.cpp` — implementation of a greedy assignment strategy



## Problem Setup



The project uses sample hardcoded input data for:

- students and their mentor preferences

- mentors and their student preferences



Each mentor has one available slot.



## How to Compile and Run



### Gale–Shapley



g++ gale_shapley.cpp -o gale_shapley

./gale_shapley

g++ greedy_algorithm.cpp -o greedy_algorithm

./greedy\_algorithm

