import sys

def square(origin, width=1):
    hw = width / 2.
    tl = origin[0] - hw, origin[1] + hw
    tr = origin[0] + hw, origin[1] + hw
    br = origin[0] + hw, origin[1] - hw
    bl = origin[0] - hw, origin[1] - hw
    return (tl, tr, br, bl)

def midpt(a, b):
    return ((a[0] + b[0]) / 2., (a[1] + b[1]) /2.)

def center(sq):
    tl, tr, br, bl = sq
    return midpt(tl, br)

def bottom_right_center(sq):
    tl, tr, br, bl = sq
    brc =  center((center(sq), midpt(tr, br), br, midpt(bl, br)))
    print(brc)
    return brc

def top_left_center(sq):
    tl, tr, br, bl = sq
    tlc =  center((tl, midpt(tl, tr), center(sq), midpt(tl, bl)))
    print(tlc)
    return tlc

def gen_sq(origin, n, start_width=2.):
    last_ssq = None
    for i in range(0,n,2):
        last_bsq = square(origin if not last_ssq else top_left_center(last_ssq), start_width/(2**(i)))
        tl, tr, br, bl = last_bsq
        last_ssq = square(bottom_right_center(last_bsq), start_width/(2**(i+1)))
        yield i, last_bsq
        yield i+1, last_ssq


if __name__ == '__main__':
    n = int(sys.argv[1])
    print('\n'.join(str(t) for t in gen_sq((0,0), n)))
