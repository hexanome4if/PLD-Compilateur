OUTPUT=output
GENERATED=antlr4-generated
SYMBOL_TABLE=symbol-table/*.cpp
GRAMMAR=ifcc.g4
ANTLR4_CPP=antlr4-generated/*.cpp
ROOT=./*.cpp

#override with your local installation
ANTLR4_BINDIR=/usr/bin
ANTLR4_INCDIR=/shares/public/tp/ANTLR4-CPP/antlr4-runtime
ANTLR4_LIBDIR=/shares/public/tp/ANTLR4-CPP/lib

CC=clang++
CCARGS=-g -c -I $(ANTLR4_INCDIR) -I $(GENERATED) -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDARGS=-g

TARGET = ifcc

DEPS = $(ANTLR4_CPP) $(SYMBOL_TABLE) $(ROOT)

all: ifcc

ifcc: dirs antlr compile edl

edl:
	$(CC) $(LDARGS) -o $(TARGET) $(OUTPUT)/*.o $(ANTLR4_LIBDIR)/libantlr4-runtime.a

compile:
	-$(CC) $(CCARGS) $(DEPS)
	mv *.o $(OUTPUT)

antlr: $(GRAMMAR)
	$(ANTLR4_BINDIR)/antlr4 -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR)

dirs:
	mkdir -p $(OUTPUT)
	mkdir -p $(GENERATED)

clean:
	rm -rf $(OUTPUT)
	rm -rf $(GENERATED)
