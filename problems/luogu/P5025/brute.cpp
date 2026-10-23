/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 13:34
 * update_at: 2026-10-23 15:05
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接按定义建出「引爆关系」：从每个炸弹出发做 BFS，能到达多少炸弹就是答案。
// 单个起点一次 BFS 是 O(n^2)，全部起点是 O(n^3)，只适合 n <= 300 的小数据。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1005;  // 暴力解只用于小数据对拍
const ll MOD = 1000000007;

int n;
ll x[MAXN];          // x[i]：第 i 个炸弹的坐标
ll r[MAXN];          // r[i]：第 i 个炸弹的爆炸半径
bool visited[MAXN];  // visited[i]：本次 BFS 中第 i 个炸弹是否已被引爆

// 从 start 出发按定义 BFS，返回一共能引爆多少个炸弹
int explode_count(int start) {
    for (int i = 1; i <= n; i++) visited[i] = false;
    queue<int> q;
    q.push(start);
    visited[start] = true;
    int total = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        total++;
        // 直接枚举所有炸弹，能被 u 引爆且还没进队的就入队
        for (int v = 1; v <= n; v++) {
            if (visited[v]) continue;
            ll dist = x[v] - x[u];
            if (dist < 0) dist = -dist;
            if (dist <= r[u]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return total;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &x[i], &r[i]);
    }

    ll answer = 0;
    for (int i = 1; i <= n; i++) {
        ll cnt = explode_count(i);
        answer = (answer + ll(i) * cnt) % MOD;
    }
    printf("%lld\n", answer);
    return 0;
}
