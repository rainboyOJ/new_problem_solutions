/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 3000; // 1000! 大约 2568 位

// 大整数乘法：a[0..len_a-1] *= b，b 是一个小整数
// a 是逆序存储的数组，低位在前
int mul_int(int *a, int len_a, int b) {
    int carry = 0;
    for (int i = 0; i < len_a; i++) {
        int prod = a[i] * b + carry;
        a[i] = prod % 10;
        carry = prod / 10;
    }
    while (carry) {
        a[len_a++] = carry % 10;
        carry /= 10;
    }
    return len_a;
}

// 统计大整数 a[0..len-1] 中数码 digit 出现的次数
int count_digit(int *a, int len, int digit) {
    int cnt = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] == digit) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, digit;
        cin >> n >> digit;

        int fact[MAXLEN] = {0};
        fact[0] = 1;      // 0! = 1
        int len = 1;

        // 计算 n!
        for (int i = 2; i <= n; i++) {
            len = mul_int(fact, len, i);
        }

        cout << count_digit(fact, len, digit) << "\n";
    }

    return 0;
}
