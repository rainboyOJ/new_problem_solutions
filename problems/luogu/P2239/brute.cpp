#include <bits/stdc++.h>
using namespace std;

// brute.cpp：按题目描述直接模拟走螺旋。
// 只适合很小的 n，用来帮助理解题意并辅助对拍。
const int MAXN = 205;

int n, target_i, target_j;
int a[MAXN][MAXN];
bool vis[MAXN][MAXN];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool inside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> target_i >> target_j;

    int x = 1;
    int y = 1;
    int dir = 0;

    for (int val = 1; val <= n * n; val++) {
        a[x][y] = val;
        vis[x][y] = true;

        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (!inside(nx, ny) || vis[nx][ny]) {
            dir = (dir + 1) % 4;
            nx = x + dx[dir];
            ny = y + dy[dir];
        }
        x = nx;
        y = ny;
    }

    cout << a[target_i][target_j] << '\n';
    return 0;
}
