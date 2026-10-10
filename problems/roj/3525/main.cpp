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

int m, n, p;
vector<string> people;
vector<pair<string, string> > statements;   // (说话者, 原句)

const char* MONDAY[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

// 证词立场：0 表示与假设一致，1 表示冲突，2 表示闲话
int sentence_opinion(const string& sentence, const string& suspect, const string& speaker, const string& day) {
    if (sentence == "I am guilty." || sentence == "I am GUILTY.")
        return (speaker == suspect) ? 0 : 1;
    if (sentence == "I am not guilty.")
        return (speaker != suspect) ? 0 : 1;
    if (sentence.size() > 11 && sentence.substr(sentence.size() - 11) == " is guilty.") {
        string name = sentence.substr(0, sentence.size() - 11);
        return (name == suspect) ? 0 : 1;
    }
    if (sentence.size() > 15 && sentence.substr(sentence.size() - 15) == " is not guilty.") {
        string name = sentence.substr(0, sentence.size() - 15);
        return (name != suspect) ? 0 : 1;
    }
    if (sentence.size() > 9 && sentence.substr(0, 9) == "Today is ") {
        string d = sentence.substr(9);
        if (!d.empty() && d.back() == '.') d.pop_back();
        return (d == day) ? 0 : 1;
    }
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string firstline;
    getline(cin, firstline);
    stringstream ss(firstline);
    ss >> m >> n >> p;
    for (int i = 0; i < m; i++) {
        string name;
        getline(cin, name);
        people.push_back(name);
    }
    for (int i = 0; i < p; i++) {
        string line;
        getline(cin, line);
        size_t pos = line.find(":");
        string speaker = line.substr(0, pos);
        string sentence = line.substr(pos + 1);
        // 去首尾空白
        int a = 0, b = (int)sentence.size();
        while (a < b && isspace((unsigned char)sentence[a])) a++;
        while (b > a && isspace((unsigned char)sentence[b - 1])) b--;
        sentence = sentence.substr(a, b - a);
        statements.push_back(make_pair(speaker, sentence));
    }

    vector<string> suspects;
    for (int si = 0; si < m; si++) {
        const string& suspect = people[si];
        bool found = false;
        for (int di = 0; di < 7 && !found; di++) {
            const string& day = MONDAY[di];
            set<string> honest, liars;
            bool ok = true;
            for (int i = 0; i < p && ok; i++) {
                int opinion = sentence_opinion(statements[i].second, suspect, statements[i].first, day);
                if (opinion == 2) continue;
                bool liar = (opinion == 1);
                if ((liars.count(statements[i].first) && !liar) ||
                    (honest.count(statements[i].first) && liar)) {
                    ok = false;
                    break;
                }
                if (liar) liars.insert(statements[i].first);
                else honest.insert(statements[i].first);
            }
            if (!ok) continue;
            set<string> speakers;
            for (int i = 0; i < p; i++) speakers.insert(statements[i].first);
            int free = 0;
            for (set<string>::iterator it = speakers.begin(); it != speakers.end(); ++it)
                if (!honest.count(*it) && !liars.count(*it)) free++;
            if ((int)liars.size() <= n && n <= (int)liars.size() + free) {
                suspects.push_back(suspect);
                found = true;
            }
        }
    }

    set<string> unique_suspects(suspects.begin(), suspects.end());
    if (suspects.empty()) {
        cout << "Impossible\n";
    } else if (unique_suspects.size() > 1) {
        cout << "Cannot Determine\n";
    } else {
        cout << suspects[0] << "\n";
    }
    return 0;
}
