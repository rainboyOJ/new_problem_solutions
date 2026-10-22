/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* CF912E Prime Gift */
/* 把质数交错分成两组，DFS 枚举 <= 1e18 的所有乘积；二分答案 limit，
 * 用只向左移动的右指针统计 left[i]*right[j] <= limit 的配对数。 */

#include <bits/stdc++.h>
using namespace std;

const long long LIMIT = 1000000000000000000LL; // 1e18

int n;              // 质数个数（<= 16）
long long k;        // 第 k 小
long long primes[20];
vector<long long> left_vals, right_vals; // 两组的所有乘积（升序）

// 枚举 selected 中质数的幂乘积，value 不超过 LIMIT
void dfs(vector<long long> &out, const vector<long long> &selected,
         int index, long long value) {
    if (index == (int)selected.size()) {
        out.push_back(value);
        return;
    }
    long long p = selected[index];
    while (value <= LIMIT) {
        dfs(out, selected, index + 1, value);
        if (value > LIMIT / p)
            break; // 乘下一个 p 会超过 LIMIT
        value *= p;
    }
}

// 统计乘积 <= limit 的对数
long long count_not_greater(long long limit) {
    long long count = 0;
    int j = (int)right_vals.size() - 1;
    for (long long v : left_vals) {
        while (j >= 0 && v > limit / right_vals[j])
            j--; // 用除法避免溢出：v * right > limit 等价于 v > limit / right
        if (j < 0)
            break;
        count += j + 1;
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> primes[i];
    cin >> k;

    // 交错拆分：小的质数尽量分到两边，让乘积数平衡
    vector<long long> a, b;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            a.push_back(primes[i]);
        else
            b.push_back(primes[i]);
    }
    dfs(left_vals, a, 0, 1);
    dfs(right_vals, b, 0, 1);
    sort(left_vals.begin(), left_vals.end());
    sort(right_vals.begin(), right_vals.end());

    // 二分答案：第一个 count_not_greater(mid) >= k 的 mid
    long long low = 1, high = LIMIT;
    while (low < high) {
        long long mid = (low + high) / 2;
        if (count_not_greater(mid) >= k)
            high = mid;
        else
            low = mid + 1;
    }
    cout << low << '\n';
    return 0;
}
