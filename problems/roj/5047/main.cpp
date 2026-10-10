/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 20:40
 * update_at: 2026-10-08 20:40
 */
#include <iostream>

using namespace std;

typedef long long ll;

const int MAXN = 25;

// 方阵，a[i][j] 表示第 i 行第 j 列填入的数字，0 表示还没填过
int a[MAXN][MAXN];

// 四个方向的增量，按「下、左、上、右」顺时针循环：
// 0=下(dx=1,dy=0) 1=左(0,-1) 2=上(-1,0) 3=右(0,1)
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

// 从右上角起笔，按「下、左、上、右」螺旋填入 1..n*n
void solve() {
    ll n;
    if (!(cin >> n)) return;

    ll x = 0, y = n - 1; // 起点：第 0 行、第 n-1 列（右上角）
    ll dir = 0;          // 当前方向下标，初值 0 即先向下

    for (ll v = 1; v <= n * n; ++v) {
        a[x][y] = v;

        // 先看后走：下一步越界或已填过，就顺时针转一次方向
        ll nx = x + dx[dir];
        ll ny = y + dy[dir];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n || a[nx][ny] != 0) {
            dir = (dir + 1) % 4;
            nx = x + dx[dir];
            ny = y + dy[dir];
        }
        x = nx;
        y = ny;
    }

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            cout << a[i][j] << (j == n - 1 ? "" : " "); // 行末不留多余空格
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
