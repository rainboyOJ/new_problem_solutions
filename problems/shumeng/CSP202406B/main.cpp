/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:34
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, operation_count;
    cin >> n >> m >> operation_count;
    vector<int> value(n * m);
    for (int i = 0; i < n * m; i++) cin >> value[i];

    while (operation_count--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            n = x;
            m = y;
        } else if (type == 2) {
            vector<int> transposed(value.size());
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    transposed[j * n + i] = value[i * m + j];
                }
            }
            value.swap(transposed);
            swap(n, m);
        } else {
            cout << value[x * m + y] << '\n';
        }
    }

    return 0;
}
