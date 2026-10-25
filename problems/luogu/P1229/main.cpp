/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-25 14:18
 * update_at: 2026-10-25 14:18
 */
/**
 * P1229 遍历问题
 * 由前序遍历和后序遍历，统计可能的中序遍历个数。
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string pre;        // 前序遍历：根、左、右
string post;       // 后序遍历：左、右、根
ll post_pos[256];  // post_pos[ch] 表示字符 ch 在后序遍历中的下标

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> pre >> post;
    ll n = pre.size();

    for (ll i = 0; i < n; ++i) {
        post_pos[post[i]] = i;
    }

    // 关键观察：若前序里相邻的 pre[i]、pre[i+1] 在后序里也正好反向相邻，
    // 说明 pre[i+1] 是 pre[i] 唯一的孩子，它挂左边还是右边
    // 得到的前序、后序完全一样，只有中序不同 —— 这就是一个“单孩子歧义点”。
    // 每出现一个这样的点，中序遍历的方案数就翻一倍。
    ll ambiguous = 0;  // 单孩子歧义点的个数
    for (ll i = 0; i + 1 < n; ++i) {
        if (post_pos[pre[i]] == post_pos[pre[i + 1]] + 1) {
            ++ambiguous;
        }
    }

    // 答案是 2^ambiguous，题目保证结果不超过 2^63-1，用 ll 存得下。
    ll ans = 1;
    for (ll i = 0; i < ambiguous; ++i) {
        ans *= 2;
    }

    cout << ans << '\n';
    return 0;
}
