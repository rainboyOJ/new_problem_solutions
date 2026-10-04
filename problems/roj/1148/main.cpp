/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:36
 * update_at: 2026-10-05 03:36
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const ll MAXL = 2600; // 字符串长度上限 2500

char s[MAXL]; // 输入字符串
ll k;         // 至少连续出现的次数

int main() {
    scanf("%lld %s", &k, s);
    ll len = strlen(s);

    ll run = 0; // 当前段计数，0 表示还没有进入任何段
    for (ll i = 0; i < len; i++) {
        if (run == k) { // 先判：前一段已连续出现 k 次，输出当前字符
            printf("%c\n", s[i]);
            return 0;
        }
        if (i + 1 < len && s[i] == s[i + 1]) // 后更：向右看一位是否同字符
            run++;
        else
            run = 1; // 段断裂（或到达串尾），重新从 1 数起
    }
    printf("No\n"); // 整串扫完都没有触发（含末端段恰好凑满 k 的情况）
    return 0;
}
