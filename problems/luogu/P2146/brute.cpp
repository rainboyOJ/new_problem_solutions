#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
int parent_arr[MAXN];
vector<int> children[MAXN];
int installed[MAXN];

int install_package(int x) {
    int changed = 0;
    while (x != -1) {
        if (!installed[x]) {
            installed[x] = 1;
            changed++;
        }
        x = parent_arr[x];
    }
    return changed;
}

int uninstall_package(int x) {
    int changed = 0;
    stack<int> st;
    st.push(x);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (installed[u]) {
            installed[u] = 0;
            changed++;
        }

        for (int v : children[u]) {
            st.push(v);
        }
    }

    return changed;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个朴素模拟：
    // install 就沿父亲链往上装，uninstall 就把整棵子树暴力扫掉。
    cin >> n;
    parent_arr[0] = -1;
    for (int i = 1; i < n; i++) {
        cin >> parent_arr[i];
        children[parent_arr[i]].push_back(i);
    }

    int q;
    cin >> q;
    while (q--) {
        string op;
        int x;
        cin >> op >> x;
        if (op[0] == 'i') {
            cout << install_package(x) << '\n';
        } else {
            cout << uninstall_package(x) << '\n';
        }
    }

    return 0;
}
