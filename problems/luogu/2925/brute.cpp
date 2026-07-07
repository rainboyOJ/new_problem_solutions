#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。

const int MAXH = 5005;

int c, h;
int volume[MAXH];
int choose_hay[MAXH]; // choose_hay[i] = 0/1，表示第 i 捆草不买/买
int answer;

int calc_volume() {
    int total_volume = 0;
    for (int i = 1; i <= h; i++) {
        if (choose_hay[i] == 1) total_volume += volume[i];
    }
    return total_volume;
}

bool check() {
    return calc_volume() <= c;
}

// dfs_choose 只负责生成完整 01 序列。
void dfs_choose(int dep) {
    if (dep == h + 1) {
        if (check()) {
            int value = calc_volume();
            if (answer < value) answer = value;
        }
        return;
    }

    // 第 dep 捆草的 01 选择：0 不买，1 买。
    for (int i = 0; i <= 1; i++) {
        choose_hay[dep] = i;
        dfs_choose(dep + 1);
    }
}

void read_input() {
    cin >> c >> h;
    for (int i = 1; i <= h; i++) {
        cin >> volume[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    dfs_choose(1);
    cout << answer << '\n';

    return 0;
}
