/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 00:22
 * update_at: 2026-10-07 00:35
 */
// 这是 STL 写法：把 32 位整数装进 bitset<32>，用 (b << 16) | (b >> 16) 交换高低 16 位，
// 再用 to_ulong() 转回十进制输出。对应 cppbook 的《bitset：一组二进制开关》。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

unsigned long long number; // 输入可能达到 2^32-1，超过 int，所以用 unsigned long long 读入

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> number;

    // bitset<32> 把整数摊成 32 个开关：下标 0 是最低位，下标 31 是最高位。
    // 题面说的“前 16 位（高位）”正是下标 16..31，“后 16 位（低位）”是下标 0..15。
    bitset<32> bits(number);

    // 左移 16 位把低 16 位顶到高位，右移 16 位把高 16 位落回低位；
    // 两段互不重叠，按位或合并就完成了交换。移出 32 位宽度的位直接丢弃，不影响结果。
    bitset<32> swapped = (bits << 16) | (bits >> 16);

    // 转回整数输出十进制。32 位值一定能被 unsigned long 表示，不会触发 overflow_error。
    unsigned long answer = swapped.to_ulong();
    cout << answer << '\n';

    return 0;
}
