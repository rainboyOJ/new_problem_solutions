// brute_01_style.cpp：01 序列风格暴力，按牛舍位置依次决定放牛或不放。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, m;
int x[MAXN];
int choose_cow[MAXN]; // choose_cow[i] = 0/1，表示第 i 个牛舍不放/放牛
int answer;

bool check() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_cow[i] == 1) cnt++;
    }
    return cnt == m;
}

int calc_answer() {
    int last_pos = -1;
    int min_dist = 1000000000;
    for (int i = 1; i <= n; i++) {
        if (choose_cow[i] == 0) continue;
        if (last_pos != -1) {
            min_dist = min(min_dist, x[i] - last_pos);
        }
        last_pos = x[i];
    }
    return min_dist;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (answer < value) answer = value;
        }
        return;
    }

    // 第 dep 个牛舍的 01 选择：0 不放，1 放。
    for (int i = 0; i <= 1; i++) {
        choose_cow[dep] = i;
        dfs_choose(dep + 1);
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
    dfs_choose(1);

    cout << answer << '\n';
    return 0;
}
