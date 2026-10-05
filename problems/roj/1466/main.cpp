/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:18
 * update_at: 2026-10-06 00:18
 */
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 1000005; // 单串最大长度

char s[MAXN];
int pi[MAXN]; // 失败函数：pi[i] 为前缀 s[0..i] 的最长 border 长度

// 返回字符串 s[0..n-1] 的最大重复重数
int power_count(int n) {
    for (int i = 0; i < n; ++i) pi[i] = 0;
    int border = 0; // 当前已匹配的 border 长度
    for (int i = 1; i < n; ++i) {
        char ch = s[i];
        while (border && s[border] != ch) // 失配则沿 border 链回退
            border = pi[border - 1];
        if (s[border] == ch) // 匹配成功，border 延长
            ++border;
        pi[i] = border;
    }
    int p = n - border; // 最小正周期
    return (n % p == 0) ? (n / p) : 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> s) {
        if (s[0] == '.' && s[1] == '\0') break; // 单独一行 '.' 结束输入
        int n = strlen(s);
        cout << power_count(n) << '\n';
    }
    return 0;
}
