/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:23
 * update_at: 2026-10-07 17:23
 */
// 1684《翻转序列》：每次可以翻转前缀 x[1..i]，求把 1~n 的排列变成升序的最少步数。
// 算法：迭代加深 + IDA*，估价函数取「断点数」——在末尾补一个虚拟的 n+1 之后，
//       相邻两数差的绝对值不等于 1 的位置数。
//   1. 翻转前缀 1..i（i < n）时，块内相邻对的差的绝对值整体不变，唯一被改动的
//      邻接是「块尾 a[i] 与后继 a[i+1]」这一处；翻转整串（i = n）时块内邻接
//      全不变，但末项换成了原来的首项 a[1]。两种情况下断点数都至多减 1。
//   2. 升序排列的断点数是 0，于是断点数是剩余步数的可采纳下界，可以直接当估价剪枝。
//   3. 反过来断点数为 0 时：内部邻接全好说明序列单调，末项又是 n，只能是升序，
//      所以「断点数 == 0」就是达成条件，不必再扫一遍数组。
//   深度上限 limit 从小到大枚举，DFS 内用 tot + h > limit 剪枝；连着两次翻同一长度
//   等于原样翻回去，属于白翻一步，直接跳过。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 30;   // 题面 n <= 23，留一点余量

ll n;                  // 本组数据的排列长度
ll a[MAXN];            // 当前排列，下标 1..n
ll limit_depth;        // 本轮迭代加深的步数上限

// 相邻两数差的绝对值不等于 1 就叫一个断点；把 a[n+1] 看作虚拟的 n + 1
ll bad(ll x, ll y) {
    return (abs(x - y) != 1);
}

// 断点数：整个排列的断点个数，是剩余步数的下界
ll break_count() {
    ll h = bad(a[n], n + 1);           // 末项与虚拟的 n+1 之间
    for (ll i = 1; i < n; i++) h += bad(a[i], a[i + 1]);
    return h;
}

// 已翻 tot 步、上一步翻转长度为 last_len（0 表示还没翻过），当前断点数为 h。
// 在 limit_depth 步以内能否把排列翻成升序。
bool dfs(ll tot, ll last_len, ll h) {
    if (tot + h > limit_depth) return false;   // 估价剪枝：剩下 tot 步以外至少要 h 步
    // 断点清零即已升序。注意先剪枝再判达成：超过上限的升序状态不算这一层的解。
    if (h == 0) return true;

    for (ll i = 2; i <= n; i++) {
        if (i == last_len) continue;           // 连着翻同一长度 = 白翻一步
        ll head = a[1], tail = a[i];           // 翻转后 a[i] 位置变成原来的 a[1]
        ll nh = h;
        if (i < n) {                           // 只有 (a[i], a[i+1]) 这一处邻接会变
            nh += bad(head, a[i + 1]) - bad(tail, a[i + 1]);
        } else {                               // 翻整串：末项换成原来的首项
            nh += bad(head, n + 1) - bad(tail, n + 1);
        }
        reverse(a + 1, a + 1 + i);
        if (dfs(tot + 1, i, nh)) return true;
        reverse(a + 1, a + 1 + i);             // 再翻同一前缀即还原
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    if (!(cin >> t)) return 0;
    while (t--) {
        cin >> n;
        for (ll i = 1; i <= n; i++) cin >> a[i];

        ll ans = 0;
        for (limit_depth = 0; ; limit_depth++) {
            if (dfs(0, 0, break_count())) { ans = limit_depth; break; }
        }
        cout << ans << '\n';
    }
    return 0;
}
