import sys


input = sys.stdin.buffer.readline
n, contests = map(int, input().split())
reachable = [0] * n
for _ in range(contests):
    winner, loser = map(int, input().split())
    reachable[winner - 1] |= 1 << (loser - 1)
for middle in range(n):
    bit = 1 << middle
    for start in range(n):
        if reachable[start] & bit:
            reachable[start] |= reachable[middle]
answer = 0
for cow in range(n):
    known = reachable[cow].bit_count() + sum(mask >> cow & 1 for mask in reachable)
    answer += known == n - 1
print(answer)
