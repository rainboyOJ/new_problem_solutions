#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。

const int MAXN = 55;

int n, begin_level, max_level;
int change_value[MAXN];
int answer = -1;

// 枚举每一次调音量时选择加还是减。
// 复杂度是 O(2^n)，只适合小数据验证。
void dfs(int idx, int volume) {
    if (idx > n) {
        answer = max(answer, volume);
        return;
    }

    int up = volume + change_value[idx];
    int down = volume - change_value[idx];

    if (up <= max_level) {
        dfs(idx + 1, up);
    }
    if (down >= 0) {
        dfs(idx + 1, down);
    }
}

void read_input() {
    cin >> n >> begin_level >> max_level;
    for (int i = 1; i <= n; i++) {
        cin >> change_value[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    dfs(1, begin_level);
    cout << answer << '\n';

    return 0;
}
