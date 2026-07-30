line_count = int(input())
maximum = -1
lines_with_maximum = []

for line_number in range(1, line_count + 1):
    numbers = map(int, input().split(","))
    line_maximum = max(numbers)
    if line_maximum > maximum:
        maximum = line_maximum
        lines_with_maximum = [line_number]
    elif line_maximum == maximum:
        lines_with_maximum.append(line_number)

print(maximum)
print(*lines_with_maximum, sep=",")
