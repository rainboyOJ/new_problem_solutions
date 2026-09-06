/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 19:06
 * update_at: 2026-09-06 19:22
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    vector<unsigned char> current(n + 1, 0);
    int answer = 0;

    // 按下标从小到大决定是否操作 i。操作 i 只影响 i 的倍数，
    // 所以处理到 i 时，current[i] 已经只包含更小操作的影响。
    for (int i = 1; i <= n; i++) {
        int need = (s[i - 1] == '0');
        if (current[i] != need) {
            answer++;
            for (int j = i; j <= n; j += i) {
                current[j] ^= 1;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
