/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:04
 * update_at: 2026-07-11 14:06
 */
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

// 找两个已有奶牛之间最大的内部空段，返回两头奶牛的距离。
int find_largest_gap(const string &str, int &gap_start) {
    int biggest_gap = 0;
    int current_start = -1;

    for (int i = 0; i < n; i++) {
        if (str[i] == '1') {
            if (current_start != -1 && i - current_start > biggest_gap) {
                biggest_gap = i - current_start;
                gap_start = current_start;
            }
            current_start = i;
        }
    }

    return biggest_gap;
}

// 计算当前方案里最近两头奶牛的距离。
int find_smallest_gap(const string &str) {
    int smallest_gap = 1000000000;
    int last = -1;

    for (int i = 0; i < n; i++) {
        if (str[i] == '1') {
            if (last != -1 && i - last < smallest_gap) {
                smallest_gap = i - last;
            }
            last = i;
        }
    }

    return smallest_gap;
}

// 在当前最大内部空段中心放一头牛，然后返回最小距离。
int try_cow_in_largest_gap(string str) {
    int gap_start = -1;
    int largest_gap = find_largest_gap(str, gap_start);

    if (largest_gap >= 2) {
        str[gap_start + largest_gap / 2] = '1';
        return find_smallest_gap(str);
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    int answer = 0;
    string t;

    // 情况 1：两头新牛都放进同一个最大的内部空段，近似放在三等分点。
    int gap_start = -1;
    int largest_gap = find_largest_gap(s, gap_start);
    if (largest_gap >= 3) {
        t = s;
        t[gap_start + largest_gap / 3] = '1';
        t[gap_start + largest_gap * 2 / 3] = '1';
        answer = max(answer, find_smallest_gap(t));
    }

    // 情况 2：两头新牛分别放在最左端和最右端。
    if (s[0] == '0' && s[n - 1] == '0') {
        t = s;
        t[0] = '1';
        t[n - 1] = '1';
        answer = max(answer, find_smallest_gap(t));
    }

    // 情况 3：一头放最左端，另一头放当前最大内部空段中心。
    if (s[0] == '0') {
        t = s;
        t[0] = '1';
        answer = max(answer, try_cow_in_largest_gap(t));
    }

    // 情况 4：一头放最右端，另一头放当前最大内部空段中心。
    if (s[n - 1] == '0') {
        t = s;
        t[n - 1] = '1';
        answer = max(answer, try_cow_in_largest_gap(t));
    }

    // 情况 5：先在最大内部空段中心放一头，再继续把另一头放到新的最大内部空段中心。
    if (largest_gap >= 2) {
        t = s;
        t[gap_start + largest_gap / 2] = '1';
        answer = max(answer, try_cow_in_largest_gap(t));
    }

    cout << answer << '\n';

    return 0;
}
