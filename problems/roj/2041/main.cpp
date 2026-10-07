/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:09
 * update_at: 2026-10-06 10:09
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXM = 10000;

int M, N;
ll dp[MAXM + 1]; // dp[t] 表示限时 t 内的最大得分

struct Kind {
    int t; // 耗时
    int p; // 得分
} kinds[MAXM + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> M >> N;
    for (int i = 1; i <= N; ++i) {
        int points, minutes;
        cin >> points >> minutes;
        kinds[i].t = minutes;
        kinds[i].p = points;
    }

    // 按耗时升序排序，耗时相同则得分高的在前
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (kinds[j].t < kinds[i].t ||
                (kinds[j].t == kinds[i].t && kinds[j].p > kinds[i].p)) {
                Kind tmp = kinds[i];
                kinds[i] = kinds[j];
                kinds[j] = tmp;
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        int t = kinds[i].t;
        int p = kinds[i].p;
        if (t > M) break; // 耗时升序，后面的种类耗时更长，连一题都放不下
        if (dp[t] >= p) continue; // 被支配种类，跳过
        // 完全背包：容量正序遍历，同一种类可重复选取
        for (int cap = t; cap <= M; ++cap) {
            ll cand = dp[cap - t] + p;
            if (cand > dp[cap]) dp[cap] = cand;
        }
    }

    cout << dp[M] << "\n";
    return 0;
}
