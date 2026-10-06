/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:11
 * update_at: 2026-10-06 13:11
 */

#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1 << 10 | 5; // N <= 10，串长最多 2^10

char s[MAXN]; // 输入 01 串
char ans[MAXN * 2]; // 后序序列，长度 2^(N+1) - 1
ll ans_len; // 当前已写入 ans 的字符数

// 判断 [l, r] 区间内子串类型：全 0 为 B，全 1 为 I，都有为 F
char node_type(ll l, ll r) {
    bool has0 = false, has1 = false;
    for (ll i = l; i <= r; i++) {
        if (s[i] == '0') has0 = true;
        else has1 = true;
    }
    if (!has1) return 'B';
    if (!has0) return 'I';
    return 'F';
}

// 递归处理子串 [l, r]，先左右子树，返回前把本结点字符写入 ans
void build(ll l, ll r) {
    if (l == r) {
        ans[ans_len++] = s[l] == '0' ? 'B' : 'I';
        return;
    }
    ll mid = (l + r) >> 1;
    build(l, mid);      // 左子树
    build(mid + 1, r);  // 右子树
    ans[ans_len++] = node_type(l, r); // 根
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n >> (s + 1);
    ll m = 1LL << n; // 串长 2^N
    ans_len = 0;
    build(1, m);
    ans[ans_len] = '\0';
    cout << ans << "\n";
    return 0;
}
