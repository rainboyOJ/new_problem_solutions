def is_prime(number: int) -> bool:
    if number < 2:
        return False
    for divisor in (2, 3, 5, 7, 11):
        if number == divisor:
            return True
        if number % divisor == 0:
            return False

    exponent = number - 1
    power_of_two = 0
    while exponent % 2 == 0:
        power_of_two += 1
        exponent //= 2

    for base in (2, 3, 5, 7, 11):
        value = pow(base, exponent, number)
        if value in (1, number - 1):
            continue
        for _ in range(power_of_two - 1):
            value = value * value % number
            if value == number - 1:
                break
        else:
            return False
    return True


digit_count = int(input())
if digit_count == 1:
    answers = [2, 3, 5, 7]
elif digit_count % 2 == 0:
    answers = [11] if digit_count == 2 else []
else:
    half_length = digit_count // 2 + 1
    answers = []
    for prefix in range(10 ** (half_length - 1), 10**half_length):
        text = str(prefix)
        candidate = int(text + text[-2::-1])
        if is_prime(candidate):
            answers.append(candidate)

print(len(answers))
print(*answers)
