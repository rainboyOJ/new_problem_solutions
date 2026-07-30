def to_base(number, base):
    digits = []
    while number:
        digits.append(str(number % base))
        number //= base
    return "".join(reversed(digits))


for number in range(9**2, 7**3):
    base7 = to_base(number, 7)
    base9 = to_base(number, 9)
    if len(base7) == len(base9) == 3 and base7 == base9[::-1]:
        print(number)
        print(base7)
        print(base9)
        break
