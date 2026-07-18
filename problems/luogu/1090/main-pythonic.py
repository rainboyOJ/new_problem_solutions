import heapq
import sys

def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    heap = data[1:1 + n]

    heapq.heapify(heap)
    answer = 0

    while len(heap) > 1:
        a = heapq.heappop(heap)
        b = heapq.heappop(heap)
        merged = a + b
        answer += merged
        heapq.heappush(heap, merged)

    print(answer)

if __name__ == "__main__":
    main()
