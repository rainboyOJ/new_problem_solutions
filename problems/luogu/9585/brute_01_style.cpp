// brute_01_style.cpp：01 序列风格暴力，按房间编号依次决定住人或空着。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 25;

int n, m;
int occupied[MAXM]; // occupied[i] 表示第 i 个房间是否住人。
int best;

int calc_anger() {
    int anger = 0;
    for (int i = 0; i < m; i++) {
        if (!occupied[i]) {
            continue;
        }
        int left = (i - 1 + m) % m;
        int right = (i + 1) % m;
        anger += occupied[left];
        anger += occupied[right];
    }
    return anger;
}

bool check() {
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (occupied[i] == 1) cnt++;
    }
    return cnt == n;
}

void dfs_room(int pos) {
    if (pos == m) {
        if (check()) {
            best = min(best, calc_anger());
        }
        return;
    }

    // 第 pos 个房间的 01 选择：0 空着，1 住人。
    for (int i = 0; i <= 1; i++) {
        occupied[pos] = i;
        dfs_room(pos + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    best = 1000000000;
    dfs_room(0);

    cout << best << '\n';
    return 0;
}
