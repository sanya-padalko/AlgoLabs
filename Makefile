CC = gcc
CFLAGS = -DLOAD_TEST -fsanitize=address -g -Wall

unit_test_cep:
	$(CC) $(CFLAGS) unit_tests/test_cep.c \
					hash_tables/hash_table_cep.c \
					hash_func.c \
					-o test_cep
	./test_cep
	rm -f test_cep

unit_test_2h:
	$(CC) $(CFLAGS) unit_tests/test_2h.c \
					hash_tables/hash_table_2h.c \
					hash_tables/hash_table_cep.c \
					hash_tables/hash_table_open.c \
					hash_func.c \
					-o test_2h
	./test_2h
	rm -f test_2h

unit_test_lin:
	$(CC) $(CFLAGS) unit_tests/test_lin.c \
					hash_tables/hash_table_lin.c \
					hash_tables/hash_table_cep.c \
					hash_tables/hash_table_open.c \
					hash_func.c \
					-o test_lin
	./test_lin
	rm -f test_lin

unit_test_sq:
	$(CC) $(CFLAGS) unit_tests/test_sq.c \
					hash_tables/hash_table_sq.c \
					hash_tables/hash_table_cep.c \
					hash_tables/hash_table_open.c \
					hash_func.c \
					-o test_sq
	./test_sq
	rm -f test_sq

unit_test_kuk:
	$(CC) $(CFLAGS) unit_tests/test_kuk.c \
					hash_tables/hash_table_kuk.c \
					hash_tables/hash_table_cep.c \
					hash_tables/hash_table_open.c \
					hash_func.c \
					-o test_kuk
	./test_kuk
	rm -f test_kuk

hash_functions:
	./scripts/test_gen.sh
	@echo "\n ------ MAKE ------ Tests generated\n"

	./scripts/start_func.sh
	@echo "\n ------ MAKE ------ Results counted\n"

	./scripts/func_plot.sh
	@echo "\n ------ MAKE ------ Plot's drew\n"

	rm -f hash_func
	@echo "\n ------ MAKE ------ Hash function's testing is ended\n"

load_testing:
	./scripts/table_load.sh
	@echo "\n ------ MAKE ------ Results of load factor's testing in plots/table_load.svg\n"

	rm -f table_load
	@echo "\n ------ MAKE ------ Load testing is ended\n"

oper_comparison:
	./scripts/table_test.sh
	@echo "\n ------ MAKE ------ Results of tests in plots/table_plot_1.svg and plots/table_plot_2.svg\n"
	
	rm -f table_test
	@echo "\n ------ MAKE ------ Operation's comparison is ended\n"

.PHONY: unit_test_cep unit_test_2h unit_test_lin unit_test_sq unit_test_kuk hash_functions load_testing oper_comparison