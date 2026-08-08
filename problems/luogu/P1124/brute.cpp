#include <bits/stdc++.h>
using namespace std;

int n, p;
string last_col;
string first_col;
vector<char> kind_char;
map<char, int> id_of_char;
vector<int> total_cnt;
vector<vector<int> > preds;
vector<int> ans_id;
bool found_answer = false;

void dfs(int last_id, vector<int> &used_cnt) {
    if (found_answer) {
        return;
    }

    int used_sum = 0;
    for (int x : used_cnt) {
        used_sum += x;
    }
    if (used_sum == n) {
        for (int x : ans_id) {
            cout << kind_char[x];
        }
        cout << '\n';
        found_answer = true;
        return;
    }

    for (int c = 0; c < (int)kind_char.size(); c++) {
        int k = used_cnt[c];
        if (k < total_cnt[c] && preds[c][k] == last_id) {
            used_cnt[c]++;
            ans_id.push_back(c);
            dfs(c, used_cnt);
            ans_id.pop_back();
            used_cnt[c]--;
            if (found_answer) {
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> last_col;
    cin >> p;

    first_col = last_col;
    sort(first_col.begin(), first_col.end());

    kind_char.clear();
    id_of_char.clear();
    for (char ch : first_col) {
        if (id_of_char.find(ch) == id_of_char.end()) {
            id_of_char[ch] = (int)kind_char.size();
            kind_char.push_back(ch);
        }
    }

    int m = (int)kind_char.size();
    total_cnt.assign(m, 0);
    preds.assign(m, vector<int>());

    for (char ch : first_col) {
        total_cnt[id_of_char[ch]]++;
    }
    for (int i = 0; i < n; i++) {
        int to = id_of_char[first_col[i]];
        int from = id_of_char[last_col[i]];
        preds[to].push_back(from);
    }

    int s1 = id_of_char[last_col[p - 1]];
    if (n == 1) {
        cout << last_col << '\n';
        return 0;
    }

    int s2 = id_of_char[first_col[p - 1]];
    vector<int> used_cnt(m, 0);
    used_cnt[s1]++;
    used_cnt[s2]++;

    ans_id.clear();
    ans_id.push_back(s1);
    ans_id.push_back(s2);
    found_answer = false;
    dfs(s2, used_cnt);
    return 0;
}
