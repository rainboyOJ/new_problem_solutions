#include <bits/stdc++.h>
using namespace std;

int n, p;
string last_col;
string first_col;
vector<char> kind_char;
map<char, int> id_of_char;
vector<int> total_cnt;
vector<vector<int> > preds;
map<pair<int, string>, bool> memo_ok;

string encode_state(const vector<int> &cnt) {
    string s;
    s.reserve(cnt.size());
    for (int x : cnt) {
        s.push_back((char)x);
    }
    return s;
}

bool can_finish(int last_id, const vector<int> &used_cnt) {
    int used_sum = 0;
    for (int x : used_cnt) {
        used_sum += x;
    }
    if (used_sum == n) {
        return true;
    }

    pair<int, string> key = make_pair(last_id, encode_state(used_cnt));
    map<pair<int, string>, bool>::iterator it = memo_ok.find(key);
    if (it != memo_ok.end()) {
        return it->second;
    }

    for (int c = 0; c < (int)kind_char.size(); c++) {
        int k = used_cnt[c];
        if (k < total_cnt[c] && preds[c][k] == last_id) {
            vector<int> nxt = used_cnt;
            nxt[c]++;
            if (can_finish(c, nxt)) {
                memo_ok[key] = true;
                return true;
            }
        }
    }

    memo_ok[key] = false;
    return false;
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

    if (n == 1) {
        cout << last_col << '\n';
        return 0;
    }

    // 题目中的 p 表示原串首字符 S[1] 在最后一列中的位置。
    int s1 = id_of_char[last_col[p - 1]];
    int s2 = id_of_char[first_col[p - 1]];

    vector<int> used_cnt(m, 0);
    used_cnt[s1]++;
    used_cnt[s2]++;

    vector<int> ans_id;
    ans_id.push_back(s1);
    ans_id.push_back(s2);

    memo_ok.clear();
    int last_id = s2;
    for (int pos = 3; pos <= n; pos++) {
        bool found = false;
        for (int c = 0; c < m; c++) {
            int k = used_cnt[c];
            if (k < total_cnt[c] && preds[c][k] == last_id) {
                vector<int> nxt = used_cnt;
                nxt[c]++;
                if (can_finish(c, nxt)) {
                    ans_id.push_back(c);
                    used_cnt = nxt;
                    last_id = c;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            return 0;
        }
    }

    for (int x : ans_id) {
        cout << kind_char[x];
    }
    cout << '\n';
    return 0;
}
