/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:34
 * update_at: 2026-10-06 18:34
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 30;          // N < 29
const char IMPOSSIBLE[] = "Oh,it's impossible~!!";

int n;                        // 开关数量
ll row[MAXN];                 // 第 j 行：低 n 位为系数，第 n 位为右端常数

// 读入一组数据并构建 n 个 GF(2) 方程
void build_equations() {
    static int st[MAXN], ed[MAXN];
    for (int i = 0; i < n; ++i) scanf("%d", &st[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &ed[i]);

    for (int j = 0; j < n; ++j) row[j] = 0;

    int i, j;
    while (scanf("%d%d", &i, &j) == 2 && (i || j)) {
        // 操作第 i 个开关会翻转第 j 个开关：变量 x_i 进入第 j 行
        row[j - 1] ^= 1LL << (i - 1);
    }

    // 自环：操作第 j 个开关必定翻转第 j 个开关
    for (int j = 0; j < n; ++j) row[j] |= 1LL << j;

    // 右端常数：第 j 位是否需要翻转
    for (int j = 0; j < n; ++j) row[j] ^= (ll)(st[j] ^ ed[j]) << n;
}

// 高斯消元求自由元个数；返回 -1 表示出现 0 = 1 的矛盾行
int free_variables() {
    int rank = 0;
    for (int col = 0; col < n; ++col) {
        int pivot = -1;
        for (int k = rank; k < n; ++k) {
            if (row[k] >> col & 1LL) {
                pivot = k;
                break;
            }
        }
        if (pivot < 0) continue; // 无主元，该列自由

        swap(row[rank], row[pivot]);
        for (int k = 0; k < n; ++k) {
            if (k != rank && (row[k] >> col & 1LL)) row[k] ^= row[rank];
        }
        ++rank;
    }

    // 检查只剩常数位的矛盾行 0 = 1
    for (int k = 0; k < n; ++k) {
        if (row[k] == (1LL << n)) return -1;
    }
    return n - rank;
}

int main() {
    int K;
    scanf("%d", &K);
    while (K--) {
        scanf("%d", &n);
        build_equations();
        int free_cnt = free_variables();
        if (free_cnt < 0) {
            printf("%s\n", IMPOSSIBLE);
        } else {
            printf("%lld\n", 1LL << free_cnt);
        }
    }
    return 0;
}
