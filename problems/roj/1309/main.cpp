/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:01
 * update_at: 2026-10-05 09:07
 */
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXL = 1005;

int base;        // 进制 N（2 < N <= 10 或 N = 16）
int len;         // 当前数码长度
int a[MAXL];     // 数码数组，低位在前

// 字符转面值：0-9、A-F（含小写）
int char_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

// 判断当前数码序列（低位在前）是否回文
bool is_palindrome() {
    for (int i = 0, j = len - 1; i < j; i++, j--)
        if (a[i] != a[j]) return false;
    return true;
}

// 一次 N 进制加法：a = a + reverse(a)
// 与评测机（原 main.py，已 AC）语义一致：只对原有 len 位做 "除 base 取余" 归化，
// 最高位溢出的进位直接追加落地，不再继续归约（数据可能有越界数码）
void add_reverse() {
    int s[MAXL + 5];  // 逐位求和的结果，s[i] = a[i] + a[len-1-i]
    int n = len;
    int bound = n;    // 只归化原有 len 位，与 Python 的 range(len(s)) 一致
    for (int i = 0; i < len; i++) s[i] = a[i] + a[len - 1 - i];
    for (int i = 0; i < bound; i++) {      // 上界固定为旧 len，新追加的最高位不再归约
        int carry = s[i] / base;
        s[i] %= base;
        if (carry > 0) {
            if (i + 1 < n) s[i + 1] += carry;
            else { s[n] = carry; n++; }    // 最高位进位直接落地
        }
    }
    len = n;
    for (int i = 0; i < len; i++) a[i] = s[i];
}

int main() {
    char str[MAXL];
    scanf("%d %s", &base, str);
    len = strlen(str);
    for (int i = 0; i < len; i++) a[i] = char_value(str[len - 1 - i]); // 低位在前

    // 第 0 步先判初始是否回文，之后最多做 30 次加法
    for (int step = 0; step <= 30; step++) {
        if (is_palindrome()) {
            printf("%d\n", step);
            return 0;
        }
        if (step == 30) break;
        add_reverse();
    }
    printf("Impossible\n");
    return 0;
}
