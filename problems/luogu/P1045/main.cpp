/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 08:51
 * update_at: 2026-07-19 08:51
 */
#include <bits/stdc++.h>
using namespace std;

const int KEEP_DIGITS = 500;

int p;
int answer_digits[KEEP_DIGITS]; // 低位在前，只保存答案的最后 500 位
int base_digits[KEEP_DIGITS];
int temp_digits[KEEP_DIGITS];

// 计算两个 500 位数的乘积，并舍去超过 500 位的高位。
void multiply_mod(const int a[], const int b[], int result[]) {
    long long product[KEEP_DIGITS] = {0};

    for (int i = 0; i < KEEP_DIGITS; i++) {
        if (a[i] == 0) continue;
        for (int j = 0; i + j < KEEP_DIGITS; j++) {
            product[i + j] += a[i] * b[j];
        }
    }

    for (int i = 0; i < KEEP_DIGITS; i++) {
        if (i + 1 < KEEP_DIGITS) {
            product[i + 1] += product[i] / 10;
        }
        result[i] = product[i] % 10;
    }
}

void copy_digits(int target[], const int source[]) {
    for (int i = 0; i < KEEP_DIGITS; i++) {
        target[i] = source[i];
    }
}

// 二进制快速幂计算 2^p，整个过程只保留最后 500 位。
void fast_power() {
    answer_digits[0] = 1;
    base_digits[0] = 2;

    int exponent = p;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            multiply_mod(answer_digits, base_digits, temp_digits);
            copy_digits(answer_digits, temp_digits);
        }

        multiply_mod(base_digits, base_digits, temp_digits);
        copy_digits(base_digits, temp_digits);
        exponent /= 2;
    }
}

void subtract_one() {
    int pos = 0;
    while (answer_digits[pos] == 0) {
        answer_digits[pos] = 9;
        pos++;
    }
    answer_digits[pos]--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> p;

    int digit_count = (int)(p * log10(2.0)) + 1;
    cout << digit_count << '\n';

    fast_power();
    subtract_one();

    for (int i = KEEP_DIGITS - 1; i >= 0; i--) {
        cout << answer_digits[i];
        if (i % 50 == 0) cout << '\n';
    }

    return 0;
}
