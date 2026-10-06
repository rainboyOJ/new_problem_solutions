/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:26
 * update_at: 2026-10-06 15:26
 */
// 雪花判重：把每片雪花 12 种写法（顺时针 6 个起点 + 逆时针 6 个起点）
// 规范化成字典序最小的六元组作为形状指纹，指纹相同当且仅当两片雪花同形状。
// 用哈希集合扫描判重，O(n)。

#include <cstdio>
#include <set>

typedef long long ll;

const int MAXN = 100005;

int n;
ll a[MAXN][6];  // a[i][j] 表示第 i 片雪花第 j 个角的长度（下标 0..5）

// 形状指纹：六元组最小表示，自定义比较直接放进 set
struct SnowKey {
    ll v[6];
};

bool operator<(const SnowKey &x, const SnowKey &y) {
    for (int i = 0; i < 6; ++i) {
        if (x.v[i] != y.v[i]) return x.v[i] < y.v[i];
    }
    return false;
}

std::set<SnowKey> seen;  // 已经出现过的形状指纹集合

// 计算第 idx 片雪花的最小表示，枚举 12 种写法取字典序最小
SnowKey make_key(int idx) {
    SnowKey best;
    bool first = true;
    // dir = 0 顺时针，dir = 1 逆时针；k 表示从第 k 个角开始读
    for (int dir = 0; dir < 2; ++dir) {
        for (int k = 0; k < 6; ++k) {
            SnowKey cur;
            for (int t = 0; t < 6; ++t) {
                int j;
                if (dir == 0)
                    j = (k + t) % 6;         // 顺时针：从 k 往后读
                else
                    j = (k - t + 6) % 6;     // 逆时针：从 k 往前读
                cur.v[t] = a[idx][j];
            }
            if (first || cur < best) {       // 取 12 种写法里字典序最小的
                best = cur;
                first = false;
            }
        }
    }
    return best;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 6; ++j) scanf("%lld", &a[i][j]);
        SnowKey key = make_key(i);
        // 指纹已经出现过，说明前面存在同形状的雪花
        if (seen.count(key)) {
            printf("Twin snowflakes found.\n");
            return 0;
        }
        seen.insert(key);
    }
    printf("No two snowflakes are alike.\n");
    return 0;
}
