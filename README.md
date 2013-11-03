What is this?
=============

This is a simple console tool written in C, which extracts highlighted text from PDF file.

Installation
============

Be sure that you have all needed packages installed. You need `gcc` compiler, and package `poppler` (Gentoo) or `libpoppler-glib-dev` (Debian). I recommend the use of `git` utility to clone the repo:

```sh
git clone git://github.com/vonavi/pdf-show-highlights.git
cd pdf-show-highlights
```

Otherwise download source files manually.

To make the `pdf-show-highlights` executable, run

```sh
make
```

Usage
=====

To extract highlighted text from `sample.pdf`, run

```sh
./pdf-show-highlights sample.pdf
```
