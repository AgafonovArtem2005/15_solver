#include "board.h"

#include <cassert>
#include <ostream>
#include <stdexcept>

namespace NBoard {

////////////////////////////////////////////////////////////////////////////////

TBoard::TBoard()
{
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            Board_[i][j] = i * BoardSize + j + 1;
        }
    }

    Board_[BoardSize - 1][BoardSize - 1] = 0;
    Empty_ = {
        .i = BoardSize - 1,
        .j = BoardSize - 1
    };
}

TBoard::TBoard(std::array<std::array<int, BoardSize>, BoardSize> board)
    : Board_(board)
{
    Validate();
    FindEmpty();
}

bool TBoard::TryMove(NBoard::EDirections direction)
{
    switch (direction) {
        case NBoard::EDirections::Right:
            if (Empty_.j + 1 < BoardSize) {
                std::swap(Board_[Empty_.i][Empty_.j], Board_[Empty_.i][Empty_.j + 1]);
                ++Empty_.j;
                return true;
            }
            break;
        
        case NBoard::EDirections::Up:
            if (Empty_.i > 0) {
                std::swap(Board_[Empty_.i][Empty_.j], Board_[Empty_.i - 1][Empty_.j]);
                --Empty_.i;
                return true;
            }
            break;

        case NBoard::EDirections::Left:
            if (Empty_.j > 0) {
                std::swap(Board_[Empty_.i][Empty_.j], Board_[Empty_.i][Empty_.j - 1]);
                --Empty_.j;
                return true;
            }
            break;

        case NBoard::EDirections::Down:
            if (Empty_.i + 1 < BoardSize) {
                std::swap(Board_[Empty_.i][Empty_.j], Board_[Empty_.i + 1][Empty_.j]);
                ++Empty_.i;
                return true;
            }
            break;
    }

    return false;
}

bool TBoard::IsSolved() const
{
    if (Empty_.i != BoardSize - 1 || Empty_.j != BoardSize - 1) {
        return false;
    }

    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (Board_[i][j] != i * BoardSize + j + 1) {
                return i == BoardSize - 1 && j == BoardSize - 1;
            }
        }
    }

    // We should never reach this line.
    assert(false);
}

const std::array<std::array<int, BoardSize>, BoardSize>& TBoard::GetBoard() const
{
    return Board_;
}

bool TBoard::operator==(const TBoard& other) const
{
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (Board_[i][j] != other.Board_[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void TBoard::Validate() const
{
    std::array<bool, BoardSize * BoardSize> usedTiles;
    usedTiles.fill(false);
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (Board_[i][j] < 0 || Board_[i][j] >= BoardSize * BoardSize) {
                throw std::invalid_argument("Failed to validate board; Tile " + std::to_string(Board_[i][j]) + " is not permitted");
            }

            if (usedTiles[Board_[i][j]]) {
                throw std::invalid_argument("Failed to validate board; Tile " + std::to_string(Board_[i][j]) + " is dublicated");
            }

            usedTiles[Board_[i][j]] = true;
        }
    }
}

void TBoard::FindEmpty()
{
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (Board_[i][j] == 0) {
                Empty_ = {
                    .i = i,
                    .j = i
                };
                return;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

size_t TBoard::TBoardHasher::operator()(const TBoard& board) const
{
    size_t hash = 0;
    std::array<bool, BoardSize * BoardSize> used;
    used.fill(true);
    size_t factorial = 1;
    size_t current = 1;
    for (int i = BoardSize - 1; i >= 0; i--) {
        for (int j = BoardSize - 1; j >= 0; j--) {
            size_t counter = 0;
            for (size_t x = 0; x < board.Board_[i][j]; x++) {
                if (!used[x]) {
                    ++counter;
                }
            }

            hash += counter * factorial;
            factorial *= current;
            ++current;
        }
    }

    return hash;
}

////////////////////////////////////////////////////////////////////////////////

std::istream& operator>>(
    std::istream& inputStream,
    TBoard& board)
{
    std::array<std::array<int, BoardSize>, BoardSize> holder;
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            if (!(inputStream >> holder[i][j])) {
                throw std::invalid_argument("Failed to read the board; Not enough input was provided");
            }
        }
    }

    board = TBoard(std::move(holder));
    return inputStream;
}

std::ostream& operator<<(
    std::ostream& outputStream,
    const TBoard& board)
{
    const auto& holder = board.GetBoard();
    for (int i = 0; i < BoardSize; i++) {
        for (int j = 0; j < BoardSize; j++) {
            outputStream << holder[i][j];
            if (j != BoardSize - 1) {
                outputStream << " ";
            }
        }

        if (i != BoardSize - 1) {
            outputStream << "\n";
        }
    }

    return outputStream;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace NBoard
