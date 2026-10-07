/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:36
 * update_at: 2026-10-06 18:36
 */
// main.cpp：把每秒的搬运动作写成 65×65 矩阵，用周期合成 + 矩阵快速幂解石头游戏。
// 关键点：所有操作序列每秒循环，整周期 P = lcm(各序列长度) ≤ 60；
// 加 0~9 个石头是仿射项，补一个恒为 1 的「外界」分量吸收进矩阵；
// 推出网格的石头直接消失，绝不能回流进外界，否则注入量会指数爆炸。

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:35
 * update_at: 2026-10-06 18:35
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 8;          // 网格每边最大 8
const int V = MAXN * MAXN;   // 格子数上限 64
const int D = V + 1;         // 状态维数：格子 + 外界，最大 65
const int MAXP = 60;         // 周期上限：lcm(1..6) = 60

int n, m, act;               // 网格规格与操作序列种数
ll t;                        // 总秒数，最大 1e8
char grid[MAXN][MAXN + 1];   // grid[i][j] = 该格使用的操作序列编号（字符 '0'~'9'）
char prog[10][10];           // prog[k] = 第 k 个操作序列，长度 ≤ 6
int plen[10];                // 每个操作序列的长度

ll period_mat[MAXP][D][D];   // period_mat[s] = 第 s 秒的转移矩阵（mat[新][旧]）
ll cycle_mat[D][D];          // 一个完整周期的合成矩阵 C
ll pow_mat[D][D];            // 矩阵快速幂的工作数组
ll tmp_mat[D][D];            // 矩阵乘法的暂存数组
ll vec[D];                   // 当前状态向量（含外界分量）
ll ans_vec[D];               // 乘完矩阵后的结果向量

// 两个方向增量：N 上 / S 下 / W 左 / E 右
int dir_dx(char c) {
    if (c == 'N') return -1;
    if (c == 'S') return 1;
    return 0;
}

int dir_dy(char c) {
    if (c == 'W') return -1;
    if (c == 'E') return 1;
    return 0;
}

// 求 a、b 的最小公倍数
ll gcd_ll(ll a, ll b) {
    while (b) {
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}

ll lcm_ll(ll a, ll b) {
    return a / gcd_ll(a, b) * b;
}

// 构造第 s 秒的转移矩阵，存进 res：res[新下标][旧下标]
void build_second_matrix(ll res[][D], int s) {
    memset(res, 0, sizeof(ll) * D * D);
    int outside = n * m; // 外界下标：恒为 1，只作为数字操作的注水源
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int pos = i * m + j;
            int k = grid[i][j] - '0';
            char c = prog[k][s % plen[k]];
            if (c >= '0' && c <= '9') {
                res[pos][pos] = 1;              // 原有石头原地保留
                res[pos][outside] = c - '0';    // 外界每秒恒定注入 d 个
            } else if (c != 'D') {
                int ni = i + dir_dx(c);
                int nj = j + dir_dy(c);
                // 整格石头搬到相邻格；越界时不写任何项，整列保持 0，石头消失
                if (ni >= 0 && ni < n && nj >= 0 && nj < m)
                    res[ni * m + nj][pos] = 1;
            }
            // 'D'：整列保持 0，石头被拿走
        }
    }
    res[outside][outside] = 1; // 外界自保持为 1，注入量才是常数
}

// c = a × b（都是 D×D）
void mat_mul(ll c[][D], ll a[][D], ll b[][D]) {
    memset(tmp_mat, 0, sizeof(tmp_mat));
    for (int i = 0; i < D; i++)
        for (int k = 0; k < D; k++) {
            if (a[i][k] == 0) continue; // 稀疏跳零，剪掉大量无效乘法
            for (int j = 0; j < D; j++)
                tmp_mat[i][j] += a[i][k] * b[k][j];
        }
    memcpy(c, tmp_mat, sizeof(tmp_mat));
}

int main() {
    scanf("%d %d %lld %d", &n, &m, &t, &act);
    for (int i = 0; i < n; i++)
        scanf("%s", grid[i]);
    for (int k = 0; k < act; k++) {
        scanf("%s", prog[k]);
        plen[k] = strlen(prog[k]);
    }

    // 整周期 P = 各序列长度的最小公倍数（每个 ≤ 6，所以 P ≤ 60）
    int P = 1;
    for (int k = 0; k < act; k++)
        P = (int)lcm_ll(P, plen[k]);

    // 建出周期内每秒的矩阵，并按时间顺序合成整周期矩阵 C = M_{P-1}···M_1 M_0
    for (int s = 0; s < P; s++)
        build_second_matrix(period_mat[s], s);
    for (int i = 0; i < D; i++)
        cycle_mat[i][i] = 1; // 单位矩阵作乘法初值
    for (int s = 0; s < P; s++)
        mat_mul(cycle_mat, period_mat[s], cycle_mat); // 后发生的动作乘在左边

    // q = t / P 个整周期用快速幂，余下 r = t % P 秒逐个乘单秒矩阵
    ll q = t / P;
    int r = (int)(t % P);

    for (int i = 0; i < D; i++)
        pow_mat[i][i] = 1;
    while (q) {
        if (q & 1)
            mat_mul(pow_mat, pow_mat, cycle_mat);
        mat_mul(cycle_mat, cycle_mat, cycle_mat);
        q >>= 1;
    }

    // 初始状态：石头全为 0，只有外界恒为 1
    memset(vec, 0, sizeof(vec));
    vec[n * m] = 1;

    // 物理顺序：先过 q 个整周期（C^q 在右），再过余下 r 秒
    for (int i = 0; i < D; i++) {
        ans_vec[i] = 0;
        for (int j = 0; j < D; j++)
            ans_vec[i] += pow_mat[i][j] * vec[j];
    }
    for (int s = 0; s < r; s++) {
        ll nxt[D]; // nxt[新] = M_s × ans_vec
        for (int i = 0; i < D; i++) {
            nxt[i] = 0;
            for (int j = 0; j < D; j++)
                nxt[i] += period_mat[s][i][j] * ans_vec[j];
        }
        for (int i = 0; i < D; i++)
            ans_vec[i] = nxt[i];
    }

    // 只统计真实格子分量，外界只是记账位
    ll ans = 0;
    for (int i = 0; i < n * m; i++)
        if (ans_vec[i] > ans)
            ans = ans_vec[i];
    printf("%lld\n", ans);
    return 0;
}
