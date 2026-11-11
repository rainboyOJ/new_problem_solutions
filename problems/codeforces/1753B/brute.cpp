#include <iostream>
#include <vector>

using namespace std;

// 暴力计算真实数值（适用于小规模 x <= 15 的对拍验证）
long long fact(int k) {
    long long res = 1;
    for (int i = 1; i <= k; i++) res *= i;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    long long sum_facts = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        sum_facts += fact(a);
    }

    long long target = fact(x);
    if (sum_facts % target == 0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
