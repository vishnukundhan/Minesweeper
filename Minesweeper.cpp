// C++ Program for Implementation of Minesweeper Game: Input
// for coordinates is taken from user
#include <bits/stdc++.h>
using namespace std;

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526 // (25 * 25 - 99)

int SIDE;  // side length of the board
int MINES; // number of mines on the board

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not
bool isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE);
}

class Board
{

public:
    char **board;
    Board()
    {
        board = new char *[MAXSIDE + 1];
        for (int i = 0; i <= MAXSIDE; i++)
        {
            board[i] = new char[MAXSIDE + 1];
            for (int j = 0; j <= MAXSIDE; j++)
            {
                board[i][j] = '-';
            }
        }
    }

    // A Utility Function to check whether given cell (row,
    // col) has a mine or not.
    bool isMine(int row, int col)
    {
        if (board[row][col] == '*')
            return (true);
        else
            return (false);
    }

    void makeMove(int *x, int *y, int moves[][2],
                  int currentMoveIndex)
    {
        *x = moves[currentMoveIndex][0];
        *y = moves[currentMoveIndex][1];

        printf("\nMy move is (%d, %d)\n", *x, *y);

        /*
        // The above moves are pre-defined
        // If you want to make your own move
        // then uncomment this section and comment
        // the above section

          scanf("%d %d", x, y);
        */
        return;
    }

    // A Function to randomly assign moves
    void assignMoves(int moves[][2], int movesLeft)
    {
        bool mark[MAXSIDE * MAXSIDE];

        memset(mark, false, sizeof(mark));

        // Continue until all moves are assigned.
        for (int i = 0; i < movesLeft;)
        {
            int random = rand() % (SIDE * SIDE);
            int x = random / SIDE;
            int y = random % SIDE;

            // Add the mine if no mine is placed at this
            // position on the board
            if (mark[random] == false)
            {
                // Row Index of the Mine
                moves[i][0] = x;
                // Column Index of the Mine
                moves[i][1] = y;

                mark[random] = true;
                i++;
            }
        }

        return;
    }

    // A Function to print the current gameplay board
    void printBoard()
    {
        int i, j;
        printf("    ");

        for (i = 0; i < SIDE; i++)
            printf("%d ", i);

        printf("\n\n");

        for (i = 0; i < SIDE; i++)
        {
            printf("%d   ", i);

            for (j = 0; j < SIDE; j++)
                printf("%c ", board[i][j]);
            printf("\n");
        }
        return;
    }

    // A Function to count the number of
    // mines in the adjacent cells
    int countAdjacentMines(int row, int col, int mines[][2])
    {
        int i;
        int count = 0;

        //    Count all the mines in the 8 adjacent cells

        int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int d = 0; d < 8; d++)
        {
            int newRow = row + dx[d];
            int newCol = col + dy[d];

            if (isValid(newRow, newCol) == true)
            {
                if (isMine(newRow, newCol) == true)
                    count++;
            }
        }
        return (count);
    }

    // A Function to place the mines randomly
    // on the board
    void placeMines(int mines[][2])
    {
        bool mark[MAXSIDE * MAXSIDE];

        memset(mark, false, sizeof(mark));

        // Continue until all random mines have been
        // created.
        for (int i = 0; i < MINES;)
        {
            int random = rand() % (SIDE * SIDE);
            int x = random / SIDE;
            int y = random % SIDE;

            // Add the mine if no mine is placed at this
            // position on the board
            if (mark[random] == false)
            {
                // Row Index of the Mine
                mines[i][0] = x;
                // Column Index of the Mine
                mines[i][1] = y;

                // Place the mine
                board[mines[i][0]][mines[i][1]] = '*';
                mark[random] = true;
                i++;
            }
        }
        return;
    }

    // A function to replace the mine from (row, col) and
    // put it to a vacant space
    void replaceMine(int row, int col)
    {
        for (int i = 0; i < SIDE; i++)
        {
            for (int j = 0; j < SIDE; j++)
            {
                // Find the first location in the board
                // which is not having a mine and put a mine
                // there.
                if (board[i][j] != '*')
                {
                    board[i][j] = '*';
                    board[row][col] = '-';
                    return;
                }
            }
        }
        return;
    }
};
class Game
{
public:
    // A Recursive Function to play the Minesweeper Game
    bool playMinesweeperUtil(Board &myBoard,
                             Board &realBoard,
                             int mines[][2], int row,
                             int col, int *movesLeft)
    {
        // Base Case of Recursion
        if (myBoard.board[row][col] != '-')
            return (false);

        int i, j;

        // You opened a mine
        // You are going to lose
        if (realBoard.board[row][col] == '*')
        {
            myBoard.board[row][col] = '*';
            for (i = 0; i < MINES; i++)
                myBoard.board[mines[i][0]][mines[i][1]] = '*';

            myBoard.printBoard();
            printf("\nYou lost!\n");
            return (true);
        }
        else
        {
            // Calculate the number of adjacent mines and
            // put it on the board
            int count = realBoard.countAdjacentMines(
                row, col, mines);
            (*movesLeft)--;

            myBoard.board[row][col] = count + '0';

            if (!count)
            {

                // Recur for all 8 adjacent cells

                int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
                int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

                for (int d = 0; d < 8; d++)
                {
                    int newRow = row + dx[d];
                    int newCol = col + dy[d];

                    if (isValid(newRow, newCol) == true)
                    {
                        if (realBoard.isMine(newRow, newCol) == false)
                            playMinesweeperUtil(
                                myBoard, realBoard, mines,
                                newRow, newCol, movesLeft);
                    }
                }
            }
            return (false);
        }
    }

    // A Function to cheat by revealing where the mines are
    // placed.
    void cheatMinesweeper(Board &realBoard)
    {
        printf("The mines locations are-\n");
        realBoard.printBoard();
        return;
    }

    // A Function to play Minesweeper game
    void playMinesweeper(Board &realBoard, Board &myBoard)
    {
        // Initially the game is not over
        bool gameOver = false;

        // Actual Board and My Board
        // char realBoard[MAXSIDE][MAXSIDE],
        // myBoard[MAXSIDE][MAXSIDE];

        int movesLeft = SIDE * SIDE - MINES, x, y;
        int mines[MAXMINES][2]; // stores (x,y) coordinates
                                // of all mines.
        int moves[MOVESIZE][2];

        // Place the Mines randomly
        realBoard.placeMines(mines);

        //         If you want to cheat and know
        //         where mines are before playing the game
        //         then uncomment this part

        //         cheatMinesweeper(realBoard);

        // You are in the game until you have not opened a
        // mine So keep playing

        myBoard.assignMoves(moves, movesLeft);

        int currentMoveIndex = 0;
        while (gameOver == false)
        {
            printf("Current Status of Board : \n");
            myBoard.printBoard();
            myBoard.makeMove(&x, &y, moves,
                             currentMoveIndex);

            // This is to guarantee that the first move is
            // always safe
            // If it is the first move of the game
            if (currentMoveIndex == 0)
            {
                // If the first move itself is a mine
                // then we remove the mine from that
                // location
                if (realBoard.isMine(x, y) == true)
                    realBoard.replaceMine(x, y);
            }

            currentMoveIndex++;

            gameOver = playMinesweeperUtil(
                myBoard, realBoard, mines, x, y,
                &movesLeft);

            if ((gameOver == false) && (movesLeft == 0))
            {
                printf("\nYou won !\n");
                gameOver = true;
            }
        }
        return;
    }
};

void chooseDifficultyLevel()
{
    /*
    --> BEGINNER = 9 * 9 Cells and 10 Mines
    --> INTERMEDIATE = 16 * 16 Cells and 40 Mines
    --> ADVANCED = 24 * 24 Cells and 99 Mines
    */

    int level;

    printf("Enter the Difficulty Level\n");
    printf("Press 0 for BEGINNER (9 * 9 Cells and 10 "
           "Mines)\n");
    printf("Press 1 for INTERMEDIATE (16 * 16 Cells and 40 "
           "Mines)\n");
    printf("Press 2 for ADVANCED (24 * 24 Cells and 99 "
           "Mines)\n");

    scanf("%d", &level);

    if (level == BEGINNER)
    {
        SIDE = 9;
        MINES = 10;
    }

    if (level == INTERMEDIATE)
    {
        SIDE = 16;
        MINES = 40;
    }

    if (level == ADVANCED)
    {
        SIDE = 24;
        MINES = 99;
    }
}

int main()
{
    /* Choose a level between
--> BEGINNER = 9 * 9 Cells and 10 Mines
--> INTERMEDIATE = 16 * 16 Cells and 40 Mines
--> ADVANCED = 24 * 24 Cells and 99 Mines
*/

    Board myBoard, realBoard;

    Game *game = new Game();
    chooseDifficultyLevel();

    game->playMinesweeper(myBoard, realBoard);
    return 0;
}
