import heapq
import sys


input = sys.stdin.buffer.readline
n = int(input())
gender = input().strip()
skill = list(map(int, input().split()))
previous = [i - 1 for i in range(n)]
following = [i + 1 for i in range(n)]
following[-1] = -1
alive = bytearray(b"\1" * n)
heap = [(abs(skill[i] - skill[i + 1]), i, i + 1)
        for i in range(n - 1) if gender[i] != gender[i + 1]]
heapq.heapify(heap)
answer = []

while heap:
    _, left, right = heapq.heappop(heap)
    if not alive[left] or not alive[right] or following[left] != right:
        continue
    answer.append((left + 1, right + 1))
    alive[left] = alive[right] = 0
    new_left, new_right = previous[left], following[right]
    if new_left >= 0:
        following[new_left] = new_right
    if new_right >= 0:
        previous[new_right] = new_left
    if new_left >= 0 and new_right >= 0 and gender[new_left] != gender[new_right]:
        heapq.heappush(heap, (abs(skill[new_left] - skill[new_right]), new_left, new_right))

print(len(answer))
print("\n".join(f"{left} {right}" for left, right in answer))
