# Minesweeper

Here's an explanation of the Minesweeper game implementation that you can add to your GitHub README file:

## Minesweeper Game Implementation

This C++ program implements the classic Minesweeper game, offering a command-line interface for players to enjoy this strategic puzzle game.

### Game Features

- **Multiple Difficulty Levels**: Players can choose from three difficulty levels:
  - Beginner: 9x9 grid with 10 mines
  - Intermediate: 16x16 grid with 40 mines
  - Advanced: 24x24 grid with 99 mines

- **Random Mine Placement**: Mines are randomly placed on the board at the start of each game.

- **Safe First Move**: The first move is always guaranteed to be safe. If a mine is randomly placed at the first selected position, it is moved to another location.

- **Recursive Revealing**: When a cell with no adjacent mines is revealed, all neighboring cells are automatically revealed, potentially triggering a chain reaction.

### Key Components

1. **Board Class**: Manages the game board, including mine placement and cell revealing.

2. **Game Class**: Handles the game logic, including player moves and win/lose conditions.

3. **Utility Functions**: 
   - `isValid()`: Checks if a given cell is within the board boundaries.
   - `countAdjacentMines()`: Counts the number of mines in adjacent cells.
   - `placeMines()`: Randomly places mines on the board.
   - `replaceMine()`: Moves a mine if it's placed on the first revealed cell.

### How to Play

1. Run the program and choose a difficulty level.
2. The game will display the current board state after each move.
3. Enter the coordinates of the cell you want to reveal.
4. Continue revealing cells until you either reveal all non-mine cells (win) or reveal a mine (lose).

### Code Structure

The code is organized into classes and functions for better modularity and readability:

```cpp
class Board {
    // Manages the game board
};

class Game {
    // Handles game logic
};

// Utility functions
bool isValid(int row, int col);
void chooseDifficultyLevel();
// ... other functions
```

This Minesweeper implementation provides a solid foundation for understanding game logic and can be extended with additional features for a more comprehensive gaming experience.
