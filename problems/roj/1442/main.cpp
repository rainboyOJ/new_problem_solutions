/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:15
 * update_at: 2026-10-05 01:15
 */

// 小木棍：把 N 段碎片拼回若干根等长原木棍，求原木棍的最小可能长度。
// 做法：从大到小枚举候选长度 L（L 必须整除总长且 >= 最长碎片），
// 用"逐根拼满"的 DFS + 四类剪枝判断 L 是否可行。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 65;

int n;                       // 碎片总数
ll a[MAXN];                  // a[i]：第 i 段碎片的长度（从大到小排序）
bool used[MAXN];             // used[i]：第 i 段碎片是否已被用掉
ll total;                    // 所有碎片长度之和
ll length;                   // 当前正在尝试的原木棍长度 L

// 判断候选长度 L 能否把所有碎片拼成若干根长度为 L 的原木棍。
// idx：这一层允许使用的最小下标（保证同根棍内碎片下标递增，避免同组碎片换序重复搜索）；
// rest：手上这根还差的长度。pieces 已从大到小排序，优先放大的碎片。
bool dfs(int idx, ll rest) {
    if (rest == 0) {         // 这根拼满了，重开一根新的原木棍
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {  // 还有碎片没用完，从最小的下标开新棍
                return dfs(i, length);
            }
        }
        return true;         // 所有碎片全部用完，每根都恰好拼满，可行
    }
    ll prev = 0;             // 同一层里上一个尝试过的碎片长度，等长的只试第一次
    for (int i = idx; i <= n; i++) {
        if (used[i] || a[i] == prev || a[i] > rest) continue;
        prev = a[i];
        used[i] = true;
        if (dfs(i + 1, rest - a[i])) return true;
        used[i] = false;
        // 两条"立刻失败"的判据：
        // 1) rest == length：这根棍的第一块就失败。所有新棍此刻都是空的、完全等价，
        //    换个首块只是重复同一个局面，直接否定当前 L。
        // 2) a[i] == rest：这一块恰好填满却失败。留出的空隙只能被更小的碎片填上，
        //    而这些小碎片直接填在这里同样合法，局面不会更好，直接否定当前 L。
        if (rest == length || a[i] == rest) return false;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    total = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        total += a[i];
    }
    // 从大到小排序：大碎片能去的位置少，先放它们能更快暴露矛盾
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n / 2; i++) swap(a[i], a[n + 1 - i]);

    // 从大到小枚举候选长度：L 必须整除总长，且不小于最长碎片
    for (ll L = a[1]; L <= total; L++) {
        if (total % L != 0) continue;
        length = L;
        for (int i = 1; i <= n; i++) used[i] = false;
        if (dfs(1, L)) {     // 开第一根新棍，从最大的碎片（下标 1）开始
            printf("%lld\n", L);
            return 0;
        }
    }
    return 0;
}
