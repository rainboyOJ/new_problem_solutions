#include <bits/stdc++.h>
using namespace std;

// brute.cpp：暴力递归枚举当前位置三种对齐方式。

const int NEG_INF = -1000000000;

int n, m;
string a, b;
int score[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, 0}
};

int id(char ch) {
    if (ch == 'A') return 0;
    if (ch == 'C') return 1;
    if (ch == 'G') return 2;
    if (ch == 'T') return 3;
    return 4;
}

int dfs(int i, int j) {
    if (i > n && j > m) {
        return 0;
    }

    int best = NEG_INF;

    if (i <= n && j <= m) {
        best = max(best, dfs(i + 1, j + 1) + score[id(a[i])][id(b[j])]);
    }
    if (i <= n) {
        best = max(best, dfs(i + 1, j) + score[id(a[i])][4]);
    }
    if (j <= m) {
        best = max(best, dfs(i, j + 1) + score[4][id(b[j])]);
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a;
    cin >> m >> b;

    a = " " + a;
    b = " " + b;

    cout << dfs(1, 1) << '\n';
    return 0;
}
