import pandas as pd
import matplotlib.pyplot as plt
import os
import glob

# Set the path to your CSV files
csv_path = "/home/sepehr/uni/DS/paper/EfficientLinearList/timeTakenResults/remove_all/"

# Define the test categories and their corresponding file patterns
test_categories = [
    ("pushBack", "Push Back Operations"),
    ("get_after_pushBack", "Get After Push Back"),
    ("popBackAfterPushBack", "Pop Back After Push Back"),
    ("get_after_popBackAfterPushBack", "Get After Pop Back (After Push Back)"),
    ("popFrontAfterPushBack", "Pop Front After Push Back"),
    ("get_after_popFrontAfterPushBack", "Get After Pop Front (After Push Back)"),
    ("removeRandomIndicesAfterPushBack", "Remove Random Indices After Push Back"),
    (
        "get_after_removeRandomIndicesAfterPushBack",
        "Get After Remove Random Indices (After Push Back)",
    ),
    ("pushFront", "Push Front Operations"),
    ("get_after_pushFront", "Get After Push Front"),
    ("popFrontAfterPushFront", "Pop Front After Push Front"),
    ("get_after_popFrontAfterPushFront", "Get After Pop Front (After Push Front)"),
    ("popBackAfterPushFront", "Pop Back After Push Front"),
    ("get_after_popBackAfterPushFront", "Get After Pop Back (After Push Front)"),
    ("insertRandomIndices", "Insert Random Indices"),
    ("get_after_insertRandomIndices", "Get After Insert Random Indices"),
    ("removeRandomIndices", "Remove Random Indices"),
    ("get_after_removeRandomIndices", "Get After Remove Random Indices"),
    ("pushFront_pushBack", "Push Front then Push Back"),
    ("get_after_pushFront_pushBack", "Get After Push Front then Push Back"),
    ("popFront_popBack", "Pop Front then Pop Back"),
    ("get_after_popFront_popBack", "Get After Pop Front then Pop Back"),
    ("pushBack_pushFront", "Push Back then Push Front"),
    ("get_after_pushBack_pushFront", "Get After Push Back then Push Front"),
    ("popBack_popFront", "Pop Back then Pop Front"),
    ("get_after_popBack_popFront", "Get After Pop Back then Pop Front"),
]


def load_and_plot_comparison(test_name, title):
    """Load ELL and Vector CSV files and create comparison plot with three broken y-axes."""
    ell_file = f"{csv_path}{test_name}_ell_results.csv"
    vec_file = f"{csv_path}{test_name}_vec_results.csv"

    if not (os.path.exists(ell_file) and os.path.exists(vec_file)):
        print(f"Skipping {test_name}: Missing files")
        return

    try:
        ell_data = pd.read_csv(ell_file)
        vec_data = pd.read_csv(vec_file)

        # Create three subplots, sharing the same x-axis
        fig, (ax1, ax2, ax3) = plt.subplots(
            3,
            1,
            sharex=True,
            figsize=(12, 10),
            gridspec_kw={"height_ratios": [2, 1, 1]},
        )

        # Plot both datasets on all axes
        for ax in (ax1, ax2, ax3):
            ax.plot(
                ell_data["Size"],
                ell_data["Time"],
                label="EfficientLinearList",
                marker="o",
                linewidth=2,
                markersize=4,
            )
            ax.plot(
                vec_data["Size"],
                vec_data["Time"],
                label="Vector",
                marker="s",
                linewidth=2,
                markersize=4,
            )
            ax.grid(True, alpha=0.3)

        # Set y-limits for each subplot
        ax1.set_ylim(20, 150)
        ax2.set_ylim(1, 20)
        ax3.set_ylim(0, 1)

        # Hide the spines between axes
        ax1.spines["bottom"].set_visible(False)
        ax2.spines["top"].set_visible(False)
        ax2.spines["bottom"].set_visible(False)
        ax3.spines["top"].set_visible(False)
        ax1.tick_params(labeltop=False)
        ax2.tick_params(labeltop=False)
        ax3.xaxis.tick_bottom()

        # Diagonal lines to indicate the breaks
        d = 0.015
        kwargs = dict(color="k", clip_on=False)
        # Between ax1 and ax2
        ax1.plot((-d, +d), (-d, +d), transform=ax1.transAxes, **kwargs)
        ax1.plot((1 - d, 1 + d), (-d, +d), transform=ax1.transAxes, **kwargs)
        ax2.plot((-d, +d), (1 - d, 1 + d), transform=ax2.transAxes, **kwargs)
        ax2.plot((1 - d, 1 + d), (1 - d, 1 + d), transform=ax2.transAxes, **kwargs)
        # Between ax2 and ax3
        ax2.plot((-d, +d), (-d, +d), transform=ax2.transAxes, **kwargs)
        ax2.plot((1 - d, 1 + d), (-d, +d), transform=ax2.transAxes, **kwargs)
        ax3.plot((-d, +d), (1 - d, 1 + d), transform=ax3.transAxes, **kwargs)
        ax3.plot((1 - d, 1 + d), (1 - d, 1 + d), transform=ax3.transAxes, **kwargs)

        # Labels and title
        ax3.set_xlabel("Size (log scale)", fontsize=12)
        ax1.set_ylabel("Time (seconds)", fontsize=12)
        ax2.set_ylabel("Time (seconds)", fontsize=12)
        ax3.set_ylabel("Time (seconds)", fontsize=12)
        ax1.set_title(
            f"{title}\nEfficientLinearList vs Vector Performance",
            fontsize=14,
            fontweight="bold",
        )
        ax3.legend(fontsize=11)

        # X axis log scale
        ax3.set_xscale("log")

        plt.tight_layout()
        output_file = f"{csv_path}plots/{test_name}_comparison.png"
        os.makedirs(os.path.dirname(output_file), exist_ok=True)
        plt.savefig(output_file, dpi=300, bbox_inches="tight")
        # plt.show()
        print(f"Saved plot: {output_file}")

    except Exception as e:
        print(f"Error processing {test_name}: {e}")


def create_summary_plot():
    """Create a summary plot showing performance ratios"""
    plt.figure(figsize=(15, 10))

    operation_types = ["Insert", "Remove", "Get"]
    colors = ["#1f77b4", "#ff7f0e", "#2ca02c"]

    for i, op_type in enumerate(operation_types):
        plt.subplot(2, 2, i + 1)

        # Find relevant test categories for this operation type
        relevant_tests = []
        if op_type == "Insert":
            relevant_tests = [
                cat
                for cat in test_categories
                if "push" in cat[0].lower() or "insert" in cat[0].lower()
            ]
        elif op_type == "Remove":
            relevant_tests = [
                cat
                for cat in test_categories
                if "pop" in cat[0].lower() or "remove" in cat[0].lower()
            ]
        else:  # Get
            relevant_tests = [
                cat for cat in test_categories if "get_after" in cat[0].lower()
            ]

        # Plot performance ratios for relevant tests
        for test_name, title in relevant_tests[
            :5
        ]:  # Limit to first 5 to avoid overcrowding
            ell_file = f"{csv_path}{test_name}_ell_results.csv"
            vec_file = f"{csv_path}{test_name}_vec_results.csv"

            if os.path.exists(ell_file) and os.path.exists(vec_file):
                try:
                    ell_data = pd.read_csv(ell_file)
                    vec_data = pd.read_csv(vec_file)

                    # Calculate ratio (Vector time / ELL time)
                    ratio = vec_data["Time"] / ell_data["Time"]

                    plt.plot(
                        ell_data["Size"],
                        ratio,
                        label=test_name.replace("_", " ").title(),
                        marker="o",
                        linewidth=2,
                        markersize=3,
                    )
                except:
                    continue

        plt.xlabel("Size")
        plt.ylabel("Performance Ratio (Vector/ELL)")
        plt.title(f"{op_type} Operations\nVector Time / ELL Time")
        plt.legend(fontsize=8)
        plt.grid(True, alpha=0.3)
        plt.axhline(
            y=1, color="red", linestyle="--", alpha=0.7, label="Equal Performance"
        )

    plt.tight_layout()
    output_file = f"{csv_path}plots/performance_summary.png"
    plt.savefig(output_file, dpi=300, bbox_inches="tight")
    # plt.show()
    print(f"Saved summary plot: {output_file}")


# Main execution
if __name__ == "__main__":
    print("Creating comparison plots for EfficientLinearList vs Vector...")

    # Create individual comparison plots
    for test_name, title in test_categories:
        load_and_plot_comparison(test_name, title)

    # Create summary plot
    create_summary_plot()

    print("All plots have been generated!")
