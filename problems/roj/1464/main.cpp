/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:18
 * update_at: 2026-10-06 00:18
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 1e6 + 5;
const int HASH = 2097151; // 哈希表长度取 2^21 - 1，方便取模

// 由于雪花编号 x <= 1e9 开不下数组，用链地址法哈希表记录每个形状最近出现的位置
int head[HASH + 1]; // head[h] 表示哈希值为 h 的链表头，0 表示空（下标从 1 开始）
int nxt[MAXN];      // nxt[i] 表示哈希链表中第 i 条记录的下一条
ll val[MAXN];       // val[i] 表示第 i 条记录保存的雪花形状
ll pos_[MAXN];      // pos_[i] 表示形状 val[i] 最近一次出现的下标
ll a[MAXN];         // a[i] 表示第 i 个时刻落下的雪花形状
int cnt = 0;        // 已经用掉的记录条数

// 返回形状 x 在当前窗口内最近一次出现的位置，没出现过返回 0
ll find_last(ll x) {
    int h = (int)(x % HASH);
    for (int e = head[h]; e; e = nxt[e]) {
        if (val[e] == x)
            return pos_[e];
    }
    return 0;
}

// 把形状 x 最近出现的位置更新为 p
void update(ll x, ll p) {
    int h = (int)(x % HASH);
    for (int e = head[h]; e; e = nxt[e]) {
        if (val[e] == x) {
            pos_[e] = p;
            return;
        }
    }
    // 该形状第一次出现，新建一条记录挂在链表头上
    cnt++;
    val[cnt] = x;
    pos_[cnt] = p;
    nxt[cnt] = head[h];
    head[h] = cnt;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);

    int left = 1;   // 当前无重复窗口的左端点，单调不降
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll p = find_last(a[i]);
        // 该形状在窗口内部出现过，左端点必须跳到上次出现位置的下一位
        if (p >= left)
            left = (int)p + 1;
        update(a[i], i);
        if (i - left + 1 > ans)
            ans = i - left + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
