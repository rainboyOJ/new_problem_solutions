import sys


s1, s2 = [x.decode() for x in sys.stdin.buffer.read().split()]

def find_all(s1,s2):
    if not s2 :
        return []
    ans ,pos = [],s1.find(s2)
    while pos != -1:
        ans.append(pos+1) # 位置从1开始
        pos = s1.find(s2,pos+1)
    return ans


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

def solve():
    ans = find_all(s1, s2)
    if ans:
        print(*ans, sep="\n")
    pi = build_prefix(s2)
    if pi:
        print(*pi, sep=" ")
    print(*pi, sep=" ")
    


if __name__ == "__main__":
    solve()
