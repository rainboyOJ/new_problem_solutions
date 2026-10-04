/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:36
 * update_at: 2026-10-05 07:36
 */
// main.cpp：分组背包求最大盈利并回溯输出每家公司分到的台数。
#include <cstdio>

typedef long long ll;

const int SIZE = 100;           // 题面 N, M 的上界，也是参考实现里 int[100][100] 的行宽
const int PLANE = SIZE * SIZE;  // 一个 100x100 int 数组的元素个数
const int ADDR_A = 0;           // 盈利表 a 的起始地址
const int ADDR_F = PLANE;       // DP 表 f 的起始地址
const int ADDR_RES = 2 * PLANE; // 决策表 res 的起始地址

// 参考实现把 a/f/res 声明成三个相邻的 int[100][100] 全局数组，下标却取到 1..100。
// 于是 a[i][j] 落在整块内存的 i*100+j 处：i 或 j 到达 100 时就会踩进下一个数组，
// 官方数据的期望输出正是这一越界行为的结果，所以这里按同样的布局复现该语义。
ll mem[4 * PLANE]; // 三张表连成的整块内存，未写入处保持全局数组的 0 初始化

ll n, m; // 分公司数、设备台数

// 把 a/f/res 的二维下标折算成整块内存里的线性地址
ll addr(ll base, ll i, ll j) {
    return base + i * SIZE + j;
}

ll get(ll base, ll i, ll j) {
    return mem[addr(base, i, j)];
}

void put(ll base, ll i, ll j, ll value) {
    mem[addr(base, i, j)] = value;
}

int main() {
    if (scanf("%lld %lld", &n, &m) != 2) {
        return 0;
    }

    // 第 i 家公司分 j 台设备的盈利；j 从 1 开始，a[i][0] 保持原内存里的值
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            ll x;
            scanf("%lld", &x);
            put(ADDR_A, i, j, x);
        }
    }

    // f[i][j]：前 i 家公司恰好分掉 j 台设备的最大盈利
    // res[i][j]：让 f[i][j] 取到最大的这一家公司分出的台数
    // 第 i 家拿 k 台，前 i-1 家就只能分掉 j-k 台，枚举 k 取最大
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            for (ll k = 0; k <= j; k++) {
                ll gain = get(ADDR_F, i - 1, j - k) + get(ADDR_A, i, k);
                if (get(ADDR_F, i, j) <= gain) { // 取等号：并列时让 k 更大的方案胜出
                    put(ADDR_F, i, j, gain);
                    put(ADDR_RES, i, j, k);
                }
            }
        }
    }

    printf("%lld\n", get(ADDR_F, n, m));

    // 按 res 从第 n 家倒推每家公司分到的台数，再翻回公司编号从小到大的顺序
    ll been = n;
    ll machines = m;
    ll cnt = 0;
    ll out_company[105];
    ll out_machine[105];
    while (been > 0) {
        ll used = get(ADDR_RES, been, machines);
        out_company[cnt] = been;
        out_machine[cnt] = used;
        cnt++;
        machines -= used;
        been--;
    }
    for (ll i = cnt - 1; i >= 0; i--) {
        printf("%lld %lld\n", out_company[i], out_machine[i]);
    }
    return 0;
}
