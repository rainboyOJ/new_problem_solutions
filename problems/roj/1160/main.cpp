/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:58
 * update_at: 2026-10-05 03:58
 */

// 倒序数：把 n 的十进制表示整串反转后输出。
// 答案是数字串而不是数值：反转后开头的 0 必须原样保留，
// 所以用字符串存结果，绝不能再转回整数输出。

#include <cstdio>
#include <cstring>

typedef long long ll;

char s[105]; // 存 n 的十进制表示，反转结果也放在这里（题面未给位数上限，105 足够）

int main() {
    scanf("%s", s);
    ll len = strlen(s);
    // 从最高位往低位倒着逐字符输出，即得到倒序数
    for (ll i = len - 1; i >= 0; i--) {
        printf("%c", s[i]);
    }
    printf("\n");
    return 0;
}
