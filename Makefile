test_cep:
	gcc -DLOAD_TEST unit_tests/test_cep.c hash_tables/hash_table_cep.c hash_func.c -o test_cep
	./test_cep
	rm -f test_cep



hash_functions:
	./scripts/test_gen.sh
	echo "\n ------ MAKE ------ Tests generated\n"

	./scripts/start_func.sh
	echo "\n ------ MAKE ------ Results counted\n"

	./scripts/func_plot.sh
	echo "\n ------ MAKE ------ Plot's drew\n"

	rm -f hash_func
	echo "\n ------ MAKE ------ Hash function's testing is ended\n"

load_testing:
	./scripts/table_load.sh
	echo "\n ------ MAKE ------ Results of load factor's testing in plots/table_load.svg\n"

	rm -f table_load
	echo "\n ------ MAKE ------ Load testing is ended\n"

oper_comparison:
	./scripts/table_test.sh
	echo "\n ------ MAKE ------ Results of tests in plots/table_plot_1.svg and plots/table_plot_2.svg\n"
	
	rm -f table_test
	echo "\n ------ MAKE ------ Operation's comparison is ended\n"