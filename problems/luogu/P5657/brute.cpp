/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:28
 * update_at: 2026-10-01 20:28
 */
// brute.cpp：小数据/教学版，按格雷码的递归定义直接定位第 k 个串，用来辅助对拍。
// 每一层只做一次选择：判断 k 落在前半段还是后半段，再决定这一位填 0 还是 1。
// 递归深度只有 n 层，所以 n = 64 也能跑；它只是写法朴素，不代表复杂度高。
#include <bits/stdc++.h>
using namespace std;

// 与 main.cpp 保持一致的输入范围：k 可能达到 2^64-1，必须用无符号 64 位。
typedef unsigned long long ull;

int n; // 编码位数
ull k; // 编号

// solve_gray(len, idx)：返回 len 位格雷码中编号为 idx 的二进制串。
string solve_gray(int len, ull idx) {
    if (len == 1) {
        return idx == 0 ? "0" : "1";
    }

    ull half = 1ULL << (len - 1); // 前半段的串数，len <= 64 时最多到 2^63

    if (idx < half) {
        // 前半段：保持 len-1 位格雷码原顺序，前面补 0。
        return "0" + solve_gray(len - 1, idx);
    }

    // 后半段：使用 len-1 位格雷码的逆序，前面补 1。
    ull reversed_idx = (half - 1) - (idx - half);
    return "1" + solve_gray(len - 1, reversed_idx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    cout << solve_gray(n, k) << '\n';

    return 0;
}
