/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:40
 * update_at: 2026-10-05 01:40
 */

#include <cstdio>

typedef long long ll;

// ===== IDA* 迭代加深搜索 埃及分数 =====
// 目标：把 a/b 拆成加数最少、其次最大分母最小、再字典序最小的单位分数和

ll ga, gb;      // 当前还差多少（最简分数）需要凑出
ll best[16];    // 目前全局最优的分母序列
ll path[16];    // 当前搜索路径上已选的分母
int depLimit;   // 本轮迭代加深允许的加数个数
bool hasBest = false; // 是否已经找到过可行解

// 计算最大公约数（辗转相除）
ll gcd_ll(ll a, ll b) {
    if (b == 0) return a;
    return gcd_ll(b, a % b);
}

// 比较两条分母序列谁更优：先比最大分母（小者优，即最小的分数更大），
// 再比整个序列的字典序（小者优）。返回 true 表示新序列比 best 更优
bool better() {
    // depLimit 相同时两条序列长度一致，最大分母就是最后一个元素
    if (path[depLimit] != best[depLimit]) return path[depLimit] < best[depLimit];
    for (int i = 1; i <= depLimit; i++) {
        if (path[i] != best[i]) return path[i] < best[i];
    }
    return false;
}

// 还剩 k 个加数要凑出 ga/gb，上一个已选分母是 last（初始为 0）
// dep 表示当前填到第几个位置
void dfs(int k, ll a, ll b, ll last, int dep) {
    // 边界：只剩最后一个加数，必须恰好 1/x = a/b，即 x = b/a
    if (k == 1) {
        if (b % a != 0) return;
        ll x = b / a;
        if (x <= last) return;      // 分母必须严格递增
        path[dep] = x;
        // 注意：最优性要等本层搜完才知道，同一层内始终保留目前最优的一条
        if (!hasBest || better()) {
            hasBest = true;
            for (int i = 1; i <= dep; i++) best[i] = path[i];
        }
        return;
    }

    // 下界：分母严格递增；且 1/x < a/b 才不会立刻超额，即 x > b/a
    ll lo = last + 1;
    if (b / a + 1 > lo) lo = b / a + 1;
    // 上界：剩下 k 项每个都 <= 1/x，所以必须有 k/x >= a/b，即 x <= k*b/a
    ll hi = k * b / a;

    for (ll x = lo; x <= hi; x++) {
        // a/b - 1/x = (a*x - b) / (b*x)，约分后进入下一层
        ll na = a * x - b;
        ll nb = b * x;
        ll g = gcd_ll(na, nb);
        path[dep] = x;
        dfs(k - 1, na / g, nb / g, x, dep + 1);
    }
}

int main() {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    ll g = gcd_ll(a, b); // 先约分，保证搜索状态里是最简分数
    a /= g;
    b /= g;

    // IDA*：加数个数从 1 开始逐层加深，第一个搜出解的深度即最少项数
    for (depLimit = 1; depLimit <= 10; depLimit++) {
        // 重新初始化全局最优记录
        hasBest = false;
        dfs(depLimit, a, b, 0, 1);
        if (hasBest) {
            // 输出最优解：按升序输出各分母（与题解 main.py 一致，只输出分母序列一行）
            for (int i = 1; i <= depLimit; i++) {
                printf("%lld%c", best[i], i == depLimit ? '\n' : ' ');
            }
            break;
        }
    }
    return 0;
}
