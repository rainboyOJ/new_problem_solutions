def express(number):
    parts = []
    power = 0

    while (1 << power) <= number:
        power += 1

    for exponent in range(power - 1, -1, -1):
        if number >> exponent & 1:
            if exponent == 0:
                parts.append("2(0)")
            elif exponent == 1:
                parts.append("2")
            else:
                parts.append(f"2({express(exponent)})")

    return "+".join(parts)

n = int(input())
print(express(n))
