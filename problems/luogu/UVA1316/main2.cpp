/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 21:05
 * update_at: 2026-10-27 21:05
 */
// main2.cpp：贪心 + 并查集。按利润从大到小处理，每个商品都抢占"不晚于自己截止日期的最晚空位"。
// 并查集 fa[i] 表示「第 i 天或它之前最晚的可用日期」，占用一天就把 fa[r] 指向 r-1。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 10000 + 5;

// 一个商品：利润 p，截止日期 d
struct Item {
    int p;
    int d;
};

int n;
Item item[MAXN];
int fa[MAXN]; // fa[i]：第 i 天或它之前最晚的可用日期

// 按利润从大到小排序
bool compare_by_profit(const Item &a, const Item &b) {
    return a.p > b.p;
}

// 并查集查找，带路径压缩。返回最近的可用的那一天，0 表示从 1 到 x 全被占满
int find_root(int x) {
    if (fa[x] == x) return x;
    fa[x] = find_root(fa[x]);
    return fa[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 本题是多组输入，读到 EOF 为止
    while (cin >> n) {
        int max_day = 0; // 本组数据出现的最大截止日期，用来决定并查集要初始化到哪一天
        for (int i = 0; i < n; i++) {
            cin >> item[i].p >> item[i].d;
            max_day = max(max_day, item[i].d);
        }

        sort(item, item + n, compare_by_profit);

        // 初始时每一天都可用，fa[i] = i 表示第 i 天就是它自己
        for (int i = 0; i <= max_day; i++) fa[i] = i;

        ll answer = 0;
        for (int i = 0; i < n; i++) {
            // 为这个商品找不晚于 item[i].d 的最晚空位
            int day = find_root(item[i].d);
            if (day > 0) {
                answer += item[i].p;
                fa[day] = find_root(day - 1); // 占用第 day 天，之后再来就往前找
            }
        }
        cout << answer << '\n';
    }

    return 0;
}
