/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P3853 [TJOI2007] 路标设置 */
/* 二分最大间距的最小值，用 (gap-1)/limit 统计每段需新增路标数。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int length, n, limit;
int pos[MAXN]; // 已有路标位置
int gap[MAXN]; // 相邻路标间距

// 检查最大间距 mid 是否可行
bool check(int mid) {
    int need = 0;
    for (int i = 1; i < n; i++) {
        // 长度为 gap[i] 的线段，间距不超过 mid 需要插入的路标数
        need += (gap[i] - 1) / mid;
    }
    return need <= limit;
}

int main() {
    cin >> length >> n >> limit;
    for (int i = 1; i <= n; i++) {
        cin >> pos[i];
    }

    // 预处理相邻间距
    int max_gap = 0;
    for (int i = 2; i <= n; i++) {
        gap[i - 1] = pos[i] - pos[i - 1];
        if (gap[i - 1] > max_gap) max_gap = gap[i - 1];
    }

    // 二分答案：间距越小，需要的新路标越多
    int l = 1, r = max_gap, ans = max_gap;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid; // mid 可行，尝试更小的
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << "\n";
    return 0;
}
