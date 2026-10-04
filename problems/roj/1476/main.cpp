/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:22
 * update_at: 2026-10-05 03:22
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 500005; // 节点总数不超过信息位总数 5*10^5，再加根

typedef long long ll;

// 01-Trie：ch[v][t] 是节点 v 的 t 孩子（t=0/1），0 同时表示"不存在"和根
int ch[MAXNODE][2];
int through_cnt[MAXNODE]; // through_cnt[v]：路径经过 v 的信息条数（终止在 v 的也算经过）
int end_cnt[MAXNODE];     // end_cnt[v]：恰好终止在 v 的信息条数
int node_cnt = 0;         // 已用节点数，根是 0

int pwd[MAXNODE]; // 当前密码的每一位，先整行读入再走树，断路也不用担心输入残留

// 把一条信息插入 Trie：沿路每个节点 through+1，终点 end+1
void trie_insert(ll len) {
    int v = 0; // 从根出发
    for (ll i = 1; i <= len; i++) {
        int t;
        cin >> t;
        if (ch[v][t] == 0) {
            node_cnt++;
            ch[v][t] = node_cnt;
        }
        v = ch[v][t];
        through_cnt[v]++;
    }
    end_cnt[v]++;
}

// 查询一条密码：沿途累加 end（比密码短、是密码前缀的信息），
// 全部走通再补 through-end（比密码长、以密码为前缀的信息）
ll trie_query(ll len) {
    ll ans = 0;
    int v = 0;
    for (ll i = 1; i <= len; i++) {
        int t = pwd[i];
        if (ch[v][t] == 0) {
            // 断路：更深处没有任何信息，第 2 类不存在
            return ans;
        }
        v = ch[v][t];
        ans += end_cnt[v];
    }
    // 与密码完全相等的信息在沿途已被计入一次，
    // through-end 恰好把它减掉，不会重复统计
    ans += through_cnt[v] - end_cnt[v];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        ll len;
        cin >> len;
        trie_insert(len);
    }
    for (ll j = 1; j <= m; j++) {
        ll len;
        cin >> len;
        for (ll k = 1; k <= len; k++) cin >> pwd[k];
        cout << trie_query(len) << "\n";
    }
    return 0;
}
