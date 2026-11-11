#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    if (!(cin >> a >> b)) return 0;

    // 从大到小全排列，找到第一个 <= b 的数
    sort(a.begin(), a.end(), greater<char>());

    if (a.length() < b.length()) {
        cout << a << "\n";
        return 0;
    }

    do {
        if (a <= b) {
            cout << a << "\n";
            return 0;
        }
    } while (prev_permutation(a.begin(), a.end()));

    return 0;
}
