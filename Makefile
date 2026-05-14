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

calc_rsq:
	gcc RSQ/fenwick.c		\
		RSQ/seg_tree.c		\
		RSQ/tester.c		\
		-o rsq_calc
	
	mkdir -p results
	./rsq_calc
	rm -f rsq_calc