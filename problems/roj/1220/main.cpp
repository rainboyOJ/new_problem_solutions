/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:52
 * update_at: 2026-10-05 05:52
 */
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int MAXN = 25; // 单词数上限 20，留出余量

ll n;
string word[MAXN];   // word[i]：第 i 个单词（下标从 1 开始）
ll len[MAXN];        // len[i]：第 i 个单词的长度，不超过 20
ll used[MAXN];       // used[i]：第 i 个单词在龙里已出现的次数，最多 2
ll gain[MAXN][MAXN]; // gain[i][j]：词 j 接在词 i 后新增的字符数，0 表示接不上
ll cand[MAXN][MAXN]; // cand[i]：词 i 的所有可接后继，按增益降序排列
ll cand_cnt[MAXN];   // cand_cnt[i]：词 i 的可接后继个数
char head_char;      // 龙的开头字母
ll ans;              // 当前最长龙的长度

// 计算词 b 接在词 a 后新增的字符数 = |b| - 最小合法重叠，返回 0 表示接不上。
// 合法重叠要求 a 的后缀等于 b 的前缀，且重叠长度严格小于两词长度（排除整词包含）。
// 取最小重叠：接出的龙最长，接完后后续只由 b 决定，所以短重叠严格更优。
ll calc_gain(const string &a, const string &b) {
    ll la = a.size();
    ll lb = b.size();
    ll limit = min(la, lb);
    for (ll k = 1; k < limit; k++) {
        bool match = true;
        for (ll t = 0; t < k; t++) {
            if (a[la - k + t] != b[t]) {
                match = false;
                break;
            }
        }
        if (match) {
            return lb - k;
        }
    }
    return 0;
}

// 以 last 结尾、长度 cur 的龙继续往下接；slack 是剩余单词最多还能贡献的长度上界。
void dfs(ll last, ll cur, ll slack) {
    if (cur > ans) {
        ans = cur;
    }
    if (cur + slack <= ans) {
        return; // 剩余潜力追不上当前最优，整枝剪掉
    }
    for (ll t = 1; t <= cand_cnt[last]; t++) {
        ll j = cand[last][t];
        if (used[j] < 2) {
            used[j]++;
            dfs(j, cur + gain[last][j], slack - (len[j] - 1));
            used[j]--;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> word[i];
        len[i] = word[i].size();
    }
    cin >> head_char;

    // 剩余长度上界：每个单词每次接上至少被重叠吃掉 1 个字符，单次贡献 <= len-1
    ll slack0 = 0;
    for (ll i = 1; i <= n; i++) {
        slack0 += 2 * (len[i] - 1);
    }

    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            gain[i][j] = calc_gain(word[i], word[j]);
        }
    }

    // 候选后继按增益降序：先试接得长的分支，尽快抬高 ans 提高剪枝命中率
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (gain[i][j] > 0) {
                cand_cnt[i]++;
                cand[i][cand_cnt[i]] = j;
            }
        }
        for (ll x = 1; x <= cand_cnt[i]; x++) {
            for (ll y = x + 1; y <= cand_cnt[i]; y++) {
                if (gain[i][cand[i][y]] > gain[i][cand[i][x]]) {
                    ll tmp = cand[i][x];
                    cand[i][x] = cand[i][y];
                    cand[i][y] = tmp;
                }
            }
        }
    }

    ans = 0;
    // 龙头：枚举所有以开头字母打头的单词作为第一个词
    for (ll s = 1; s <= n; s++) {
        if (word[s][0] == head_char) {
            used[s] = 1;
            dfs(s, len[s], slack0 - (len[s] - 1));
            used[s] = 0;
        }
    }

    cout << ans << "\n";
    return 0;
}
