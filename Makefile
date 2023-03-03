COMPILATEUR=gcc
SOURCE=bataille.c

clean: compiler executer
	rm -f bataille core
executer: compiler
	@echo "Execution : "
	./bataille
compiler: $(SOURCE)
	@echo "Compilation : "
	$(COMPILATEUR) $(SOURCE) -o bataille
