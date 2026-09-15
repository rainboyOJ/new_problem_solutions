import sys


def lcp(text, x, y):
    answer = 0
    while x + answer < len(text) and y + answer < len(text) and text[x + answer] == text[y + answer]:
        answer += 1
    return answer


def solve():
    readline = sys.stdin.buffer.readline
    text = list(readline().strip())
    operation_count = int(readline())
    answers = []

    for _ in range(operation_count):
        operation = readline().split()
        if operation[0] == b'I':
            text.insert(int(operation[1]), operation[2][0])
        elif operation[0] == b'R':
            text[int(operation[1]) - 1] = operation[2][0]
        else:
            answers.append(str(lcp(text, int(operation[1]) - 1, int(operation[2]) - 1)))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
