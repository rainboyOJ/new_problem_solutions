/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:31
 * update_at: 2026-11-10 20:15
 */
// main.cpp：位运算与状态统计，用 unsigned __int128 消除 2^64 溢出特判。
// 核心思路：由于题目保证所有 q_i 互不相同，每种饲料仅受唯一二进制位限制。
// 已有动物掩码 zoo_mask 记录哪些位已有 1（对应饲料已买）；
// 只有当某位存在规则约束且 zoo_mask 该位为 0 时，新动物才不能取 1。
// 统计所有可自由取值的位数 free_cnt，最终答案即为 ((unsigned __int128)1 << free_cnt) - n。
#include <iostream>

using namespace std;

typedef unsigned long long ull;
typedef unsigned __int128 u128;

int n, m, c, k;
int rule_p[100005];   // rule_p[i]：第 i 条要求限制的二进制位编号（0 ~ k-1）
int rule_q[100005];   // rule_q[i]：第 i 条要求对应的饲料编号（1 ~ c）
bool bought[100005];  // bought[q]：第 q 种饲料是否已被现有动物引入
bool bad_bit[65];     // bad_bit[p]：新动物第 p 位不能取 1

// 打印 unsigned __int128 整数
void print_u128(u128 x) {
    if (x == 0) {
        cout << 0 << '\n';
        return;
    }
    char buf[50];
    int top = 0;
    while (x > 0) {
        buf[top++] = char('0' + (x % 10));
        x /= 10;
    }
    while (top > 0) {
        cout << buf[--top];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c >> k;

    // 读入已有动物，合并为全局位掩码
    ull zoo_mask = 0;
    for (int i = 0; i < n; i++) {
        ull a;
        cin >> a;
        zoo_mask |= a;
    }

    for (int i = 0; i < m; i++) {
        cin >> rule_p[i] >> rule_q[i];
    }

    // 现有动物第 p 位为 1，说明这条要求对应的饲料已经被引入。
    // 判据必须按饲料编号 q 去重：同一种饲料可能被多条要求引用，
    // 只要任一相关位已有 1，该饲料就已到手，不必再受限制。
    for (int i = 0; i < m; i++) {
        if ((zoo_mask >> rule_p[i]) & 1ULL) {
            bought[rule_q[i]] = true;
        }
    }

    // 饲料尚未引入的要求，把它的二进制位标为禁止取 1。
    for (int i = 0; i < m; i++) {
        if (!bought[rule_q[i]]) {
            bad_bit[rule_p[i]] = true;
        }
    }

    // 统计新动物可以自由取 0 或 1 的位数
    int free_cnt = 0;
    for (int p = 0; p < k; p++) {
        if (!bad_bit[p]) {
            free_cnt++;
        }
    }

    // 用 128 位无符号整数承载 2^free_cnt，直接消除 2^64 溢出的特判
    u128 total = (u128)1 << free_cnt;
    u128 ans = total - n;

    print_u128(ans);

    return 0;
}
