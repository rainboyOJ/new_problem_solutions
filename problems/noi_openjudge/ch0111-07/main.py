input()
numbers = sorted(map(int, input().split()))
target_sum = int(input())

left, right = 0, len(numbers) - 1
while left < right:
    current_sum = numbers[left] + numbers[right]
    if current_sum == target_sum:
        print(numbers[left], numbers[right])
        break
    if current_sum < target_sum:
        left += 1
    else:
        right -= 1
else:
    print("No")
