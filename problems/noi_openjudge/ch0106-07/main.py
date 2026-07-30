data = list(map(int, input().split()))
length, numbers = data[0], data[1:]
differences = {abs(right - left) for left, right in zip(numbers, numbers[1:])}
print("Jolly" if differences == set(range(1, length)) else "Not jolly")
