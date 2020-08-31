#--Vars--

CC=g++ # compilador, troque para gcc se preferir utilizar C
CFLAGS=-Wall -Wextra -std=c++11# compiler flags, troque o que quiser, exceto bibliotecas externas
EXEC=./tp1 # nome do executavel que sera gerado
TMPOUT=tp1.testresult

#--Regras--

$(EXEC): main.cpp auxiliary_functions.o graph_functions.o movement_functions.o
	$(CC) $(CFLAGS) main.cpp auxiliary_functions.o graph_functions.o movement_functions.o -o $(EXEC)

main.o: main.cpp header.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

auxiliary_functions.o: auxiliary_functions.cpp header.h
	$(CC) $(CFLAGS) -c auxiliary_functions.cpp -o auxiliary_functions.o

graph_functions.o: graph_functions.cpp header.h
	$(CC) $(CFLAGS) -c graph_functions.cpp -o graph_functions.o

movement_functions.o: movement_functions.cpp header.h
	$(CC) $(CFLAGS) -c movement_functions.cpp -o movement_functions.o

test: $(EXEC)
	@bash run_tests.sh $(EXEC) $(TMPOUT)

clean: # remove todos os arquivos temporarios que forem gerados pela compilacao
	rm -rf foo.o

# === END =====