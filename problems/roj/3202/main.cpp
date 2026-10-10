/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 导弹防御：二分最小可行截止时刻 + 匈牙利算法（入侵者 对 发射位）
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double SECOND = 60.0; // 题面 T1 用秒、T2 用分钟、飞行时间也用分钟

// 匈牙利：从入侵者 u 出发找增广路
bool augment(int u, vector<char>& seen, vector<int>& mt, const vector<vector<int> >& adj) {
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int x = adj[u][i];
        if (!seen[x]) {
            seen[x] = 1;
            if (mt[x] < 0 || augment(mt[x], seen, mt, adj)) {
                mt[x] = u;
                return true;
            }
        }
    }
    return false;
}

// 每个入侵者只需抢到一个发射位；有一个抢不到就判定不可行
int max_matching(const vector<vector<int> >& adj, int size) {
    vector<int> mt(size, -1);
    int matched = 0;
    for (int u = 0; u < (int)adj.size(); u++) {
        vector<char> seen(size, 0);
        if (augment(u, seen, mt, adj)) {
            matched++;
        } else {
            break;
        }
    }
    return matched;
}

int main() {
    int n, m, t1, t2, v;
    if (scanf("%d %d %d %d %d", &n, &m, &t1, &t2, &v) != 5) {
        return 0;
    }
    vector<double> ix(m), iy(m), tx(n), ty(n);
    for (int j = 0; j < m; j++) {
        scanf("%lf %lf", &ix[j], &iy[j]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &tx[i], &ty[i]);
    }

    // slot_time[j][i*m+k]：第 i 座塔第 k 次发射命中第 j 个入侵者的时刻（秒）
    vector<double> shoot(m);
    for (int k = 0; k < m; k++) {
        shoot[k] = (double)(k + 1) * t1 + (double)k * SECOND * t2; // 射出时刻
    }
    int size = n * m;
    vector<vector<double> > slot(m, vector<double>(size, 0));
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            double dx = tx[i] - ix[j], dy = ty[i] - iy[j];
            double ready = SECOND * sqrt(dx * dx + dy * dy) / v; // 纯飞行时间（秒）
            for (int k = 0; k < m; k++) {
                slot[j][i * m + k] = ready + shoot[k];
            }
        }
    }

    // 每个入侵者按时刻升序排出全部发射位
    vector<vector<int> > order(m);
    vector<vector<double> > by_time(m);
    for (int j = 0; j < m; j++) {
        order[j].resize(size);
        for (int s = 0; s < size; s++) {
            order[j][s] = s;
        }
        for (int a = 0; a < size; a++) { // 简单选择排序，规模小
            int best = a;
            for (int b = a + 1; b < size; b++) {
                if (slot[j][order[j][b]] < slot[j][order[j][best]]) {
                    best = b;
                }
            }
            int t = order[j][a];
            order[j][a] = order[j][best];
            order[j][best] = t;
        }
        by_time[j].resize(size);
        for (int s = 0; s < size; s++) {
            by_time[j][s] = slot[j][order[j][s]];
        }
    }

    vector<double> timeline;
    for (int j = 0; j < m; j++) {
        for (int s = 0; s < size; s++) {
            timeline.push_back(slot[j][s]);
        }
    }
    sort(timeline.begin(), timeline.end());
    timeline.erase(unique(timeline.begin(), timeline.end()), timeline.end());

    // 在 [0, len-1] 上二分出最小的可行截止时刻下标
    int lo = 0, hi = (int)timeline.size() - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        double deadline = timeline[mid];
        vector<vector<int> > adj(m);
        for (int j = 0; j < m; j++) {
            int cnt = (int)(upper_bound(by_time[j].begin(), by_time[j].end(), deadline) -
                            by_time[j].begin());
            for (int s = 0; s < cnt; s++) {
                adj[j].push_back(order[j][s]);
            }
        }
        if (max_matching(adj, size) == m) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    printf("%.6f\n", timeline[lo] / SECOND);
    return 0;
}
