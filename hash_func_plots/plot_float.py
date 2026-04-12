import matplotlib.pyplot as plt
import numpy as np

files = ["fl_intbit.csv", "fl_bits.csv", "fl_mant.csv", "fl_exp.csv", "fl_mul_me.csv"]

for name in files:
    buckets = []
    cnt = []
    
    f = open("results/" + name, "r")
    for line in f:
        parts = line.split(',')
        buckets.append(int(parts[0]))
        cnt.append(int(parts[1]))
    f.close()
    
    var = round(np.var(cnt), 2)
    print(f"{name:15}| Variance: {var:15}")
    
    plt.figure()
    plt.bar(buckets, cnt, color='green')
    plt.xlabel("buckets")
    plt.ylabel("counts")
    title_str = f"{name}, Variance: {var}"
    plt.title(title_str)
    plt.savefig("plots/" + name + ".png")