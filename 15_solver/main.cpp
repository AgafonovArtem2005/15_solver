#include "solver/solver.h"

#include <iostream>

using namespace NBoard;
using namespace NSolver;

int main() {
    TBoard board;
    std::cin >> board;
    auto solver = CreateBfsSolver();
    std::cout << solver->Solve(std::move(board)) << "\n";
    return 0;
}
