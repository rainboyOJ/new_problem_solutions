import sys

data = sys.stdin.buffer.read().split()
cnt = [int(x) for x in data[:6]]
weights = [1, 2, 3, 5, 10, 20]

ans = set()

def dfs(i, cur):
    if i == 6:
        if cur > 0:
            ans.add(cur)
        return
    for k in range(cnt[i] + 1):
        dfs(i + 1, cur + k * weights[i])

dfs(0, 0)
print(len(ans))
