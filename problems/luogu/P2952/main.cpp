#include <bits/stdc++.h>
using namespace std;

int s;
int cur = 1;
char op, dir;
int k;
deque<int> q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    for (int i = 1; i <= s; i++) {
        cin >> op >> dir;

        if (op == 'A') {
            if (dir == 'L') {
                q.push_front(cur);
            } else {
                q.push_back(cur);
            }
            cur++;
        } else {
            cin >> k;
            while (k--) {
                if (dir == 'L') {
                    q.pop_front();
                } else {
                    q.pop_back();
                }
            }
        }
    }

    for (int x : q) {
        cout << x << '\n';
    }

    return 0;
}
