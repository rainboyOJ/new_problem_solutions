/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:59
 * update_at: 2026-07-19 11:59
 */
#include <cstdio>

const int BUFFER_SIZE = 1 << 16;

char input_buffer[BUFFER_SIZE];
int buffer_position;
int buffer_length;

bool read_integer(int &value) {
    char current;

    do {
        if (buffer_position == buffer_length) {
            buffer_length = fread(input_buffer, 1, BUFFER_SIZE, stdin);
            buffer_position = 0;
            if (buffer_length == 0) return false;
        }
        current = input_buffer[buffer_position++];
    } while (current < '0' || current > '9');

    value = 0;
    while (current >= '0' && current <= '9') {
        value = value * 10 + current - '0';
        if (buffer_position == buffer_length) {
            buffer_length = fread(input_buffer, 1, BUFFER_SIZE, stdin);
            buffer_position = 0;
            if (buffer_length == 0) return true;
        }
        current = input_buffer[buffer_position++];
    }
    return true;
}

int main() {
    int n;
    read_integer(n);

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        int length;
        read_integer(length);
        answer ^= length;
    }

    printf("%d\n", answer);
    return 0;
}
