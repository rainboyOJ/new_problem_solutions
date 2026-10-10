/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 最大重复：s2 作为子序列在 conn(s1, n1) 中的最大重复次数，贪心 + 倍增状态。
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

typedef long long ll;

struct St {
    ll blocks; // 跨过的完整 s1 份数
    ll pos;    // 下一份内的起点
};

std::string s1, s2;
ll L1, L2;

// 从 s1 的下标 p 出发贪心匹配一整份 s2
St match_once(ll p) {
    ll j = 0;
    ll blocks = 0, pos = p;
    while (j < L2) {
        if (s1[pos] == s2[j]) j++;
        pos++;
        if (pos == L1) { // 走完一份 s1，落到下一份的开头
            pos = 0;
            blocks++;
        }
    }
    St r;
    r.blocks = blocks;
    r.pos = pos;
    return r;
}

ll bit_length(ll x) {
    ll c = 0;
    while (x) {
        c++;
        x >>= 1;
    }
    return c;
}

// 返回 s2 作为子序列最多能在 conn(s1, n1) 中出现多少次
ll max_copies(ll n1) {
    bool has[256];
    for (int i = 0; i < 256; i++) has[i] = false;
    for (ll i = 0; i < L1; i++) has[(int)(unsigned char)s1[i]] = true;
    for (ll i = 0; i < L2; i++) {
        if (!has[(int)(unsigned char)s2[i]]) return 0; // 有字符不在 s1 里，一份都放不下
    }

    std::vector<St> base(L1);
    for (ll p = 0; p < L1; p++) base[p] = match_once(p);

    ll LOG = bit_length(n1 * L1 / L2 + 1);
    if (LOG < 1) LOG = 1;
    std::vector<std::vector<St> > up(LOG);
    up[0] = base;
    for (ll k = 1; k < LOG; k++) {
        up[k].assign(L1, St());
        for (ll p = 0; p < L1; p++) {
            St a = up[k - 1][p];
            St b = up[k - 1][a.pos];
            up[k][p].blocks = a.blocks + b.blocks;
            up[k][p].pos = b.pos;
        }
    }

    ll used = 0, p = 0, copies = 0;
    for (ll k = LOG - 1; k >= 0; k--) { // 从大步到小步，能加就加
        St a = up[k][p];
        ll need = used + a.blocks + (a.pos > 0 ? 1 : 0); // 落点不在份首时当前这一份也被占用
        if (need <= n1) {
            used += a.blocks;
            p = a.pos;
            copies += 1LL << k;
        }
    }
    return copies;
}

int main() {
    std::vector<std::string> tok;
    std::string t;
    while (std::cin >> t) tok.push_back(t);
    // 输入末尾可能粘着一个 '}'，它不是字符串内容
    if (!tok.empty() && tok.back() == "}") tok.pop_back();

    for (size_t g = 0; g + 3 < tok.size(); g += 4) {
        s2 = tok[g];
        ll n2 = atoll(tok[g + 1].c_str());
        s1 = tok[g + 2];
        ll n1 = atoll(tok[g + 3].c_str());
        L1 = (ll)s1.size();
        L2 = (ll)s2.size();
        // conn(s2, n2) 重复 m 次就是 s2 重复 m * n2 次
        printf("%lld\n", max_copies(n1) / n2);
    }
    return 0;
}
