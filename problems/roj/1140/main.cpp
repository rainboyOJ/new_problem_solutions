/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:21
 * update_at: 2026-10-05 03:21
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 205;

char s1[MAXN]; // 第一个字符串
char s2[MAXN]; // 第二个字符串

// 判断模式串 p（长度 lp）是否为文本串 t（长度 lt）的连续子串
bool is_substring(char t[], ll lt, char p[], ll lp) {
    if (lp > lt) return false; // 子串不可能比母串长
    for (ll k = 0; k + lp <= lt; k++) { // 枚举起点 k，比较窗口 t[k:k+lp]
        ll j = 0;
        while (j < lp && t[k + j] == p[j]) j++;
        if (j == lp) return true; // 整段窗口匹配成功
    }
    return false;
}

int main() {
    scanf("%s%s", s1, s2);
    ll n = strlen(s1);
    ll m = strlen(s2);

    // 按题面顺序：先判 s1 是否为 s2 的子串，再反过来判，最后输出 No substring
    if (is_substring(s2, m, s1, n)) {
        printf("%s is substring of %s\n", s1, s2);
    } else if (is_substring(s1, n, s2, m)) {
        printf("%s is substring of %s\n", s2, s1);
    } else {
        printf("No substring\n");
    }
    return 0;
}
