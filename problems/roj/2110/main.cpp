/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:30
 * update_at: 2026-10-08 07:30
 */
// 一本通 2110《【例5.1】素数环》
// 题意：把 1..n 排成一个环，使相邻两数之和（含首尾这一对）均为素数，输出任意一组解。
// 数据范围：4 <= n <= 30，time 1000 ms / memory 64 MB。
//
// 关键结论（先判有无解，再搜索）：
//   n >= 4 时相邻两数之和至少为 1+2=3，不可能是素数 2，故相邻和都是奇素数，
//   于是环上每对相邻数必须一奇一偶 => 环上奇偶必须交替。
//   n 为奇数时 1..n 中奇数比偶数多一个，环上必然出现"奇+奇"，其和为偶数且 > 2，
//   不是素数 => 奇数 n 无解。偶数 n（n=4..30）都有解（本地逐点实测）。
//   正因如此先对奇数直接空输出，否则 n=29 的穷举会指数级变慢。
// 偶数 n 用 DFS 回溯：固定 a0=1 破掉"环的旋转对称"，候选值递增枚举，
//   每放一个数就立即判定相邻和是否为素数，找到第一组解就层层返回。
#include <cstdio>

typedef long long ll;

const int MAXN = 30;           // 题面上限 n <= 30
const int PMAX = 2 * MAXN + 1; // 相邻两数之和最大为 n+(n-1) = 59

bool is_prime[PMAX + 1];       // is_prime[s]：相邻两数之和 s 是否为素数
bool used[MAXN + 1];           // used[v]：数字 v 是否已经放进环里
int ring[MAXN];                // ring[0..n-1]：以 1 开头的素数链
ll n;                          // 输入的环长

// 埃氏筛：预处理 0..PMAX 的素数标记，使相邻和判定变成 O(1)
void build_prime_table() {
    for (int s = 0; s <= PMAX; ++s) is_prime[s] = true;
    is_prime[0] = false;
    is_prime[1] = false;
    for (int p = 2; p * p <= PMAX; ++p) {
        if (!is_prime[p]) continue;
        for (int s = p * p; s <= PMAX; s += p) is_prime[s] = false;
    }
}

// ring[0..len-1] 已填好且链上相邻和均为素数，尝试填第 len 个位置；
// 找到一个完整素数环返回 true。len 从 1 开始（ring[0]=1 已固定）。
bool dfs(int len) {
    if (len == n) return is_prime[ring[len - 1] + ring[0]]; // 只剩尾首闭合要检查
    for (int v = 2; v <= n; ++v) {
        if (used[v]) continue;
        if (!is_prime[ring[len - 1] + v]) continue; // 相邻和不是素数，当前分支已死，剪枝
        used[v] = true;
        ring[len] = v;
        if (dfs(len + 1)) return true; // 只要任意一组解，成功信号层层上传
        used[v] = false;               // 失败回溯：撤销 v 的占用
    }
    return false;
}

int main() {
    if (scanf("%lld", &n) != 1) return 0;
    if (n < 1) return 0;           // 题面范围外，防御性退出
    if (n > MAXN) return 0;        // 数组按题面上限静态开，超范围直接退出
    build_prime_table();
    if (n % 2 != 0) return 0;      // 奇数 n 无解：数据约定无解时输出为空，不打印任何内容

    ring[0] = 1;                   // 固定起点消除旋转重复
    used[1] = true;
    if (!dfs(1)) return 0;

    // 输出时把起点 1 挪到末尾：环没有起点，这是同一个环的另一种读法，
    // 与题面样例 `4 3 2 5 6 1`（n=6）以及随仓数据的读法一致。
    for (int i = 1; i < n; ++i) printf("%d ", ring[i]);
    printf("%d\n", ring[0]);
    return 0;
}
