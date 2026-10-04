/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:18
 * update_at: 2026-10-05 04:18
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXLEN = 105; // 输入位数不超过 100，多开几位防止越界
char num[MAXLEN];       // 题面给出的十进制大整数
char quotient[MAXLEN];  // 保存商的每一位

int main() {
    scanf("%s", num);
    ll len = strlen(num);
    int remainder = 0; // 当前余数，始终在 [0, 13) 之间
    int qlen = 0;      // 商的位数
    // 字符串模拟竖式除法：从高位到低位逐位计算
    for (ll i = 0; i < len; i++) {
        int cur = remainder * 10 + (num[i] - '0');
        char digit = '0' + cur / 13;
        remainder = cur % 13;
        // 商的前导零不输出
        if (digit != '0' || qlen > 0) {
            quotient[qlen] = digit;
            qlen++;
        }
    }
    if (qlen == 0) { // 商为 0 时仍需输出一个 0
        quotient[qlen] = '0';
        qlen++;
    }
    quotient[qlen] = '\0';
    printf("%s\n%d\n", quotient, remainder);
    return 0;
}
