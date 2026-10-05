/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:53
 * update_at: 2026-10-05 12:53
 */

// main.cpp：一本通 5.6 练习 3「特别行动队」（APIO 2010 特别行动队）。
// 编号必须连续，所以任何编队方案就是把序列切成若干连续段的划分，
// 设 f[i] 为前 i 名士兵的最大修正战斗力和，枚举最后一支队伍的起点 j：
//     f[i] = max_{j<i} { f[j] + g(S_i - S_j) }，g(u) = a*u^2 + b*u + c。
// 展开 g 后，只与 j 有关的项收成截距 Y_j = f[j] + a*S_j^2 - b*S_j，
// 与 i 有关的项提到 max 外面，转移变成「在直线族 l_j(u) = S_j*u + Y_j 的
// 上包络上查询 u_i = -2*a*S_i」：
//     f[i] = max_j { S_j*u_i + Y_j } + a*S_i^2 + b*S_i + c。
// x_i >= 1 使直线斜率 S_j 随 j 递增，a < 0 使查询点 u_i 随 i 递增，
// 两条单调同向，于是用单调队列维护上包络即可：队头弹出已被超过的直线，
// 队尾弹出被新直线压得不再可能最优的直线，摊还 O(1)，总时间 O(n)。

#include <cstdio>

typedef long long ll;
typedef __int128 lll;

const int MAXN = 1000005; // n 的上限

ll n;           // 士兵总数
ll a, b, c;     // 经验公式系数，满足 a < 0
ll pre[MAXN];   // pre[i] = 前 i 名士兵的初始战斗力之和 S_i，S_0 = 0
ll f[MAXN];     // f[i] = 前 i 名士兵编队后能得到的最大修正战斗力和
ll y[MAXN];     // y[i] = 直线 l_i 的截距 Y_i = f[i] + a*S_i^2 - b*S_i
int hull[MAXN]; // 上包络上的直线编号队列，斜率 S_j 随入队递增
int head;       // 队列头下标，head 指向当前最优直线
int tail;       // 队列尾下标

// 快速读入，n 最大 10^6，避免 cin / scanf 的额外开销
ll read_ll() {
    int ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9')) {
        ch = getchar();
    }
    ll sign = 1;
    if (ch == '-') {
        sign = -1;
        ch = getchar();
    }
    ll value = 0;
    while (ch >= '0' && ch <= '9') {
        value = value * 10 + (ch - '0');
        ch = getchar();
    }
    return sign * value;
}

// 两个数相乘，用 __int128 承接结果：叉积可达 10^25，超出 long long
lll product(lll x, lll y) {
    return x * y;
}

// 直线 l_j 在查询点 u 处的取值 l_j(u) = S_j * u + Y_j
lll value_at(int j, ll u) {
    return y[j] + product(u, pre[j]);
}

// 直线 q 是否被直线 p 与 i 夹在上包络之下（q 的领先区间为空，可以丢掉）。
// 等价于两交点位置比较 x[p][q] >= x[q][i]，即
//     (Y_q - Y_p) * (S_i - S_q) <= (Y_i - Y_q) * (S_q - S_p)，
// 交叉相乘代替除法，既避免浮点误差也不需要判分母符号。
// 取等号时三线共点，丢掉中间那条不影响答案。
bool is_hidden(int p, int q, int i) {
    return product(y[q] - y[p], pre[i] - pre[q])
           <= product(y[i] - y[q], pre[q] - pre[p]);
}

void solve() {
    n = read_ll();
    a = read_ll();
    b = read_ll();
    c = read_ll();
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + read_ll(); // 前缀和
    }

    head = 0;
    tail = 0;
    hull[0] = 0; // 只有 j = 0 可选，f[0] = 0、S_0 = 0、Y_0 = 0

    for (int i = 1; i <= n; i++) {
        ll s = pre[i];
        ll u = -2 * a * s; // 查询点 u_i = -2*a*S_i，随 i 严格递增

        // 插入前先查询：次队头在 u_i 处已不劣于队头，说明队头的领先区间已经过去，
        // 而后续查询点只会更大，队头此后永远用不到，直接弹出
        while (tail > head) {
            int first = hull[head];
            int second = hull[head + 1];
            if (value_at(first, u) <= value_at(second, u)) {
                head++;
            } else {
                break;
            }
        }
        int j = hull[head]; // 最优切点：最后一支队伍的起点是 j+1

        ll len = s - pre[j]; // 最后一支队伍的初始战斗力
        f[i] = f[j] + a * len * len + b * len + c;
        y[i] = f[i] + a * s * s - b * s; // 新直线的截距

        // 新直线斜率 S_i 最大，只会接在包络右端；入队前检查队尾两条直线，
        // 若 q 还没超过 p 就被 i 超过，q 的领先区间为空，弹出
        while (tail > head) {
            int p = hull[tail - 1];
            int q = hull[tail];
            if (is_hidden(p, q, i)) {
                tail--;
            } else {
                break;
            }
        }
        tail++;
        hull[tail] = i;
    }

    printf("%lld\n", f[n]);
}

int main() {
    solve();
    return 0;
}
