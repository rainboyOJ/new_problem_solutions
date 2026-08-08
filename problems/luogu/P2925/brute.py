import sys

data = sys.stdin.buffer.read().split()
c = int(data[0])
h = int(data[1])
v = [int(x) for x in data[2:2+h]]

ans = 0

def dfs(i, cur):
    global ans
    if cur > c:
        return
    if cur > ans:
        ans = cur
    if i == h:
        return
    dfs(i + 1, cur + v[i])
    dfs(i + 1, cur)

dfs(0, 0)
print(ans)
