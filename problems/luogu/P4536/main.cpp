#include <bits/stdc++.h>
using namespace std;

string path_code;

// side:
// 'D' -> 斜边（在右三角仿射模型里，对应对角线方向）
// 'H' -> 水平边
// 'V' -> 竖直边
string get_neighbor(const string &path, char side) {
    if (path.empty()) return "";

    int len = (int)path.size();
    char last = path[len - 1];
    string prefix = path.substr(0, len - 1);

    if (last == '4') {
        if (side == 'D') return prefix + '2';
        if (side == 'H') return prefix + '1';
        return prefix + '3';
    }

    if (last == '1') {
        if (side == 'H') return prefix + '4';
        return get_neighbor(prefix, side);
    }

    if (last == '2') {
        if (side == 'D') return prefix + '4';
        return get_neighbor(prefix, side);
    }

    // last == '3'
    if (side == 'V') return prefix + '4';
    return get_neighbor(prefix, side);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string full_name;
    cin >> full_name;
    path_code = full_name.substr(1);

    vector<string> answer;
    answer.push_back(get_neighbor(path_code, 'D'));
    answer.push_back(get_neighbor(path_code, 'H'));
    answer.push_back(get_neighbor(path_code, 'V'));

    sort(answer.begin(), answer.end());
    answer.erase(unique(answer.begin(), answer.end()), answer.end());

    for (int i = 0; i < (int)answer.size(); i++) {
        if (answer[i].empty()) continue;
        cout << 'T' << answer[i] << '\n';
    }

    return 0;
}
