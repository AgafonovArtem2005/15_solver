## How to build

    mkdir build
    cd build
    cmake ..
    make 15_solver

## How to run

    ./build/15_solver/15_solver

Then you can provide a 3x3 board for solving. Input 9 digits separated by spaces. The empty tile should be marked with 0. For example:

    4 1 3
    2 8 5
    0 7 6

In return, you will receive instructions on how to solve the puzzle, or a message indicating that the solution does not exist.
