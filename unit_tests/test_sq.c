#include "../hash_tables/hash_table_sq.h"

#define TESTS \
	ADD(test_insert_search) \
	ADD(test_remove) \
	ADD(test_collisions)

#define CTEST_IMPLEMENTATION
#include "../ctest.h"

TEST(test_insert_search,
	OpenTable* table = OpenTableCtor(4, 0.75f);

	for (int i = 0; i < 10000; ++i)
		SqInsert(table, i);
	
	for (int i = 0; i < 20000; ++i) {
		bool predict_res = (i < 10000);
		ASSERT_EQ_MSG(predict_res, SqSearch(table, i), "Searching of key %d went wrong", i);
	}

	OpenTableDtor(table);
)

TEST(test_remove,
	OpenTable* table = OpenTableCtor(4, 0.75f);
	
	for (int i = 0; i < 10000; ++i)
		SqInsert(table, i);
	
	for (int i = 0; i < 10000; i += 2)
		SqRemove(table, i);

	for (int i = 0; i < 10000; ++i) {
		if (i % 2 == 0)
			ASSERT_EQ_MSG(false, SqSearch(table, i), "Key %d should be removed", i);
		else 
			ASSERT_EQ_MSG(true, SqSearch(table, i), "Key %d shouldn't be removed", i);
	}
	
	OpenTableDtor(table);
)

TEST(test_collisions,
	OpenTable* table = OpenTableCtor(4, 0.75f);
	
	for (int i = 0; i < 10000; ++i)
		SqInsert(table, i);
	
	for (int i = 0; i < 10000; ++i)
		ASSERT_EQ_MSG(true, SqSearch(table, i), "There is collision on key %d", i);

	OpenTableDtor(table);
)

RUN_TESTS();