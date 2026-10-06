/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:25
 * update_at: 2026-10-06 09:25
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 105;   // 公司编号上限：题面保证 i, j, p 都在 1..100
const ll MAJORITY = 50; // 控股线：汇总持股要「大于 50%」才算控制

int n;                  // 输入的三对数数量
int v;                  // 实际出现的最大公司编号，枚举上界
ll own[MAXN][MAXN];     // own[a][b] = 公司 a 直接持有 b 的股份百分比（多条边累加）
bool ctrl[MAXN][MAXN];  // ctrl[h][s] = 公司 h 是否控制公司 s

// 对固定的 h，从 {h} 出发反复做不动点迭代，求出 h 控制的全部公司。
// 每一轮把「当前已知被 h 控制的公司」持有的股份汇总一次，超过 50% 就纳入；
// 关系会连锁：本轮新控制到的公司，它的股份下一轮立刻能计入。
void solve_for(int h) {
    ctrl[h][h] = true; // 条件一：控制自己

    while (true) {
        bool added = false; // 本轮是否有新公司被控制
        for (int s = 1; s <= v; s++) {
            if (ctrl[h][s])
                continue;
            // 汇总所有受 h 控制的公司（含 h 自己）持有的 s 的股份
            ll stake = 0;
            for (int c = 1; c <= v; c++)
                if (ctrl[h][c])
                    stake += own[c][s];
            if (stake > MAJORITY) { // 严格大于 50%：正好 50% 不算控制
                ctrl[h][s] = true;
                added = true;
            }
        }
        if (!added) // 一整轮没有新增，控制闭包已经取完
            break;
    }
}

int main() {
    scanf("%d", &n);
    for (int k = 1; k <= n; k++) {
        int i, j;
        ll p;
        scanf("%d %d %lld", &i, &j, &p);
        own[i][j] += p; // 同一条持股边可能在输入里出现多次，必须累加
        if (i > v)
            v = i;
        if (j > v)
            v = j;
    }
    if (v < 1)
        v = 1; // 输入为空时也要有一个非空枚举范围

    for (int h = 1; h <= v; h++)
        solve_for(h);

    // 输出所有 h != s 的控制对，双重循环保证按 (h, s) 字典序
    for (int h = 1; h <= v; h++)
        for (int s = 1; s <= v; s++)
            if (ctrl[h][s] && h != s)
                printf("%d %d\n", h, s);
    return 0;
}
