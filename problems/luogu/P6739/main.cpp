#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000005;

int n;
char s[MAXN];

// 检查 longer 这段串能否删除恰好一个字符后变成 shorter。
bool can_delete_one(int longer_l, int longer_r, int shorter_l, int shorter_r) {
    int i = longer_l;
    int j = shorter_l;
    bool used = false;

    while (i <= longer_r && j <= shorter_r) {
        if (s[i] == s[j]) {
            i++;
            j++;
        }
        else {
            if (used) {
                return false;
            }
            used = true;
            i++;
        }
    }

    // 如果 shorter 已经匹配完，而 longer 还剩一个字符，也可以把这个字符删掉。
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> (s + 1);

    if (n % 2 == 0) {
        cout << "NOT POSSIBLE\n";
        return 0;
    }

    int len = (n - 1) / 2;

    // 情况 1：多出来的字符在前半段，答案应该是后半段。
    bool ok_right = can_delete_one(1, len + 1, len + 2, n);

    // 情况 2：多出来的字符在后半段，答案应该是前半段。
    bool ok_left = can_delete_one(len + 1, n, 1, len);

    if (!ok_right && !ok_left) {
        cout << "NOT POSSIBLE\n";
        return 0;
    }

    if (ok_right && ok_left) {
        bool same = true;
        for (int i = 1; i <= len; i++) {
            if (s[i] != s[len + 1 + i]) {
                same = false;
                break;
            }
        }
        if (!same) {
            cout << "NOT UNIQUE\n";
            return 0;
        }
    }

    if (ok_left) {
        for (int i = 1; i <= len; i++) {
            cout << s[i];
        }
        cout << '\n';
    }
    else {
        for (int i = len + 2; i <= n; i++) {
            cout << s[i];
        }
        cout << '\n';
    }

    return 0;
}
