#include <bits/stdc++.h>
using namespace std;

int total_s, total_t, n, m;
vector<string> s_list, t_list;

bool is_rotation(const string &a, const string &b) {
    if (a.size() != b.size()) {
        return false;
    }
    string t = a + a;
    return t.find(b) != string::npos;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> total_s >> total_t >> n >> m;
    s_list.resize(total_s);
    t_list.resize(total_t);
    for (int i = 0; i < total_s; i++) {
        cin >> s_list[i];
    }
    for (int i = 0; i < total_t; i++) {
        cin >> t_list[i];
    }

    int half = (n + m) / 2;
    long long answer = 0;

    // brute.cpp：直接枚举每一对 (S_i, T_j)，检查拼接后前半段与后半段是否为旋转关系。
    for (int i = 0; i < total_s; i++) {
        for (int j = 0; j < total_t; j++) {
            string w = s_list[i] + t_list[j];
            string u = w.substr(0, half);
            string v = w.substr(half, half);
            if (is_rotation(u, v)) {
                answer++;
            }
        }
    }

    cout << answer << '\n';

    return 0;
}
