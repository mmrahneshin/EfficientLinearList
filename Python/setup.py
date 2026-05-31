from setuptools import setup, Extension

efficient_list_module = Extension(
    name="efficient_list",
    sources=[
        "efficient_list_module.c",  # Python wrapper (renamed for consistency)
        "efficient_list.c",  # Core logic
        "indexed_PPS23RB_binaryTree.c",
        "indexed_PPS23RB_binaryTree_node.c",
    ],
    include_dirs=["."],
    extra_compile_args=["-g", "-O0"],  # Enable debug symbols, disable optimizations
)

setup(
    name="efficient_list",
    version="0.1",
    description="Efficient list using a red-black tree",
    ext_modules=[efficient_list_module],
)
