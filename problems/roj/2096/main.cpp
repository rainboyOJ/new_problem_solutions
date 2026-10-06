/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:28
 * update_at: 2026-10-06 13:28
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int BITS = 21;                              // 数值范围 0..2^21-1，从第 20 位往低位决策
const int MAXNODE = MAXN * (BITS + 1) + 5;        // 每个前缀最多新增 BITS+1 个结点

ll n;               // 奶牛数量
ll pre[MAXN];       // pre[i] = a[1]^...^a[i]；pre[0]=0 是空前缀哨兵，对应起点 1

int child[MAXNODE * 2]; // 01 字典树孩子表：结点 u 的 0/1 孩子是 child[2u]/child[2u+1]，0 表示空
ll leaf_id[MAXNODE];    // 叶子登记该前缀值已插入的最大下标，非叶子恒为 -1
int node_cnt;           // 已用结点数，结点 0 作根

// 把前缀值 val 插入字典树，并在叶子登记下标 j；同值重复插入时覆盖为更大的 j。
void trie_insert(ll val, ll j) {
    int u = 0;
    for (int k = BITS - 1; k >= 0; k--) {
        ll b = (val >> k) & 1;
        int v = child[2 * u + b];
        if (v == 0) {
            v = node_cnt;
            node_cnt++;
            child[2 * v] = 0;
            child[2 * v + 1] = 0;
            leaf_id[v] = -1;
            child[2 * u + b] = v;
        }
        u = v;
    }
    leaf_id[u] = j; // 后插入的下标更大，直接覆盖即保留最大下标 -> 同值下子段最短
}

// 贪心走“异或后该位为 1”的分支，返回与 val 异或最大的那个前缀下标。
ll trie_query(ll val) {
    int u = 0;
    for (int k = BITS - 1; k >= 0; k--) {
        ll b = (val >> k) & 1;
        int other = child[2 * u + (b ^ 1)];
        if (other != 0) {
            u = other; // 反向位存在就走，该位异或得 1
        } else {
            u = child[2 * u + b]; // 反向位不存在只能顺走，该位异或得 0
        }
    }
    return leaf_id[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    pre[0] = 0;
    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        pre[i] = pre[i - 1] ^ x;
    }

    // 建树：清空根，插入空前缀哨兵（值 0、下标 0）。
    child[0] = 0;
    child[1] = 0;
    leaf_id[0] = -1;
    node_cnt = 1;
    trie_insert(0, 0);

    ll best_v = -1; // 最大异或值
    ll best_l = 1;  // 最优子段起点
    ll best_r = 1;  // 最优子段终点
    for (ll r = 1; r <= n; r++) {
        ll j = trie_query(pre[r]); // 先查后插，保证 j < r、子段非空
        ll cand = pre[r] ^ pre[j];
        if (cand > best_v) { // 严格大于：并列时保留最早结尾
            best_v = cand;
            best_l = j + 1;
            best_r = r;
        }
        trie_insert(pre[r], r);
    }

    cout << best_v << ' ' << best_l << ' ' << best_r << '\n';
    return 0;
}
