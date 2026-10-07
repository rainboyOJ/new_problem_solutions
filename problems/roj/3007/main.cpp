/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:53
 * update_at: 2026-10-06 10:55
 */
// main.cpp：从 1..n 中递归选 m 个数，按字典序输出全部组合。
#include <iostream>
using namespace std;

typedef long long ll;

ll n, m;
ll path[30]; // path[i] 表示当前方案中第 i 个选中的数

// 从 start..n 中再选 remaining 个数，当前位置是第 dep 个。
// 强制后选的数严格大于先选的数，于是行内升序、行间天然字典序。
void dfs(ll dep, ll start, ll remaining) {
    if (remaining == 0) {
        // 一个完整方案已经生成，末尾带空格输出
        for (ll i = 1; i <= m; i++) {
            cout << path[i] << ' ';
        }
        cout << '\n';
        return;
    }
    // 本层选的数 first 最大取 n - remaining + 1，否则后面凑不够剩余的个数
    for (ll first = start; first <= n - remaining + 1; first++) {
        path[dep] = first;
        dfs(dep + 1, first + 1, remaining - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    dfs(1, 1, m);

    return 0;
}
