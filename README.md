# C++ Bootstrap

Simple C++ Bootstrap:

* install dependencies using CPM
* build project and tests with cmake
* test using ctest

Bonus:
* provides a dev-watch, i.e. continuous compilation and testing during development
* builds compile_commands.json, for use e.g. with Neovim

## Reasoning

C++ Bootstrapping is too tedious.

I don't want to deal with conan files and package repositories, centralized approval via github issues for wanting to use a package.
I just want to download the package from e.g. github, compile and link against it.
Nothing more.

## Relevant xkcd

![Relevant xkcd](https://imgs.xkcd.com/comics/standards_2x.png "Relevant xkcd")

