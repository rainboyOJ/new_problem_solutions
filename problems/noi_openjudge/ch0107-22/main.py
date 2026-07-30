email = input().strip()
account_count = int(input())
accounts = []

for _ in range(account_count):
    username, password, account_email = input().split()
    if account_email == email:
        accounts.append(f"{username} {password.swapcase()}")

print("\n".join(accounts) if accounts else "empty")
