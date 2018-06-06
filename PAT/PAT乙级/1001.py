if __name__ == '__main__':
    n = int(input())
    cnt = 0
    while n > 1:
        if n % 2 == 1:
            n = (3 * n + 1) / 2
        else:
            n = n / 2
        cnt = cnt + 1
    print(cnt)
