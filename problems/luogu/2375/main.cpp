/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* P2375 [NOI2014] 动物园 */
/* 核心观察：
 *   1. 前缀的所有 border 按长度严格嵌套成一条链（失配树上的一条祖先路径）。
 *   2. num[i] = 链上长度不超过 (i+1)/2 的节点个数。
 *   3. 链深一次扫描刻好刻度；游标 j 每轮至多 +1，第二遍扫描线性。 */
/* 下标约定与 rbook 文章《KMP 字符串匹配》一致：从 0 开始。 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000000 + 7;

// 前缀函数模板（原样取自 rbook 文章《KMP 字符串匹配》）
// pi[i]：pattern[0..i] 的最长相等真前后缀长度，pi[0] = 0
vector<int> build_prefix_function(const string &pattern) {
    int m = (int)pattern.size();
    vector<int> pi(m, 0);

    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];                 // 上一个位置的最长 border
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];                 // 失配：在失配树上向父节点跳跃
        }
        if (pattern[i] == pattern[j]) j++; // 匹配成功，border 延长 1
        pi[i] = j;
    }

    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; // 测试数据组数
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int L = (int)s.size();

        /* 第一遍：前缀函数 pi */
        vector<int> pi = build_prefix_function(s);

        /* 刻度：border_count[i] = 失配树上节点 i 到根的节点数（含自己） */
        // 例：s = aaaaa → pi = [0,1,2,3,4]，border_count = [1,2,3,4,5]
        vector<int> border_count(L, 0);
        for (int i = 0; i < L; i++) {
            if (pi[i] > 0)
                border_count[i] = border_count[pi[i] - 1] + 1; // 父节点下标是 pi[i]-1
            else
                border_count[i] = 1; // 没有 border，链上只有自己
        }

        /* 第二遍：游标 j 扫描，求 num[i] */
        // j 沿用文章含义"已匹配前缀长度"，下一个要比较的字符是 s[j]；
        // 额外要求 2*j <= i+1（不重叠）。
        long long ans = 1; // 答案：所有 (num[i]+1) 的乘积；num[0] 恒为 0，从 i=1 开始
        int j = 0;
        for (int i = 1; i < L; i++) {
            while (j > 0 && s[i] != s[j]) j = pi[j - 1]; // 失配回退
            if (s[i] == s[j]) j++;                        // 匹配，j 延长 1
            while (j * 2 > i + 1) j = pi[j - 1];          // 重叠，继续沿链缩短

            // num[i] = border_count[j-1]；j == 0 时没有 border，因子是 1
            int factor = (j == 0) ? 1 : border_count[j - 1] + 1;
            ans = ans * factor % MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}
