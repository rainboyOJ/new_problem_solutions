/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-07-31 16:22
 */
#include <bits/stdc++.h>
using namespace std;

int f_value(int x, int k) {
    return (((x * x + k * k) & 7) ^ k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> k(m);
    for (int i = 0; i < m; i++) cin >> k[i];

    vector<int> inverse(512, -1);
    for (int start = 0; start < 512; start++) {
        int value = start;
        for (int step : k) {
            int a = (value >> 6) & 7;
            int b = (value >> 3) & 7;
            int c = value & 7;
            int na = b;
            int nb = c ^ f_value(b, step);
            int nc = a ^ f_value(c, step);
            value = (na << 6) | (nb << 3) | nc;
        }
        inverse[value] = start;
    }

    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        if (i) cout << ' ';
        cout << inverse[value];
    }
    cout << '\n';
    return 0;
}
