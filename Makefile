test_seg_tree:
	gcc RSQ/unit-test/seg_tree_test.c 				\
		RSQ/seg_tree.c								\
		-o test_seg_tree							\
		-DDEBUG
	./test_seg_tree
	rm -f test_seg_tree