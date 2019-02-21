def rec(a, b, ll, size):
    ret = []
    '''for i,e in enumerate(a):
        for j,f in enumerate(b):
            l = [e+f]
            new_l = rec(a[i+1:], b[:j]+b[j+1:], ll, size)
            if not new_l:
                ret.append(l)
            for k in new_l:
                l_k = l + k
                ret.append(l_k)
                if len(l_k) == size:
                    ll.append(l_k)
    return ret
    '''
    for i in range(len(a)):
        for j in range(len(b)):
            l = [e+f]
            new_l = rec(a[i+1:], b[:j]+b[j+1:], ll, size)
            if not new_l:
                ret.append(l)
            for k in new_l:
                l_k = l + k
                ret.append(l_k)
                if len(l_k) == size:
                    ll.append(l_k)
    return ret


a = ['5,9', '7,8', '7,5', '6,2', '3,3', '2,5', '3,8']
b = ['-d1', '-d2', '-d3', '-d4', '-d5']
ll = []
rec(a, b, ll, min(len(a), len(b)))
print(ll)
