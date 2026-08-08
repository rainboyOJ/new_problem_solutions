import sys
from array import array


n, word = sys.stdin.buffer.read().split()
n = int(n)
prefix = array("i", [0]) * (n + 1)
shortest_border = array("i", [0]) * (n + 1)
answer = 0

for length in range(2, n + 1):
    j = prefix[length - 1]
    while j and word[length - 1] != word[j]:
        j = prefix[j]
    if word[length - 1] == word[j]:
        j += 1
    prefix[length] = j
    if j:
        shortest_border[length] = shortest_border[j] or j
        answer += length - shortest_border[length]

print(answer)
