/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:31
 * update_at: 2026-07-11 15:34
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, q;
bool removed_block[MAXN][MAXN][MAXN]; // true 表示这个 1x1x1 小块已经被切掉。

bool empty_x_line(int y, int z) {
    for (int x = 0; x < n; x++) {
        if (!removed_block[x][y][z]) return false;
    }
    return true;
}

bool empty_y_line(int x, int z) {
    for (int y = 0; y < n; y++) {
        if (!removed_block[x][y][z]) return false;
    }
    return true;
}

bool empty_z_line(int x, int y) {
    for (int z = 0; z < n; z++) {
        if (!removed_block[x][y][z]) return false;
    }
    return true;
}

long long calc_answer() {
    long long ans = 0;

    for (int y = 0; y < n; y++) {
        for (int z = 0; z < n; z++) {
            if (empty_x_line(y, z)) ans++;
        }
    }

    for (int x = 0; x < n; x++) {
        for (int z = 0; z < n; z++) {
            if (empty_y_line(x, z)) ans++;
        }
    }

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (empty_z_line(x, y)) ans++;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;

        removed_block[x][y][z] = true;
        cout << calc_answer() << '\n';
    }

    return 0;
}
