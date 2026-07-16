import sys


input = sys.stdin.buffer.readline
number, rule_count = input().split()
reachable = [1 << digit for digit in range(10)]
for _ in range(int(rule_count)):
    source, target = map(int, input().split())
    reachable[source] |= 1 << target
for middle in range(10):
    bit = 1 << middle
    for start in range(10):
        if reachable[start] & bit:
            reachable[start] |= reachable[middle]
answer = 1
for digit in number:
    answer *= reachable[digit - 48].bit_count()
print(answer)
