import sys
from itertools import batched
from bisect import bisect_left, bisect_right
from collections import defaultdict

out = []

def work(s,t):

    # pos = [[] for _ in range(26)]
    pos = defaultdict(list)

    for i, ch in enumerate(s):
        # record the pos of each char
        pos[ch].append(i)
    ans = 1
    cur = -1

    for ch in t:
        if ch not in pos:
            return -1
        arr = pos[ch]
        j = bisect_right(arr,cur)
        if j == len(arr):
            ans += 1
            cur = arr[0]
        else:
            cur = arr[j]
    return ans

def solve():
    global out
    data = sys.stdin.buffer.read().decode().split()
    # 两个一组 
    ss = batched(data[1:],2)

    out = [work(a,b) for a,b in ss]
    print(*out,sep="\n")

    


if __name__ == "__main__":
    solve()
