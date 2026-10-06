/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:15
 * update_at: 2026-10-06 13:15
 */

// 4×N 网格上的哈密顿回路计数：按列扫描，切口上横边的配对方式只有 7 种，
// 逐列做一次固定的线性转移；N=1000 时答案约 340 位，用压位高精度加法维护。
#include <cstdio>

typedef long long ll;

const ll BASE = 1000000000LL; // 大数按 10^9 压位，每个数组元素存 9 位十进制
const int MAXL = 55;          // N=1000 时答案约 340 位（39 段），多留空间给进位

// 状态编号（切口上配在一起的两行）：
// 0: 空切面   1:{01}   2:{03}   3:{12}   4:{23}   5:{01,23}   6:{03,12}
ll big[7][MAXL];
int len[7]; // big[s] 当前的段数

ll tmp[7][MAXL];
int tlen[7]; // 下一列的转移结果，算完再拷回 big，避免边加边覆盖

// tmp[dst] += big[src]（把旧列的状态加进新列的某个状态）
void add_old(int dst, int src) {
    if (len[src] > tlen[dst]) tlen[dst] = len[src];
    for (int i = 0; i < len[src]; i++) {
        tmp[dst][i] += big[src][i];
        if (tmp[dst][i] >= BASE) { // 压位加法的进位
            tmp[dst][i] -= BASE;
            tmp[dst][i + 1] += 1;
            if (tlen[dst] < i + 2) tlen[dst] = i + 2;
        }
    }
}

void solve() {
    int n;
    scanf("%d", &n);

    // 邮局左侧切口是空的：只有空切面一种初始状态
    len[0] = 1;
    big[0][0] = 1;

    // 扫过第 1 … n-1 列；第 n 列右侧没有横边，只能收口
    if (n == 1) { // 只有一列 4 个路口连不成环，路线数为 0
        printf("0\n");
        return;
    }
    for (int col = 1; col <= n - 1; col++) {
        // 新列的临时结果整块清零，避免上一列残留值混进答案
        for (int s = 0; s < 7; s++)
            for (int i = 0; i < MAXL; i++) tmp[s][i] = 0;
        for (int s = 0; s < 7; s++) tlen[s] = 0;
        // 转移表：新 {01}、{23}、{03,12} 来自旧 {03} 和 {03,12}
        add_old(1, 2); add_old(1, 6);
        add_old(4, 2); add_old(4, 6);
        add_old(6, 2); add_old(6, 6);
        // 新 {03} 来自除 {03}、{03,12} 外的任意旧切面
        add_old(2, 0); add_old(2, 1); add_old(2, 3); add_old(2, 4); add_old(2, 5);
        // 新 {01,23} 来自旧 空切面、{01}、{23}、{01,23}
        add_old(5, 0); add_old(5, 1); add_old(5, 4); add_old(5, 5);
        // 新 {12} 只来自旧 {03}
        add_old(3, 2);
        // 空切面只在第一列左侧出现，转移后恒为 0

        for (int s = 0; s < 7; s++) {
            len[s] = tlen[s];
            for (int i = 0; i < len[s]; i++) big[s][i] = tmp[s][i];
        }
    }

    // 收口数 = {03} + {03,12}；每条回路顺、逆时针算两条路线，再乘 2
    // 用大数加法直接算 ans = 2 * (big[2] + big[6])
    ll ans[MAXL];
    int alen = 0;
    if (len[2] > len[6]) alen = len[2]; else alen = len[6];
    for (int i = 0; i < alen; i++) {
        ll s = 0;
        if (i < len[2]) s += big[2][i];
        if (i < len[6]) s += big[6][i];
        ans[i] = s;
    }
    for (int i = 0; i < alen; i++) ans[i] *= 2; // 方向因子 2
    for (int i = 0; i < alen; i++) {            // 逐位进位
        if (ans[i] >= BASE) {
            ans[i + 1] += ans[i] / BASE;
            ans[i] %= BASE;
            if (alen < i + 2) alen = i + 2;
        }
    }
    while (alen > 1 && ans[alen - 1] == 0) alen--; // 去掉前导零段

    printf("%lld", ans[alen - 1]); // 最高段不补零
    for (int i = alen - 2; i >= 0; i--) printf("%09lld", ans[i]); // 其余段补足 9 位
    printf("\n");
}

int main() {
    solve();
    return 0;
}
