OUTPUT=output
GENERATED=antlr4-generated

ASSEMBLY_TRANS=assembly-translation/*.cpp
AST=ast/*.cpp
IR=ir/*.cpp
IR_GEN=ir/generator/*.cpp
IR_GEN_EXPR=ir/generator/expressions/*.cpp
SYMBOLS_MANAGEMENT=symbols-management/*.cpp
VISITORS=visitors/*.cpp
ANTLR4_CPP=antlr4-generated/*.cpp
ROOT=./*.cpp

GRAMMAR=ifcc.g4

#override with your local installation
ANTLR4_BINDIR=/usr/bin
ANTLR4_INCDIR=/shares/public/tp/ANTLR4-CPP/antlr4-runtime
ANTLR4_LIBDIR=/shares/public/tp/ANTLR4-CPP/lib

CC=clang++
CCARGS=-g -c -I $(ANTLR4_INCDIR) -I $(GENERATED) -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDARGS=-g

TARGET = ifcc

DEPS = $(ANTLR4_CPP) $(ASSEMBLY_TRANS) $(AST) $(IR) $(IR_GEN) $(IR_GEN_EXPR) $(SYMBOLS_MANAGEMENT) $(VISITORS) $(ROOT)

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
