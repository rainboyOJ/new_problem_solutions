/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 15:54
 * update_at: 2026-09-06 15:57
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举每个位置翻还是不翻。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
char s[MAXN];
int choose[MAXN]; // choose[i] = 0 表示第 i 位不翻，1 表示翻
int ans;

// 判断当前 choose[] 对应的翻转方案是否把字符串变成非递减。
bool check() {
    bool seenB = false;
    for (int i = 1; i <= n; i++) {
        char c = s[i];
        if (choose[i] == 1) c = (c == 'A' ? 'B' : 'A'); // 翻转过后的字符
        if (c == 'B') seenB = true;
        if (seenB && c == 'A') return false; // B 后面出现了 A，不是非递减
    }
    return true;
}

// 统计当前方案的翻转次数。
int calc_answer() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose[i] == 1) cnt++;
    }
    return cnt;
}

void dfs(int dep) {
    if (dep == n + 1) {
        if (check()) {
            ans = min(ans, calc_answer());
        }
        return;
    }

    // 这一层决定第 dep 个位置翻还是不翻。
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> (s + 1);
    n = strlen(s + 1);
    ans = n; // 最多翻 n 次

    dfs(1);

    cout << ans << "\n";
    return 0;
}
