import sys


def build_prefix(s):
    pi = [0] * len(s)
    j = 0
    for i in range(1, len(s)):
        while j and s[i] != s[j]:
            j = pi[j - 1]
        if s[i] == s[j]:
            j += 1
        pi[i] = j
    return pi


n, word = [x.decode() for x in sys.stdin.buffer.read().split()]
pi = build_prefix(word)

print(int(n) - pi[-1])
