#include "../hash_tables/hash_table_cep.h"

#define TESTS \
	ADD(test_insert_search) \
	ADD(test_remove) \
	ADD(test_collisions)

#define CTEST_IMPLEMENTATION
#include "../ctest.h"

TEST(test_insert_search,
	CepTable* table = CepTableCtor(4, 0.75f);

	for (int i = 0; i < 10000; ++i)
		CepInsert(table, i);
	
	for (int i = 0; i < 20000; ++i) {
		bool predict_res = (i < 10000);
		ASSERT_EQ_MSG(predict_res, CepSearch(table, i), "Searching of key %d went wrong", i);
	}

	CepTableDtor(table);
)

TEST(test_remove,
	CepTable* table = CepTableCtor(4, 0.75f);
	
	for (int i = 0; i < 10000; ++i)
		CepInsert(table, i);
	
	for (int i = 0; i < 10000; i += 2)
		CepRemove(table, i);

	for (int i = 0; i < 10000; ++i) {
		if (i % 2 == 0)
			ASSERT_EQ_MSG(false, CepSearch(table, i), "Key %d should be removed", i);
		else 
			ASSERT_EQ_MSG(true, CepSearch(table, i), "Key %d shouldn't be removed", i);
	}
	
	CepTableDtor(table);
)

TEST(test_collisions,
	CepTable* table = CepTableCtor(4, 0.75f);
	
	for (int i = 0; i < 10000; ++i)
		CepInsert(table, i);
	
	for (int i = 0; i < 10000; ++i)
		ASSERT_EQ_MSG(true, CepSearch(table, i), "There is collision on key %d", i);

	CepTableDtor(table);
)

RUN_TESTS();