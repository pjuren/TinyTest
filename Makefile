# TinyTest
# Copyright (C) 2014 Philip J. Uren
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
# USA

PACKAGE = TinyTest
VERSION = 0.1.0b
TARNAME = $(PACKAGE)
DISTDIR = $(TARNAME)-$(VERSION)

CXX = g++
CFLAGS = -g -Wall -fPIC -fmessage-length=50
OPTFLAGS = -O3
DEBUGFLAGS =

ifeq "$(shell uname)" "Darwin"
CFLAGS += -arch x86_64
ifeq "$(shell if [ `sysctl -n kern.osrelease | cut -d . -f 1` -ge 13 ];\
              then echo 'true'; fi)" "true"
CFLAGS += -stdlib=libstdc++
endif
endif

ifdef DEBUG
CFLAGS += $(DEBUGFLAGS)
endif

ifdef OPT
CFLAGS += $(OPTFLAGS)
endif

all : test

test: TestTinyTest
	@TMPF=`mktemp -t tmpOutXXXX`; ./TestTinyTest > $${TMPF}; \
	diff $${TMPF} regressionTestExpectedOutput.txt > /dev/null; \
	if [ $$? -ne 0 ]; then \
		echo "TinyTest build failed regression test!"; \
		exit 1;\
	fi;\
	echo "TinyTest build passed regression test!"
.PHONY: test

TestTinyTest : TinyTest.cpp TestTinyTest.cpp 
	$(CXX) $(CFLAGS) -o $@ $^ $(INCLUDEARGS) $(LIBS) 

developmentDocs:
	@doxygen doxygen.config
.PHONY: developmentDocs 

clean:
	@-rm -f TestTinyTest *.o *.so *.a *~
	@-rm -rf *.dSYM
.PHONY: clean

distclean: clean
	@rm -rf $(DISTDIR) $(DISTDIR).tar.gz
.PHONY: distclean

dist: $(DISTDIR).tar.gz

distcheck : $(DISTDIR).tar.gz
	gzip -cd $(DISTDIR).tar.gz | tar xvf -
	cd $(DISTDIR) && $(MAKE) test
	cd $(DISTDIR) && $(MAKE) clean
	rm -rf $(DISTDIR)
	@echo "*** Package $(DISTDIR).tar.gz is ready for distribution"

$(DISTDIR).tar.gz : $(DISTDIR)
	tar chof - $(DISTDIR) | gzip -9 -c > $@
	rm -rf $(DISTDIR)

$(DISTDIR) : FORCE
	# make the directory structure 
	mkdir -p $(DISTDIR)
	# copy files for distribution
	cp Makefile $(DISTDIR)
	cp README.md $(DISTDIR)
	cp LICENSE $(DISTDIR)
	cp doxygen.config $(DISTDIR) 
	cp regressionTestExpectedOutput.txt $(DISTDIR) 
	cp TinyTest.cpp $(DISTDIR)
	cp TinyTest.hpp $(DISTDIR)
	cp TestTinyTest.cpp $(DISTDIR)	
.PHONY: dist

FORCE:
	-rm $(DISTDIR).tar.gz > /dev/null 2>&1
	-rm -rf $(DISTDIR) > /dev/null 2>&1
.PHONY: FORCE

