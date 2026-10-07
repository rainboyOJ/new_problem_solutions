/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:35
 * update_at: 2026-10-06 00:35
 */
#include <cstdio>

typedef long long ll;

const int MAXX = 32000;          // 横坐标最大值
const int MAXN = 15000;          // 星星数量上限
int tree[MAXX + 2];              // 树状数组，维护各横坐标出现次数
ll level_cnt[MAXN + 1];          // level_cnt[k] = 等级为 k 的星星数量

// 在位置 pos 上加 1。
void add(int pos) {
    while (pos <= MAXX + 1) {
        tree[pos]++;
        pos += pos & -pos;
    }
}

// 查询前缀和 [1, pos]，即横坐标不超过 pos-1 的已读入星星数。
int query(int pos) {
    int res = 0;
    while (pos > 0) {
        res += tree[pos];
        pos -= pos & -pos;
    }
    return res;
}

int main() {
    ll n;
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        // 输入已按 y 增序给出，故此前读入的点 y 均不超过当前点，
        // 只需统计横坐标不超过 x 的点数即为等级。
        int pos = x + 1;         // 树状数组下标从 1 开始
        int level = query(pos);
        level_cnt[level]++;
        add(pos);
    }
    for (ll k = 0; k <= n - 1; k++) {
        printf("%lld\n", level_cnt[k]);
    }
    return 0;
}
