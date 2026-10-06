/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:17
 * update_at: 2026-10-06 09:17
 */

// 最长前缀：布尔线性 DP，dp[i] 表示前缀 S[0:i] 能否由集合 P 拼出。
// 元素长度不超过 10，所以转移只需向前看 1..10 个字符；
// 用 set<string> 按长度存集合元素，转移时做一次子串查询。

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>

typedef long long ll;

using namespace std;

const int MAXL = 11; // 元素长度最大为 10，转移步长只取 1..10

string s;                        // 拼接后的长序列 S
bool dp[200005];                 // dp[i]：前缀长度 i 是否可分解，下标即状态
set<string> by_len[MAXL];        // by_len[L]：长度为 L 的所有元素，按长度分组
vector<ll> lens;                 // 出现过的元素长度，从小到大（已排序，方便 break）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 元素集合与 S 都可能跨多行，直接按空白切 token 读，
    // 读到单独一个 "." 就说明集合结束，其后所有 token 拼成 S
    string token;
    bool seen_dot = false;
    while (cin >> token) {
        if (!seen_dot) {
            if (token == ".") {
                seen_dot = true;
            } else {
                ll l = token.size();
                if (by_len[l].empty()) lens.push_back(l); // 记录出现过的长度
                by_len[l].insert(token);
            }
        } else {
            s += token; // S 跨多行，换行符不是 S 的一部分
        }
    }
    sort(lens.begin(), lens.end()); // lens 必须有序，转移时才能 l > i 就 break

    ll n = s.size();
    dp[0] = true; // 空串可分解
    ll ans = 0;

    for (ll i = 1; i <= n; i++) {
        // 枚举最后一段元素的长度 L，只有 dp[i-L] 为真才值得查子串
        for (ll j = 0; j < (ll)lens.size(); j++) {
            ll l = lens[j];
            if (l > i) break;          // lens 有序，后面更长，直接停
            if (!dp[i - l]) continue;
            // S 的下标从 0 开始：末段是 S[i-l .. i-1]
            if (by_len[l].count(s.substr(i - l, l))) {
                dp[i] = true;
                ans = i;               // 命中即更新答案，跳出内层
                break;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
