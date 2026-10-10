/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 蒲公英：分块预处理「整块区间众数」，询问只补两端不足一块的零散位置。
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long ll;

ll n, m;

std::vector<ll> vals;               // 值去重升序
std::vector<ll> a;                  // 压缩后的种类编号
std::vector<std::vector<ll> > mode; // mode[i][j] = 只看块 i..j 时的众数种类编号
std::vector<std::vector<ll> > pre;  // pre[i][v] = 前 i 个完整块里 v 的出现次数

int main() {
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回
    std::vector<ll> raw(n);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &raw[i]);
    }
    vals = raw;
    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    ll kinds = (ll)vals.size();

    a.assign(n, 0);
    for (ll i = 0; i < n; i++) {
        a[i] = std::lower_bound(vals.begin(), vals.end(), raw[i]) - vals.begin();
    }

    ll block = (ll)std::sqrt((double)n); // 块大小取 sqrt(n)，块数与块长同为 O(sqrt(n))
    if (block < 1) block = 1;
    ll nblk = (n + block - 1) / block;

    // 出现位置表（升序），询问时用二分统计区间内次数
    std::vector<std::vector<ll> > occ(kinds);
    for (ll i = 0; i < n; i++) {
        occ[a[i]].push_back(i);
    }

    // mode[i][j]：j 递增时增量维护计数
    mode.assign(nblk, std::vector<ll>(nblk, 0));
    std::vector<ll> cnt(kinds, 0);
    for (ll i = 0; i < nblk; i++) {
        for (ll v = 0; v < kinds; v++) cnt[v] = 0;
        ll best = 0, cur = 0;
        for (ll j = i; j < nblk; j++) {
            ll hi = (j + 1) * block;
            if (hi > n) hi = n;
            for (ll t = j * block; t < hi; t++) {
                ll v = a[t];
                cnt[v]++;
                // 出现更多即换；出现一样多时下标更小才换（对应编号最小）
                if (cnt[v] > best || (cnt[v] == best && v < cur)) {
                    best = cnt[v];
                    cur = v;
                }
            }
            mode[i][j] = cur;
        }
    }

    // 前 i 个完整块的值计数前缀表
    pre.assign(nblk + 1, std::vector<ll>(kinds, 0));
    for (ll i = 0; i < nblk; i++) {
        for (ll v = 0; v < kinds; v++) {
            pre[i + 1][v] = pre[i][v];
        }
        ll hi = (i + 1) * block;
        if (hi > n) hi = n;
        for (ll t = i * block; t < hi; t++) {
            pre[i + 1][a[t]]++;
        }
    }

    std::vector<ll> touch;            // 本询问里动过的种类编号，用于清零
    std::vector<ll> ccnt(kinds, 0);   // 零散段内的值计数
    std::vector<ll> cand;             // 候选值（种类编号）

    ll x = 0; // 上一次询问的答案（明文，用于解密下标）
    for (ll q = 0; q < m; q++) {
        ll ql, qr;
        scanf("%lld %lld", &ql, &qr);
        ll l = (ql + x - 1) % n;
        ll r = (qr + x - 1) % n;
        if (l > r) {
            ll tmp = l; l = r; r = tmp;
        }
        ll bl = l / block, br = r / block;

        touch.clear();
        cand.clear();
        if (bl == br) {
            // 两端落在同一块：整段都不足一块
            for (ll i = l; i <= r; i++) {
                ll v = a[i];
                if (ccnt[v] == 0) {
                    touch.push_back(v);
                    cand.push_back(v);
                }
                ccnt[v]++;
            }
        } else {
            ll lhi = (bl + 1) * block;
            for (ll i = l; i < lhi; i++) {
                ll v = a[i];
                if (ccnt[v] == 0) {
                    touch.push_back(v);
                    cand.push_back(v);
                }
                ccnt[v]++;
            }
            for (ll i = br * block; i <= r; i++) {
                ll v = a[i];
                if (ccnt[v] == 0) {
                    touch.push_back(v);
                    cand.push_back(v);
                }
                ccnt[v]++;
            }
            if (br - 1 > bl) { // 中间整块区间的众数只需和零散值比一比
                cand.push_back(mode[bl + 1][br - 1]);
            }
        }

        ll best = -1, bestc = -1; // 众数的种类编号与出现次数
        for (size_t t = 0; t < cand.size(); t++) {
            ll v = cand[t];
            ll c = ccnt[v];
            if (bl != br) {
                c += pre[br][v] - pre[bl + 1][v];
            }
            if (c > bestc || (c == bestc && v < best)) {
                best = v;
                bestc = c;
            }
        }
        x = vals[best];
        printf("%lld\n", x);

        for (size_t t = 0; t < touch.size(); t++) {
            ccnt[touch[t]] = 0;
        }
    }
    return 0;
}
