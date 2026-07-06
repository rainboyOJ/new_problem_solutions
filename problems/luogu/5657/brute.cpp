// brute.cpp：小数据/教学版，按格雷码的递归定义直接定位第 k 个串。
#include <bits/stdc++.h>
using namespace std;

int n;
unsigned long long k;

// solve_gray(len, idx)：返回 len 位格雷码中编号为 idx 的二进制串。
string solve_gray(int len, unsigned long long idx) {
    if (len == 1) {
        return idx == 0 ? "0" : "1";
    }

    unsigned long long half = 1ULL << (len - 1);

    if (idx < half) {
        // 前半段：保持 len-1 位格雷码原顺序，前面补 0。
        return "0" + solve_gray(len - 1, idx);
    }

    // 后半段：使用 len-1 位格雷码的逆序，前面补 1。
    unsigned long long reversed_idx = (half - 1) - (idx - half);
    return "1" + solve_gray(len - 1, reversed_idx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    cout << solve_gray(n, k) << '\n';

    return 0;
}
