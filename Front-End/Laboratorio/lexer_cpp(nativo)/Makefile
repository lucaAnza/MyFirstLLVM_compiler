OBJ = main.o lexer.o
CXXFLAGS=-Wall
NOME_FILE_EXE = Lexer_exe

$(NOME_FILE_EXE): $(OBJ)
	g++ -o $(NOME_FILE_EXE) $(OBJ)

.PHONY: clean cleanall
clean:
	rm -f *.o
cleanall:
	rm -f $(NOME_FILE_EXE) *.o
