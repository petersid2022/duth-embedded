#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np

plt.style.use("seaborn-v0_8-whitegrid")

techniques = [
    "Default",
    "Χρήση memcpy",
    "Loop Collapsing",
    "Loop Unrolling",
    "Loop tiling",
    "CPU Registers",
    "Lookup table",
]
parameters = ["Instructions", "Core Cycles", "S-Cycles", "N-Cycles", "I-Cycles"]
data = [
    [320481178, 635583431, 418381257, 164600466, 52601708],  # Default
    [318906536, 633086251, 417314031, 163447277, 52324943],  # Χρήση memcpy
    [321209183, 636311436, 419109262, 164600466, 52601708],  # Loop Collapsing
    [344656616, 611510407, 418524011, 140476233, 52510163],  # Loop Unrolling
    [434536556, 758997515, 537110039, 169279815, 52607661],  # Loop tiling
    [342889121, 609742370, 417724929, 129784044, 52233397],  # Global CPU Registers
    [343068334, 608002829, 416944765, 138824667, 52233397],  # Lookup tablee
]
data = np.array(data)

plt.figure(figsize=(20, 10), dpi=300)

x = np.arange(len(techniques))
bar_width = 0.15

colors = plt.cm.Set2(np.linspace(0, 1, 5))

for i, parameter in enumerate(parameters):
    plt.bar(
        x + i * bar_width,
        data[:, i],
        width=bar_width,
        label=parameter,
        color=colors[i],
        edgecolor="black",
        linewidth=1,
        alpha=0.7,
    )

    # Annotations
    for j, value in enumerate(data[:, i]):
        plt.text(
            x[j] + i * bar_width,
            value,
            f"{value:,}",
            ha="center",
            va="bottom",
            fontsize=10,
            fontweight="bold",
        )

# Formatting
plt.ylabel("Cycle Count", fontsize=15, fontweight="bold")

# X-axis setup
plt.xticks(
    x + bar_width * (len(parameters) / 2 - 0.5),  # Adjusted for symmetry
    techniques,
    ha="center",
    fontsize=15,
)

# Legend
plt.legend(title="Performance Parameters", loc="best", fontsize=15, title_fontsize=15)

# Adjust layout
plt.tight_layout()

# Save high-resolution image
plt.savefig("optimized_comparison.png", dpi=300, bbox_inches="tight")
