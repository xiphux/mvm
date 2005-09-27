#!/bin/sh

aclocal
autoheader
#libtoolize --automake --force --copy
automake --add-missing --copy --gnu
autoconf
