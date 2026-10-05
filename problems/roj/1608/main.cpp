/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:30
 * update_at: 2026-10-05 12:30
 */
// main.cpp：任务安排 3，把启动费改记为「批开始时对之后所有任务的费用系数付费」，
// 消掉完成时刻里的批数，DP 化为直线族 y = -sum_c[j]*x + f[j] 在 x = sum_t[i] + S 处的最小值查询。
// 斜率 -sum_c[j] 单调不增，维护下凸壳；查询点 x 不单调（T_i 可负），故在交点上二分，总复杂度 O(N log N)。
#include <cstdio>

typedef long long ll;
typedef __int128 wide; // 只用于交点比较时的交叉相乘，乘积可达 1e24，超出 ll

const int MAXN = 300005;

ll n;            // 任务个数
ll setup;        // 每批的启动时间 S
ll sum_t[MAXN];  // sum_t[i]：前 i 个任务的用时前缀和
ll sum_c[MAXN];  // sum_c[i]：前 i 个任务的费用系数前缀和，同时充当直线斜率

// 下凸壳：直线 y = hull_m[k]*x + hull_b[k]，斜率严格递减
ll hull_m[MAXN];   // hull_m[k] = -sum_c[j]，随 j 单调不增
ll hull_b[MAXN];   // hull_b[k] = f[j]（记账口径的 DP 值）
ll cut_num[MAXN];  // cut_num[k]/cut_den[k]：第 k 与第 k+1 条直线的交点横坐标
ll cut_den[MAXN];  // 交点分母恒为正（相邻两条直线前一条斜率更大）
int hull_size = 0; // 凸壳上的直线条数

// 快速读入一个整数：跳过所有非数字、非负号的字符，
// 这样即使分隔符里混有损坏的控制字符也能正确读完（本地数据出现过这种情况）。
ll read_int() {
    int ch = getchar();
    while (ch != EOF && ch != '-' && (ch < '0' || ch > '9')) {
        ch = getchar();
    }
    ll sign = 1;
    if (ch == '-') {
        sign = -1;
        ch = getchar();
    }
    ll value = 0;
    while (ch >= '0' && ch <= '9') {
        value = value * 10 + (ch - '0');
        ch = getchar();
    }
    return sign * value;
}

// 往凸壳里插入直线 y = m*x + b，斜率保持不增，删掉以后取不到最小值的直线
void hull_push(ll m, ll b) {
    // 同斜率只留截距小的；新直线处处不更优就直接丢弃
    while (hull_size > 0 && m == hull_m[hull_size - 1]) {
        if (b >= hull_b[hull_size - 1]) {
            return;
        }
        hull_size--;
    }
    // 相邻交点必须严格递增，否则夹在中间的那条直线在任何 x 处都轮不到
    while (hull_size >= 2) {
        ll n1 = hull_b[hull_size - 1] - hull_b[hull_size - 2];
        ll d1 = hull_m[hull_size - 2] - hull_m[hull_size - 1];
        ll n2 = b - hull_b[hull_size - 1];
        ll d2 = hull_m[hull_size - 1] - m;
        if ((wide)n1 * d2 < (wide)n2 * d1) { // 分数比较：交点左移说明中间直线是废的
            break;
        }
        hull_size--;
    }
    if (hull_size > 0) {
        cut_num[hull_size - 1] = b - hull_b[hull_size - 1];
        cut_den[hull_size - 1] = hull_m[hull_size - 1] - m;
    }
    hull_m[hull_size] = m;
    hull_b[hull_size] = b;
    hull_size++;
}

// 在下凸壳上二分：找到第一条查询点尚未越过其左端交点的直线，返回它在 x 处的值
ll hull_min(ll x) {
    int left = 0;
    int right = hull_size - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if ((wide)x * cut_den[mid] > cut_num[mid]) { // x 已越过交点，右侧直线更优
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return hull_m[left] * x + hull_b[left];
}

int main() {
    n = read_int();
    setup = read_int();
    for (int i = 1; i <= n; i++) {
        ll t = read_int();
        ll c = read_int();
        sum_t[i] = sum_t[i - 1] + t;
        sum_c[i] = sum_c[i - 1] + c;
    }
    ll tail_c = sum_c[n]; // 记账口径里所有批共用的总费用系数

    hull_push(0, 0); // 预置 j = 0 的直线：斜率 -sum_c[0] = 0，截距 f[0] = 0
    ll f = 0;
    for (int i = 1; i <= n; i++) {
        ll x = sum_t[i] + setup; // 查询点
        f = sum_t[i] * sum_c[i] + setup * tail_c + hull_min(x);
        hull_push(-sum_c[i], f); // 先查询后插入，保证转移来源 j < i
    }
    printf("%lld\n", f);
    return 0;
}
