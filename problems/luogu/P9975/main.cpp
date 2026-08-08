#include <bits/stdc++.h>
using namespace std;

int n;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;
    s = " " + s;

    // 把最终状态中的连续 1 全部提出来，后面按“每一段”分别分析。
    vector<pair<int, int>> seg;
    for (int i = 1; i <= n; ) {
        if (s[i] == '0') {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && s[j + 1] == '1') {
            j++;
        }
        seg.push_back(make_pair(i, j));
        i = j + 1;
    }

    // 题面保证最终一定至少有一头奶牛感染。
    // 这里额外做个保护，便于读者理解代码的完整性。
    if (seg.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    // 整串全是 1 时，可以只让一头奶牛最初感染。
    if ((int)seg.size() == 1 && seg[0].first == 1 && seg[0].second == n) {
        cout << 1 << '\n';
        return 0;
    }

    int max_day = (int)1e9;
    for (int i = 0; i < (int)seg.size(); i++) {
        int l = seg[i].first;
        int r = seg[i].second;
        int len = r - l + 1;

        // 反推这段能允许的最大传播天数。
        // 贴边的连续段只受一侧 0 的限制；中间段受两侧限制。
        if (l == 1 || r == n) {
            max_day = min(max_day, len - 1);
        } else {
            max_day = min(max_day, (len - 1) / 2);
        }
    }

    // 传播 max_day 晚以后，一头初始感染奶牛最终最多覆盖这么长的一段。
    int cover = 2 * max_day + 1;
    int ans = 0;

    for (int i = 0; i < (int)seg.size(); i++) {
        int len = seg[i].second - seg[i].first + 1;
        // 当前连续段长度是 len，每个起点最多覆盖 cover，
        // 所以这一段至少需要 ceil(len / cover) 个起点。
        ans += (len + cover - 1) / cover;
    }

    cout << ans << '\n';
    return 0;
}
