/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:25
 * update_at: 2026-11-11 00:25
 */

// brute.cpp：小数据一步一步暴力模拟
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;

const int MAXN = 1005;
ll h[MAXN];
int to_A[MAXN], to_B[MAXN];

pair<ll, ll> sim(int s, ll x, int n) {
    ll curA = 0, curB = 0;
    int cur = s;
    int turn = 0; // 0: A, 1: B

    while (cur != 0) {
        if (turn == 0) {
            int nxt = to_A[cur];
            if (nxt == 0) break;
            ll cost = abs(h[cur] - h[nxt]);
            if (curA + curB + cost > x) break;
            curA += cost;
            cur = nxt;
            turn = 1;
        } else {
            int nxt = to_B[cur];
            if (nxt == 0) break;
            ll cost = abs(h[cur] - h[nxt]);
            if (curA + curB + cost > x) break;
            curB += cost;
            cur = nxt;
            turn = 0;
        }
    }
    return {curA, curB};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) cin >> h[i];

    // O(n^2) 暴力预处理后继
    for (int i = 1; i <= n; ++i) {
        vector<pair<ll, pair<ll, int>>> cands; // (dist, (alt, id))
        for (int j = i + 1; j <= n; ++j) {
            cands.push_back({abs(h[i] - h[j]), {h[j], j}});
        }
        sort(cands.begin(), cands.end());
        if (cands.size() >= 1) to_B[i] = cands[0].second.second;
        if (cands.size() >= 2) to_A[i] = cands[1].second.second;
    }

    ll x0;
    cin >> x0;
    int best_s = 0;
    ll bestA = 1, bestB = 0;

    for (int i = 1; i <= n; ++i) {
        auto res = sim(i, x0, n);
        ll curA = res.first, curB = res.second;
        if (best_s == 0) {
            best_s = i;
            bestA = curA;
            bestB = curB;
        } else {
            bool is_better = false;
            if (curB == 0 && bestB == 0) {
                if (h[i] > h[best_s]) is_better = true;
            } else if (curB == 0) {
                is_better = false;
            } else if (bestB == 0) {
                is_better = true;
            } else {
                __int128 v1 = (__int128)curA * bestB;
                __int128 v2 = (__int128)bestA * curB;
                if (v1 < v2) is_better = true;
                else if (v1 == v2 && h[i] > h[best_s]) is_better = true;
            }
            if (is_better) {
                best_s = i;
                bestA = curA;
                bestB = curB;
            }
        }
    }
    cout << best_s << "\n";

    int m;
    cin >> m;
    while (m--) {
        int s;
        ll x;
        cin >> s >> x;
        auto res = sim(s, x, n);
        cout << res.first << " " << res.second << "\n";
    }

    return 0;
}
