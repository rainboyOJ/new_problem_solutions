/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 2005;

char a_str[MAXLEN], b_str[MAXLEN];
int  a_int[MAXLEN], b_int[MAXLEN]; // 逆序存储
int  res[MAXLEN * 2];              // 乘积最多 lena+lenb 位

// 字符串转逆序数字数组
int to_array(char *s, int *arr) {
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        arr[i] = s[len - 1 - i] - '0';
    return len;
}

// 高精度乘法：a[0..lena-1] * b[0..lenb-1] => res[0..]
int big_mul(int *a, int lena, int *b, int lenb) {
    // 每一位相乘
    for (int i = 0; i < lena; i++) {
        for (int j = 0; j < lenb; j++) {
            res[i + j] += a[i] * b[j];
        }
    }
    // 统一处理进位
    int len_res = lena + lenb;
    for (int i = 0; i < len_res; i++) {
        if (res[i] >= 10) {
            res[i + 1] += res[i] / 10; // 进位到高位
            res[i] %= 10;               // 保留个位
        }
    }
    // 去掉前导 0
    while (len_res > 1 && res[len_res - 1] == 0)
        len_res--;
    return len_res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a_str >> b_str;

    int lena = to_array(a_str, a_int);
    int lenb = to_array(b_str, b_int);
    int len_res = big_mul(a_int, lena, b_int, lenb);

    for (int i = len_res - 1; i >= 0; i--)
        cout << res[i];
    cout << "\n";

    return 0;
}
