/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:19
 * update_at: 2026-10-06 00:19
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXL = 1010;          // 字符串最大长度
char s[MAXL], t[MAXL];          // s 为主串，t 为模式串
int nxt[MAXL];                  // nxt[i] 表示模式串前缀 t[0..i] 的最长相等真前后缀长度

// 预处理模式串 t 的 nxt（前缀函数）数组
void get_next(char t[], int m) {
    int j = 0;
    nxt[0] = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && t[i] != t[j]) j = nxt[j - 1];
        if (t[i] == t[j]) j++;
        nxt[i] = j;
    }
}

// KMP 匹配，每匹配到一个完整 t 就计数并将匹配指针清零，保证剪出的子串互不重叠
int kmp_count(char s[], int n, char t[], int m) {
    int j = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && s[i] != t[j]) j = nxt[j - 1];
        if (s[i] == t[j]) j++;
        if (j == m) {
            ans++;
            j = 0; // 剪下这一段，从下一字符重新匹配
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> s) {
        if (s[0] == '#' && s[1] == '\0') break; // 单独一个 # 结束输入
        cin >> t;
        int n = strlen(s);
        int m = strlen(t);
        get_next(t, m);
        cout << kmp_count(s, n, t, m) << "\n";
    }
    return 0;
}
