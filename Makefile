
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
	./TestTinyTest
.PHONY: test

TestTinyTest : TinyTest.cpp TestTinyTest.cpp 
	$(CXX) $(CFLAGS) -o $@ $^ $(INCLUDEARGS) $(LIBS) 

clean:
	@-rm -f TestTinyTest *.o *.so *.a *~
	@-rm -rf *.dSYM
.PHONY: clean



	