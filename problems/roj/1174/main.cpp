/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:18
 * update_at: 2026-10-05 04:18
 */
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 205;        // 题目输入最多 200 位，再加 1 用于 "\0"
const int MAXR = 410;        // 两个 200 位数相乘结果最多 400 位

char sa[MAXN], sb[MAXN];     // 读入的两个大整数字符串（按题面不含前导 0）
int a[MAXN], b[MAXN];        // a[i] / b[i]：i 是低位序号（i=0 为个位），每位存十进制 0..9
int c[MAXR];                 // 乘积 c，c[i] 同理：i 是低位序号，0..9；运算中可能 >=10，最后统一进位

int la, lb;                  // a、b 的有效位数（不含 '\0'）

// 把字符数组 sa 转成低位在前的数字数组 a，并返回有效位数
void read_num(char s[], int num[], int &len) {
    len = (int)strlen(s);
    // 输入是高位在前（人类书写顺序），逐位取倒数写入 num[]，变成低位在前
    for (int i = 0; i < len; i++) {
        num[i] = s[len - 1 - i] - '0';
    }
}

// 核心：按 a 的每一位 i 和 b 的每一位 j 累加 a[i]*b[j] 到 c[i+j]
void multiply() {
    // 双重循环：i 是 a 的位（低位在前），j 是 b 的位
    for (int i = 0; i < la; i++) {
        for (int j = 0; j < lb; j++) {
            c[i + j] += a[i] * b[j];
        }
    }
}

// 把 c 中可能 >=10 的每位处理成 0..9，并把多余的进位写到更高位
void normalize() {
    // 进位一直向前传递；MAXR 足够装 200 位 × 200 位的 400 位结果
    for (int i = 0; i < MAXR - 1; i++) {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }
}

// 找到 c 的最高有效位下标（低位在前）；全 0 时返回 0
int top_digit() {
    int p = MAXR - 1;
    while (p > 0 && c[p] == 0) p--;
    return p;
}

int main() {
    // 题目两行输入，每行一个不超过 200 位的非负整数
    if (!fgets(sa, MAXN, stdin)) return 0;
    if (!fgets(sb, MAXN, stdin)) return 0;

    // fgets 会保留末尾 '\n'，这里按"两行大整数"处理，把换行去掉再交给 read_num
    sa[strcspn(sa, "\r\n")] = '\0';
    sb[strcspn(sb, "\r\n")] = '\0';

    read_num(sa, a, la);
    read_num(sb, b, lb);

    multiply();
    normalize();

    // 输出：从最高有效位到最低位按十进制写出（低位在前的 c[] 正好反着打印）
    int top = top_digit();
    for (int i = top; i >= 0; i--) {
        putchar('0' + c[i]);
    }
    putchar('\n');
    return 0;
}