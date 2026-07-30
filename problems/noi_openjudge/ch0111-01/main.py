from bisect import bisect_left

input()
numbers = list(map(int, input().split()))
query_count = int(input())

for _ in range(query_count):
    target = int(input())
    right = bisect_left(numbers, target)
    if right == 0:
        print(numbers[0])
    elif right == len(numbers):
        print(numbers[-1])
    else:
        left = right - 1
        if numbers[right] - target < target - numbers[left]:
            print(numbers[right])
        else:
            print(numbers[left])
