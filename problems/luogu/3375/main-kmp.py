import sys


s1, s2 = [x.decode() for x in sys.stdin.buffer.read().split()]

def build_prefix(s):
    if not s:
        return []
    pi = [0] * len(s)
    j = 0
    for i in range(1,len(s)):
        while j != 0 and s[i] != s[j]:
            j = pi[j-1]
        if s[i] == s[j]:
            j += 1
        pi[i] = j

    return pi

def kmp(s1,s2,prefix = []):
    if not prefix:
        prefix = build_prefix(s2)
    equal_pos = []
    j = 0
    for i in range(0,len(s1)):
        while j !=0 and s1[i] != s2[j]:
            j = prefix[j-1]
        if s1[i] == s2[j]:
            j += 1
        if j == len(s2):
            equal_pos.append(i - len(s2) +1)
            j = prefix[j-1]

    return equal_pos


def solve():
    pi = build_prefix(s2)
    pos = kmp(s1,s2,pi)
    pos2 = map(lambda x: x+1,pos)
    if pos:
        print(*(pos2),  sep="\n")
    print(*pi, sep=" ")
    


if __name__ == "__main__":
    solve()
