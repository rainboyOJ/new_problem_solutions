import sys

data = sys.stdin.buffer.read().split()
n = int(data[0])
w = [int(x) for x in data[1:1+n]]

ans = set()

def dfs(i, left, right):
    if i == n:
        diff = abs(left - right)
        if diff > 0:
            ans.add(diff)
        return
    dfs(i + 1, left + w[i], right)
    dfs(i + 1, left, right + w[i])
    dfs(i + 1, left, right)

dfs(0, 0, 0)
print(len(ans))
