#include <bits/stdc++.h>
using namespace std;

int s;
int cur = 1;
char op, dir;
int k;
vector<int> line_cows;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    for (int i = 1; i <= s; i++) {
        cin >> op >> dir;

        if (op == 'A') {
            if (dir == 'L') {
                line_cows.insert(line_cows.begin(), cur);
            } else {
                line_cows.push_back(cur);
            }
            cur++;
        } else {
            cin >> k;
            while (k--) {
                if (dir == 'L') {
                    line_cows.erase(line_cows.begin());
                } else {
                    line_cows.pop_back();
                }
            }
        }
    }

    for (int x : line_cows) {
        cout << x << '\n';
    }

    return 0;
}
