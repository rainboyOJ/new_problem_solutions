#include <bits/stdc++.h>
using namespace std;

const int mod = 10000;

string s;
vector<long long> nums;
vector<char> ops;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    long long num = 0;
    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else {
            nums.push_back(num);
            ops.push_back(c);
            num = 0;
        }
    }
    nums.push_back(num);

    vector<long long> nums2;
    vector<char> ops2;
    nums2.push_back(nums[0] % mod);

    for (int i = 0; i < (int) ops.size(); i++) {
        if (ops[i] == '*') {
            nums2.back() = nums2.back() * (nums[i + 1] % mod) % mod;
        } else {
            ops2.push_back('+');
            nums2.push_back(nums[i + 1] % mod);
        }
    }

    long long ans = 0;
    for (long long x : nums2) {
        ans = (ans + x) % mod;
    }

    cout << ans % mod << '\n';
    return 0;
}
