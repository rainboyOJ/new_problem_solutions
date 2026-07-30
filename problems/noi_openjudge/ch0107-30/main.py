first, second = input().split()
first_twice = first + first
second_twice = second + second
maximum_length = min(len(first), len(second))
previous = [0] * (len(second_twice) + 1)
answer = 0

for first_character in first_twice:
    current = [0] * (len(second_twice) + 1)
    for index, second_character in enumerate(second_twice, 1):
        if first_character == second_character:
            current[index] = min(previous[index - 1] + 1, maximum_length)
            answer = max(answer, current[index])
    previous = current

print(answer)
