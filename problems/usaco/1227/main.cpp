/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:14
 * update_at: 2026-07-11 13:17
 */
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    int answer = 0;
    char last = '.';

    // 每两个位置成一组：相同的组无影响，不同的组只关心首字符变化。
    for (int i = 0; i < n; i += 2) {
        if (s[i] != s[i + 1]) {
            if (s[i] != last) {
                answer++;
                last = s[i];
            }
        }
    }

    // 末尾为 H 的最后一段已经天然满足目标，不需要额外反转。
    if (last == 'H') {
        answer--;
    }

    cout << answer << '\n';

    return 0;
}
