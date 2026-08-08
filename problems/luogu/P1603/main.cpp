#include <bits/stdc++.h>
using namespace std;

map<string, int> value_of_word;
int nums[10];
int cnt;

void init_dict() {
    value_of_word["zero"] = 0;
    value_of_word["one"] = 1;
    value_of_word["two"] = 2;
    value_of_word["three"] = 3;
    value_of_word["four"] = 4;
    value_of_word["five"] = 5;
    value_of_word["six"] = 6;
    value_of_word["seven"] = 7;
    value_of_word["eight"] = 8;
    value_of_word["nine"] = 9;
    value_of_word["ten"] = 10;
    value_of_word["eleven"] = 11;
    value_of_word["twelve"] = 12;
    value_of_word["thirteen"] = 13;
    value_of_word["fourteen"] = 14;
    value_of_word["fifteen"] = 15;
    value_of_word["sixteen"] = 16;
    value_of_word["seventeen"] = 17;
    value_of_word["eighteen"] = 18;
    value_of_word["nineteen"] = 19;
    value_of_word["twenty"] = 20;

    value_of_word["a"] = 1;
    value_of_word["both"] = 2;
    value_of_word["another"] = 1;
    value_of_word["first"] = 1;
    value_of_word["second"] = 2;
    value_of_word["third"] = 3;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_dict();

    string word;
    while (cin >> word) {
        if (value_of_word.count(word) == 0) {
            continue;
        }

        int value = value_of_word[word];
        nums[++cnt] = value * value % 100;
    }

    sort(nums + 1, nums + cnt + 1);

    string ans;
    for (int i = 1; i <= cnt; i++) {
        if (nums[i] < 10) {
            ans += '0';
        }
        ans += to_string(nums[i]);
    }

    int pos = 0;
    while (pos < (int) ans.size() && ans[pos] == '0') {
        pos++;
    }

    if (pos == (int) ans.size()) {
        cout << 0 << '\n';
    }
    else {
        cout << ans.substr(pos) << '\n';
    }

    return 0;
}
