/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:40
 * update_at: 2026-10-05 02:40
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105; // 矩阵最大行数/列数

ll a[MAXN][MAXN]; // 矩阵 A
ll b[MAXN][MAXN]; // 矩阵 B

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // 行数、列数
    cin >> n >> m;

    for (int i = 1; i <= n; i++) // 读入矩阵 A
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    for (int i = 1; i <= n; i++) // 读入矩阵 B
        for (int j = 1; j <= m; j++)
            cin >> b[i][j];

    for (int i = 1; i <= n; i++) { // 逐位相加并输出
        for (int j = 1; j <= m; j++) {
            if (j > 1) cout << ' ';
            cout << a[i][j] + b[i][j];
        }
        cout << '\n';
    }
    return 0;
}
