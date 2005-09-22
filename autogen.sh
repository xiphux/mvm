#!/bin/sh

aclocal
autoheader
#libtoolize --automake --force --copy
autoconf
automake --add-missing --copy --gnu
