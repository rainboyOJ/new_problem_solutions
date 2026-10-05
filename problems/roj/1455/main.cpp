/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:14
 * update_at: 2026-10-06 00:14
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

typedef long long ll;

const int MAXP = 1e4 + 5;   // |s1| <= 1e4
const int MAXT = 1e6 + 5;   // |s2| <= 1e6

char s1[MAXP];  // 模式串
char s2[MAXT];  // 文本串
int fail[MAXP]; // fail[i] = s1[:i] 的最长相等真前后缀长度

// 对模式串 s1 预处理失配指针，均摊 O(|s1|)
void build_fail() {
    int m = strlen(s1 + 1); // 串从下标 1 开始存
    fail[1] = 0;
    int k = 0;              // 当前已匹配的 s1 前缀长度
    for (int i = 2; i <= m; ++i) {
        while (k && s1[i] != s1[k + 1]) k = fail[k]; // 沿失配链回退
        if (s1[i] == s1[k + 1]) ++k;
        fail[i] = k;
    }
}

// 统计 s1 在 s2 中出现的次数（允许重叠），均摊 O(|s2|)
int kmp_count() {
    int m = strlen(s1 + 1);
    int n = strlen(s2 + 1);
    int ans = 0;
    int k = 0;              // 已匹配的 s1 前缀长度
    for (int i = 1; i <= n; ++i) {
        while (k && s2[i] != s1[k + 1]) k = fail[k]; // 不回退主串指针，只回退 k
        if (s2[i] == s1[k + 1]) ++k;
        if (k == m) {       // 完整出现一次
            ++ans;
            k = fail[k];    // 回退而不是清零，重叠出现也能被数到
        }
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    if (!(std::cin >> T)) return 0;
    while (T--) {
        std::cin >> (s1 + 1) >> (s2 + 1);
        build_fail();
        std::cout << kmp_count() << "\n";
    }
    return 0;
}
