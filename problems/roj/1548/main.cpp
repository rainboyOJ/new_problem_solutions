/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:28
 * update_at: 2026-10-05 07:28
 */

// 区间加、区间求和：双树状数组维护差分序列
// 设 d[i] = a[i] - a[i-1]，则前缀和
//   S[k] = sum_{j=1..k} (k-j+1) * d[j] = (k+1) * sum(d[j]) - sum(j * d[j])
// 用 t1 维护 d[i]，t2 维护 i*d[i]，两个操作都只需 O(log n)。

#include <cstdio>

typedef long long ll;

const int MAXN = 1000005;

int n, q;
ll t1[MAXN]; // 维护差分序列 d[i] 的树状数组
ll t2[MAXN]; // 维护加权差分序列 i*d[i] 的树状数组

// 在位置 pos 累加差分增量 val，同时维护 d 与 i*d 两个树状数组
void update(int pos, ll val) {
    if (pos > n) // r+1 可能越界，直接丢弃
        return;
    ll weighted = (ll)pos * val; // 该位置上加权序列的增量
    for (int i = pos; i <= n; i += i & (-i)) {
        t1[i] += val;
        t2[i] += weighted;
    }
}

// 查询前缀 1..pos 的元素和：(pos+1) * sum(d) - sum(i*d)
ll query(int pos) {
    ll sum_d = 0, sum_id = 0;
    for (int i = pos; i > 0; i -= i & (-i)) {
        sum_d += t1[i];
        sum_id += t2[i];
    }
    return (ll)(pos + 1) * sum_d - sum_id;
}

int main() {
    scanf("%d %d", &n, &q);
    // 初始数列按差分拆开建树：a[i]-a[i-1] 加在位置 i
    ll prev = 0;
    for (int i = 1; i <= n; ++i) {
        ll cur;
        scanf("%lld", &cur);
        update(i, cur - prev);
        prev = cur;
    }
    for (int i = 1; i <= q; ++i) {
        int op;
        scanf("%d", &op);
        if (op == 1) { // 区间加：差分上只有 d[l] 与 d[r+1] 两处变化
            int l, r;
            ll x;
            scanf("%d %d %lld", &l, &r, &x);
            update(l, x);
            update(r + 1, -x);
        } else { // 区间求和：两次前缀和相减
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(r) - query(l - 1));
        }
    }
    return 0;
}
