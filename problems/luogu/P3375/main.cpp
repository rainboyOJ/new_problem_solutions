#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

string text_s, pat_s;
int nxt[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> text_s >> pat_s;

    int n = (int) text_s.size();
    int m = (int) pat_s.size();

    // 计算模式串的 next 数组。
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && pat_s[i] != pat_s[j]) {
            j = nxt[j - 1];
        }
        if (pat_s[i] == pat_s[j]) {
            j++;
        }
        nxt[i] = j;
    }

    // 在文本串中匹配模式串。
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && text_s[i] != pat_s[j]) {
            j = nxt[j - 1];
        }
        if (text_s[i] == pat_s[j]) {
            j++;
        }
        if (j == m) {
            cout << i - m + 2 << '\n';
            j = nxt[j - 1];
        }
    }

    for (int i = 0; i < m; i++) {
        cout << nxt[i] << (i + 1 == m ? '\n' : ' ');
    }

    return 0;
}
