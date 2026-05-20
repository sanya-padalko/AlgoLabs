import matplotlib.pyplot as plt

def draw_plots():
    files = ["2h", "cep", "kuk", "lin", "sq"]
    labels = ["Double Hashing", "Chaining", "Kukushka", "Linear", "Quadratic"]

    plt.figure(figsize=(10, 6))

    for i in range(len(files)):
        filename = files[i]
        label_name = labels[i]

        with open(f"hash_table_res/{filename}", "r") as f:
            times = list(map(float, f))

        lf_axis = [0.4 + j * 0.01 for j in range(len(times))]

        plt.plot(lf_axis, times, label=label_name, marker='.', markersize=4)

    plt.title("Hash Table LF Comparison")
    plt.xlabel("Load Factor")
    plt.ylabel("Execution Time (ms)")
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend()
    
    plt.savefig("plots/table_load.svg")

draw_plots()