import img2pdf
import os


def merge_png_to_pdf(input_dir, output_pdf):
    try:
        # Get list of all PNG files in the input directory
        png_files = [
            os.path.join(input_dir, f)
            for f in os.listdir(input_dir)
            if f.lower().endswith(".png")
        ]

        # Check if any PNG files were found
        if not png_files:
            print(f"No PNG files found in {input_dir}")
            return

        # Sort files by creation time
        png_files.sort(key=lambda x: os.path.getctime(x))

        # Merge PNG files into a single PDF
        with open(output_pdf, "wb") as f:
            f.write(
                img2pdf.convert([os.path.abspath(png_file) for png_file in png_files])
            )
        print(f"PDF created successfully: {output_pdf} with {len(png_files)} images")
    except Exception as e:
        print(f"Error: {e}")


# Example usage
if __name__ == "__main__":
    # Specify the directory containing PNG files
    input_dir = "/home/sepehr/uni/DS/paper/EfficientList/doc/remove/"  # Replace with your folder path
    output_pdf = "Remove_random_indices.pdf"  # Replace with desired output PDF path

    # Check if the input directory exists
    if not os.path.isdir(input_dir):
        print(f"Error: Directory {input_dir} does not exist")
    else:
        merge_png_to_pdf(input_dir, output_pdf)
