/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 09:58
 * update_at: 2026-11-13 09:58
 */
// main2.cpp：基于位运算迭代生成的折半搜索实现
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] %= m;
    }

    int mid = n / 2;
    int len_a = mid;
    int len_b = n - mid;

    // 位运算枚举前半段
    vector<long long> set_a(1 << len_a);
    for (int mask = 0; mask < (1 << len_a); ++mask) {
        long long sum = 0;
        for (int i = 0; i < len_a; ++i) {
            if ((mask >> i) & 1) {
                sum = (sum + a[i]) % m;
            }
        }
        set_a[mask] = sum;
    }

    // 位运算枚举后半段
    vector<long long> set_b(1 << len_b);
    for (int mask = 0; mask < (1 << len_b); ++mask) {
        long long sum = 0;
        for (int i = 0; i < len_b; ++i) {
            if ((mask >> i) & 1) {
                sum = (sum + a[mid + i]) % m;
            }
        }
        set_b[mask] = sum;
    }

    sort(set_b.begin(), set_b.end());
    set_b.erase(unique(set_b.begin(), set_b.end()), set_b.end());

    long long ans = 0;
    for (long long u : set_a) {
        auto it = lower_bound(set_b.begin(), set_b.end(), m - u);
        if (it != set_b.begin()) {
            ans = max(ans, u + *prev(it));
        }
        ans = max(ans, (u + set_b.back()) % m);
    }

    cout << ans << "\n";
    return 0;
}
