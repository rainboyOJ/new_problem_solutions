/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:25
 * update_at: 2026-10-06 15:25
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // n <= 1e5

int n;
ll a[MAXN];   // a[1..n]：原序列，数值两两不同
int order[MAXN]; // order[k]：有序表第 k 个位置上放的是原序列的哪个下标
int rank_of[MAXN]; // rank_of[i]：A_i 在有序表里的位置
int pre[MAXN]; // pre[k]：有序表里位置 k 的前一个位置，0 表示无前驱
int nxt[MAXN]; // nxt[k]：有序表里位置 k 的后一个位置，0 表示无后继
ll ans_diff[MAXN]; // ans_diff[i]：第 i 个数的最近差值
int ans_pos[MAXN]; // ans_pos[i]：取到最近差值的原始下标

// 按数值升序排列原始下标，供 sort 使用
bool cmp_value(int x, int y) {
    return a[x] < a[y];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        order[i] = i;
    }

    // 排序得到有序表，并记录每个下标在表中的位置
    sort(order + 1, order + n + 1, cmp_value);
    for (int k = 1; k <= n; k++) {
        rank_of[order[k]] = k;
    }

    // 建双向链表，删除一个位置只需改两条边
    for (int k = 1; k <= n; k++) {
        pre[k] = k - 1;
        nxt[k] = k + 1;
    }
    pre[1] = 0;
    nxt[n] = 0;

    // 从 i=n 倒推：此时表里是 S_i 并上 A_i，取它的左右邻居即为候选
    for (int i = n; i >= 2; i--) {
        int k = rank_of[i];
        ll best_diff = -1;
        ll best_val = 0;
        int best_pos = 0;
        for (int t = 0; t < 2; t++) {
            int p = (t == 0 ? pre[k] : nxt[k]);
            if (p == 0) continue;
            int j = order[p];
            ll diff = a[i] - a[j];
            if (diff < 0) diff = -diff;
            // 三元组 (差值, A_j, 下标) 字典序最小者
            bool better = false;
            if (best_diff == -1) better = true;
            else if (diff < best_diff) better = true;
            else if (diff == best_diff && a[j] < best_val) better = true;
            else if (diff == best_diff && a[j] == best_val && j < best_pos) better = true;
            if (better) {
                best_diff = diff;
                best_val = a[j];
                best_pos = j;
            }
        }
        ans_diff[i] = best_diff;
        ans_pos[i] = best_pos;

        // 摘掉 A_i：它的左右邻居直接相连
        if (pre[k] != 0) nxt[pre[k]] = nxt[k];
        if (nxt[k] != 0) pre[nxt[k]] = pre[k];
    }

    for (int i = 2; i <= n; i++) {
        printf("%lld %d\n", ans_diff[i], ans_pos[i]);
    }
    return 0;
}
