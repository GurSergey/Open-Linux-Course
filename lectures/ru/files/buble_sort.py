
# taskset -p -c 3 <pid of bash>
# nice -5 python buble_sort.py &  nice -20 python buble_sort.py &
from random import randint
import time
start_time = time.time()
 
N = 10000
a = []
for i in range(N):
    a.append(randint(1, 999999))
 
 
for i in range(N-1):
    for j in range(N-i-1):
        if a[j] > a[j+1]:
            a[j], a[j+1] = a[j+1], a[j]
 
print("--- %s seconds ---" % (time.time() - start_time))
