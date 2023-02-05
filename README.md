<p align="center">
  <img src="header.png" /><br />
  <a href="https://github.com/curiositas-books/bring-your-own-int/actions/workflows/project.yml"><img src="https://github.com/curiositas-books/bring-your-own-int/actions/workflows/project.yml/badge.svg" /></a>
  <a href="https://github.com/curiositas-books/bring-your-own-int/actions/workflows/reference.yml"><img src="https://github.com/curiositas-books/bring-your-own-int/actions/workflows/reference.yml/badge.svg" /></a><br />
  <a href="#about">About</a> |
  <a href="#get-the-book">Get Book</a> |
  <a href="#quickstart">Quickstart</a> |
  <a href="#curiositas-books">Curiositas Books</a>
</p>

## About

Supplementary repository for the book "Bring Your Own Int" that implements an integer type with arbitrary length from scratch, just using booleans as bits.

## Get the Book

The book is available in multiple digital formats, as `PDF`, `epub` or Kindle E-Book.

- [GumRoad (PDF, EPUB) - Preferred Option](https://curiositasbooks.gumroad.com/l/build-your-own-int)
- [Amazon (EPUB only)](https://www.amazon.com/dp/B0BTCFQCND)

## Quickstart

The simplest way to start coding is creating your own respository from this
template and using `Github Codespaces` for your own version of the project.
The `devcontainer` provided contains the necessary tools to build the project
and execute tests.

### Dependencies

- [catch2 2.x](https://github.com/catchorg/Catch2/tree/v2.x)
- [cmake >= 3.23.0](https://cmake.org/download/) or [meson 1.0.0](https://mesonbuild.com/Getting-meson.html)
- (optional when using `CMake`) [ninja-build](https://ninja-build.org/)

### Building in Ubuntu 22.04

In an `ubuntu:22.04` based environment (WSL2, Native Ubuntu, Docker Container, Cloud VM):
```bash
$ # Optionally: Install dependencies to build C++ software
$ sudo apt-get update
$ # 'catch2' might not be present in the repository, depending on the ubuntu
$ # version.
$ sudo apt-get install build-essential catch2 git ninja-build pkg-config python3-pip
$ sudo pip3 install meson cmake

$ cd <your-software-directory>
$ # Use your own repository path here!
$ git clone https://github.com/curiositas-books/bring-your-own-int.git
$ cd bring-your-own-int
$ meson setup build
$ meson compile -C build
$ meson test -C build

$ # Run the provided executables:
$ ./build/bin/sieve_eratosthenes 10
> <No output, Implementation is your job :)>
$ ./build/bin/collatz_chain 1230815809128370172541231203988123
> <No output, Implementation is your job :)>
```

### Building and Using the Reference Implementation

The instruction assume, that you already cloned the project as described above.
```bash
$ cd bring-your-own-int/reference-impl
$ meson setup build
$ meson compile -C build
$ meson test -C build

$ # Run the provided executables:
$ ./build/bin/sieve_eratosthenes 10
> 2
> 3
> 5
> 7
$ ./build/bin/collatz_chain 1230815809128370172541231203988123
> Chain Length for 1230815809128370172541231203988123: 1007
```

## Curiositas Books

This project is part of the [Curiositas Books Project](https://github.com/curiositas-books).

## License

This project and all its works are under [Creative Commons CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/) license.
You may do anything with the code and text provided, but please keep it open and please don't make any money from it.
The books are sold for fair prices and make no use of DRM. It takes a lot of time and effort to create these works.
I don't want to rely on an ad infested platform or publish only to DRM and device restricted media. Please do not exploit this.

<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/">Creative Commons Attribution-NonCommercial 4.0 International License</a>.
