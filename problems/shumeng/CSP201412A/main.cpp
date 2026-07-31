/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:20
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> count(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int reader;
        cin >> reader;
        count[reader]++;
        if (i > 0) {
            cout << ' ';
        }
        cout << count[reader];
    }
    cout << '\n';
    return 0;
}
