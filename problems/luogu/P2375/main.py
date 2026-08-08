import sys
from array import array


MOD = 10**9 + 7
input = sys.stdin.buffer.readline
answers = []

for _ in range(int(input())):
    word = input().strip()
    n = len(word)
    prefix = array("i", [0]) * (n + 1)
    border_count = array("i", [0]) * (n + 1)
    border_count[1] = 1

    for length in range(2, n + 1):
        j = prefix[length - 1]
        while j and word[length - 1] != word[j]:
            j = prefix[j]
        if word[length - 1] == word[j]:
            j += 1
        prefix[length] = j
        border_count[length] = border_count[j] + 1

    answer = 1
    j = 0
    for length in range(2, n + 1):
        while j and word[length - 1] != word[j]:
            j = prefix[j]
        if word[length - 1] == word[j]:
            j += 1
        while j * 2 > length:
            j = prefix[j]
        answer = answer * (border_count[j] + 1) % MOD
    answers.append(str(answer))

print("\n".join(answers))
