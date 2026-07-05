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

void dfs_room(int pos, int count_people) {
    if (count_people > n) {
        return;
    }
    if (count_people + (m - pos) < n) {
        return;
    }
    if (pos == m) {
        if (count_people == n) {
            best = min(best, calc_anger());
        }
        return;
    }

    // 选择 0：第 pos 个房间空着。
    occupied[pos] = 0;
    dfs_room(pos + 1, count_people);

    // 选择 1：第 pos 个房间住人。
    occupied[pos] = 1;
    dfs_room(pos + 1, count_people + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    best = 1000000000;
    dfs_room(0, 0);

    cout << best << '\n';
    return 0;
}
