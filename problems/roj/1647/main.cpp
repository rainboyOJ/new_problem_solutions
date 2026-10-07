/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:23
 * update_at: 2026-10-06 00:23
 */
#include <cstdio>

typedef long long ll;

const int MOD = 2009;   // 题目要求的模数
const int MAXN = 12;    // 原图节点数上限 N <= 10
const int CHAIN = 9;    // 每个原节点拆成 9 个状态：真正到达 + 8 个等待态
const int MAXS = MAXN * CHAIN; // 扩展图节点数上限 9N <= 90

int n;                  // 原图节点数
long long T;            // 要求的恰好时刻

char grid[MAXN][MAXN];  // grid[u][v] 为 '0' 无这条边，为 '1'..'9' 表示边权
int size_all;           // 扩展图节点数 size_all = n * CHAIN

ll base_mat[MAXS][MAXS]; // 扩展图的 0/1 邻接矩阵，也是快速幂的底数
ll res_mat[MAXS][MAXS];  // 累乘结果，最终为 M^T
ll tmp_mat[MAXS][MAXS];  // 矩阵乘法临时存放

// c = a * b (mod MOD)；运算结果恒小于 2009，用 ll 防止内层求和溢出。
void mat_mul(ll a[][MAXS], ll b[][MAXS], ll c[][MAXS]) {
    for (int i = 0; i < size_all; i++) {
        for (int j = 0; j < size_all; j++) {
            ll sum = 0;
            for (int k = 0; k < size_all; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum % MOD;
        }
    }
}

// 把 from 拷回 to，用于矩阵乘法后替换原矩阵。
void mat_copy(ll to[][MAXS], ll from[][MAXS]) {
    for (int i = 0; i < size_all; i++) {
        for (int j = 0; j < size_all; j++) {
            to[i][j] = from[i][j];
        }
    }
}

// 拆点建图：把「边权 1~9 的 N 点图走恰好 T 时间」变成「9N 个点的无权图走恰好 T 步」。
// 状态 (v,0) 表示真正站在节点 v 上，(v,k)(k>=1) 表示还差 k 步才落到节点 v。
void build_matrix() {
    // 原边：走一条耗时 w 的边，先花 1 步进入等待态 (v,w-1)，再沿等待链消耗剩余时间。
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (grid[u][v] != '0') {
                base_mat[u * CHAIN][v * CHAIN + (grid[u][v] - '1')] = 1;
            }
        }
    }
    // 等待链 (v,k) -> (v,k-1)：原地消耗一个单位时间，终点不变。
    for (int v = 0; v < n; v++) {
        for (int k = 1; k < CHAIN; k++) {
            base_mat[v * CHAIN + k][v * CHAIN + k - 1] = 1;
        }
    }
}

int main() {
    scanf("%d %lld", &n, &T);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    size_all = n * CHAIN;
    build_matrix();

    // 单位矩阵作为累乘初值，做 M^T 的矩阵快速幂。
    for (int i = 0; i < size_all; i++) {
        res_mat[i][i] = 1;
    }
    while (T > 0) {
        if (T & 1LL) {
            mat_mul(res_mat, base_mat, tmp_mat);
            mat_copy(res_mat, tmp_mat);
        }
        mat_mul(base_mat, base_mat, tmp_mat);
        mat_copy(base_mat, tmp_mat);
        T >>= 1LL;
    }

    // 时刻 0 只有起点落地状态 (0,0) 为 1，故答案就是 M^T 第 0 行中 (N-1,0) 的分量。
    printf("%lld\n", res_mat[0][(n - 1) * CHAIN]);
    return 0;
}
