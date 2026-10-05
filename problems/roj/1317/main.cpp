/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:17
 * update_at: 2026-10-05 09:17
 */

// 组合的输出：从 1..n 中按字典序输出所有 r 元组合（递归实现）。

#include <cstdio>

typedef long long ll;

const int MAXR = 25;

ll n, r;
int choose[MAXR]; // choose[i] 表示组合中第 i 个数（严格递增）

// 这一层在选组合的第 dep 个数：从上一个数+1 枚举到 n，保证严格递增
// 递增性天然保证不重不漏，且首元从小到大枚举即得字典序
void dfs(ll dep, ll last) {
    if (dep > r) { // r 个数已选满，输出当前组合
        for (ll i = 1; i <= r; i++) {
            printf("  %d", choose[i]); // 固定两个空格 + 十进制：两位数自然占 3 列
        }
        printf("\n");
        return;
    }
    // 剪枝：还要取 r-dep+1 个数，最后一个数最大到 n-(r-dep+1)+1
    for (ll v = last + 1; v <= n - (r - dep + 1) + 1; v++) {
        choose[dep] = v;
        dfs(dep + 1, v);
    }
}

int main() {
    scanf("%lld %lld", &n, &r);
    dfs(1, 0); // 从「上一个数是 0」开始，即第一个数从 1 枚举
    return 0;
}
