#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string a, b;
int cnt[10];
string ans;

// pos: 当前正在决策的数位索引
// is_less: 前缀是否已经严格小于 b 对应的数位
bool dfs(int pos, bool is_less) {
    if (pos == (int)a.length()) {
        return true;
    }

    // 若已经严格小于，剩余数位直接降序全选最大的可用数字
    if (is_less) {
        for (int d = 9; d >= 0; --d) {
            while (cnt[d] > 0) {
                ans[pos++] = '0' + d;
                cnt[d]--;
            }
        }
        return true;
    }

    int limit = b[pos] - '0';
    // 前面完全相等，当前位只能在 <= limit 中由大到小贪心尝试
    for (int d = limit; d >= 0; --d) {
        if (cnt[d] > 0) {
            cnt[d]--;
            ans[pos] = '0' + d;
            if (dfs(pos + 1, d < limit)) {
                return true;
            }
            cnt[d]++; // 回溯
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> a >> b)) return 0;

    for (char c : a) {
        cnt[c - '0']++;
    }

    // 1. 若 A 的长度小于 B 的长度，直接输出 A 的降序全排列
    if (a.length() < b.length()) {
        for (int d = 9; d >= 0; --d) {
            while (cnt[d]-- > 0) {
                cout << d;
            }
        }
        cout << "\n";
        return 0;
    }

    // 2. 两者一样长，启动带回溯的数位贪心 DFS
    ans.resize(a.length());
    dfs(0, false);

    cout << ans << "\n";
    return 0;
}
