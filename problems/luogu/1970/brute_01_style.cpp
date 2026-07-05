// brute_01_style.cpp：01 序列风格暴力，按花的下标依次决定保留或删除。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;

int n;
int h[MAXN];
int answer;

void dfs_choose(int pos, int last_height, int last_sign, int count_chosen) {
    if (pos == n + 1) {
        answer = max(answer, count_chosen);
        return;
    }

    // 选择 0：删除第 pos 朵花。
    dfs_choose(pos + 1, last_height, last_sign, count_chosen);

    // 选择 1：保留第 pos 朵花，并检查是否仍然高低交替。
    if (count_chosen == 0) {
        dfs_choose(pos + 1, h[pos], 0, 1);
    } else if (h[pos] != last_height) {
        int cur_sign = (h[pos] > last_height ? 1 : -1);
        if (last_sign == 0 || cur_sign != last_sign) {
            dfs_choose(pos + 1, h[pos], cur_sign, count_chosen + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    answer = 0;
    dfs_choose(1, 0, 0, 0);

    cout << answer << '\n';
    return 0;
}
