
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
	@TMPF=`mktemp -t tmpOut`; ./TestTinyTest > $${TMPF}; \
	diff $${TMPF} regressionTestExpectedOutput.txt > /dev/null; \
	if [ $$? -ne 0 ]; then \
		echo "TinyTest build failed regression test!"; \
		exit 1;\
	fi;\
	echo "TinyTest build passed regression test!"
.PHONY: test

TestTinyTest : TinyTest.cpp TestTinyTest.cpp 
	$(CXX) $(CFLAGS) -o $@ $^ $(INCLUDEARGS) $(LIBS) 

clean:
	@-rm -f TestTinyTest *.o *.so *.a *~
	@-rm -rf *.dSYM
.PHONY: clean



	