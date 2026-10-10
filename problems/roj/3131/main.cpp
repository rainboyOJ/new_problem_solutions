/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 陨石雨：整体二分，把同一轮里所有国家的区间一起处理，用排序 + 节点内前缀和批量算收集量。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

const ll CAP = 2000000000LL; // 单个太空站的收集量上限（远超任何国家的需求 10^9）

struct E3 {
    ll node; // 该事件属于哪个二分节点
    ll pos;  // 位置
    ll delta; // 差分增量
};

bool e3_less(const E3& a, const E3& b) {
    if (a.node != b.node) return a.node < b.node;
    return a.pos < b.pos;
}

ll n, m, k;
std::vector<ll> own, need, rl, rr, ra;
std::vector<ll> lo, hi, res;
std::vector<std::vector<ll> > stations; // 每个国家的太空站位置（1 基）

int main() {
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回
    own.assign(m + 1, 0);
    for (ll i = 1; i <= m; i++) scanf("%lld", &own[i]);
    need.assign(n + 1, 0);
    for (ll i = 1; i <= n; i++) scanf("%lld", &need[i]);
    scanf("%lld", &k);
    rl.assign(k + 1, 0);
    rr.assign(k + 1, 0);
    ra.assign(k + 1, 0);
    for (ll i = 1; i <= k; i++) scanf("%lld %lld %lld", &rl[i], &rr[i], &ra[i]);

    stations.assign(n + 1, std::vector<ll>());
    for (ll i = 1; i <= m; i++) stations[own[i]].push_back(i);

    lo.assign(n + 1, 1);
    hi.assign(n + 1, k + 1); // hi = k+1 表示到 K 场雨结束仍不够
    res.assign(n + 1, 0);
    for (ll i = 1; i <= n; i++) res[i] = need[i];

    std::vector<ll> act;
    for (ll i = 1; i <= n; i++) {
        if (lo[i] < hi[i]) act.push_back(i);
    }

    std::vector<ll> keys, uniq, node_lo, node_hi, node_mid, nidx;
    std::vector<E3> ev;
    std::vector<ll> cum;

    while (!act.empty()) {
        keys.clear();
        for (size_t t = 0; t < act.size(); t++) {
            ll c = act[t];
            keys.push_back(lo[c] * (k + 2) + hi[c]);
        }
        uniq = keys;
        std::sort(uniq.begin(), uniq.end());
        uniq.erase(std::unique(uniq.begin(), uniq.end()), uniq.end());

        ll nn = (ll)uniq.size();
        node_lo.assign(nn, 0);
        node_hi.assign(nn, 0);
        node_mid.assign(nn, 0);
        for (ll i = 0; i < nn; i++) {
            node_lo[i] = uniq[i] / (k + 2);
            node_hi[i] = uniq[i] % (k + 2);
            node_mid[i] = (node_lo[i] + node_hi[i]) >> 1;
        }
        nidx.assign(act.size(), 0);
        for (size_t t = 0; t < act.size(); t++) {
            nidx[t] = std::lower_bound(uniq.begin(), uniq.end(), keys[t]) - uniq.begin();
        }

        // 每场雨落在哪个节点；只保留落在该节点左半边（编号 ≤ mid）的雨
        ev.clear();
        for (ll j = 1; j <= k; j++) {
            ll idx = std::upper_bound(node_lo.begin(), node_lo.end(), j) - node_lo.begin() - 1;
            if (idx < 0 || j > node_mid[idx]) continue;
            ll left = rl[j], right = rr[j], val = ra[j];
            E3 e;
            e.node = idx; e.pos = left; e.delta = val; ev.push_back(e);
            if (left > right) { // 环形区间跨过 m，拆成 [left, m] 与 [1, right]
                e.node = idx; e.pos = 1; e.delta = val; ev.push_back(e);
            }
            if (right < m) {
                e.node = idx; e.pos = right + 1; e.delta = -val; ev.push_back(e);
            }
        }
        std::sort(ev.begin(), ev.end(), e3_less);
        cum.assign(ev.size(), 0);
        for (size_t i = 0; i < ev.size(); i++) {
            // 累加要按节点清零：同节点内才是前缀和
            cum[i] = ev[i].delta + ((i > 0 && ev[i].node == ev[i - 1].node) ? cum[i - 1] : 0);
        }

        for (size_t t = 0; t < act.size(); t++) {
            ll c = act[t];
            ll nd = nidx[t];
            ll S = 0;
            for (size_t s = 0; s < stations[c].size(); s++) {
                ll p = stations[c][s];
                // 本节点内最后一个不晚于 p 的事件
                ll lo_i = std::lower_bound(ev.begin(), ev.end(), E3{nd, 0, 0}, e3_less) - ev.begin();
                ll pos = lo_i;
                ll len = (ll)ev.size();
                // 同节点内按 pos 二分
                ll a = lo_i, b = len;
                while (a < b) {
                    ll mid = (a + b) >> 1;
                    if (ev[mid].node == nd && ev[mid].pos <= p) a = mid + 1;
                    else b = mid;
                }
                pos = a - 1;
                ll got = (pos >= lo_i && pos < len && ev[pos].node == nd) ? cum[pos] : 0;
                if (got > CAP) got = CAP;
                S += got;
            }
            if (S >= res[c]) {
                hi[c] = node_mid[nd];
            } else {
                res[c] -= S;
                lo[c] = node_mid[nd] + 1;
            }
        }

        act.clear();
        for (ll i = 1; i <= n; i++) {
            if (lo[i] < hi[i]) act.push_back(i);
        }
    }

    for (ll i = 1; i <= n; i++) {
        if (lo[i] == k + 1) printf("NIE\n");
        else printf("%lld\n", lo[i]);
    }
    return 0;
}
