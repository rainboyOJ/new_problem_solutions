/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 23:40
 * update_at: 2026-10-06 23:50
 */
// 这是 STL 写法：用 vector<ll> 装下全部数据，再用 nth_element 直接把第 k 小放到下标 k。
// 题面说“请尽量不要使用 nth_element”，那是希望读者手写分治选择算法；
// 这份写法保留下来，书里也用它来和手写分治对拍，互相核对答案。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> numbers; // 全部 n 个数；nth_element 需要随机访问迭代器，所以先把数据读全

int main() {
    ll n, k;
    // 数据量最大接近 5e6，用 scanf 快速读入
    scanf("%lld %lld", &n, &k);

    numbers.resize(n);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &numbers[i]);
    }

    // 题面里最小的数是第 0 小，所以第 k 小正好落在下标 k 上。
    // nth_element 只保证 numbers[k] 这个位置就位，两侧各自有序并不保证。
    nth_element(numbers.begin(), numbers.begin() + k, numbers.end());

    printf("%lld\n", numbers[k]);

    return 0;
}
