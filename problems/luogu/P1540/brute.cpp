#include <bits/stdc++.h>
using namespace std;

int m, n;
int x;
int ans;
vector<int> memory_words;

bool exists_in_memory(int word) {
    for (int v : memory_words) {
        if (v == word) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    for (int i = 1; i <= n; i++) {
        cin >> x;

        if (exists_in_memory(x)) {
            continue;
        }

        ans++;
        if ((int) memory_words.size() == m) {
            memory_words.erase(memory_words.begin());
        }
        memory_words.push_back(x);
    }

    cout << ans << '\n';
    return 0;
}
