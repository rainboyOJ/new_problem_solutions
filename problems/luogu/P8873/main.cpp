#include <bits/stdc++.h>
using namespace std;

int q;

// 前 i 段（从第 0 段到第 i 段）的总长度。
// 第 i 段长度是 4*i+1，所以总和为 (i+1)*(2*i+1)。
__int128 prefix_len(long long i) {
    return (__int128)(i + 1) * (2LL * i + 1);
}

// 已知位置落在第 seg 段内，且段内位置是 pos（从 1 开始），求该值。
long long value_in_segment(long long seg, long long pos) {
    if (pos <= seg + 1) {
        return pos - 1;
    }
    if (pos <= 3 * seg + 1) {
        return 2 * seg + 1 - pos;
    }
    return pos - (4 * seg + 1);
}

long long solve_one(long long k) {
    long long l = 0;
    long long r = 2000000000LL;

    // 二分找到最小的 seg，使得前 seg 段总长度 >= k。
    while (l < r) {
        long long mid = (l + r) >> 1;
        if (prefix_len(mid) >= (__int128)k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    long long seg = l;
    __int128 prev = 0;
    if (seg > 0) {
        prev = prefix_len(seg - 1);
    }

    long long pos = (long long)((__int128)k - prev);
    return value_in_segment(seg, pos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> q;
    while (q--) {
        long long k;
        cin >> k;
        cout << solve_one(k) << '\n';
    }

    return 0;
}
