digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def convert(value: int, base: int) -> str:
    if value == 0:
        return "0"
    result = []
    while value:
        value, remainder = divmod(value, base)
        result.append(digits[remainder])
    return "".join(reversed(result))


case_count = int(input())
for _ in range(case_count):
    source_base, source_number, target_base = input().split(",")
    print(convert(int(source_number, int(source_base)), int(target_base)))
