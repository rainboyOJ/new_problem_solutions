#include <bits/stdc++.h>
using namespace std;

struct Cube {
    int a[6][3][3];
};

Cube move_one(const Cube &cube, int op) {
    Cube next = cube;

    if (op == 1 || op == 2) {
        int order1[4] = {0, 5, 1, 4};
        int order2[4] = {0, 4, 1, 5};
        int *order = (op == 1 ? order1 : order2);
        for (int idx = 0; idx < 4; ++idx) {
            int from = order[(idx + 1) % 4];
            int to = order[idx];
            for (int r = 0; r < 3; ++r) {
                next.a[to][r][2] = cube.a[from][r][2];
            }
        }

        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (op == 1) {
                    next.a[3][r][c] = cube.a[3][2 - c][r];
                } else {
                    next.a[3][r][c] = cube.a[3][c][2 - r];
                }
            }
        }
    } else {
        int order1[4] = {0, 2, 1, 3};
        int order2[4] = {0, 3, 1, 2};
        int *order = (op == 3 ? order1 : order2);
        for (int idx = 0; idx < 4; ++idx) {
            int from = order[(idx + 1) % 4];
            int to = order[idx];
            for (int c = 0; c < 3; ++c) {
                next.a[to][0][c] = cube.a[from][0][c];
            }
        }

        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (op == 3) {
                    next.a[4][r][c] = cube.a[4][2 - c][r];
                } else {
                    next.a[4][r][c] = cube.a[4][c][2 - r];
                }
            }
        }
    }

    return next;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string steps;
    cin >> steps;

    Cube cube;
    string row;
    for (int f = 0; f < 6; ++f) {
        for (int r = 0; r < 3; ++r) {
            cin >> row;
            for (int c = 0; c < 3; ++c) {
                cube.a[f][r][c] = row[c] - '0';
            }
        }
    }

    for (char ch : steps) {
        cube = move_one(cube, ch - '0');
    }

    for (int f = 0; f < 6; ++f) {
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                cout << cube.a[f][r][c];
            }
            cout << '\n';
        }
    }
    return 0;
}
