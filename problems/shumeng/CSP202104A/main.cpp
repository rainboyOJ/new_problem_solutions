/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:54
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, levels;
    cin >> n >> m >> levels;
    vector<int> count(levels);
    for (int i = 0; i < n * m; i++) {
        int value;
        cin >> value;
        count[value]++;
    }
    for (int i = 0; i < levels; i++) {
        if (i) cout << ' ';
        cout << count[i];
    }
    cout << '\n';
    return 0;
}
