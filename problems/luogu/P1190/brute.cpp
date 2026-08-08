// brute.cpp：按秒模拟每个水龙头当前还要接多少水。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 105;

int n, m;
int w[MAXN];
int tap[MAXM];     // tap[i] 表示第 i 个水龙头当前同学还要接多少水
int next_id;       // 下一位还没安排的同学编号

bool all_done() {
    if (next_id <= n) {
        return false;
    }
    for (int i = 1; i <= m; i++) {
        if (tap[i] > 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    next_id = 1;
    for (int i = 1; i <= m && next_id <= n; i++) {
        tap[i] = w[next_id];
        next_id++;
    }

    int sec = 0;
    while (!all_done()) {
        sec++;

        for (int i = 1; i <= m; i++) {
            if (tap[i] > 0) {
                tap[i]--;
            }
        }

        for (int i = 1; i <= m; i++) {
            if (tap[i] == 0 && next_id <= n) {
                tap[i] = w[next_id];
                next_id++;
            }
        }
    }

    cout << sec << '\n';

    return 0;
}
