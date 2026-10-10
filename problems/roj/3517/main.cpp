/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string a, b;
vector<pair<string, string> > rules;
vector<pair<string, string> > back_rules;

// 返回 s 中所有 sub 的出现起点
vector<int> hits(const string& s, const string& sub) {
    vector<int> res;
    size_t i = s.find(sub);
    while (i != string::npos) {
        res.push_back((int)i);
        i = s.find(sub, i + 1);
    }
    return res;
}

// 把 front 这一层向外扩一步，返回 (新一层, 本层相遇点)
void step(map<string, int>& front, map<string, int>& seen, const map<string, int>& other,
          const vector<pair<string, string> >& r, int depth,
          map<string, int>& nxt, vector<string>& meeting) {
    nxt.clear();
    meeting.clear();
    for (map<string, int>::iterator it = front.begin(); it != front.end(); ++it) {
        const string& s = it->first;
        for (size_t ri = 0; ri < r.size(); ri++) {
            const string& sa = r[ri].first;
            const string& sb = r[ri].second;
            vector<int> pos = hits(s, sa);
            for (size_t pi = 0; pi < pos.size(); pi++) {
                int i = pos[pi];
                string t = s.substr(0, i) + sb + s.substr(i + sa.size());
                if (seen.find(t) == seen.end()) {
                    seen[t] = depth;
                    if (other.find(t) != other.end()) meeting.push_back(t);
                    nxt[t] = depth;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> words;
    string w;
    while (cin >> w) words.push_back(w);

    a = words[0];
    b = words[1];
    for (size_t i = 2; i + 1 < words.size(); i += 2) {
        rules.push_back(make_pair(words[i], words[i + 1]));
        back_rules.push_back(make_pair(words[i + 1], words[i]));
    }

    if (a == b) { cout << "0\n"; return 0; }

    map<string, int> fa, fb;
    map<string, int> seen_a, seen_b;
    fa[a] = 0; seen_a[a] = 0;
    fb[b] = 0; seen_b[b] = 0;

    for (int round = 0; round < 10; round++) {
        bool forward = fa.size() <= fb.size();
        map<string, int> nxt;
        vector<string> meeting;
        int side_depth = 0;
        if (forward) {
            int maxd = 0;
            for (map<string, int>::iterator it = seen_a.begin(); it != seen_a.end(); ++it)
                maxd = max(maxd, it->second);
            side_depth = maxd + 1;
            step(fa, seen_a, seen_b, rules, side_depth, nxt, meeting);
            if (!meeting.empty()) {
                int best = 1 << 30;
                for (size_t i = 0; i < meeting.size(); i++) {
                    int v = side_depth + seen_b[meeting[i]];
                    best = min(best, v);
                }
                cout << best << "\n";
                return 0;
            }
            fa = nxt;
        } else {
            int maxd = 0;
            for (map<string, int>::iterator it = seen_b.begin(); it != seen_b.end(); ++it)
                maxd = max(maxd, it->second);
            side_depth = maxd + 1;
            step(fb, seen_b, seen_a, back_rules, side_depth, nxt, meeting);
            if (!meeting.empty()) {
                int best = 1 << 30;
                for (size_t i = 0; i < meeting.size(); i++) {
                    int v = side_depth + seen_a[meeting[i]];
                    best = min(best, v);
                }
                cout << best << "\n";
                return 0;
            }
            fb = nxt;
        }
        if (forward ? fa.empty() : fb.empty()) break;
    }
    cout << "NO ANSWER!\n";
    return 0;
}
