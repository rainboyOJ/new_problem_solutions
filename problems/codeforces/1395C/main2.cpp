/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-05 19:31
 * update_at: 2026-11-05 19:45
 */
// main2.cpp：把"已确定位的前缀约束"显式存成二维候选桶，不再每次重算完整掩码判定。
/*
 * 思路：
 *   答案从高位到低位确定，同时维护 alive[i][j]：
 *   在已经确定的高位约束下，第 i 行还能不能选择 b[j]。
 *
 *   每一轮分两次扫描：
 *   1. 判定这一位能否清零：每行是否还有"活着的、该位为 0"的候选值。
 *      若某行一个都没有，这一位只能留 1，候选桶保持原样。
 *   2. 全部行都能取到 0 时，把各行该位为 1 的活候选全部淘汰。
 *
 *   这与"每轮用掩码重算一遍判定"是同一件事：
 *   桶里保留的正是满足已确定 0 位的候选，淘汰动作等于给掩码加一条限制。
 *
 * 复杂度 O(10 * n * m)：每轮一次判定扫描 + 一次淘汰扫描。
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n, m;
int a[MAXN];              // a[i]：第 i 行的第一个操作数
int b[MAXN];              // b[j]：备选的第二个操作数
bool alive[MAXN][MAXN];   // alive[i][j]：第 i 行还能不能选 b[j]

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int j = 1; j <= m; j++) cin >> b[j];
}

// 第 i 行是否还有"活着的、在 bit 位上为 0"的候选值
bool row_can_zero(int i, int bit) {
    for (int j = 1; j <= m; j++) {
        if (!alive[i][j]) continue;
        if (((a[i] & b[j]) >> bit & 1) == 0) return true;
    }
    return false;
}

// 这一位能清零时，淘汰各行该位为 1 的活候选
void drop_bit_one(int bit) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!alive[i][j]) continue;
            if (((a[i] & b[j]) >> bit & 1) == 1) alive[i][j] = false;
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) alive[i][j] = true;
    }

    int ans = 0;
    // 第 9 位不可能出现在 a[i]&b[j] 里，多扫一位无副作用
    for (int bit = 9; bit >= 0; bit--) {
        bool all_can_zero = true;
        for (int i = 1; i <= n; i++) {
            if (!row_can_zero(i, bit)) {
                all_can_zero = false;
                break;
            }
        }

        if (!all_can_zero) {
            // 低位还没限制都清不掉这一位，它只能为 1；桶不用动
            ans |= 1 << bit;
            continue;
        }

        // 每行都留了至少一个该位为 0 的候选，淘汰后桶不会变空
        drop_bit_one(bit);
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
