/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:55
 * update_at: 2026-10-07 15:55
 */
// main.cpp：PFS 集合，字典树上数「两两不成前缀」的子集个数。
// 与 main.py 同一算法：把字符串按字典序排序，第 i 个串在 trie 中的父节点深度就是
// 它与前一个串的最长公共前缀长度，于是不必真的开出 26 叉字典树，
// 只用一个手工栈按深度收拢节点即可完成同样的树形 DP。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 9191;    // 题目要求的取模值
const int MAXN = 50005;  // 字符串个数上限

// trie 上的一个节点。只保留「单词结尾」与「分叉点」：
// 不是结尾且只有一个儿子的节点，其答案等于儿子的答案，可以整段跳过。
struct Frame {
    ll depth;   // 该节点对应的前缀长度
    ll prod;    // 已并入的儿子答案累乘值
    ll is_end;  // 该前缀本身是不是一个单词（0/1）
};

string word[MAXN];  // 按字典序排序后的所有字符串
Frame stk[MAXN];    // 手工栈：stk[0] 是根（深度 0，不是任何单词的结尾），stk[top_cnt] 是当前最深节点
ll top_cnt;         // 栈顶下标

// 弹出栈顶节点，把它自己的答案乘进父亲的累乘值。
// f[v] = (所有儿子 f 的乘积) + (v 是单词结尾 ? 1 : 0)：
// 乘积那部分对应「不选 v，在每棵子树里各选一个合法子集」，
// 加上的 1 对应「选 v，则子树里一个都不能再选」。
void fold_top() {
    ll f_val = (stk[top_cnt].prod + stk[top_cnt].is_end) % MOD;
    top_cnt--;
    stk[top_cnt].prod = stk[top_cnt].prod * f_val % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) cin >> word[i];
    sort(word, word + n);  // 同一前缀的串排在一起，子树变成连续区间

    stk[0].depth = 0;   // 根节点
    stk[0].prod = 1;    // 累乘初值
    stk[0].is_end = 0;  // 空串不是输入里的元素
    top_cnt = 0;

    ll prev_len = 0;  // 上一个字符串的长度
    for (ll i = 0; i < n; i++) {
        ll len = word[i].size();
        ll lcp = 0;
        if (i > 0) {
            // 与上一个串的最长公共前缀长度，就是本串所在节点的父亲深度
            ll lim = min(len, prev_len);
            while (lcp < lim && word[i][lcp] == word[i - 1][lcp]) lcp++;
        }
        while (stk[top_cnt].depth > lcp) fold_top();  // 收掉比父亲更深的节点
        top_cnt++;
        stk[top_cnt].depth = len;
        stk[top_cnt].prod = 1;
        stk[top_cnt].is_end = 1;  // 当前字符串本身是一个结尾节点
        prev_len = len;
    }
    while (top_cnt > 0) fold_top();  // 把整条路径收拢回根

    cout << stk[0].prod % MOD << '\n';  // 根的累乘值就是答案（空集已被算作一种）
    return 0;
}
