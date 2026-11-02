/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-11-02 09:20
 */
// main.cpp：逐位贪心，用阶段标记维护候选集合。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;
int n, m;
int a[maxn];          // a[i]：第 i 个数；数值小于 2^30，用 int 即可
int stage[maxn];      // 处理第 k 位前，stage[i] == k + 1 表示 i 仍是候选
int candidate[maxn];  // 本轮候选中第 k 位为 1 的数的下标

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        stage[i] = 30;  // 第 29 位开始前，所有数都是候选
    }

    int ans = 0;  // 已经确定取 1 的位
    for (int k = 29; k >= 0; --k) {
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            if (stage[i] != k + 1) continue;
            if (((a[i] >> k) & 1) == 0) continue;
            candidate[++cnt] = i;
        }

        if (cnt >= m) {
            ans |= 1 << k;
            // 保留第 k 位：只有这一位为 1 的候选进入下一轮。
            for (int j = 1; j <= cnt; ++j) {
                stage[candidate[j]] = k;
            }
            // 其余数的标记不变，下一轮便不再满足候选条件。
        } else {
            // 放弃第 k 位：所有原候选都要进入下一轮，不能淘汰。
            for (int i = 1; i <= n; ++i) {
                if (stage[i] == k + 1) stage[i] = k;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
