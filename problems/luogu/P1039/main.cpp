#include <bits/stdc++.h>
using namespace std;

const int MAXM = 25;
const int MAXP = 105;
const int UNKNOWN = -1;
const int ALWAYS_TRUE = 1;
const int ALWAYS_FALSE = 0;

int m, n, p;
string name_list[MAXM];
map<string, int> name_id;

string week_name[7] = {
    "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday"
};

struct Statement {
    int speaker;
    int type;   // 0: 无关, 1: 某人有罪, 2: 某人无罪, 3: 今天是某星期
    int who;
    int week;
};

Statement st[MAXP];

bool ends_with(const string &s, const string &suffix) {
    int n1 = (int)s.size();
    int n2 = (int)suffix.size();
    if (n1 < n2) {
        return false;
    }
    return s.substr(n1 - n2) == suffix;
}

Statement parse_statement(const string &line) {
    Statement cur;
    cur.speaker = -1;
    cur.type = 0;
    cur.who = -1;
    cur.week = -1;

    int pos = line.find(':');
    string speaker = line.substr(0, pos);
    string content = line.substr(pos + 2);

    cur.speaker = name_id[speaker];

    if (content == "I am guilty.") {
        cur.type = 1;
        cur.who = cur.speaker;
        return cur;
    }
    if (content == "I am not guilty.") {
        cur.type = 2;
        cur.who = cur.speaker;
        return cur;
    }

    if (ends_with(content, " is guilty.")) {
        string who = content.substr(0, (int)content.size() - 11);
        if (name_id.count(who)) {
            cur.type = 1;
            cur.who = name_id[who];
            return cur;
        }
    }

    if (ends_with(content, " is not guilty.")) {
        string who = content.substr(0, (int)content.size() - 15);
        if (name_id.count(who)) {
            cur.type = 2;
            cur.who = name_id[who];
            return cur;
        }
    }

    if (content.substr(0, 9) == "Today is " && content.back() == '.') {
        string day = content.substr(9, (int)content.size() - 10);
        for (int i = 0; i < 7; i++) {
            if (day == week_name[i]) {
                cur.type = 3;
                cur.week = i;
                return cur;
            }
        }
    }

    return cur;
}

// 返回这句话在当前“罪犯 + 星期”假设下是真还是假。
bool statement_value(const Statement &s, int guilty, int today) {
    if (s.type == 1) {
        return s.who == guilty;
    }
    if (s.type == 2) {
        return s.who != guilty;
    }
    if (s.type == 3) {
        return s.week == today;
    }
    return true;
}

bool check_candidate(int guilty) {
    for (int today = 0; today < 7; today++) {
        int person_state[MAXM];
        for (int i = 0; i < m; i++) {
            person_state[i] = UNKNOWN;
        }

        bool bad = false;

        for (int i = 0; i < p; i++) {
            if (st[i].type == 0) {
                continue;
            }

            bool val = statement_value(st[i], guilty, today);
            int want = val ? ALWAYS_TRUE : ALWAYS_FALSE;
            int sp = st[i].speaker;

            if (person_state[sp] == UNKNOWN) {
                person_state[sp] = want;
            } else if (person_state[sp] != want) {
                bad = true;
                break;
            }
        }

        if (bad) {
            continue;
        }

        int liar_cnt = 0;
        int honest_cnt = 0;
        for (int i = 0; i < m; i++) {
            if (person_state[i] == ALWAYS_FALSE) {
                liar_cnt++;
            } else if (person_state[i] == ALWAYS_TRUE) {
                honest_cnt++;
            }
        }

        if (liar_cnt <= n && n <= m - honest_cnt) {
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n >> p;
    for (int i = 0; i < m; i++) {
        cin >> name_list[i];
        name_id[name_list[i]] = i;
    }

    string line;
    getline(cin, line);
    for (int i = 0; i < p; i++) {
        getline(cin, line);
        st[i] = parse_statement(line);
    }

    vector<int> candidates;
    for (int guilty = 0; guilty < m; guilty++) {
        if (check_candidate(guilty)) {
            candidates.push_back(guilty);
        }
    }

    if ((int)candidates.size() == 0) {
        cout << "Impossible\n";
    } else if ((int)candidates.size() >= 2) {
        cout << "Cannot Determine\n";
    } else {
        cout << name_list[candidates[0]] << '\n';
    }

    return 0;
}
