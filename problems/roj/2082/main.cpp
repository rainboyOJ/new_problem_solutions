/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:08
 * update_at: 2026-10-06 12:08
 */
#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll MAXQ = 20000;  // 夸脱数上限
const ll MAXP = 100;    // 桶数上限

typedef bitset<MAXQ + 1> Bits;  // 第 x 位为 1 表示恰好能量出 x 夸脱

ll Q, P, m;
vector<ll> buckets;   // 去重并升序排列后的桶容积
ll chosen[MAXP + 5];  // 当前搜索到的组合，chosen[0..k-1]

// 在 bits 上并入“再倒任意整数桶 v”的效果：
// 依次左移 v、2v、4v… 再或回去，恰好补齐所有 j*v 增量（j 可按二进制拆分）。
Bits extend(Bits bits, ll v) {
    ll step = v;
    while (step <= Q) {
        bits |= (bits << step);
        step <<= 1;
    }
    return bits;
}

// 在升序 buckets[start..m-1] 中按字典序再选 rest 个桶，depth 是已选个数。
// 每个买来的桶至少倒一次，total 为已选容积之和；桶升序，total+v>Q 时后面
// 的桶更大，整条分支直接 break。
bool dfs(ll start, ll rest, ll total, ll depth, Bits bits) {
    if (rest == 0) {
        return bits.test(Q);  // 第 Q 位为 1 表示该组合能恰好量出 Q
    }
    for (ll i = start; i + rest <= m; i++) {  // 剩余桶必须够 rest 个
        ll v = buckets[i];
        if (total + v > Q) {
            break;
        }
        chosen[depth] = v;
        if (dfs(i + 1, rest - 1, total + v, depth + 1, extend(bits, v))) {
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%lld", &Q);
    scanf("%lld", &P);
    for (ll i = 1; i <= P; i++) {
        ll x;
        scanf("%lld", &x);
        buckets.push_back(x);
    }
    sort(buckets.begin(), buckets.end());
    buckets.erase(unique(buckets.begin(), buckets.end()), buckets.end());
    m = buckets.size();

    // 桶数从 1 往上枚举：更少桶必更优；同数量下 dfs 天然按升序字典序，
    // 首个成功的组合就是“桶数最少且字典序最小”的答案。
    for (ll k = 1; k <= m; k++) {
        if (dfs(0, k, 0, 0, Bits(1))) {  // Bits(1)：仅 0 夸脱可达
            printf("%lld", k);
            for (ll i = 0; i < k; i++) {
                printf(" %lld", chosen[i]);
            }
            printf("\n");
            return 0;
        }
    }
    return 0;
}
