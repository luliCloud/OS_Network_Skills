#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < n; i++) {
            if (board[0][i] == 'O') {
                floodEdge(board, 0, i);
            }
            if (board[m - 1][i] == 'O') {
                floodEdge(board, m - 1, i);
            }
        }
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') {
                floodEdge(board, i, 0);
            }
            if (board[i][n - 1] == 'O') {
                floodEdge(board, i, n - 1);
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    flood(board, i, j);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'I') {
                    board[i][j] = 'O';
                }
            }
        }
    }

    void floodEdge(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
            return;
        }

        if (board[i][j] == 'I' || board[i][j] == 'X') {
            return;
        }

        board[i][j] = 'I';
        floodEdge(board, i + 1, j);
        floodEdge(board, i - 1, j);
        floodEdge(board, i, j + 1);
        floodEdge(board, i, j - 1);
    }

    void flood(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
            return;
        }

        if (board[i][j] == 'I' || board[i][j] == 'X') {
            return;
        }

        board[i][j] = 'X';
        flood(board, i + 1, j);
        flood(board, i - 1, j);
        flood(board, i, j + 1);
        flood(board, i, j - 1);
    }
};

int main() {
    vector<vector<char>> board = {
        {'X','O','X','O','X','O'},
        {'O','X','O','X','O','X'},
        {'X','O','X','O','X','O'},
        {'O','X','O','X','O','X'}
    };

    Solution s;
    s.solve(board);
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}