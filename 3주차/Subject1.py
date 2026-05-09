import random

target = f"{random.randint(0, 9999):04d}"

print("생성된 타겟:", target)

count = 0

for i in range(10000):
    guess = f"{i:04d}"
    count += 1

    if guess == target:
        print("정답 발견:", guess)
        print("총 시도 횟수:", count)
        break
