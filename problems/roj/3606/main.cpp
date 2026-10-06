/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:06
 * update_at: 2026-10-06 15:06
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll NEG = -(1LL << 62); // 足够小的哨兵

ll n, p;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p;

    ll best = NEG;      // 所有分数的最大值（带符号）
    ll end_here = 0;    // 以当前位置结尾的最大子段和
    ll trait = NEG;     // 特征值：前缀 [1..i] 的最大子段和
    ll g = NEG;         // 已处理的人中 score_j + trait_j 的最大值

    for (ll i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        end_here = max(end_here + a, a);
        trait = max(trait, end_here); // 特征值不要求子段以 i 结尾

        ll score = trait;
        if (i > 0) score = g; // 第 1 个人特征值，其余取前面 score+trait 的最大值
        best = max(best, score);
        g = max(g, score + trait);
    }

    if (best >= 0)
        cout << (best % p) << "\n";
    else
        cout << -(abs(best) % p) << "\n";

    return 0;
}
