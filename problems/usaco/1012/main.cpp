/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:17
 * update_at: 2026-07-11 14:19
 */
#include <bits/stdc++.h>
using namespace std;

int n;
string a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b;

    int ans = 0;
    bool in_bad_segment = false;

    // 每一段连续不匹配的位置，需要一次翻转。
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            if (!in_bad_segment) {
                ans++;
                in_bad_segment = true;
            }
        } else {
            in_bad_segment = false;
        }
    }

    cout << ans << '\n';

    return 0;
}
