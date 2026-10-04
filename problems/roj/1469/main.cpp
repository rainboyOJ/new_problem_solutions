/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:59
 * update_at: 2026-10-05 02:59
 */
// main.cpp：固定左端点，用 Z 数组一次求出该段全部 lcp，再按偏移递增扫连续右端点区间求并，O(n^2)。
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 15005;

typedef long long ll;

char s[MAXN]; // 题目给定的小写字母串，下标从 1 开始，s[1..n] 有效
ll n;
ll k;
ll z[MAXN]; // z[i] = lcp(s[l..], s[l+i..])，下标是相对当前左端点 l 的偏移，每换一个 l 全部重算

// 统计以 l 为左端点的合法 A+B+A 子串个数（同一子串只算一次）。
// 第二个 A 的起点偏移为 i 时，合法的 |A| 是一段连续整数，于是右端点也落在连续区间里；
// 偏移 i 从小到大递增时区间左端也递增，用 covered 记录已覆盖的最右偏移就能线性去重。
ll count_left(ll l) {
    ll m = n - l + 1;   // 当前段 s[l..n] 的长度
    ll box_l = 0;       // Z 盒：[box_l, box_r) 与 [l, l+box_r-box_l) 逐字符相同
    ll box_r = 0;
    ll covered = -1;    // 区间并已经覆盖到的最右偏移
    ll res = 0;

    for (ll i = 1; i < m; i++) {
        ll zi = 0;
        if (i < box_r) {
            zi = box_r - i;
            ll v = z[i - box_l];
            if (v < zi) {
                zi = v; // 没顶到盒边：z[i] 已精确，不必逐字符比较
            } else {
                while (l + i + zi <= n && s[l + zi] == s[l + i + zi]) zi++; // 顶到盒边，继续向后延伸
            }
        } else {
            while (l + i + zi <= n && s[l + zi] == s[l + i + zi]) zi++; // 盒外从头求 lcp
        }
        if (i + zi > box_r) {
            box_l = i;
            box_r = i + zi;
        }

        // i > k 保证 |B| >= 1，zi >= k 保证 |A| >= k，否则该偏移无合法拆分
        if (i > k && zi >= k) {
            ll upper = zi < i - 1 ? zi : i - 1; // min(lcp, i-1)：两个 A 不能重叠
            ll b = i + k - 1;                   // |A| 取最小 k 时的右端点偏移
            ll e = i + upper - 1;               // |A| 取最大时的右端点偏移
            if (e > covered) {
                if (b > covered) {
                    res += e - b + 1; // 整段区间都是新的
                } else {
                    res += e - covered; // 只有尾部是新的，前面已被别的偏移数过
                }
                covered = e;
            }
        }
        z[i] = zi; // 写在最后，供更后面的位置复用 Z 盒
    }

    return res;
}

void read_input() {
    string text;
    cin >> text >> k;
    n = text.size();
    for (ll i = 1; i <= n; i++) {
        s[i] = text[i - 1];
    }
}

void solve() {
    ll ans = 0;
    for (ll l = 1; l <= n; l++) {
        ans += count_left(l);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
