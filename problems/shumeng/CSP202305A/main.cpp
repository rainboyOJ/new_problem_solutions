/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:21
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<string, int> appeared;
    for (int step = 1; step <= n; step++) {
        string board;
        for (int row = 0; row < 8; row++) {
            string line;
            cin >> line;
            board += line;
        }
        appeared[board]++;
        cout << appeared[board] << '\n';
    }

    return 0;
}
