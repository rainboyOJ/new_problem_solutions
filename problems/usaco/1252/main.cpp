/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:15
 * update_at: 2026-07-11 17:16
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, k;
char cow[MAXN];
char answer_plan[MAXN];
int patch_count;

void place_patch(char c, int pos, int &last_patch) {
    int patch_pos;

    if (pos + k <= n) {
        patch_pos = pos + k;
    } else {
        patch_pos = pos;
        if (answer_plan[patch_pos] != '.') {
            patch_pos--;
        }
    }

    answer_plan[patch_pos] = c;
    last_patch = patch_pos;
    patch_count++;
}

void solve_case() {
    string s;
    cin >> n >> k;
    cin >> s;

    for (int i = 1; i <= n; i++) {
        cow[i] = s[i - 1];
        answer_plan[i] = '.';
    }

    int last_g_patch = -k;
    int last_h_patch = -k;
    patch_count = 0;

    for (int i = 1; i <= n; i++) {
        if (cow[i] == 'G' && i - last_g_patch > k) {
            place_patch('G', i, last_g_patch);
        }
        if (cow[i] == 'H' && i - last_h_patch > k) {
            place_patch('H', i, last_h_patch);
        }
    }

    cout << patch_count << '\n';
    for (int i = 1; i <= n; i++) {
        cout << answer_plan[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
