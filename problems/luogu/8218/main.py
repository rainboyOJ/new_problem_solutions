import sys
from itertools import accumulate


input = sys.stdin.buffer.readline
n = int(input())
prefix = list(accumulate(map(int, input().split()), initial=0))
answers = (str(prefix[r] - prefix[l - 1]) for l, r in
           (map(int, input().split()) for _ in range(int(input()))))
print("\n".join(answers))
