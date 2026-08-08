#include <bits/stdc++.h>
using namespace std;

int q;

long long segment_len(long long seg) {
    return 4 * seg + 1;
}

long long value_in_segment(long long seg, long long pos) {
    if (pos <= seg + 1) {
        return pos - 1;
    }
    if (pos <= 3 * seg + 1) {
        return 2 * seg + 1 - pos;
    }
    return pos - (4 * seg + 1);
}

// 朴素做法：从第 0 段开始，一段一段减掉长度，
// 直到定位到第 k 个位置属于哪一段。
long long solve_one(long long k) {
    long long seg = 0;
    while (k > segment_len(seg)) {
        k -= segment_len(seg);
        seg++;
    }
    return value_in_segment(seg, k);
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
