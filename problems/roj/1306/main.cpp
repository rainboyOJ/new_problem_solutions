/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:58
 * update_at: 2026-10-04 23:58
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 505;

ll a[MAXN];    // 第一个序列 A
ll b[MAXN];    // 第二个序列 B
ll lens[MAXN]; // lens[i] 表示以 A[i] 结尾的最长上升公共子序列长度
ll pre[MAXN];  // pre[i] 记录 A[i] 在答案中的前驱下标，0 表示没有前驱
ll ans[MAXN];  // 还原出来的最长上升公共子序列

int main() {
    int n = 0, m = 0;

    if (scanf("%d", &n) != 1) {
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    scanf("%d", &m);
    for (int t = 1; t <= m; t++) {
        scanf("%lld", &b[t]);
    }

    // 逐个取出 B 中的元素作为当前要接的末尾，扫描 A 更新状态。
    for (int t = 1; t <= m; t++) {
        ll best_len = 0; // 当前 target 之前能接上的最长上升公共子序列长度
        int best_idx = 0; // 这个最长子序列在 A 中的结尾下标
        for (int i = 1; i <= n; i++) {
            if (a[i] < b[t] && lens[i] > best_len) {
                // A[i] 比当前末尾小，可以作为前驱
                best_len = lens[i];
                best_idx = i;
            } else if (a[i] == b[t]) {
                // A[i] 可以作为当前公共子序列的末尾
                lens[i] = best_len + 1;
                pre[i] = best_idx;
            }
        }
    }

    // 在所有以 A[i] 结尾的答案中找最长的
    int best = 0;
    for (int i = 1; i <= n; i++) {
        if (lens[i] > lens[best]) {
            best = i;
        }
    }

    ll length = lens[best];
    // 顺着 pre 指针从后往前填回答案
    int cnt = 0;
    int cur = best;
    while (cur != 0) {
        ans[cnt] = a[cur];
        cnt++;
        cur = pre[cur];
    }
    reverse(ans, ans + cnt);

    printf("%lld\n", length);
    for (int i = 0; i < cnt; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%lld", ans[i]);
    }
    printf("\n");

    return 0;
}
