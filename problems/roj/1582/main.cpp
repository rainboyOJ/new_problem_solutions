/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:48
 * update_at: 2026-10-06 00:48
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll MAXN = 6005; // 职员数上界 6000，多开一点

ll n; // 职员总数
ll joy[MAXN]; // joy[i]：第 i 个职员的欢乐度
vector<ll> children[MAXN]; // children[u]：u 的直接下属
bool has_boss[MAXN]; // has_boss[u]：u 是否有直接上司，用来找树根

ll dp0[MAXN]; // dp0[u]：u 不参加时，u 子树的最大欢乐度
ll dp1[MAXN]; // dp1[u]：u 参加时，u 子树的最大欢乐度
ll order[MAXN]; // order[]：父先于子的遍历序

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> joy[i];
    }

    // 关系行 "L K"：K 是 L 的直接上司，输入以 0 0 结束
    ll emp = 0;
    ll boss = 0;
    while (cin >> emp >> boss) {
        if (emp == 0 && boss == 0) {
            break;
        }
        children[boss].push_back(emp);
        has_boss[emp] = true;
    }

    // 树根就是从没当过下属的人
    ll root = 1;
    for (ll u = 1; u <= n; u++) {
        if (!has_boss[u]) {
            root = u;
            break;
        }
    }

    // 先做一遍父先于子的遍历，得到 order[]
    ll head = 0;
    ll tail = 0;
    order[tail++] = root;
    while (head < tail) {
        ll u = order[head++];
        ll cnt = children[u].size();
        for (ll i = 0; i < cnt; i++) {
            order[tail++] = children[u][i];
        }
    }

    // 倒序遍历即后序：孩子必然先于父亲算完
    for (ll i = n - 1; i >= 0; i--) {
        ll u = order[i];
        dp1[u] = joy[u];
        ll cnt = children[u].size();
        for (ll j = 0; j < cnt; j++) {
            ll v = children[u][j];
            dp0[u] += max(dp0[v], dp1[v]); // u 不来，下属随意
            dp1[u] += dp0[v]; // u 来了，直接下属都不能来
        }
    }

    // 根来或不来取大；都不选即空名单，值为 0
    cout << max(dp0[root], dp1[root]) << '\n';
    return 0;
}
