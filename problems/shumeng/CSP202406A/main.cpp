/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int value[MAXN]; // 行优先顺序读取的线性序列

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p, q;
    cin >> n >> m >> p >> q;
    for (int i = 0; i < n * m; i++) cin >> value[i];

    // 重塑不改变行优先线性顺序，只需按新列数 q 重新解释下标
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            if (j > 0) cout << ' ';
            cout << value[i * q + j];
        }
        cout << '\n';
    }

    return 0;
}