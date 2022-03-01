# Contributing

There are several ways to contribute to Eigency!
- Submit issue/bug reports [here](https://github.com/wouterboomsma/eigency/issues),
or try to fix the problem yourself and then [submit a pull request](https://github.com/wouterboomsma/eigency/pulls).
- Request features or ask questions [here](https://github.com/wouterboomsma/eigency/issues).
- Browse [the source code](https://github.com/wouterboomsma/eigency) and see if anything looks out of place - let us know!

## Getting Started

The recommended operating system for Eigency development is `Linux`, preferably a modern version of `Ubuntu`.
The source code can be edited on other operating systems, such as `Windows`, but `GCC` is required to build Eigency.

Clone the upstream Git repository to your local computer:
```bash
git clone git@github.com:wouterboomsma/eigency.git
```

Or, clone your own fork.

## Building

Eigency uses the modern [PEP 517](https://www.python.org/dev/peps/pep-0517/) build system for consistent and reproducible source distribution packages.
[PyPA build](https://github.com/pypa/build) is a simple reference implementation of this standardized build system.

```bash
user@host:~/eigency$ python3 -m venv venv
user@host:~/eigency$ source ./venv/bin/activate
(venv) user@host:~/eigency$ python -m pip install --upgrade pip
...
(venv) user@host:~/eigency$ python -m pip install --upgrade build
...
(venv) user@host:~/eigency$ python -m build --sdist
...
Successfully built eigency-x.xx.tar.gz
```

It is still possible to invoke the legacy `setup.py` script directly:
```bash
python setup.py sdist
```

However, this requires installing all the build dependencies into the virtual environment before running `setup.py`.
Doing it this way also doesn't guarantee that the builds are consistent and reproducible
since it uses a non-isolated virtual environment that the user manages, or no virtual environment at all - **yikes!**

## Installing from source

Pip can be used to directly install the project into your virtual environment:
```bash
python -m pip install .
```

### For development

Pip can also install the project in "editable" mode:
```bash
python -m pip install -e .
```

Although, this is largely untested for this project due to the Cython compilation step.

## Linting

Before you submit that pull request on GitHub, use `pre-commit` to run the automated linting and code style tools.

Install `pre-commit` to your virtual environment:
```bash
(venv) user@host:~/eigency$ python -m pip install pre-commit
```

Run `pre-commit`:
```bash
(venv) user@host:~/eigency$ pre-commit run --all-files
```

The first run will take longer than subsequent runs as it sets up the isolated virtual environments for each configured tool.

If all checks pass, then you're ready to [submit that pull request](https://github.com/wouterboomsma/eigency/pulls)!

**Thank you for your contribution!**

## Release Distribution
> _For maintainers only_

[Twine](https://twine.readthedocs.io/en/stable/) is used to upload package releases to PyPi.

Install Twine:
```bash
(venv) user@host:~/eigency$ python -m pip install twine
```

Follow [Building](#building) instructions to build the source distribution (sdist) `.tar.gz` file.

Then, upload the source distribution using Twine:
```bash
(venv) user@host:~/eigency$ twine upload dist/eigency-x.xx.tar.gz
```
