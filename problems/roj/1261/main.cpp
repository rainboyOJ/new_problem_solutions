/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:19
 * update_at: 2026-10-05 07:19
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 25;
const ll INF = 1000000000000000000LL;

int n;                 // 城市数量
ll w[MAXN][MAXN];      // w[i][j]：城市 i 直达城市 j 的费用，0 表示没有直通边
ll f[MAXN];            // f[i]：从城市 i 到城市 n 的最小费用
int go[MAXN];          // go[i]：最优路线上从城市 i 出发的下一站，0 表示终点或不可达

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w[i][j];
        }
    }

    // 所有边都是小编号指向大编号，编号即拓扑序，从 n 倒着推就是逆拓扑序 DP
    for (int i = 1; i <= n; i++) {
        f[i] = INF;
    }
    f[n] = 0;

    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            if (w[i][j] != 0 && w[i][j] + f[j] < f[i]) {
                f[i] = w[i][j] + f[j];
                go[i] = j;
            }
        }
    }

    cout << "minlong=" << f[1] << "\n";

    // 从城市 1 沿 go 逐跳回溯到 n，输出路径上的城市编号
    int cur = 1;
    cout << cur;
    while (go[cur] != 0) {
        cur = go[cur];
        cout << " " << cur;
    }
    cout << "\n";

    return 0;
}
