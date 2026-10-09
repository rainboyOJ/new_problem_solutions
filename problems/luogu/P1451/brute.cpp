/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:06
 * update_at: 2026-10-09 21:06
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 这里故意换一种和 main.cpp 完全独立的想法——并查集：
// 把上下左右相邻的两个细胞数字合并到同一个集合，最后数一共有几个集合，集合数就是细胞数。
// 它和 main.cpp 的 BFS 没有共用任何一行逻辑，对拍时才能真的互相印证。
// 并查集的复杂度是 O(nm α(nm))，只在 n,m <= 100 的小数据上用来做基线，不追求更快的做法。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
char g[MAXN][MAXN]; // g[i][j]：'1'..'9' 是细胞数字，'0' 不是细胞（下标从 0 开始）
int fa[MAXN * MAXN]; // fa[k]：格子 (i,j) 的并查集父亲，编号 k = i * m + j

// 把格子 (i, j) 压平成一维编号，方便并查集数组寻址
int id_of(int i, int j) {
    return i * m + j;
}

// 查编号 x 所在集合的根，顺手把路径上的点都挂到根上（路径压缩）
int find_root(int x) {
    int root = x;
    while (fa[root] != root) {
        root = fa[root];
    }
    int cur = x;
    while (fa[cur] != root) { // 第二趟把整条路径的父亲都改成 root
        int nxt = fa[cur];
        fa[cur] = root;
        cur = nxt;
    }
    return root;
}

// 把编号 x、y 的两个格子合并到同一个集合
void unite(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);
    if (rx != ry) {
        fa[rx] = ry;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> (g[i]); // 第 i 行读成一个字符串，正好是 g[i][0..m-1]
    }

    // 每个格子先各自成一个集合
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fa[id_of(i, j)] = id_of(i, j);
        }
    }

    // 每个相邻格子对只需处理一次：只看右边和下边的邻居
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '0') {
                continue; // '0' 不是细胞，不参与合并
            }
            if (i + 1 < n && g[i + 1][j] != '0') {
                unite(id_of(i, j), id_of(i + 1, j)); // 和下边相邻的细胞合并
            }
            if (j + 1 < m && g[i][j + 1] != '0') {
                unite(id_of(i, j), id_of(i, j + 1)); // 和右边相邻的细胞合并
            }
        }
    }

    // 数不同集合的个数：只有"自己就是根"的细胞格子，才代表一个集合
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] != '0' && find_root(id_of(i, j)) == id_of(i, j)) {
                cnt++;
            }
        }
    }

    cout << cnt << '\n';
    return 0;
}
