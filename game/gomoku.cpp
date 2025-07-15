#include <iostream>
#include <vector>
#include <string>

const int SIZE = 15;

void printBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "  ";
    for (int i = 0; i < SIZE; ++i) std::cout << (i < 10 ? " " : "") << i << " ";
    std::cout << std::endl;
    for (int y = 0; y < SIZE; ++y) {
        std::cout << (y < 10 ? " " : "") << y << " ";
        for (int x = 0; x < SIZE; ++x) {
            std::cout << " " << (board[y][x] == 0 ? '.' : board[y][x]) << " ";
        }
        std::cout << std::endl;
    }
}

bool checkWin(const std::vector<std::vector<char>>& board, int x, int y, char player) {
    int dx[] = {1, 0, 1, 1};
    int dy[] = {0, 1, 1, -1};
    for (int d = 0; d < 4; ++d) {
        int count = 1;
        for (int step = 1; step < 5; ++step) {
            int nx = x + dx[d]*step, ny = y + dy[d]*step;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[ny][nx] == player) count++;
            else break;
        }
        for (int step = 1; step < 5; ++step) {
            int nx = x - dx[d]*step, ny = y - dy[d]*step;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[ny][nx] == player) count++;
            else break;
        }
        if (count >= 5) return true;
    }
    return false;
}

int main() {
    std::vector<std::vector<char>> board(SIZE, std::vector<char>(SIZE, 0));
    char players[2] = {'X', 'O'};
    int turn = 0;
    std::cout << "五子棋小游戏，输入格式：行 列 (如 7 7)\n";
    printBoard(board);
    while (true) {
        std::cout << "玩家 " << players[turn] << " 落子: ";
        int y, x;
        std::cin >> y >> x;
        if (y < 0 || y >= SIZE || x < 0 || x >= SIZE || board[y][x] != 0) {
            std::cout << "无效位置，请重新输入。\n";
            continue;
        }
        board[y][x] = players[turn];
        printBoard(board);
        if (checkWin(board, x, y, players[turn])) {
            std::cout << "玩家 " << players[turn] << " 获胜！\n";
            break;
        }
        turn = 1 - turn;
    }
    return 0;
}
