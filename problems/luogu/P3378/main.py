import heapq
import sys


input = sys.stdin.buffer.readline
heap = []
output = bytearray()
for _ in range(int(input())):
    operation = input().split()
    if operation[0] == b"1":
        heapq.heappush(heap, int(operation[1]))
    elif operation[0] == b"2":
        output.extend(f"{heap[0]}\n".encode())
    else:
        heapq.heappop(heap)
sys.stdout.buffer.write(output)
