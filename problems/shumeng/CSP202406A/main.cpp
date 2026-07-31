/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:31
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p, q;
    cin >> n >> m >> p >> q;
    vector<int> value(n * m);
    for (int i = 0; i < n * m; i++) cin >> value[i];

    // 行优先线性序号保持不变，只需按照新矩阵的列数重新解释下标。
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            if (j > 0) cout << ' ';
            cout << value[i * q + j];
        }
        cout << '\n';
    }

    return 0;
}
