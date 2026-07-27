/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

// 比较两个数字字符串：如果 s1 > s2 返回 true
bool bigger(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2) return len1 > len2; // 位数多的更大
    return strcmp(s1, s2) > 0;            // 位数相同，字典序比较
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int    best_idx = 1;
    char   best[105];
    cin >> best; // 读入第 1 个人的票数

    for (int i = 2; i <= n; i++) {
        char cur[105];
        cin >> cur;
        if (bigger(cur, best)) {
            best_idx = i;
            strcpy(best, cur);
        }
    }

    cout << best_idx << "\n";
    cout << best << "\n";

    return 0;
}
