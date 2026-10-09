/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:09
 * update_at: 2026-10-09 21:09
 */
// main-stl.cpp：P1596 [USACO10OCT] Lake Counting S（STL 写法）。
// 算法和 main.cpp 完全一样：扫到未访问的 'W' 就说明是新水塘，从它开始八方向
// 洪水填充，把整个水塘淹掉，答案加一。
// 差别只在“网格和队列怎么表达”：
//   main.cpp 用固定数组 char g[105][105]，队列存 pair<int, int>；
//   这里网格用 vector<string>，每行一个 string，读入直接 cin >> g[i]，
//   队列存压平后的下标 x * m + y，一个整数就是一个格子，不用构造 pair。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, m;          // 网格的行数、列数
vector<string> g; // g[x][y]：'W' 是水，'.' 是干地；0 下标，压平编号是 x * m + y
ll dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // 八方向：上下左右加四条对角线
ll dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
queue<ll> q; // BFS 队列，元素是压平下标 x * m + y

// 读入 n、m 和 n 行网格
void read_input() {
    cin >> n >> m;

    g.assign(n, string());
    for (ll i = 0; i < n; i++) {
        cin >> g[i];
    }
}

// 从 (sx, sy) 出发淹掉整个水塘：沿途的 'W' 原地改成 '.'
void flood_fill(ll sx, ll sy) {
    g[sx][sy] = '.';
    q.push(sx * m + sy);

    while (!q.empty()) {
        ll id = q.front();
        q.pop();
        ll x = id / m; // 压平下标还原成行列
        ll y = id % m;

        for (ll i = 0; i < 8; i++) {
            ll nx = x + dx[i];
            ll ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue; // 越界
            }
            if (g[nx][ny] != 'W') {
                continue; // 干地，或者已经属于淹过的水塘
            }
            g[nx][ny] = '.'; // 入队前就标记，保证每个格子最多入队一次
            q.push(nx * m + ny);
        }
    }
}

// 扫描全网格：遇到的 'W' 只可能来自还没统计过的水塘
ll count_ponds() {
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (g[i][j] == 'W') {
                ans++;
                flood_fill(i, j);
            }
        }
    }
    return ans;
}

void output(ll ans) {
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    output(count_ponds());

    return 0;
}
