/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 08:59
 * update_at: 2026-07-19 08:59
 */
// brute.cpp：小数据朴素解，逐次乘 2，用来展示部分分做法并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int KEEP_DIGITS = 500;

int p;
int digits[KEEP_DIGITS]; // 低位在前，只保存当前数的最后 500 位

void multiply_by_two() {
    int carry = 0;
    for (int i = 0; i < KEEP_DIGITS; i++) {
        int value = digits[i] * 2 + carry;
        digits[i] = value % 10;
        carry = value / 10;
    }
}

void subtract_one() {
    int pos = 0;
    while (digits[pos] == 0) {
        digits[pos] = 9;
        pos++;
    }
    digits[pos]--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> p;

    int digit_count = (int)(p * log10(2.0)) + 1;
    cout << digit_count << '\n';

    digits[0] = 1;
    for (int i = 1; i <= p; i++) {
        multiply_by_two();
    }
    subtract_one();

    for (int i = KEEP_DIGITS - 1; i >= 0; i--) {
        cout << digits[i];
        if (i % 50 == 0) cout << '\n';
    }

    return 0;
}
