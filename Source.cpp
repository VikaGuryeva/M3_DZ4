#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

const int SIZE = 4;
const vector<pair<int, int>> DIRS = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // L, R, U, D

vector<vector<int>> goal = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0} };

struct State {
    vector<vector<int>> board;
    int moves;
    string path;

    State(const vector<vector<int>>& b, int m, const string& p) : board(b), moves(m), path(p) {}
};

bool is_valid(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

string bfs(const vector<vector<int>>& initial) {
    queue<State> q;
    unordered_map<string, bool> visited;

    string start = "";
    for (const auto& row : initial) {
        for (int num : row) {
            start += to_string(num);
        }
    }

    q.emplace(initial, 0, "");
    visited[start] = true;

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.board == goal) {
            return curr.path;
        }

        int zero_x, zero_y;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (curr.board[i][j] == 0) {
                    zero_x = i;
                    zero_y = j;
                }
            }
        }

        for (const auto& dir : DIRS) {
            int new_x = zero_x + dir.first;
            int new_y = zero_y + dir.second;

            if (is_valid(new_x, new_y)) {
                vector<vector<int>> new_board = curr.board;
                swap(new_board[zero_x][zero_y], new_board[new_x][new_y]);

                string new_state = "";
                for (const auto& row : new_board) {
                    for (int num : row) {
                        new_state += to_string(num);
                    }
                }

                if (!visited[new_state]) {
                    q.emplace(new_board, curr.moves + 1, curr.path + (dir.first == 0 ? (dir.second == -1 ? "L" : "R") : (dir.first == -1 ? "U" : "D")));
                    visited[new_state] = true;
                }
            }
        }
    }

    return "-1";
}

int main() {
    vector<vector<int>> initial(SIZE, vector<int>(SIZE));

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> initial[i][j];
        }
    }

    string result = bfs(initial);

    if (result == "-1") {
        cout << -1 << endl;
    }
    else {
        cout << result.size() << endl;
        
    }

    return 0;
}
