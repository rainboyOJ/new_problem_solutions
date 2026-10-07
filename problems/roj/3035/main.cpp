/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:16
 * update_at: 2026-10-06 15:16
 */
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;

// 蚯蚓（NOIP2016 / roj 3035）：三队列 + 全局偏移量，O((n+m)log(n+m))
// 队列存"历史值"，真实长度 = 存储值 + 全局偏移 delta，
// 这样"其余蚯蚓集体加 q"就折叠成一次 delta += q。

const int MAXN = 100005;   // 初始蚯蚓数上限 n <= 1e5
const int MAXM = 7000005;  // m <= 7e6，q1/q2 每秒最多各进 1 只

// 三个降序队列（证明见题解）：队首即每秒全局最长的三个候选
int q0[MAXN];  // 从未被切过的蚯蚓，初始从大到小排序
int q1[MAXM];  // 历次切出的小段 floor(p*x)，入队次序保证存储值不增
int q2[MAXM];  // 历次切出的大段 x - floor(p*x)，同理不增
int head0 = 0, tail0 = 0;  // q0 队首/队尾下标
int head1 = 0, tail1 = 0;
int head2 = 0, tail2 = 0;

// 快速输出：t=1 时两行合计可达约 1.4e7 个数，printf 太慢
char obuf[1 << 16];
int opos = 0;
void flush_out() { fwrite(obuf, 1, opos, stdout); opos = 0; }
void write_char(char c) {
    if (opos == (int)sizeof(obuf)) flush_out();
    obuf[opos++] = c;
}
void write_ll(ll x) {  // 本题长度非负，按非负处理
    if (opos > (int)sizeof(obuf) - 16) flush_out();
    char tmp[24];
    int len = 0;
    do { tmp[len++] = '0' + x % 10; x /= 10; } while (x);
    while (len) obuf[opos++] = tmp[--len];
}

int main() {
    ll n, m, q, u, v, t;
    scanf("%lld %lld %lld %lld %lld %lld", &n, &m, &q, &u, &v, &t);
    for (int i = 0; i < n; i++) scanf("%d", &q0[i]);
    sort(q0, q0 + n, greater<int>());  // q0 保持降序
    tail0 = n;

    ll delta = 0;  // 全局偏移量：真实长度 = 存储值 + delta
    bool first = true;  // 第一行控制数字间空格
    for (ll second = 1; second <= m; second++) {
        // 三个队首候选，空队列用哨兵 INT_MIN，保证选到非空队列
        int c0 = (head0 < tail0) ? q0[head0] : INT_MIN;
        int c1 = (head1 < tail1) ? q1[head1] : INT_MIN;
        int c2 = (head2 < tail2) ? q2[head2] : INT_MIN;
        ll x;  // 本秒被切蚯蚓的真实长度
        if (c0 >= c1 && c0 >= c2) { x = c0 + delta; head0++; }
        else if (c1 >= c2)        { x = c1 + delta; head1++; }
        else                      { x = c2 + delta; head2++; }

        ll left = x * u / v;   // 小段 floor(p*x)，x*u 最大约 1.5e18，用 ll
        ll right = x - left;   // 大段
        // 新切的两只不参与"本秒"加 q：历史值先倒扣 q，随后 delta 自增
        q1[tail1++] = left - delta - q;
        q2[tail2++] = right - delta - q;
        delta += q;

        if (second % t == 0) {  // 第一行：第 t, 2t, ... 秒被切前的长度
            if (!first) write_char(' ');
            first = false;
            write_ll(x);
        }
    }
    write_char('\n');  // 没有数也要输出空行

    // 第二行：m 秒后共 n+m 只，三个降序队列归并，输出排名 t, 2t, ... 的真实长度
    first = true;
    int i0 = head0, i1 = head1, i2 = head2;
    for (ll rank = 1; rank <= n + m; rank++) {
        int c0 = (i0 < tail0) ? q0[i0] : INT_MIN;
        int c1 = (i1 < tail1) ? q1[i1] : INT_MIN;
        int c2 = (i2 < tail2) ? q2[i2] : INT_MIN;
        ll val;
        if (c0 >= c1 && c0 >= c2) { val = c0 + delta; i0++; }
        else if (c1 >= c2)        { val = c1 + delta; i1++; }
        else                      { val = c2 + delta; i2++; }
        if (rank % t == 0) {
            if (!first) write_char(' ');
            first = false;
            write_ll(val);
        }
    }
    write_char('\n');
    flush_out();
    return 0;
}
