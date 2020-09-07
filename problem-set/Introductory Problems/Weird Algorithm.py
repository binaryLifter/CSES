def solve(N, v):
    v.append(N)
    if N == 1:
        return
    nxt = N * 3 + 1 if N & 1 else N >> 1
    solve(nxt, v)


def main():
    N = int(input())
    v = []
    solve(N, v)
    v = [str(i) for i in v]
    print(' '.join(v))


main()
