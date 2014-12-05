examples: examples/main.c src/list.h src/map.h src/helpers.h
	gcc examples/main.c -o examples/example
	@echo "---------"
	@echo "Compilation done."
	@echo "Run the example with: ./examples/example"
	
documentation: examples/main.c src/list.h src/map.h src/helpers.h Doxyfile
	doxygen Doxyfile
