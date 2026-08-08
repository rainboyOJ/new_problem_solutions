#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
int a[MAXN];

vector<pair<int, int> > blocks;

bool check(int need_len) {
    multiset<int> last_lengths; // 上一个值结尾的所有链长度

    for (int idx = 0; idx < (int)blocks.size(); idx++) {
        int value = blocks[idx].first;
        int cnt = blocks[idx].second;

        if (idx == 0 || value != blocks[idx - 1].first + 1) {
            // 出现断档，之前所有链必须已经满足长度要求。
            for (multiset<int>::iterator it = last_lengths.begin(); it != last_lengths.end(); ++it) {
                if (*it < need_len) return false;
            }
            last_lengths.clear();
        }

        if ((int)last_lengths.size() > cnt) {
            // 当前值数量不够接上所有旧链时，
            // 应该优先让“更长的链”在上一值结束，
            // 把更短的链留给当前值继续延长。
            int drop = (int)last_lengths.size() - cnt;
            for (int i = 0; i < drop; i++) {
                multiset<int>::iterator it = prev(last_lengths.end());
                if (*it < need_len) return false;
                last_lengths.erase(it);
            }
        }

        multiset<int> current_lengths;

        // 先延长还活着的旧链。为了尽量让短链先长大，优先接最短的。
        while (!last_lengths.empty()) {
            multiset<int>::iterator it = last_lengths.begin();
            current_lengths.insert(*it + 1);
            last_lengths.erase(it);
            cnt--;
        }

        // 剩余的同值人数只能新开长度为 1 的链。
        while (cnt--) {
            current_lengths.insert(1);
        }

        last_lengths.swap(current_lengths);
    }

    for (multiset<int>::iterator it = last_lengths.begin(); it != last_lengths.end(); ++it) {
        if (*it < need_len) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; ) {
        int j = i;
        while (j <= n && a[j] == a[i]) j++;
        blocks.push_back(make_pair(a[i], j - i));
        i = j;
    }

    int left = 1, right = n;
    while (left < right) {
        int mid = (left + right + 1) >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left << '\n';
    return 0;
}
