/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:07
 * update_at: 2026-10-05 03:07
 */
// main.cpp：01 字典树求最大异或对，先全部插入再逐个贪心查询，O(31N)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int TOP_BIT = 30;            // A_i < 2^31，二进制最高位是第 30 位
const int MAXNODE = 31 * MAXN + 5; // 每个数最多新建 31 个节点，再加一个根节点

typedef long long ll;

ll n;
ll a[MAXN]; // 输入的 N 个整数

// 01 字典树：ch[u][b] 表示从节点 u 走"第 b 位"这条边能到的孩子，0 表示这条边不存在
int ch[MAXNODE][2];
int node_cnt = 1; // 已分配的节点编号，根固定为 1，节点 0 永远空着

// 把 x 的 31 位从高位到低位插入 01 字典树，缺哪条边就新建哪个节点。
void insert_number(ll x) {
    int u = 1;
    for (int bit = TOP_BIT; bit >= 0; bit--) {
        int b = (x >> bit) & 1;
        if (ch[u][b] == 0) {
            node_cnt++;
            ch[u][b] = node_cnt;
        }
        u = ch[u][b];
    }
}

// 在树上贪心求与 x 异或最大的已插入值：每一位优先走和 x 相反的那条边。
ll best_xor(ll x) {
    int u = 1;
    ll res = 0;
    for (int bit = TOP_BIT; bit >= 0; bit--) {
        int b = (x >> bit) & 1;
        int opposite = ch[u][b ^ 1];
        if (opposite != 0) { // 相反位存在，这一位异或取 1，收益 2^bit 大于所有低位之和
            u = opposite;
            res |= 1LL << bit;
        } else { // 没有相反位可走，只能将就走相同位，这一位异或为 0
            u = ch[u][b];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        insert_number(a[i]); // 先把所有数插入，再逐个查询
    }

    // 贪心下降的终点一定是真实插入过的数，所以每次查询的结果都能由某个真实配对达成；
    // 自己和自己配对只会得到 0，不会抬高最大值。
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ll value = best_xor(a[i]);
        if (ans < value) {
            ans = value;
        }
    }
    cout << ans << "\n";

    return 0;
}
