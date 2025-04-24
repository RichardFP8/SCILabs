#include <iostream>
#include <random>
#include <string>
using namespace std;

struct MineSweeper{
    int rows, columns;
    char msymb;
    string board;
};

MineSweeper addCount(int row, int col, MineSweeper game) {
    for (int r = row - 1; r < row + 2; r++) {
        for (int c = col - 1; c < col + 2; c++) {
            int k = r * game.columns + c;
            if (k >= 0 && k < (game.board.size()) && game.board[k] != game.msymb)
                game.board[k] = game.board[k] + 1;
        }
    }
    return game;
}

MineSweeper addMinesNCount(MineSweeper game, int mines) {
    random_device rd;
    mt19937 gen(rd()); // -0 not in pseudocode
    uniform_int_distribution<unsigned int> pick(0, game.board.size() - 1);
    while (mines != 0) {
        int i = pick(gen);
        int j = pick(gen);
        if (game.board[j] > game.board[i])
            i = j;
        if (game.board[i] - '0' >= 0 && '9' - game.board[i] >= 0) { // -1 condition error
            game.board[i] = game.msymb;
            game = addCount(i / game.columns, i % game.columns, game);
            mines--;
        }
    }
    return game;
}

void displayBoard(MineSweeper game) {
    string trail = "|\n", line (game.columns*4, '-');
    cout << line << trail;
    for (int r = 0; r < game.rows; r++) {
        if (r >= 0 && r < game.rows) {
            for (int c = 0; c < game.columns; c++) {
                if (c >= 0 && c < game.columns) {
                    int k = r * game.columns + c;
                    char s = game.board[k];
                    if (s == '0') s = ' ';
                    cout << "| " << s << " ";
                }
            }
        }
        cout << trail << line << trail;
    }
    
}

int main() {
    MineSweeper game{ 12, 14, '*' };
    game.board.resize(game.rows * game.columns, '0');
    game = addMinesNCount(game, 30);
    displayBoard(game);
    
}
