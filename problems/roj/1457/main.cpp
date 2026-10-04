/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-30 12:00
 * update_at: 2026-10-05 02:26
 */
// KMP 求 fail 数组：fail[n-1] 是整个串的最长公共前后缀长度，
// 则 p = n - fail[n-1] 是最小周期；p 整除 n 时答案是 n/p，否则串不是幂串，答案 1。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

typedef long long ll;

int len;            // 当前串长
char s[MAXN];       // 当前字符串，下标从 0 开始
int fail[MAXN];     // fail[i] = s[0..i] 的最长相等前后缀长度（不含整个串）

// 对当前串求 fail 数组（KMP 失配函数）。
void get_fail() {
    fail[0] = 0;
    // j 表示 s[0..i-1] 匹配到的前缀长度，尝试把 s[i] 接在 s[j] 后面
    for (int i = 1, j = 0; i < len; i++) {
        while (j > 0 && s[i] != s[j]) j = fail[j - 1]; // 失配则跳到更短的前后缀
        if (s[i] == s[j]) j++;
        fail[i] = j;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> s) {
        len = strlen(s); // 声明 len 为 int 即可，无强制转换
        if (len == 1 && s[0] == '.') break; // 句号结束输入

        get_fail();
        int p = len - fail[len - 1]; // 最小周期
        if (len % p == 0) {
            cout << len / p << "\n"; // 整周期，串是幂串
        } else {
            cout << 1 << "\n"; // 最小周期不整除 n，无法由重复子串构成
        }
    }

    return 0;
}
