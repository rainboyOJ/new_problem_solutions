/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 200; // 拆出的项数最多约 sqrt(2*10000) ≈ 141
const int BIGLEN = 5000; // 乘积最大位数

int n;
int parts[MAXLEN]; // 拆出的数
int part_cnt;

int big[BIGLEN];   // 大整数数组（逆序）
int big_len;

// 大整数乘法：big[0..big_len-1] *= b
void mul_big(int b) {
    int carry = 0;
    for (int i = 0; i < big_len; i++) {
        int prod = big[i] * b + carry;
        big[i] = prod % 10;
        carry = prod / 10;
    }
    while (carry) {
        big[big_len++] = carry % 10;
        carry /= 10;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 贪心拆：从 2 开始尽量取连续数
    int cur = 2;
    int sum = 0;
    while (sum + cur <= n) {
        parts[part_cnt++] = cur;
        sum += cur;
        cur++;
    }

    // 剩下的数从大到小分散加回去
    int remain = n - sum;
    int idx = part_cnt - 1;
    while (remain > 0) {
        parts[idx]++;
        remain--;
        idx--;
        if (idx < 0) idx = part_cnt - 1;
    }

    // 输出拆分方案
    for (int i = 0; i < part_cnt; i++) {
        cout << parts[i] << " ";
    }
    cout << "\n";

    // 计算乘积
    big[0] = 1;
    big_len = 1;
    for (int i = 0; i < part_cnt; i++) {
        mul_big(parts[i]);
    }

    // 输出乘积
    for (int i = big_len - 1; i >= 0; i--)
        cout << big[i];
    cout << "\n";

    return 0;
}
