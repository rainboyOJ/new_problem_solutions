def express(number):
    parts = []
    for exponent in range(number.bit_length() - 1, -1, -1):
        if not (number >> exponent & 1):
            continue
        if exponent == 0:
            parts.append("2(0)")
        elif exponent == 1:
            parts.append("2")
        else:
            parts.append(f"2({express(exponent)})")
    return "+".join(parts)


print(express(int(input())))
