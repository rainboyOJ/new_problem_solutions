/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:55
 */
#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int left, right;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Segment> first(n), second(n);
    for (int i = 0; i < n; i++) {
        cin >> first[i].left >> first[i].right;
    }
    for (int i = 0; i < n; i++) {
        cin >> second[i].left >> second[i].right;
    }

    int i = 0, j = 0;
    int answer = 0;
    while (i < n && j < n) {
        int overlap_left = max(first[i].left, second[j].left);
        int overlap_right = min(first[i].right, second[j].right);
        if (overlap_left < overlap_right) {
            answer += overlap_right - overlap_left;
        }

        if (first[i].right < second[j].right) {
            i++;
        } else {
            j++;
        }
    }
    cout << answer << '\n';

    return 0;
}
