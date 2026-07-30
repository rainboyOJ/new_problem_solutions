message_count = int(input())
billable_messages = sum((int(input()) + 69) // 70 for _ in range(message_count))

print(f"{billable_messages / 10:.1f}")
