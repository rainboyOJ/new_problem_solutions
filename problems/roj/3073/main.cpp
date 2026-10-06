/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:13
 * update_at: 2026-10-06 17:13
 */

// 排书：IDA*，估价函数 = 坏接口数 / 3 上取整（一次操作最多修复 3 个接口）

#include <cstdio>

typedef long long ll;

const int MAXN = 16;
const int HASH_MOD = 1000003; // 哈希模数，只做后继去重标记，不要求严格无冲突
const int MAX_DEPTH = 4;      // 答案一旦 >= 5 就输出 "5 or more"，迭代加深只到 4

int start[MAXN];    // 本组数据的初始排列
int a[MAXN];        // 当前搜索结点的排列，下标 0..n-1；末尾哨兵 a[n] = n+1
int backup[MAX_DEPTH + 1][MAXN]; // backup[depth] = 该层结点进入枚举前的排列
                 // 必须按深度分层：全局单份会被子结点覆盖，回溯就还原错了
int rest[MAXN];     // 取走一段后剩下的书
int nxt[MAXN];      // 取走再插回之后的后继排列
int seen_id[HASH_MOD]; // 后继状态哈希去重：存的是最近一次标记它的结点编号
int node_counter;      // 搜索结点编号计数器（全局递增不重置，保证 seen_id 永不串号）
int n;
bool ok; // 当前深度限制下能否排好

// 数坏接口数 E：正确排列里 a[i] 应该恰好等于 a[i-1]+1，末尾比到哨兵 n+1
int wrong_links() {
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        if (a[i] + 1 != a[i + 1])
            ++cnt;
    return cnt;
}

// 简单多项式哈希：同一搜索结点内对后继排列去重（p 指向长度为 n 的排列）
int hash_state(const int *p) {
    int h = 0;
    for (int i = 0; i < n; ++i)
        h = (h * 31 + p[i]) % HASH_MOD;
    return h;
}

// IDA*：还剩 depth 次操作能否把排列变成 1..n
// 剪枝：每次操作最多修好 3 个坏接口，所以剩余步数下界是 ceil(E/3)
void dfs(int depth) {
    int w = wrong_links();
    if (w == 0) { // 坏接口为 0，排列已经归位
        ok = true;
        return;
    }
    if ((w + 2) / 3 > depth) // ceil(E/3) > 剩余深度，必然来不及，剪掉
        return;

    // 本结点独立的去重空间：用结点编号当时间戳，避免误杀兄弟结点的后继
    int myid = ++node_counter;

    for (int i = 0; i < n; ++i) // 备份当前排列到本层专属的一行，枚举被破坏后好恢复
        backup[depth][i] = a[i];

    // 枚举取走的连续段 [l, r]（闭区间）
    for (int l = 0; l < n && !ok; ++l) {
        for (int r = l; r < n && !ok; ++r) {
            int len = 0; // rest = 取走 [l,r] 后剩下的书
            for (int i = 0; i < l; ++i)
                rest[len++] = a[i];
            for (int i = r + 1; i < n; ++i)
                rest[len++] = a[i];

            // 枚举插入位置 k：插到 rest 下标 k 之前
            for (int k = 0; k <= len && !ok; ++k) {
                if (k == l) // 插回原位等于没操作，跳过
                    continue;

                // nxt = rest[0..k) + a[l..r] + rest[k..len)
                for (int i = 0; i < k; ++i)
                    nxt[i] = rest[i];
                for (int i = l; i <= r; ++i)
                    nxt[k + i - l] = a[i];
                for (int i = k; i < len; ++i)
                    nxt[i + (r - l + 1)] = rest[i];
                nxt[n] = n + 1; // 补回末尾哨兵

                int h = hash_state(nxt);
                if (seen_id[h] == myid) // 这个后继在本结点已经搜过，去重
                    continue;
                seen_id[h] = myid;

                for (int i = 0; i < n; ++i) // 走到后继
                    a[i] = nxt[i];
                dfs(depth - 1);
                for (int i = 0; i < n; ++i) // 回溯恢复本结点排列
                    a[i] = backup[depth][i];
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &start[i]);
            a[i] = start[i];
        }
        a[n] = n + 1; // 末尾哨兵：让最后一个数和"序列结尾"的接口也被统计

        // 迭代加深：第一个能排好的深度就是最少操作次数
        int ans = -1;
        for (int d = 0; d <= MAX_DEPTH && ans == -1; ++d) {
            ok = false;
            // node_counter 全局递增不重置：seen_id 不用清空也不会串轮
            for (int i = 0; i < n; ++i) // 从初始排列重新出发
                a[i] = start[i];
            a[n] = n + 1;
            dfs(d);
            if (ok)
                ans = d;
        }
        if (ans == -1)
            printf("5 or more\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}
