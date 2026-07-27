/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 505;

char a_str[MAXLEN], b_str[MAXLEN];
int  a_int[MAXLEN], b_int[MAXLEN]; // 逆序存储的数字，a_int[0] 是个位
int  res[MAXLEN];                  // 加法结果

// 把数字字符串 s 逆序存入数组 arr，返回位数
int to_array(char *s, int *arr) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        arr[i] = s[len - 1 - i] - '0'; // 低位存前面
    }
    return len;
}

// 高精度加法：a_int[0..lena-1] + b_int[0..lenb-1] => res[0..]
int big_add(int *a, int lena, int *b, int lenb) {
    int carry = 0; // 进位
    int max_len = max(lena, lenb);
    for (int i = 0; i < max_len; i++) {
        int sum = carry;
        if (i < lena) sum += a[i];
        if (i < lenb) sum += b[i];
        res[i] = sum % 10; // 当前位
        carry = sum / 10;  // 进位
    }
    if (carry) {          // 如果最高位还有进位
        res[max_len] = carry;
        return max_len + 1;
    }
    return max_len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a_str >> b_str;

    int lena = to_array(a_str, a_int);
    int lenb = to_array(b_str, b_int);
    int len_res = big_add(a_int, lena, b_int, lenb);

    // 逆序输出结果
    for (int i = len_res - 1; i >= 0; i--)
        cout << res[i];
    cout << "\n";

    return 0;
}
