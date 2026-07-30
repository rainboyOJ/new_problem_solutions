def shift_right_three(character: str) -> str:
    start = ord("a") if character.islower() else ord("A")
    return chr((ord(character) - start + 3) % 26 + start)


ciphertext = input().strip()
# 解密按加密操作的逆序进行：反转大小写、恢复顺序、字母右移三位。
recovered_order = ciphertext.swapcase()[::-1]
print("".join(shift_right_three(character) for character in recovered_order))
