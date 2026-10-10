/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 作诗：分块预处理「整块区间内出现正偶数次的数值个数」，询问补两端零散位置。
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

typedef long long ll;

const ll T = 1000; // 分块大小

struct BlockVal {
    int v; // 值
    int c; // 该值在本块内的出现次数
};

int main() {
    ll n, c, m;
    if (scanf("%lld %lld %lld", &n, &c, &m) != 3) return 0; // 空输入安全返回
    std::vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    ll blocks = (n + T - 1) / T;
    ll W = c + 1;

    // pre[i][v] = 前 i 个块中值 v 的出现次数
    std::vector<int> pre((blocks + 1) * W, 0);
    std::vector<std::vector<BlockVal> > nz(blocks); // 每块里出现过的值与块内次数

    std::vector<int> cntB(c + 1, 0);
    std::vector<int> touched;
    for (ll i = 0; i < blocks; i++) {
        ll lo = i * T, hi = (i + 1) * T;
        if (hi > n) hi = n;
        touched.clear();
        for (ll t = lo; t < hi; t++) {
            int v = (int)a[t];
            if (cntB[v] == 0) touched.push_back(v);
            cntB[v]++;
        }
        memcpy(&pre[(i + 1) * W], &pre[i * W], W * sizeof(int)); // 先继承前缀
        for (size_t t = 0; t < touched.size(); t++) {
            int v = touched[t];
            pre[(i + 1) * W + v] += cntB[v];
            BlockVal bv;
            bv.v = v;
            bv.c = cntB[v]; // 块内计数不能只用「出现与否」
            nz[i].push_back(bv);
            cntB[v] = 0;
        }
    }

    // g[i][j] = 完整块区间 [i, j] 内出现正偶数次的数值个数
    std::vector<std::vector<int> > g(blocks, std::vector<int>(blocks, 0));
    std::vector<int> cnt(c + 1, 0);
    for (ll i = 0; i < blocks; i++) {
        touched.clear();
        ll cur = 0;
        for (ll j = i; j < blocks; j++) {
            for (size_t t = 0; t < nz[j].size(); t++) {
                int v = nz[j][t].v;
                ll before = cnt[v];
                ll after = before + nz[j][t].c;
                cnt[v] = (int)after;
                bool db = (before % 2 == 0 && before >= 2); // 状态函数 f(x) = (x 为正偶数)
                bool da = (after % 2 == 0 && after >= 2);
                if (da && !db) cur++;
                else if (!da && db) cur--;
                if (before == 0) touched.push_back(v);
            }
            g[i][j] = (int)cur;
        }
        for (size_t t = 0; t < touched.size(); t++) cnt[touched[t]] = 0;
    }

    std::vector<int> ccnt(c + 1, 0);
    std::vector<int> touch;
    ll ans = 0; // 上一个询问的答案，强制在线解密用
    for (ll q = 0; q < m; q++) {
        ll ql, qr;
        scanf("%lld %lld", &ql, &qr);
        ll l = (ql + ans) % n;
        ll r = (qr + ans) % n;
        if (l > r) {
            ll tmp = l; l = r; r = tmp;
        }
        ll bl = l / T, br = r / T;

        touch.clear();
        if (br - bl < 2) {
            // 中间没有完整块：整段当作散段直接统计
            for (ll i = l; i <= r; i++) {
                int v = (int)a[i];
                if (ccnt[v] == 0) touch.push_back(v);
                ccnt[v]++;
            }
            ll res = 0;
            for (size_t t = 0; t < touch.size(); t++) {
                ll cntv = ccnt[touch[t]];
                if (cntv >= 2 && cntv % 2 == 0) res++;
            }
            ans = res;
        } else {
            // 两侧散段的互异值：先在完整块答案上做补偿
            ll lhi = (bl + 1) * T;
            for (ll i = l; i < lhi; i++) {
                int v = (int)a[i];
                if (ccnt[v] == 0) touch.push_back(v);
                ccnt[v]++;
            }
            for (ll i = br * T; i <= r; i++) {
                int v = (int)a[i];
                if (ccnt[v] == 0) touch.push_back(v);
                ccnt[v]++;
            }
            ll res = g[bl + 1][br - 1];
            for (size_t t = 0; t < touch.size(); t++) {
                int v = touch[t];
                ll tin = pre[br * W + v] - pre[(bl + 1) * W + v]; // 该值在中间完整块的次数
                ll total = tin + ccnt[v];
                if (total >= 2 && total % 2 == 0) res++;      // 总次数为正偶数
                if (tin >= 2 && tin % 2 == 0) res--;          // 只在中间块里算成过正偶数
            }
            ans = res;
        }

        printf("%lld\n", ans);
        for (size_t t = 0; t < touch.size(); t++) ccnt[touch[t]] = 0;
    }
    return 0;
}
