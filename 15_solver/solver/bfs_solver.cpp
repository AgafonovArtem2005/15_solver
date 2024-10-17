#include "solver.h"

#include <algorithm>
#include <cassert>
#include <queue>
#include <unordered_map>

namespace NSolver {

using namespace NBoard;

////////////////////////////////////////////////////////////////////////////////

class TBfsSolver
    : public ISolver
{
public:
    std::string Solve(TBoard startingBoard) const override
    {
        if (startingBoard.IsSolved()) {
            return "Already solved!";
        }

        std::unordered_map<TBoard, NBoard::EDirections, TBoard::TBoardHasher> backtrace;
        std::queue<TBoard> queue;

        backtrace[startingBoard] = NBoard::EDirections::Right;
        queue.push(startingBoard);

        bool solved = false;
        while (!queue.empty() && !solved) {
            auto& current_board = queue.front();
            for (auto direction : AllDirections) {
                TBoard next_board = current_board;
                if (!next_board.TryMove(direction) || backtrace.find(next_board) != backtrace.end()) {
                    continue;
                }

                backtrace[next_board] = direction;
                if (next_board.IsSolved()) {
                    solved = true;
                    break;
                }

                queue.push(std::move(next_board));
            }
            
            queue.pop();
        }

        if (!solved) {
            return "Unsolvable!";
        }

        std::string solution;
        TBoard board = TBoard();
        assert(board.IsSolved());

        while (board != startingBoard) {
            auto direction = backtrace[board];
            solution += direction;
            board.TryMove(InvertDirection(direction));
        }

        std::reverse(solution.begin(), solution.end());
        return solution;
    }
};

////////////////////////////////////////////////////////////////////////////////

std::unique_ptr<ISolver> CreateBfsSolver()
{
    return std::make_unique<TBfsSolver>();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace NSolver
