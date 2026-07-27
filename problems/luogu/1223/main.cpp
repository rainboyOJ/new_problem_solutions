/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1223 排队接水 */
/* 接水时间短的人先接水，总等待时间最小。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
// 保存每个人的接水时间和编号
int t[MAXN], id[MAXN], idx[MAXN];

// 排序规则：时间小的在前，时间相同编号小的在前
bool cmp(int a, int b) {
    if (t[a] != t[b]) return t[a] < t[b];
    return id[a] < id[b];
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        id[i] = i;
        idx[i] = i;
    }

    sort(idx + 1, idx + n + 1, cmp);

    long long total = 0; // 总等待时间
    long long elapsed = 0; // 已经过去的时间
    for (int i = 1; i <= n; i++) {
        int p = idx[i];
        // 当前人的等待时间 = 已经过去的时间
        total += elapsed;
        elapsed += t[p];
    }

    // 输出接水顺序
    for (int i = 1; i <= n; i++) {
        cout << id[idx[i]] << " \n"[i == n];
    }
    // 输出平均等待时间
    printf("%.2f\n", (double)total / n);
    return 0;
}
