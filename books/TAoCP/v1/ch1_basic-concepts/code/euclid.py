def remainder(m, n):
    if m < n:
        return m
    return remainder(m - n, n)

def euclid(m, n):
    rem = remainder(m, n)
    if rem == 0:
        return n
    return euclid(n, rem)

if __name__ == "__main__":
    print("GCD(5,30) = %s" % euclid(5,30))
    print("GCD(100,29) = %s" % euclid(100,29))
    print("GCD(25,100) = %s" % euclid(25,100))
    print("GCD(123,33) = %s" % euclid(123,33))
    print("GCD(2166,6099) = %s" % euclid(2166,6099))
    print("GCD(6099,2166) = %s" % euclid(6099,2166))

