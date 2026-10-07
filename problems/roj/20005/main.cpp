/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:17
 * update_at: 2026-10-06 02:17
 */
#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAXN = 100005;

// 每条鱼的两个参数
struct Fish {
    ll t; // 运送一条鱼需要 2*t 的时间
    ll c; // 脾气系数，开始时刻为 S 时消耗 S*c 体力
};

int n;
Fish fish[MAXN];

// 贪心比较：t_i/c_i 小的排前面，用交叉相乘避免浮点除法和除零
bool cmp_fish(const Fish &a, const Fish &b) {
    return a.t * b.c < b.t * a.c;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld %lld", &fish[i].t, &fish[i].c);

    // 按 t_i/c_i 升序排序：交换相邻两条可证逆序对必劣
    std::sort(fish + 1, fish + n + 1, cmp_fish);

    // elapsed 是当前鱼的开始时刻；第一条鱼从时刻 0 开始，体力为 0
    ll elapsed = 0;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += elapsed * fish[i].c; // 记账当前鱼的体力
        elapsed += fish[i].t * 2;   // 推进时刻：往返耗时 2*t
    }
    printf("%lld\n", ans);
    return 0;
}
