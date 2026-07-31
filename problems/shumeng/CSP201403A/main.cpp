/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 17:00
 */
#include <bits/stdc++.h>
using namespace std;

const int OFFSET = 1000;
bool seen[2005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (seen[-x + OFFSET]) {
            answer++;
        }
        seen[x + OFFSET] = true;
    }

    cout << answer << '\n';
    return 0;
}
