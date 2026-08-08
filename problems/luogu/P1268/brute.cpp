#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;
const int INF = 1e9;

int n;
int dis[MAXN][MAXN];

// brute.cpp：小数据验证版。
// 思路和正式解一致，但直接用最朴素的三重枚举去找每次删掉叶子的枝长。
int solve_bruteforce(int size_now) {
    if (size_now == 2) {
        return dis[1][2];
    }

    int x = size_now;
    int limb = INF;

    for (int i = 1; i <= size_now - 1; i++) {
        for (int j = 1; j <= size_now - 1; j++) {
            if (i == j) {
                continue;
            }
            int value = (dis[x][i] + dis[x][j] - dis[i][j]) / 2;
            limb = min(limb, value);
        }
    }

    return solve_bruteforce(size_now - 1) + limb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        dis[i][i] = 0;
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> dis[i][j];
            dis[j][i] = dis[i][j];
        }
    }

    cout << solve_bruteforce(n) << '\n';
    return 0;
}
