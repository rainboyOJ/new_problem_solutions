/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 13:53
 */
// brute.cpp：正确性优先的暴力解，用于对拍。
//
// 坐标可能到 1e9，无法直接枚举每条线，但「一条线的命中集合」只会在一组
// 断点处改变：x 轴上断点为 {1, M+1} ∪ {x1_i, x2_i+1}，y 轴同理。
// 于是把每个轴划分成若干类区间，同一类内所有取值的命中集合相同。
// 只要枚举「三个类」的组合（含同类重复，因为同一类里可以取多个不同值），
// 用类长度做组合计数即可。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MX = 1000000000LL;
const ll MOD = 998244353;
const int MAXN = 100005;

int n;
ll rx1[MAXN], ry1[MAXN], rx2[MAXN], ry2[MAXN];

// 一条线：轴（0=x,1=y）、可取值个数 w、命中矩形掩码 mask
struct Line {
    int axis;
    ll w;
    unsigned long long mask;   // n <= 64 时够用，对拍用
};

ll bx[2 * MAXN], by[2 * MAXN];
Line ln[4 * MAXN];

// 组合数 C(x,k)，k=2,3
inline __int128 C2(ll x) { return (__int128)x * (x - 1) / 2; }
inline __int128 C3(ll x) { return (__int128)x * (x - 1) * (x - 2) / 6; }

void solve() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> rx1[i] >> ry1[i] >> rx2[i] >> ry2[i];
        }
        // 两个轴的断点
        int cx = 0, cy = 0;
        bx[cx++] = 1; bx[cx++] = MX + 1;
        by[cy++] = 1; by[cy++] = MX + 1;
        for (int i = 0; i < n; ++i) {
            bx[cx++] = rx1[i];
            if (rx2[i] + 1 <= MX + 1) bx[cx++] = rx2[i] + 1;
            by[cy++] = ry1[i];
            if (ry2[i] + 1 <= MX + 1) by[cy++] = ry2[i] + 1;
        }
        sort(bx, bx + cx); cx = (int)(unique(bx, bx + cx) - bx);
        sort(by, by + cy); cy = (int)(unique(by, by + cy) - by);

        int L = 0;
        // x 轴各类
        for (int k = 0; k + 1 < cx; ++k) {
            ll lo = bx[k], hi = bx[k + 1] - 1;
            if (lo > MX) break;
            unsigned long long mask = 0;
            for (int i = 0; i < n && i < 64; ++i)
                if (rx1[i] <= lo && lo <= rx2[i]) mask |= 1ULL << i;
            ln[L].axis = 0; ln[L].w = hi - lo + 1; ln[L].mask = mask; ++L;
        }
        // y 轴各类
        for (int k = 0; k + 1 < cy; ++k) {
            ll lo = by[k], hi = by[k + 1] - 1;
            if (lo > MX) break;
            unsigned long long mask = 0;
            for (int i = 0; i < n && i < 64; ++i)
                if (ry1[i] <= lo && lo <= ry2[i]) mask |= 1ULL << i;
            ln[L].axis = 1; ln[L].w = hi - lo + 1; ln[L].mask = mask; ++L;
        }

        unsigned long long full = (n >= 64) ? ~0ULL : ((1ULL << n) - 1);
        __int128 tot = 0;
        // 枚举三类的下标 i <= j <= k（同一类可取多个不同值）
        for (int i = 0; i < L; ++i)
            for (int j = i; j < L; ++j)
                for (int k = j; k < L; ++k) {
                    if ((ln[i].mask | ln[j].mask | ln[k].mask) != full) continue;
                    __int128 cnt;
                    if (i == k) cnt = C3(ln[i].w);              // 三者同类
                    else if (i == j) cnt = C2(ln[i].w) * ln[k].w;
                    else if (j == k) cnt = ln[i].w * C2(ln[j].w);
                    else cnt = (__int128)ln[i].w * ln[j].w * ln[k].w;
                    tot += cnt;
                }
        cout << (ll)(tot % MOD) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
