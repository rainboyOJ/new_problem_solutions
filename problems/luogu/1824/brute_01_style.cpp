// brute_01_style.cpp：01 序列风格暴力，按牛舍位置依次决定放牛或不放。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, m;
int x[MAXN];
int answer;

void dfs_choose(int pos, int count_cow, int last_pos, int min_dist) {
    if (count_cow + (n - pos + 1) < m) {
        return;
    }
    if (pos == n + 1) {
        if (count_cow == m) {
            answer = max(answer, min_dist);
        }
        return;
    }

    // 选择 0：第 pos 个牛舍不放牛。
    dfs_choose(pos + 1, count_cow, last_pos, min_dist);

    // 选择 1：第 pos 个牛舍放牛。
    if (count_cow == 0) {
        dfs_choose(pos + 1, 1, x[pos], 1000000000);
    } else {
        dfs_choose(pos + 1, count_cow + 1, x[pos], min(min_dist, x[pos] - last_pos));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    sort(x + 1, x + n + 1);

    answer = 0;
    dfs_choose(1, 0, 0, 1000000000);

    cout << answer << '\n';
    return 0;
}
