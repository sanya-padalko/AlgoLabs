test_seg_tree:
	gcc RSQ/unit-test/seg_tree_test.c 				\
		RSQ/seg_tree.c								\
		-o test_seg_tree							\
		-DDEBUG
	./test_seg_tree
	rm -f test_seg_tree

test_fenwick:
	gcc RSQ/unit-test/fenwick_test.c 				\
		RSQ/fenwick.c								\
		-o test_fenwick								\
		-DDEBUG
	./test_fenwick
	rm -f test_fenwick

test_sparse:
	gcc RMQ/unit-test/sparse_test.c 				\
		RMQ/sparse_table.c							\
		-o test_sparse								\
		-DDEBUG
	./test_sparse
	rm -f test_sparse

calc_rsq:
	gcc RSQ/fenwick.c		\
		RSQ/seg_tree.c		\
		RSQ/tester.c		\
		-o rsq_calc
	
	mkdir -p results
	./rsq_calc
	rm -f rsq_calc

calc_rmq:
	gcc RMQ/sparse_table.c	\
		RMQ/tester.c		\
		-o rmq_calc
	
	mkdir -p results
	./rmq_calc
	rm -f rmq_calc