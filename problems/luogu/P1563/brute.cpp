// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
int dir[MAXN];
string name_[MAXN];

void solve() {
    int cur = 0;

    for (int i = 1; i <= m; i++) {
        int op, step;
        cin >> op >> step;
        int move_dir;

        // 这一条指令的左右方向，只由当前起点玩具的朝向决定一次。
        // move_dir = -1 表示下标减小，move_dir = 1 表示下标增大。
        if (dir[cur] == op) {
            move_dir = -1;
        }
        else {
            move_dir = 1;
        }

        // 每次一步一步地走，更直观地模拟“数第 step 个”的过程。
        for (int j = 1; j <= step; j++) {
            cur += move_dir;
            if (cur < 0) {
                cur = n - 1;
            }
            if (cur >= n) {
                cur = 0;
            }
        }
    }

    cout << name_[cur] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> dir[i] >> name_[i];
    }

    solve();

    return 0;
}
