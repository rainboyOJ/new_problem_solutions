/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 13:45
 * update_at: 2026-10-04 13:45
 */
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

const int MAXV = 125005; // 双平方数上界 2 * 250^2 = 125000

int n, m;
int maxv;                // 本题的双平方数上界 2*M*M
bool in_s[MAXV];         // in_s[x] = x 是否是双平方数（p^2 + q^2）
int s_list[MAXV];        // s_list[] 存所有双平方数（升序），下标从 0 开始
int cnt_s = 0;           // 双平方数个数

struct Ans {
    ll a;
    ll b;
};
std::vector<Ans> ans;    // 所有合法数对 (a, b)

// 预处理双平方数集合：枚举 0 <= p <= q <= M 标记所有 p^2 + q^2
void build_set() {
    for (int p = 0; p <= m; ++p) {
        for (int q = p; q <= m; ++q) {
            int v = p * p + q * q;
            in_s[v] = true;
        }
    }
    // 把双平方数按升序提取进列表
    for (int x = 0; x <= maxv; ++x) {
        if (in_s[x]) {
            s_list[cnt_s++] = x;
        }
    }
}

// 检查首项 a（列表下标 i）、第二项 c（列表下标 j）出发的数列是否合法
bool check(ll a, ll b) {
    // 末项前置剪枝：末项 a + (n-1)*b 是最严苛的关卡，先 O(1) 检查
    ll last = a + (ll)(n - 1) * b;
    if (!in_s[last]) return false;
    // 中间项倒序检验：从 k = n-2 向下检查，发现不符立刻停止
    for (int k = n - 2; k >= 1; --k) {
        if (!in_s[a + (ll)k * b]) return false;
    }
    return true;
}

// 按 (b, a) 升序比较
bool cmp_ans(const Ans &x, const Ans &y) {
    if (x.b != y.b) return x.b < y.b;
    return x.a < y.a;
}

int main() {
    scanf("%d %d", &n, &m);
    maxv = 2 * m * m;

    build_set();

    // 在双平方数列表里枚举前两项，公差 b = c - a 天然确定
    for (int i = 0; i < cnt_s; ++i) {
        ll a = s_list[i];
        // 公差上界：末项 a + (n-1)*b <= maxv
        ll b_limit = (maxv - a) / (n - 1);
        for (int j = i + 1; j < cnt_s; ++j) {
            ll b = (ll)s_list[j] - a; // 公差 = 第二项 - 首项，恒为正
            if (b > b_limit) break;   // 列表递增，b 超上界后面只会更大，直接 break
            if (check(a, b)) {
                Ans t;
                t.a = a;
                t.b = b;
                ans.push_back(t);
            }
        }
    }

    if (ans.empty()) {
        printf("NONE\n");
        return 0;
    }

    sort(ans.begin(), ans.end(), cmp_ans);
    for (int i = 0; i < (int)ans.size(); ++i) {
        printf("%lld %lld\n", ans[i].a, ans[i].b);
    }
    return 0;
}
