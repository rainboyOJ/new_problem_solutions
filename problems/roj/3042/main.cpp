/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:50
 * update_at: 2026-10-06 15:50
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int BITS = 31;                  // A_i < 2^31，所以看二进制第 30 位到第 0 位
const int MAX_NODE = BITS * MAXN + 5; // 每个数最多新建 BITS 个结点

// 01-Trie 的儿子表：children[2*p] 是结点 p 走 0 的儿子，children[2*p+1] 是走 1 的儿子。
// 0 表示这条边还没建出来（结点编号从 1 开始，根固定为 0），所以数组要开两倍结点数。
int children[2 * MAX_NODE];
int node_count = 1; // 下一个可用的结点编号

ll n;
ll a[MAXN]; // 输入序列

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

// 把一个数按二进制从高位到低位插入 01-Trie。
void insert_value(ll value) {
    int node = 0; // 从根出发
    for (int bit = BITS - 1; bit >= 0; bit--) {
        int b = value >> bit & 1;
        int slot = (node << 1) | b;
        if (children[slot] == 0) { // 这条边还没有，现场新建一个儿子
            children[slot] = node_count;
            node_count++;
        }
        node = children[slot];
    }
}

// 在 Trie 里为 value 贪心找异或最大的搭档，返回这个最大的异或值。
// 高位权重大于所有低位之和，所以每一位只要能走相反位就一定走。
ll best_xor(ll value) {
    int node = 0;
    ll result = 0;
    for (int bit = BITS - 1; bit >= 0; bit--) {
        int b = value >> bit & 1;
        int base = node << 1;
        int opposite = children[base | (b ^ 1)]; // 想要这一位异或出 1，先看相反位有没有儿子
        if (opposite != 0) {
            result |= 1LL << bit; // 相反位存在，这一位一定是 1
            node = opposite;
        } else {
            node = children[base | b]; // 只能走同位，这一位异或结果是 0
        }
    }
    return result;
}

void solve() {
    for (ll i = 1; i <= n; i++) {
        insert_value(a[i]);
    }

    ll answer = 0;
    for (ll i = 1; i <= n; i++) {
        ll current = best_xor(a[i]);
        if (current > answer) {
            answer = current;
        }
    }
    cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
