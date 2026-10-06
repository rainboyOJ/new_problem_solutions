/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:30
 * update_at: 2026-10-06 12:28
 */
// 思路（对应 index.md）：
// 1. 只固定第一行的拉丁方阵，可以把第 2..N 行按第一列排序归约为标准型，
//    所以 答案 = 标准型数量 R_N * (N-1)!。
// 2. 标准型中第二行是一个错排置换，把行、列、数值做同样的重标后，
//    环长多重集相同的第二行给出的后续方案数相同，按环结构等价类合并，
//    每类只跑一次位运算 DFS。

#include <cstdio>
#include <algorithm>
typedef long long ll;

const int MAXN = 8;

int n;                       // 题目给的 N
int all_mask;                // (1<<n)-1，表示 0..n-1 全部数字的掩码
int row_mask[MAXN];          // row_mask[r]：第 r 行已出现数字的位掩码
int col_mask[MAXN];          // col_mask[c]：第 c 列已出现数字的位掩码
int second_row[MAXN];        // 当前枚举的第二行（0 下标存列 0 的值 1）
bool vis[MAXN];              // 置换环分解时的访问标记
int cycle_len[MAXN];         // 分解出的环长
int cycle_cnt;               // 环的个数

// 等价类合并用：环长多重集相同的第二行归为一类
struct CycleType {
    int len[MAXN];       // 排序后的环长
    int num_cycles;      // 环的个数
    int count;           // 该等价类中合法第二行排列的个数
    int rep[MAXN];       // 一个代表元
};
CycleType types[1000];       // 第二行合法排列至多 720 个，等价类远少于此
int type_num;

// 把当前 second_row 当作置换 p（p[i] = 第 i 列的值），分解环长多重集
void decompose_cycles() {
    for (int i = 0; i < n; i++) vis[i] = false;
    cycle_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        int length = 0;
        int cur = i;
        while (!vis[cur]) {
            vis[cur] = true;
            cur = second_row[cur];
            length++;
        }
        cycle_len[cycle_cnt++] = length;
    }
    std::sort(cycle_len, cycle_len + cycle_cnt);
}

// 比较两个环长多重集是否相同
bool same_cycles(const CycleType &a, int *b, int cnt) {
    if (a.num_cycles != cnt) return false;
    for (int i = 0; i < cnt; i++)
        if (a.len[i] != b[i]) return false;
    return true;
}

// 搜索（r, c）之后所有格子的填法数，位运算枚举可行数字
// 剩余格子从第 2 行第 1 列开始（下标从 0 起，第 0 行、第 0 列已固定）
ll dfs(int r, int c) {
    if (r == n - 1) return 1;          // 只剩最后一行时它已被唯一确定
    int nr = r, nc = c + 1;
    if (nc == n) { nr++; nc = 1; }     // 换行，第 0 列已由第一列固定跳过
    ll res = 0;
    int avail = all_mask & ~(row_mask[r] | col_mask[c]);
    while (avail) {
        int low = avail & (-avail);    // 取最低位的可行数字
        avail ^= low;
        row_mask[r] |= low;
        col_mask[c] |= low;
        res += dfs(nr, nc);
        row_mask[r] ^= low;
        col_mask[c] ^= low;
    }
    return res;
}

// 固定第二行为 perm，统计标准型方阵的完成数
ll count_completions(int *perm) {
    all_mask = (1 << n) - 1;
    // 初始时第 r 行已含第一列的值 r，第 c 列已含第一行的值 c（0 下标）
    for (int i = 0; i < n; i++) {
        row_mask[i] = 1 << i;
        col_mask[i] = 1 << i;
    }
    row_mask[0] = all_mask;            // 第一行 0..n-1 全部出现
    col_mask[0] = all_mask;            // 第一列 0..n-1 全部出现
    for (int c = 1; c < n; c++) {
        row_mask[1] |= 1 << perm[c];
        col_mask[c] |= 1 << perm[c];
    }
    return dfs(2, 1);
}

int main() {
    if (scanf("%d", &n) != 1) return 0;

    if (n == 2) {                      // N=2 时标准型只有 1 个
        printf("1\n");
        return 0;
    }

    // 枚举第二行第 1..n-1 列的错排：0 下标下第二行是 0,2,3..n-1 的排列，列 0 固定为 1
    int rest[MAXN], rest_num = 0;
    rest[rest_num++] = 0;
    for (int v = 2; v < n; v++) rest[rest_num++] = v;
    std::sort(rest, rest + rest_num);
    do {
        // 检查错排：第 c 列的值不能等于 c（0 下标，列 1..n-1 对应 rest 的 0..rest_num-1）
        bool ok = true;
        for (int i = 0; i < rest_num && ok; i++)
            if (rest[i] == i + 1) ok = false;
        if (!ok) continue;

        second_row[0] = 1;
        for (int c = 1; c < n; c++) second_row[c] = rest[c - 1];

        // 分解置换环，按环长多重集归入等价类
        decompose_cycles();
        int found = -1;
        for (int t = 0; t < type_num; t++)
            if (same_cycles(types[t], cycle_len, cycle_cnt)) { found = t; break; }
        if (found == -1) {             // 新的环结构类型
            found = type_num++;
            types[found].count = 0;
            types[found].num_cycles = cycle_cnt;
            for (int i = 0; i < cycle_cnt; i++) types[found].len[i] = cycle_len[i];
        }
        types[found].count++;          // 该等价类的排列个数加一
        if (types[found].count == 1)   // 第一个遇到的作为代表元
            for (int i = 0; i < n; i++) types[found].rep[i] = second_row[i];
    } while (std::next_permutation(rest, rest + rest_num));

    // 对每个等价类的代表元跑一次位运算 DFS，加权求和得 R_N
    ll reduced = 0;
    for (int t = 0; t < type_num; t++)
        reduced += count_completions(types[t].rep) * (ll)types[t].count;

    // 答案 = R_N * (N-1)!
    ll factor = 1;
    for (int i = 2; i <= n - 1; i++) factor *= i;
    printf("%lld\n", reduced * factor);
    return 0;
}
