#include <bits/stdc++.h>
using namespace std;

long long T;
long long p1, p2, k;

long long gcd_value(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;

    while (T--) {
        cin >> p1 >> p2 >> k;

        // 任意一种染色方案都至少会出现长度为 1 的同色段，
        // 所以 k=1 时一定无解。
        if (k == 1) {
            cout << "No\n";
            continue;
        }

        long long g = gcd_value(p1, p2);
        long long a = p1 / g;
        long long b = p2 / g;
        if (a > b) {
            swap(a, b);
        }

        // p1 == p2 时，所有必须染色的格子都是公共点，
        // 可以任意交替染色，因此只要 k>1 就一定有解。
        if (a == 1 && b == 1) {
            cout << "Yes\n";
            continue;
        }

        // 归一化后看成：
        // - a 的倍数偏“稠密”，把它当成红色
        // - b 的倍数偏“稀疏”，把它当成蓝色
        //
        // 在两次相邻的 b 倍数之间，里面所有必须染色的点都只能是 a 的倍数，
        // 它们会形成一整段连续红色。这个连续段长度的最大值是 ceil((b-1)/a)。
        long long max_run = (a + b - 2) / a;

        if (k > max_run) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
