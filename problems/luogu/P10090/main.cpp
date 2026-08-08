#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int T;
i64 n, a, b;

i64 solve_one() {
    // 点的横坐标有 0..a，一共 a+1 个取值；
    // 纵坐标有 0..b，一共 b+1 个取值。
    i64 cnt_x = a + 1;
    i64 cnt_y = b + 1;

    i64 block_x = cnt_x / n;
    i64 block_y = cnt_y / n;
    i64 rem_x = cnt_x % n;
    i64 rem_y = cnt_y % n;

    // 一个 n * n 的完整块里：
    // 每个 x mod n 都唯一对应一个合法的 y mod n，
    // 所以恰好有 n 个点满足 x + y ≡ 0 (mod n)。
    i64 ans = n * block_x * block_y;

    // 完整横块 + 右侧残列。
    // 对于每一行完整横块，x 的每个余数都会出现一次，
    // 所以右侧 rem_y 列里，每列都能唯一配出一个合法 x。
    ans += block_x * rem_y;

    // 下方残行 + 完整竖块，同理。
    ans += block_y * rem_x;

    // 最右下角 rem_x * rem_y 的残块需要单独统计。
    // 这里的余数范围分别是 [0, rem_x-1]、[0, rem_y-1]。
    // 想要 x + y ≡ 0 (mod n)，由于 0 <= x+y <= 2n-2，
    // 只可能是：
    // 1. x + y = 0，对应点 (0,0)
    // 2. x + y = n
    //
    // (0,0) 也先算进去，最后统一减掉即可。
    i64 extra = 0;
    if (rem_x > 0 && rem_y > 0) {
        // 统计满足 x+y=n 的对数。
        // x 的范围是 [0, rem_x-1]，y 的范围是 [0, rem_y-1]。
        // 可行条件是：
        // n-(rem_y-1) <= x <= rem_x-1
        // 所以对数是 max(0, rem_x + rem_y - n - 1)。
        extra = max(0LL, rem_x + rem_y - n - 1);

        // 再加上 (0,0) 这一对。
        extra += 1;
    }
    ans += extra;

    // 题目要求 x+y 不为 0，所以删掉唯一的点 (0,0)。
    ans -= 1;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> a >> b;
        cout << solve_one() << '\n';
    }

    return 0;
}
