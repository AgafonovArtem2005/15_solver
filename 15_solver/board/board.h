#pragma once

#include <array>
#include <istream>

namespace NBoard {

////////////////////////////////////////////////////////////////////////////////

constexpr int BoardSize = 3;

////////////////////////////////////////////////////////////////////////////////

enum EDirections : char {
    Right = 'R',
    Up = 'U',
    Left = 'L',
    Down = 'D'
};

////////////////////////////////////////////////////////////////////////////////

static EDirections AllDirections[] {
    EDirections::Right,
    EDirections::Up,
    EDirections::Left,
    EDirections::Down
};

////////////////////////////////////////////////////////////////////////////////

NBoard::EDirections InvertDirection(NBoard::EDirections direction);

////////////////////////////////////////////////////////////////////////////////

class TBoard
{
public:
    TBoard();

    explicit TBoard(std::array<std::array<int, BoardSize>, BoardSize> board);

    bool TryMove(NBoard::EDirections direction);

    bool IsSolved() const;

    const std::array<std::array<int, BoardSize>, BoardSize>& GetBoard() const;

    bool operator==(const TBoard& other) const;
    bool operator!=(const TBoard& other) const;

    struct TBoardHasher
    {
        size_t operator()(const TBoard& board) const;
    };

private:
    struct Position {
        int i;
        int j;
    };

    std::array<std::array<int, BoardSize>, BoardSize> Board_;
    Position Empty_;

    void Validate() const;

    void FindEmpty();
};

////////////////////////////////////////////////////////////////////////////////

std::istream& operator>>(
    std::istream& inputStream,
    TBoard& board);

std::ostream& operator<<(
    std::ostream& outputStream,
    const TBoard& board);

////////////////////////////////////////////////////////////////////////////////

} // namespace NBoard
