/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:43
 * update_at: 2026-10-07 15:43
 */
// main.cpp：前缀和（ROJ 1696）。
// 题意：给出字符串 s，求所有长度为偶数的前缀在 s 中出现的次数之和（可重叠）。
//
// 算法：KMP 前缀函数 + fail 树上的子树求和。
//   fail[i] 表示长度 i 的前缀的最长真 border 长度；把每个前缀长度看成一个点，
//   连边 i -> fail[i]，得到一个以 0 为根的树（fail 树）。
//   长度 i 的前缀每"作为别人的 border 出现一次"，就对应 fail 树上一个后代；
//   因此 cnt[i] = 1 + sum(cnt[j])，其中 j 是 i 的儿子（+1 是它自己作为整串起点的首次出现）。
//   从长到短反向把 cnt[fail[i]] += cnt[i] 即可完成子树求和，最后累加所有偶数 i 的 cnt[i]。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005; // |s| 上限 200000，多留几个位置给 1-indexed 的下标

char s[MAXN];     // 输入的字符串，转成 0-indexed 字符数组，s[i] 表示第 i+1 个字符
int fail[MAXN];   // fail[i]：长度 i 的前缀的最长真 border 长度（1 <= i <= n）
ll cnt[MAXN];     // cnt[i]：长度 i 的前缀在 s 中出现的总次数（含自身这一次）

int main() {
    scanf("%s", s);
    ll n = strlen(s); // 字符串长度，题目数据用 ll

    // ---------- 1. 求 fail 数组（前缀函数） ----------
    // k 始终表示"已经匹配上的 border 长度"，即 fail 树上当前点的父边长度
    ll k = 0;
    for (ll i = 2; i <= n; i++) {
        while (k > 0 && s[k] != s[i - 1]) {
            k = fail[k]; // 失配就沿 fail 链往回跳，直到能接上或者跳空
        }
        if (s[k] == s[i - 1]) {
            k++; // 接上了，border 长度加一
        }
        fail[i] = k;
    }

    // ---------- 2. 在 fail 树上做子树求和 ----------
    // 初始每个前缀自己至少出现一次（就是它自己作为 s 的前缀）
    for (ll i = 1; i <= n; i++) {
        cnt[i] = 1;
    }
    // 一个点的儿子编号一定比它大，所以从 n 往 1 扫，就能在父亲被用到之前把它累加好
    for (ll i = n; i >= 1; i--) {
        cnt[fail[i]] += cnt[i];
    }
    cnt[0] = 0; // 空前缀不算答案，且它累加来的值只用于传递，最后清零

    // ---------- 3. 累加所有偶数长度的前缀 ----------
    ll ans = 0;
    for (ll i = 2; i <= n; i += 2) {
        ans += cnt[i];
    }
    printf("%lld\n", ans);
    return 0;
}
