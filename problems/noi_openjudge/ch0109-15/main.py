import heapq

student_count, tap_count = map(int, input().split())
amounts = list(map(int, input().split()))
finish_times = amounts[:tap_count]
heapq.heapify(finish_times)
for amount in amounts[tap_count:]:
    heapq.heappush(finish_times, heapq.heappop(finish_times) + amount)
print(max(finish_times))
