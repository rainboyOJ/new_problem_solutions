/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:17
 * update_at: 2026-07-11 21:18
 */
#include <bits/stdc++.h>
using namespace std;

string s;
string target = "bessie";
long long waiting[7]; // waiting[i] 表示正在等待 target[i] 的 token 数量。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    int n = (int)s.size();
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        waiting[0]++; // 新增一个从 i 开始的后缀 token。

        for (int j = 5; j >= 0; j--) {
            if (s[i] == target[j]) {
                waiting[j + 1] += waiting[j];
                waiting[j] = 0;
            }
        }

        // 在 i 处完成 "bessie" 的 token，对所有右端点 >= i 的子串都有 1 次贡献。
        ans += waiting[6] * (n - i);
        waiting[0] += waiting[6];
        waiting[6] = 0;
    }

    cout << ans << '\n';

    return 0;
}
