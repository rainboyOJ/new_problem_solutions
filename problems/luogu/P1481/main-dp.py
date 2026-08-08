from functools import partial
import sys

def flow(value, *steps):
    for step in steps:
        value = step(value)
    return value

data = sys.stdin.buffer.read().split()
words = [w.decode() for w in data[1:]]

# print(words)
dp = [1] * (len(words) + 5) 
ans = 1
for i,w in enumerate(words):
    # print(i,w)
    for j in range(i):
        pre_w = words[j]
        if w.startswith(pre_w):
            dp[i] = max(dp[j]+1, dp[i])
            ans = max(ans, dp[i]) 
print(ans)



