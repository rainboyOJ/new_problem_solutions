/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:30
 * update_at: 2026-10-06 01:30
 */
#include <cstdio>
#include <algorithm>
typedef long long ll;

const int MAXV = 10000; // 每堆石子数上限 a_i <= 10^4
const int MAXK = 105;

int k, m, n;
int s[MAXK];            // s[i]：每次允许取走的石子数集合
int sg[MAXV + 5];       // sg[x]：单堆石子数为 x 时的 SG 函数值
int tag[MAXK + 5];      // tag[v] = 最近一次出现 SG 值 v 的状态 x（时间戳标记，避免每次清空）

// 预处理 0..MAXV 的 SG 值：SG(x) = mex{ SG(x-s) | s in S, s <= x }
// k 个后继最多 k 个不同 SG 值，所以 mex <= k，tag 数组开 k+5 够用
void precompute() {
    std::sort(s + 1, s + k + 1); // 升序排序，方便提前 break
    for (int x = 1; x <= MAXV; x++) {
        for (int i = 1; i <= k && s[i] <= x; i++) {
            int v = sg[x - s[i]];
            tag[v] = x; // 给 SG 值 v 打上"本轮出现过"的时间戳
        }
        int mex = 0;
        while (tag[mex] == x) mex++; // 找最小的没出现过的非负整数
        sg[x] = mex;
    }
}

int main() {
    while (scanf("%d", &k) == 1 && k != 0) {
        for (int i = 1; i <= k; i++) scanf("%d", &s[i]);
        precompute();

        scanf("%d", &m);
        for (int t = 1; t <= m; t++) {
            scanf("%d", &n);
            int res = 0;
            for (int i = 1; i <= n; i++) {
                int a;
                scanf("%d", &a);
                res ^= sg[a]; // 多堆独立子游戏，SG 定理：异或和判胜负
            }
            if (res != 0) printf("W");
            else printf("L");
        }
        printf("\n");
    }
    return 0;
}
