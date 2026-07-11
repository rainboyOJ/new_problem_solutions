/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:24
 * update_at: 2026-07-11 13:28
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举每篇论文是否被综述引用。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, L;
int citation[MAXN];
int choose_paper[MAXN]; // choose_paper[i] 表示第 i 篇论文是否被额外引用。
int ans;

int calc_h_index() {
    int temp[MAXN];
    for (int i = 1; i <= n; i++) {
        temp[i] = citation[i] + choose_paper[i];
    }

    sort(temp + 1, temp + n + 1, greater<int>());

    int h = 0;
    for (int i = 1; i <= n; i++) {
        if (temp[i] >= i) {
            h = i;
        }
    }
    return h;
}

bool check_limit() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_paper[i] == 1) {
            cnt++;
        }
    }
    return cnt <= L;
}

void dfs(int dep) {
    if (dep == n + 1) {
        if (check_limit()) {
            int now = calc_h_index();
            if (ans < now) {
                ans = now;
            }
        }
        return;
    }

    // 这一层决定第 dep 篇论文是否被综述引用。
    choose_paper[dep] = 0;
    dfs(dep + 1);

    choose_paper[dep] = 1;
    dfs(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> citation[i];
    }

    ans = 0;
    dfs(1);

    cout << ans << '\n';

    return 0;
}
