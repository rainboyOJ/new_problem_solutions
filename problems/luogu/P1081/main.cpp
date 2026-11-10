/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:25
 * update_at: 2026-11-11 00:25
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

using ll = long long;

const int MAXN = 100005;
const int MAX_LOG = 19;

ll h[MAXN];
int to_A[MAXN], to_B[MAXN];

// 倍增表：f[k][i] 表示从城市 i 经历 2^k 轮后到达的城市
int f[MAX_LOG][MAXN];
ll distA[MAX_LOG][MAXN];
ll distB[MAX_LOG][MAXN];

struct Candidate {
    ll d;
    ll alt;
    int id;

    bool operator<(const Candidate& other) const {
        if (d != other.d) return d < other.d;
        return alt < other.alt;
    }
};

pair<ll, ll> query(int s, ll x) {
    ll totalA = 0, totalB = 0;
    int cur = s;

    // 先走整轮（A 走一步 + B 走一步）
    for (int k = MAX_LOG - 1; k >= 0; --k) {
        if (f[k][cur] != 0 && (totalA + totalB + distA[k][cur] + distB[k][cur] <= x)) {
            totalA += distA[k][cur];
            totalB += distB[k][cur];
            cur = f[k][cur];
        }
    }

    // 检查 A 是否能再单走一步
    if (to_A[cur] != 0) {
        ll costA = abs(h[cur] - h[to_A[cur]]);
        if (totalA + totalB + costA <= x) {
            totalA += costA;
        }
    }

    return {totalA, totalB};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }

    // 利用 set 倒序预处理第一近和第二近城市
    set<pair<ll, int>> st;
    for (int i = n; i >= 1; --i) {
        auto it = st.lower_bound({h[i], i});
        vector<Candidate> cands;

        // 向右检查 2 个
        auto r = it;
        for (int cnt = 0; cnt < 2 && r != st.end(); ++cnt, ++r) {
            cands.push_back({abs(r->first - h[i]), r->first, r->second});
        }
        // 向左检查 2 个
        auto l = it;
        for (int cnt = 0; cnt < 2 && l != st.begin(); ++cnt) {
            --l;
            cands.push_back({abs(l->first - h[i]), l->first, l->second});
        }

        sort(cands.begin(), cands.end());

        if (cands.size() >= 1) to_B[i] = cands[0].id;
        if (cands.size() >= 2) to_A[i] = cands[1].id;

        st.insert({h[i], i});
    }

    // 初始化倍增表 k = 0
    for (int i = 1; i <= n; ++i) {
        int nxtA = to_A[i];
        if (nxtA != 0) {
            distA[0][i] = abs(h[i] - h[nxtA]);
            int nxtB = to_B[nxtA];
            if (nxtB != 0) {
                f[0][i] = nxtB;
                distB[0][i] = abs(h[nxtA] - h[nxtB]);
            } else {
                f[0][i] = 0;
                distB[0][i] = 0;
            }
        } else {
            f[0][i] = 0;
            distA[0][i] = 0;
            distB[0][i] = 0;
        }
    }

    // 递推倍增表
    for (int k = 1; k < MAX_LOG; ++k) {
        for (int i = 1; i <= n; ++i) {
            int mid_city = f[k - 1][i];
            if (mid_city != 0) {
                f[k][i] = f[k - 1][mid_city];
                distA[k][i] = distA[k - 1][i] + distA[k - 1][mid_city];
                distB[k][i] = distB[k - 1][i] + distB[k - 1][mid_city];
            } else {
                f[k][i] = 0;
                distA[k][i] = distA[k - 1][i];
                distB[k][i] = distB[k - 1][i];
            }
        }
    }

    // 问题 1
    ll x0;
    cin >> x0;
    int best_s = 0;
    ll bestA = 1, bestB = 0; // 初始比值设为无限大 (1 / 0)

    for (int i = 1; i <= n; ++i) {
        auto res = query(i, x0);
        ll curA = res.first, curB = res.second;

        if (best_s == 0) {
            best_s = i;
            bestA = curA;
            bestB = curB;
        } else {
            // 比较 curA / curB 与 bestA / bestB
            // 若 curB == 0，比值为正无穷
            bool is_better = false;
            if (curB == 0 && bestB == 0) {
                // 两者都为无穷大，比值相同，看海拔
                if (h[i] > h[best_s]) is_better = true;
            } else if (curB == 0) {
                // 当前为无穷大，比原方案差（除非原方案也是无穷大）
                is_better = false;
            } else if (bestB == 0) {
                // 原方案是无穷大，当前是有穷值，当前更好
                is_better = true;
            } else {
                // curA * bestB 与 bestA * curB 比较
                __int128 v1 = (__int128)curA * bestB;
                __int128 v2 = (__int128)bestA * curB;
                if (v1 < v2) {
                    is_better = true;
                } else if (v1 == v2) {
                    if (h[i] > h[best_s]) is_better = true;
                }
            }

            if (is_better) {
                best_s = i;
                bestA = curA;
                bestB = curB;
            }
        }
    }

    cout << best_s << "\n";

    // 问题 2
    int m;
    cin >> m;
    while (m--) {
        int s;
        ll x;
        cin >> s >> x;
        auto res = query(s, x);
        cout << res.first << " " << res.second << "\n";
    }

    return 0;
}
