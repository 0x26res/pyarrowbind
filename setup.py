import pathlib

from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

__version__ = "0.1.2"

ROOT = pathlib.Path(__file__).parent
README = (ROOT / "README.md").read_text()

def get_extension():
    return Pybind11Extension(
        name="_protobind",
        sources=[
            str(ROOT / "bindings.cpp"),
        ],
        define_macros=[("VERSION_INFO", __version__)],
        cxx_std=11,
        extra_compile_args=["-D_GLIBCXX_USE_CXX11_ABI=0"],
        include_dirs=[
            "/usr/include"
        ],
        libraries=["protobuf", "protobuf-lite"],
        library_dirs=["/usr/lib/x86_64-linux-gnu"],
    )


ext_modules = [get_extension()]
setup(
    name="protobind",
    description="FOO BAR",
    long_description=README,
    long_description_content_type="text/markdown",
    url="https://github.com/0x26res/pyarrowbind",
    author="0x26res",
    author_email="0x26res@gmail.com",
    version=__version__,
    classifiers=[
        "License :: OSI Approved :: Apache Software License",
        "Development Status :: 4 - Beta",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: C++",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Natural Language :: English",
    ],
    packages=["protobind"],
    ext_modules=ext_modules,
    package_dir={"": "./"},
    install_requires=[
        "setuptools>=42",
        "wheel",
        "pybind11>=2.9.0",
    ],
    extras_require={"test": ["pytest", "pandas", "tabulate"]},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.9",
)
