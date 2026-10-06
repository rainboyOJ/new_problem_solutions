#include <bits/stdc++.h>
using namespace std;

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:30
 * update_at: 2026-10-06 16:30
 */

typedef long long ll;

// 每个状态反推出的前驱集合最多 81 个，交集只收缩，用数组存即可
const int MAXN = 10;   // n <= 8
const int MAXP = 100;  // 单个状态的前驱最多 5*9 + 4*9 = 81 个

ll n;                                   // 锁车后状态数
ll st[MAXN][5];                         // st[i][j] = 第 i 个状态的第 j 个拨圈数字
ll cand[MAXP][5];                       // 当前候选密码集合（前驱集合的交集）
ll cnt;                                 // 当前候选个数

// 判断数组 p 的五个数字是否已在候选集合 cand 中（去重用）
bool in_cand(ll p[5]) {
    for (ll i = 0; i < cnt; i++) {
        bool same = true;
        for (ll j = 0; j < 5; j++)
            if (cand[i][j] != p[j]) same = false;
        if (same) return true;
    }
    return false;
}

// 把状态 s 的全部前驱与候选集合求交：先枚举 81 个前驱，属于旧候选才保留
void intersect(ll s[5]) {
    ll nxt[MAXP][5]; // 新交集，最多仍 81 个
    ll ncnt = 0;
    ll p[5];

    // 单拨圈反推：第 i 位换成其余 9 个数字（幅度非零），恰一位不同
    for (ll i = 0; i < 5; i++) {
        for (ll v = 0; v < 10; v++) {
            if (v == s[i]) continue;
            for (ll j = 0; j < 5; j++) p[j] = s[j];
            p[i] = v;
            if (in_cand(p)) { // 新交集只需检查旧候选
                for (ll j = 0; j < 5; j++) nxt[ncnt][j] = p[j];
                ncnt++;
            }
        }
    }

    // 相邻双拨圈反推：相邻两位同减非零幅度 d（模 10），恰两位不同
    for (ll i = 0; i + 1 < 5; i++) {
        for (ll d = 1; d <= 9; d++) {
            for (ll j = 0; j < 5; j++) p[j] = s[j];
            p[i] = (s[i] - d + 10) % 10;
            p[i + 1] = (s[i + 1] - d + 10) % 10;
            if (in_cand(p)) {
                for (ll j = 0; j < 5; j++) nxt[ncnt][j] = p[j];
                ncnt++;
            }
        }
    }

    // 用新交集覆盖旧候选
    for (ll i = 0; i < ncnt; i++)
        for (ll j = 0; j < 5; j++) cand[i][j] = nxt[i][j];
    cnt = ncnt;
}

int main() {
    scanf("%lld", &n);
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < 5; j++) scanf("%lld", &st[i][j]);

    // 第一个状态的全部前驱作为初始候选：单拨圈 + 相邻双拨圈，共 81 个
    cnt = 0;
    ll p[5];
    for (ll i = 0; i < 5; i++)
        for (ll v = 0; v < 10; v++) {
            if (v == st[0][i]) continue;
            for (ll j = 0; j < 5; j++) p[j] = st[0][j];
            p[i] = v;
            for (ll j = 0; j < 5; j++) cand[cnt][j] = p[j];
            cnt++;
        }
    for (ll i = 0; i + 1 < 5; i++)
        for (ll d = 1; d <= 9; d++) {
            for (ll j = 0; j < 5; j++) p[j] = st[0][j];
            p[i] = (st[0][i] - d + 10) % 10;
            p[i + 1] = (st[0][i + 1] - d + 10) % 10;
            for (ll j = 0; j < 5; j++) cand[cnt][j] = p[j];
            cnt++;
        }

    // 依次与其余状态的前驱集合求交，交集大小即答案
    for (ll i = 1; i < n; i++) intersect(st[i]);
    printf("%lld\n", cnt);
    return 0;
}
