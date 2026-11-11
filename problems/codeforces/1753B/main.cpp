#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 500005;
int cnt[MAXN];

int main() {
    // 优化输入输出流
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    // 阶乘进制进位模拟：从 1! 一路进位到 x!
    for (int i = 1; i < x; i++) {
        // 若当前有零散的 i! 无法打包进位成 (i+1)!，则必不能被 x! 整除
        if (cnt[i] % (i + 1) != 0) {
            cout << "No\n";
            return 0;
        }
        // (i+1) 个 i! 进位为 1 个 (i+1)!
        cnt[i + 1] += cnt[i] / (i + 1);
    }

    // 顺利进位至 x!，低阶零散项全部消解
    cout << "Yes\n";
    return 0;
}
