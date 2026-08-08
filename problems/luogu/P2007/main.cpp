#include <bits/stdc++.h>
using namespace std;

int front_face[4][4], back_face[4][4], left_face[4][4];
int right_face[4][4], up_face[4][4], down_face[4][4];

void rotate_right_clockwise() {
    int tmp[4];
    for (int i = 1; i <= 3; ++i) {
        tmp[i] = front_face[i][3];
    }
    for (int i = 1; i <= 3; ++i) {
        front_face[i][3] = down_face[i][3];
    }
    for (int i = 1; i <= 3; ++i) {
        down_face[i][3] = back_face[i][3];
    }
    for (int i = 1; i <= 3; ++i) {
        back_face[i][3] = up_face[i][3];
    }
    for (int i = 1; i <= 3; ++i) {
        up_face[i][3] = tmp[i];
    }

    int old_face[4][4];
    memcpy(old_face, right_face, sizeof(old_face));
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            right_face[i][j] = old_face[4 - j][i];
        }
    }
}

void rotate_right_counterclockwise() {
    int tmp[4];
    for (int i = 1; i <= 3; ++i) {
        tmp[i] = front_face[i][3];
    }
    for (int i = 1; i <= 3; ++i) {
        front_face[i][3] = up_face[i][3];
    }
    for (int i = 1; i <= 3; ++i) {
        up_face[i][3] = back_face[i][3];
    }
    for (int i = 1; i <= 3; ++i) {
        back_face[i][3] = down_face[i][3];
    }
    for (int i = 1; i <= 3; ++i) {
        down_face[i][3] = tmp[i];
    }

    int old_face[4][4];
    memcpy(old_face, right_face, sizeof(old_face));
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            right_face[i][j] = old_face[j][4 - i];
        }
    }
}

void rotate_up_clockwise() {
    int tmp[4];
    for (int i = 1; i <= 3; ++i) {
        tmp[i] = front_face[1][i];
    }
    for (int i = 1; i <= 3; ++i) {
        front_face[1][i] = left_face[1][i];
    }
    for (int i = 1; i <= 3; ++i) {
        left_face[1][i] = back_face[1][i];
    }
    for (int i = 1; i <= 3; ++i) {
        back_face[1][i] = right_face[1][i];
    }
    for (int i = 1; i <= 3; ++i) {
        right_face[1][i] = tmp[i];
    }

    int old_face[4][4];
    memcpy(old_face, up_face, sizeof(old_face));
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            up_face[i][j] = old_face[4 - j][i];
        }
    }
}

void rotate_up_counterclockwise() {
    int tmp[4];
    for (int i = 1; i <= 3; ++i) {
        tmp[i] = front_face[1][i];
    }
    for (int i = 1; i <= 3; ++i) {
        front_face[1][i] = right_face[1][i];
    }
    for (int i = 1; i <= 3; ++i) {
        right_face[1][i] = back_face[1][i];
    }
    for (int i = 1; i <= 3; ++i) {
        back_face[1][i] = left_face[1][i];
    }
    for (int i = 1; i <= 3; ++i) {
        left_face[1][i] = tmp[i];
    }

    int old_face[4][4];
    memcpy(old_face, up_face, sizeof(old_face));
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            up_face[i][j] = old_face[j][4 - i];
        }
    }
}

void read_face(int face[4][4]) {
    string row;
    for (int i = 1; i <= 3; ++i) {
        cin >> row;
        for (int j = 1; j <= 3; ++j) {
            face[i][j] = row[j - 1] - '0';
        }
    }
}

void print_face(int face[4][4]) {
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            cout << face[i][j];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string steps;
    cin >> steps;
    read_face(front_face);
    read_face(back_face);
    read_face(left_face);
    read_face(right_face);
    read_face(up_face);
    read_face(down_face);

    for (char ch : steps) {
        if (ch == '1') {
            rotate_right_clockwise();
        } else if (ch == '2') {
            rotate_right_counterclockwise();
        } else if (ch == '3') {
            rotate_up_clockwise();
        } else if (ch == '4') {
            rotate_up_counterclockwise();
        }
    }

    print_face(front_face);
    print_face(back_face);
    print_face(left_face);
    print_face(right_face);
    print_face(up_face);
    print_face(down_face);
    return 0;
}
