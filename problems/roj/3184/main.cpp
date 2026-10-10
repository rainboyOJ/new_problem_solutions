/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 奶牛接力赛：min-plus 矩阵快速幂，求恰走 n 条边的最短路
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const ll INF = 1000000000000000000LL;

int size_v;

// c = a ⊗ b（min-plus 乘法），含义是“接上两段路程”
void min_plus_mul(const vector<ll>& a, const vector<ll>& b, vector<ll>& c) {
    for (int i = 0; i < size_v; i++) {
        for (int j = 0; j < size_v; j++) {
            ll best = INF;
            for (int k = 0; k < size_v; k++) {
                ll x = a[i * size_v + k], y = b[k * size_v + j];
                if (x >= INF || y >= INF) {
                    continue;
                }
                if (x + y < best) {
                    best = x + y;
                }
            }
            c[i * size_v + j] = best;
        }
    }
}

int main() {
    ll n;
    int t, s, e;
    if (scanf("%lld %d %d %d", &n, &t, &s, &e) != 4) {
        return 0;
    }
    vector<int> uniq; // 去重后的点编号，用线性查找离散化
    vector<int> el(t), eu(t), ev(t);
    for (int i = 0; i < t; i++) {
        scanf("%d %d %d", &el[i], &eu[i], &ev[i]);
        bool fa = false, fb = false;
        for (int q = 0; q < (int)uniq.size(); q++) {
            if (uniq[q] == eu[i]) fa = true;
            if (uniq[q] == ev[i]) fb = true;
        }
        if (!fa) uniq.push_back(eu[i]);
        if (!fb) uniq.push_back(ev[i]);
    }
    int cnt = (int)uniq.size();
    int s_id = -1, e_id = -1;
    for (int q = 0; q < cnt; q++) {
        if (uniq[q] == s) s_id = q;
        if (uniq[q] == e) e_id = q;
    }
    size_v = cnt;

    // 邻接矩阵：同一对点可能有多条边，只保留最短的那条
    vector<ll> adj(size_v * size_v, INF);
    for (int i = 0; i < t; i++) {
        int a = -1, b = -1;
        for (int q = 0; q < cnt; q++) {
            if (uniq[q] == eu[i]) a = q;
            if (uniq[q] == ev[i]) b = q;
        }
        if (el[i] < adj[a * size_v + b]) {
            adj[a * size_v + b] = adj[b * size_v + a] = el[i];
        }
    }

    // min-plus 快速幂：恰走 n 条边
    vector<ll> result(size_v * size_v, INF), base = adj, tmp(size_v * size_v);
    for (int i = 0; i < size_v; i++) {
        result[i * size_v + i] = 0; // 恰走 0 条边：乘法的单位元
    }
    ll pw = n;
    while (pw) {
        if (pw & 1) {
            min_plus_mul(result, base, tmp);
            result = tmp;
        }
        pw >>= 1;
        if (pw) { // 最后一次乘方前不再平方，省一次 O(V^3)
            min_plus_mul(base, base, tmp);
            base = tmp;
        }
    }
    printf("%lld\n", result[s_id * size_v + e_id]);
    return 0;
}
