// gen.cpp：随机数据生成器，用于对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;

random_device rd;
mt19937 mtrnd(rd());

// 生成 [l, r] 之间的随机整数。
int rnd(int l, int r) {
    uniform_int_distribution<int> dist(l, r);
    return dist(mtrnd);
}

// 洗牌，用于产生 n 个不重复的随机数。
// 例如：[1, n] 区间的随机排列。
struct MyShuffle {
    int a[MAXN + 5];
    int idx;

    MyShuffle(int n) {
        idx = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = i;
        }
        shuffle(a + 1, a + n + 1, mtrnd);
    }

    int get() {
        return a[++idx];
    }
};

int main() {
    int n = rnd(4, 7);
    cout << n << "\n";

    return 0;
}
