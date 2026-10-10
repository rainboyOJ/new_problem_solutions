/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 观光之旅：Floyd 过程中顺便求最小环，并还原环上的点
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const ll INF = 1LL << 60;

int V; // 实际出现过的最大编号
vector<vector<ll> > w;   // w[u][v]：原始边权（重边只留最短的一条）
vector<vector<ll> > dist; // dist[u][v]：当前只允许经过中转点 1..k-1 的最短路
vector<vector<int> > mid; // mid[u][v]：u→v 最短路上的中转点，0 表示直接相连

// 还原最短路 i→j 依次经过的点（含两端）
vector<int> restore(int i, int j) {
    int k = mid[i][j];
    if (k == 0) {
        vector<int> r;
        r.push_back(i);
        r.push_back(j);
        return r;
    }
    vector<int> left = restore(i, k), right = restore(k, j);
    for (int t = 1; t < (int)right.size(); t++) { // 去掉重复的拐点
        left.push_back(right[t]);
    }
    return left;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    vector<int> eu(m), ev(m), el(m);
    int maxv = n;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &eu[i], &ev[i], &el[i]);
        if (eu[i] > maxv) maxv = eu[i];
        if (ev[i] > maxv) maxv = ev[i];
    }
    V = maxv;
    w.assign(V + 1, vector<ll>(V + 1, INF));
    for (int i = 0; i < m; i++) {
        if (el[i] < w[eu[i]][ev[i]]) {
            w[eu[i]][ev[i]] = w[ev[i]][eu[i]] = el[i];
        }
    }
    for (int i = 0; i <= V; i++) {
        w[i][i] = 0;
    }
    dist = w;
    mid.assign(V + 1, vector<int>(V + 1, 0));

    ll best = INF;
    vector<int> loop;
    for (int k = 1; k <= n; k++) {
        // 阶段一：把 k 当作环上编号最大的点（此刻 dist 只借用了 1..k-1 中转）
        for (int i = 1; i < k; i++) {
            ll wik = w[k][i];
            if (wik >= INF) {
                continue;
            }
            for (int j = i + 1; j < k; j++) {
                if (w[k][j] >= INF || dist[i][j] >= INF) {
                    continue;
                }
                ll cand = dist[i][j] + wik + w[k][j];
                if (cand < best) {
                    best = cand;
                    loop = restore(i, j);
                    loop.push_back(k); // i..j 段接上 k
                }
            }
        }
        // 阶段二：k 升级为中转点
        vector<ll> dk = dist[k]; // 先冻结第 k 行：i=k 时对它的写不会改变任何值
        for (int i = 1; i <= V; i++) {
            ll dik = dist[i][k];
            if (dik >= INF) {
                continue;
            }
            for (int j = 1; j <= V; j++) {
                if (dk[j] >= INF) {
                    continue;
                }
                ll nxt = dik + dk[j];
                if (nxt < dist[i][j]) {
                    dist[i][j] = nxt;
                    mid[i][j] = k;
                }
            }
        }
    }

    if (loop.empty()) {
        printf("No solution.\n");
    } else {
        for (int i = 0; i < (int)loop.size(); i++) {
            if (i) printf(" ");
            printf("%d", loop[i]);
        }
        printf("\n");
    }
    return 0;
}
