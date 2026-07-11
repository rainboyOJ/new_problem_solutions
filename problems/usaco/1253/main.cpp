/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:21
 * update_at: 2026-07-11 17:23
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 105;
const int MAXN = 105;

int n, m;
string input_value[MAXM];
char output_value[MAXM];
bool removed[MAXM];

bool solve_case() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> input_value[i] >> output_value[i];
        removed[i] = false;
    }

    while (true) {
        bool found = false;

        for (int bit = 0; bit < n && !found; bit++) {
            for (char val = '0'; val <= '1' && !found; val++) {
                bool has_input = false;
                bool ok = true;
                char same_output = '?';

                for (int i = 1; i <= m; i++) {
                    if (removed[i]) {
                        continue;
                    }
                    if (input_value[i][bit] != val) {
                        continue;
                    }

                    if (!has_input) {
                        has_input = true;
                        same_output = output_value[i];
                    } else if (same_output != output_value[i]) {
                        ok = false;
                    }
                }

                if (has_input && ok) {
                    found = true;
                    for (int i = 1; i <= m; i++) {
                        if (!removed[i] && input_value[i][bit] == val) {
                            removed[i] = true;
                        }
                    }
                }
            }
        }

        if (!found) {
            break;
        }
    }

    for (int i = 1; i <= m; i++) {
        if (!removed[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        if (solve_case()) {
            cout << "OK\n";
        } else {
            cout << "LIE\n";
        }
    }

    return 0;
}
