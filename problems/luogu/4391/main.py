import sys
from array import array


n, word = sys.stdin.buffer.read().split()
n = int(n)
prefix = array("i", [0]) * n
j = 0

for i in range(1, n):
    while j and word[i] != word[j]:
        j = prefix[j - 1]
    if word[i] == word[j]:
        j += 1
    prefix[i] = j

print(n - prefix[-1])
