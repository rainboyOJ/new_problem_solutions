/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:27
 * update_at: 2026-07-11 17:28
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int INF = 1e9;

int n;
char type[MAXN];
long long p[MAXN];
long long candidate[MAXN * 3];
int candidate_cnt;

int count_liars(long long h) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (type[i] == 'G' && h < p[i]) {
            cnt++;
        }
        if (type[i] == 'L' && h > p[i]) {
            cnt++;
        }
    }
    return cnt;
}

void add_candidate(long long x) {
    candidate_cnt++;
    candidate[candidate_cnt] = x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> type[i] >> p[i];
        add_candidate(p[i]);
        if (p[i] > 0) {
            add_candidate(p[i] - 1);
        }
        add_candidate(p[i] + 1);
    }

    int ans = INF;
    for (int i = 1; i <= candidate_cnt; i++) {
        int liars = count_liars(candidate[i]);
        if (liars < ans) {
            ans = liars;
        }
    }

    cout << ans << '\n';

    return 0;
}
