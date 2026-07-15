def reverse_integer_part(text):
    result = text[::-1].lstrip("0")
    return result if result else "0"


def reverse_decimal_part(text):
    result = text[::-1].rstrip("0")
    return result if result else "0"


s = input().strip()

if "." in s:
    integer_part, decimal_part = s.split(".")
    print(reverse_integer_part(integer_part) + "." + reverse_decimal_part(decimal_part))
elif "/" in s:
    numerator, denominator = s.split("/")
    print(reverse_integer_part(numerator) + "/" + reverse_integer_part(denominator))
elif s.endswith("%"):
    print(reverse_integer_part(s[:-1]) + "%")
else:
    print(reverse_integer_part(s))
