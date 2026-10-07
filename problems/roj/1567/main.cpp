/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:50
 * update_at: 2026-10-05 08:50
 */

// 正解：全局偏移 + 值域树状数组（名次二分求第 k 大）+ 扣薪时只扫长度为 k 的阈值区间。
// 实际工资 = 存储值 x + bias，A/S 只改 bias；
// 不变量：在职者的存储值 x >= t = min - bias（入职时 k >= min 保证，扣薪后即时清理破坏者）。

#include <cstdio>

typedef long long ll;

const int X_MIN = -100000;             // 存储值下界：k >= 0、bias <= 1e5
const int X_MAX = 200000;              // 存储值上界：k <= 1e5、bias >= -1e5
const int POS_SIZE = X_MAX - X_MIN + 2; // 树状数组下标 1..POS_SIZE-1，比值域多留 1 位

ll mn;            // 工资下界 min
ll bias = 0;      // 全局偏移：实际工资 = 存储值 x + bias，A/S 只改它
ll staff_num = 0; // 在职人数，等于树状数组总和
ll leave = 0;     // 因扣薪低于下界离开的总数（不含入职即低于下界者）
ll cnt[POS_SIZE]; // 原数组：cnt[pos] = 存储值 x = pos + X_MIN - 1 当前的人数
ll tree[POS_SIZE]; // 树状数组：按存储值名次维护人数前缀和

// 树状数组第 pos 个下标增减 delta 人
void update(int pos, ll delta) {
    for (; pos < POS_SIZE; pos += pos & (-pos))
        tree[pos] += delta;
}

// 树状数组上名次二分：返回第 rank 小者的树状数组下标（rank 从 1 开始）
// 经典 binary lifting：从高位往低位试跳，走到"前缀人数 < rank"的最右位置
int kth(ll rank) {
    int pos = 0;
    for (int step = 1 << 18; step >= 1; step >>= 1) { // 2^18 > POS_SIZE，足够跳全程
        int nxt = pos + step;
        if (nxt < POS_SIZE && tree[nxt] < rank) {
            pos = nxt;
            rank -= tree[nxt];
        }
    }
    return pos + 1; // 第 rank 小者所在下标
}

// 处理一条 S 命令：bias 降 k 后，阈值 t = mn - bias 恰好升高 k，
// 由不变量"旧在职者都 >= t - k"，只需扫描存储值区间 [t-k, t)，
// 把其中还挂着的人全部清掉，其余人一定仍合法
void do_s(ll k) {
    bias -= k;
    ll hi = mn - bias;  // 新阈值 t（存储值视角，左闭右开的右端点）
    ll lo = hi - k;     // 旧阈值，旧在职者都 >= lo
    if (lo < X_MIN)
        lo = X_MIN;
    if (hi > (ll)X_MAX + 1)
        hi = X_MAX + 1;
    for (ll x = lo; x < hi; ++x) { // 左闭右开：只扫恰好这一段
        int pos = int(x - X_MIN + 1);
        ll gone = cnt[pos];        // 该存储值上在职的人数
        if (gone > 0) {
            cnt[pos] = 0;
            staff_num -= gone;
            leave += gone;
            update(pos, -gone);    // 树状数组同步减掉这些人
        }
    }
}

int main() {
    ll n;
    scanf("%lld %lld", &n, &mn);
    for (ll t = 1; t <= n; ++t) {
        char op[4];
        ll k;
        scanf("%s %lld", op, &k);
        if (op[0] == 'I') {
            // 入职即低于下界：不建档也不计入离开总数
            if (k >= mn) {
                int pos = int(k - bias - X_MIN + 1);
                cnt[pos]++;
                staff_num++;
                update(pos, 1);
            }
        } else if (op[0] == 'A') {
            bias += k; // 全员加薪：只抬偏移，不会有人低于下界
        } else if (op[0] == 'S') {
            do_s(k);
        } else { // F k：第 k 大 = 第 staff-k+1 小的存储值
            if (k > staff_num) {
                printf("-1\n");
            } else {
                int pos = kth(staff_num - k + 1);
                ll x = pos + X_MIN - 1;        // 名次二分回存储值
                printf("%lld\n", x + bias);    // 平移回实际工资
            }
        }
    }
    printf("%lld\n", leave);
    return 0;
}
