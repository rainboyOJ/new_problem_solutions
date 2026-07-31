/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:02
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> sales(n);
    for (int i = 0; i < n; i++) cin >> sales[i];
    int answer = 0;
    for (int i = 1; i + 1 < n; i++) {
        if ((sales[i] - sales[i - 1]) * (sales[i + 1] - sales[i]) < 0) answer++;
    }
    cout << answer << '\n';
    return 0;
}
