/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int ch[1005]; // 语文成绩
int ma[1005]; // 数学成绩
int en[1005]; // 英语成绩
int tot[1005]; // 总分
int n, ans;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> ch[i] >> ma[i] >> en[i];
        tot[i] = ch[i] + ma[i] + en[i];
    }
    // 枚举所有学生对 i < j
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            // 三科分差都不超过 5，且总分差不超过 10
            if (abs(ch[i] - ch[j]) <= 5 &&
                abs(ma[i] - ma[j]) <= 5 &&
                abs(en[i] - en[j]) <= 5 &&
                abs(tot[i] - tot[j]) <= 10) {
                ans++;
            }
        }
    }
    cout << ans;
    return 0;
}
