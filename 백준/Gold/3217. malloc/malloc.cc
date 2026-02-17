#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>
#include <string>
using namespace std;
#define endl '\n'
#define FASTIO ios::sync_with_stdio(0), cin.tie(0)

/* ============================================================================
 * Linux Kernel Style Segregated Free List Allocator
 *
 * This is a dynamic memory allocator using segregated free lists.
 * Inspired by the Linux kernel memory management paradigm.
 * ============================================================================ */

/* --- Configuration Constants --- */
#define MAX_MEM		100000
#define NUM_BUCKETS	32
#define HASH_SIZE	(26 * 26 * 26 * 26)
#define BUCKET_SIZE	(1 << (i))	/* 2^i bytes per bucket i */

/* --- Bit manipulation helpers --- */
static inline unsigned int fls(unsigned int x)
{
	if (x == 0)
		return 0;
	return (sizeof(unsigned int) * 8) - __builtin_clz(x);
}

/* --- Data Structures --- */

/* Memory block metadata */
struct page {
	int			size;		/* Block size in bytes */
	int			allocated;	/* True if allocated, false if free */
	int			prev_addr;	/* Physical address of previous block */
	struct page		*prev;		/* Prev in doubly-linked list */
	struct page		*next;		/* Next in doubly-linked list */
};

/* Segregated allocator instance */
struct mem_allocator {
	struct page		*buckets[NUM_BUCKETS];	/* Free list buckets */
	struct page		*pages;			/* Page pool */
	int			*var_map;		/* Hash table: var name -> address */
};

/* --- Static Storage --- */
static struct page __page_pool[MAX_MEM + 5];
static int __var_hash[HASH_SIZE];
static struct mem_allocator __alloc = {
	.buckets = {},
	.pages = __page_pool,
	.var_map = __var_hash,
};

/* ============================================================================
 * Hash Function - Convert variable name to hash key (pad with 'a' if < 4 chars)
 * ============================================================================ */
static inline int hash_var(const string& var)
{
	int key = 0;
	int len = min((int)var.length(), 4);
	for (int i = 0; i < 4; i++) {
		char c = (i < len) ? var[i] : 'a';
		key = key * 26 + (c - 'a');
	}
	return key;
}

/* ============================================================================
 * Free List Management
 * ============================================================================ */

/**
 * __list_add - Insert a page into free list bucket
 * @page: page to insert
 * @bucket_idx: bucket index determined by page size
 *
 * Adds the page as the head of the free list bucket.
 */
static void __list_add(struct page *page, int bucket_idx)
{
	struct page *head = __alloc.buckets[bucket_idx];

	if (head)
		head->prev = page;

	page->next = head;
	page->prev = NULL;
	__alloc.buckets[bucket_idx] = page;
}

/**
 * __list_del - Remove a page from free list bucket
 * @page: page to remove
 * @bucket_idx: bucket index
 *
 * Unlinks the page from its doubly-linked list.
 */
static void __list_del(struct page *page, int bucket_idx)
{
	if (page->prev)
		page->prev->next = page->next;
	else
		__alloc.buckets[bucket_idx] = page->next;

	if (page->next)
		page->next->prev = page->prev;

	page->prev = page->next = NULL;
}

/* ============================================================================
 * Buddy System Style Coalescing
 * ============================================================================ */

/**
 * __page_coalesce - Merge freed page with adjacent free blocks
 * @curr_addr: physical address of freed page
 *
 * Implements 4-way coalescing:
 *  1. Both neighbors allocated: just insert to free list
 *  2. Left free, right allocated: merge with left
 *  3. Left allocated, right free: merge with right
 *  4. Both neighbors free: merge all three
 */
static void __page_coalesce(int curr_addr)
{
	struct page *curr, *prev, *next, *next_next;
	int prev_addr, next_addr, next_next_addr;
	int bucket_idx;

	curr = &__alloc.pages[curr_addr];
	curr->allocated = 0;

	prev_addr = curr->prev_addr;
	next_addr = curr_addr + curr->size;

	prev = &__alloc.pages[prev_addr];
	next = &__alloc.pages[next_addr];

	/* Case 1: Both allocated */
	if (prev->allocated && next->allocated) {
		bucket_idx = fls(curr->size) - 1;
		__list_add(curr, bucket_idx);
	}
	/* Case 2: Left free, right allocated */
	else if (!prev->allocated && next->allocated) {
		bucket_idx = fls(prev->size) - 1;
		__list_del(prev, bucket_idx);

		prev->size += curr->size;
		next->prev_addr = prev_addr;

		bucket_idx = fls(prev->size) - 1;
		__list_add(prev, bucket_idx);
	}
	/* Case 3: Left allocated, right free */
	else if (prev->allocated && !next->allocated) {
		bucket_idx = fls(next->size) - 1;
		__list_del(next, bucket_idx);

		curr->size += next->size;
		next_next_addr = next_addr + next->size;
		next_next = &__alloc.pages[next_next_addr];
		next_next->prev_addr = curr_addr;

		bucket_idx = fls(curr->size) - 1;
		__list_add(curr, bucket_idx);
	}
	/* Case 4: Both free */
	else {
		bucket_idx = fls(prev->size) - 1;
		__list_del(prev, bucket_idx);

		bucket_idx = fls(next->size) - 1;
		__list_del(next, bucket_idx);

		prev->size += curr->size + next->size;

		next_next_addr = next_addr + next->size;
		next_next = &__alloc.pages[next_next_addr];
		next_next->prev_addr = prev_addr;

		bucket_idx = fls(prev->size) - 1;
		__list_add(prev, bucket_idx);
	}
}

/* ============================================================================
 * Page Allocation and Placement
 * ============================================================================ */

/**
 * __page_place - Mark page as allocated and split if necessary
 * @addr: physical address of page
 * @req_size: requested allocation size
 *
 * Marks the page as allocated and creates a remainder block
 * if the allocated size is smaller than the free block.
 */
static void __page_place(int addr, int req_size)
{
	struct page *curr, *next, *next_next;
	int remain_size, next_addr, next_next_addr;
	int bucket_idx;

	curr = &__alloc.pages[addr];
	curr->allocated = 1;

	bucket_idx = fls(curr->size) - 1;
	__list_del(curr, bucket_idx);

	remain_size = curr->size - req_size;
	if (remain_size) {
		curr->size = req_size;
		next_addr = addr + req_size;

		next = &__alloc.pages[next_addr];
		next->size = remain_size;
		next->allocated = 0;
		next->prev_addr = addr;

		next_next_addr = next_addr + remain_size;
		next_next = &__alloc.pages[next_next_addr];
		next_next->prev_addr = next_addr;

		bucket_idx = fls(next->size) - 1;
		__list_add(next, bucket_idx);
	}
}

/**
 * __page_find_fit - Search free lists for suitable block
 * @req_size: size needed
 *
 * Returns: physical address of best-fit block, or 0 if not found
 *
 * Searches starting from the appropriate bucket and returns
 * the smallest address of a block large enough.
 */
static int __page_find_fit(int req_size)
{
	struct page *page;
	int min_addr = INT_MAX;
	int start_bucket = fls(req_size) - 1;
	int i, page_addr;

	for (i = start_bucket; i < NUM_BUCKETS; i++) {
		page = __alloc.buckets[i];
		while (page) {
			if (page->size >= req_size) {
				page_addr = page - __alloc.pages;
				min_addr = min(min_addr, page_addr);
			}
			page = page->next;
		}
	}

	return (min_addr == INT_MAX) ? 0 : min_addr;
}

/* ============================================================================
 * Allocator Core Interface
 * ============================================================================ */

/**
 * allocator_init - Initialize the allocator
 *
 * Sets up the page pool with sentinel blocks and initializes
 * all free list buckets. Creates left and right sentinels to
 * avoid boundary checks during coalescing.
 */
static void allocator_init(void)
{
	int i;

	memset(__var_hash, 0, sizeof(__var_hash));
	memset(__page_pool, 0, sizeof(__page_pool));

	for (i = 0; i < NUM_BUCKETS; i++)
		__alloc.buckets[i] = NULL;

	/* Left sentinel (allocated, size 0) */
	__page_pool[0].size = 0;
	__page_pool[0].allocated = 1;

	/* Initial free block */
	__page_pool[1].prev_addr = 0;
	__page_pool[1].size = MAX_MEM;
	__page_pool[1].allocated = 0;

	/* Right sentinel (allocated, size 0) */
	__page_pool[1 + MAX_MEM].prev_addr = 1;
	__page_pool[1 + MAX_MEM].size = 0;
	__page_pool[1 + MAX_MEM].allocated = 1;

	__list_add(&__page_pool[1], fls(__page_pool[1].size) - 1);
}

/**
 * allocator_malloc - Allocate memory for variable
 * @var: variable name (hash key)
 * @size: number of bytes to allocate
 *
 * Returns: physical address of allocated block, or 0 on failure
 *
 * Finds a suitable free block, places it, and updates the
 * variable mapping table.
 */
static int allocator_malloc(const string& var, int size)
{
	int key = hash_var(var);
	int addr;

	addr = __page_find_fit(size);
	if (addr) {
		__page_place(addr, size);
		__alloc.var_map[key] = addr;
		return addr;
	}

	__alloc.var_map[key] = 0;
	return 0;
}

/**
 * allocator_free - Free allocated memory
 * @var: variable name
 *
 * Looks up the variable, marks its page as free, clears
 * the mapping, and initiates coalescing with neighbors.
 */
static void allocator_free(const string& var)
{
	int key = hash_var(var);
	int addr;

	if (!__alloc.var_map[key])
		return;

	addr = __alloc.var_map[key];
	__alloc.var_map[key] = 0;

	__page_coalesce(addr);
}

/**
 * allocator_query - Query the address of a variable
 * @var: variable name
 *
 * Returns: physical address, or 0 if not allocated
 */
static int allocator_query(const string& var)
{
	int key = hash_var(var);
	return __alloc.var_map[key];
}

/* ============================================================================
 * Command Parser and Main Loop
 * ============================================================================ */

static void parse_and_execute(void)
{
	int n, size;
	size_t lpar, rpar, eq_pos;
	string line, var_part, func_part;
	const string malloc_str = "malloc";
	const string free_str = "free";
	const string print_str = "print";

	cin >> n;
	cin.ignore();	/* consume newline */

	for (int i = 0; i < n; i++) {
		getline(cin, line);

		/* Remove all whitespace */
		line.erase(remove(line.begin(), line.end(), ' '), line.end());

		/* Remove trailing semicolon if present */
		if (!line.empty() && line.back() == ';')
			line.pop_back();

		/* Find function part (malloc, free, print) */
		size_t malloc_pos = line.find(malloc_str);
		size_t free_pos = line.find(free_str);
		size_t print_pos = line.find(print_str);

		if (malloc_pos != string::npos) {
			/* Format: var=malloc(size); */
			eq_pos = line.find('=');
			if (eq_pos == string::npos) continue;

			var_part = line.substr(0, eq_pos);
			lpar = line.find('(');
			rpar = line.find(')');

			if (lpar == string::npos || rpar == string::npos) continue;

			size = stoi(line.substr(lpar + 1, rpar - lpar - 1));
			allocator_malloc(var_part, size);
		}
		else if (free_pos != string::npos) {
			/* Format: free(var); */
			lpar = line.find('(');
			rpar = line.find(')');

			if (lpar == string::npos || rpar == string::npos) continue;

			var_part = line.substr(lpar + 1, rpar - lpar - 1);
			allocator_free(var_part);
		}
		else if (print_pos != string::npos) {
			/* Format: print(var); */
			lpar = line.find('(');
			rpar = line.find(')');

			if (lpar == string::npos || rpar == string::npos) continue;

			var_part = line.substr(lpar + 1, rpar - lpar - 1);
			cout << allocator_query(var_part) << '\n';
		}
	}
}

/* ============================================================================
 * Unit Tests
 * ============================================================================ */

#define TEST 0

#if TEST
#define ASSERT_EQ(a, b, msg) \
	if ((a) != (b)) { \
		fprintf(stderr, "[FAIL] %s (expected %d, got %d)\n", msg, b, a); \
		return 0; \
	}

#define ASSERT_TRUE(cond, msg) \
	if (!(cond)) { \
		fprintf(stderr, "[FAIL] %s\n", msg); \
		return 0; \
	}

/* 1. 기본 할당 및 쪼개기(Splitting) 테스트 */
static int test_basic_allocation(void)
{
	allocator_init();
	allocator_malloc("aaaa", 100);
	allocator_malloc("bbbb", 200);

	ASSERT_EQ(allocator_query("aaaa"), 1, "aaaa addr mismatch");
	ASSERT_EQ(allocator_query("bbbb"), 101, "bbbb addr mismatch");

	struct page *remain = &__alloc.pages[301];
	ASSERT_TRUE(remain->allocated == 0, "Remaining block must be free");
	ASSERT_EQ(remain->size, MAX_MEM - 300, "Remaining block size incorrect");
	ASSERT_EQ(remain->prev_addr, 101, "Remaining block prev_addr incorrect");

	fprintf(stdout, "  [OK] test_basic_allocation\n");
	return 1;
}

/* 2. 가장 작은 주소 반환 보장 테스트 */
static int test_search_smallest_address(void)
{
	allocator_init();
	allocator_malloc("aaaa", 10);
	allocator_malloc("bbbb", 100);
	allocator_malloc("cccc", 10);
	allocator_malloc("dddd", 100);

	allocator_free("bbbb");
	allocator_free("dddd");

	int addr_new = allocator_malloc("eeee", 50);
	ASSERT_EQ(addr_new, 11, "Must return smallest address 11, not 121");

	fprintf(stdout, "  [OK] test_search_smallest_address\n");
	return 1;
}

/* 3. 물리적 병합 테스트 (Case 1~3) */
static int test_coalesce_case_1_to_3(void)
{
	allocator_init();
	allocator_malloc("aaaa", 10); // 1
	allocator_malloc("bbbb", 10); // 11
	allocator_malloc("cccc", 10); // 21
	allocator_malloc("dddd", 10); // 31 

	// Case 1: 양쪽 할당 상태 (bbbb 해제)
	allocator_free("bbbb");
	ASSERT_TRUE(__alloc.pages[11].allocated == 0, "bbbb should be free");
	ASSERT_EQ(__alloc.pages[11].size, 10, "bbbb size must be exactly 10");

	// Case 3: 뒤가 Free 상태 (aaaa 해제 -> aaaa와 bbbb 병합)
	allocator_free("aaaa");
	ASSERT_EQ(__alloc.pages[1].size, 20, "aaaa and bbbb must be merged");

	allocator_init();
	allocator_malloc("aaaa", 10); // 1
	allocator_malloc("bbbb", 10); // 11
	allocator_malloc("cccc", 10); // 21
	allocator_malloc("dddd", 10); // 31 

	// Case 2: 앞이 Free 상태 (bbbb 해제 후 cccc 해제 -> bbbb와 cccc 병합)
	allocator_free("bbbb");
	allocator_free("cccc");
	ASSERT_EQ(__alloc.pages[11].size, 20, "bbbb and cccc must be merged");

	fprintf(stdout, "  [OK] test_coalesce_case_1_to_3\n");
	return 1;
}

/* 4. Case 4: 양쪽 모두 Free일 때 유령 블록 테스트 */
static int test_coalesce_case_4_ghost_block(void)
{
	allocator_init();
	allocator_malloc("aaaa", 10); // 1
	allocator_malloc("bbbb", 10); // 11
	allocator_malloc("cccc", 10); // 21
	allocator_malloc("dddd", 10); // 31 

	allocator_free("aaaa");
	allocator_free("cccc");

	// bbbb를 해제하면 앞(aaaa)과 뒤(cccc)가 모두 Free. 유령 블록 테스트.
	allocator_free("bbbb");

	ASSERT_EQ(__alloc.pages[1].size, 30, "Merge aaaa, bbbb, cccc correctly");

	int addr = allocator_malloc("eeee", 20);
	ASSERT_EQ(addr, 1, "Must allocate safely from the merged block");

	fprintf(stdout, "  [OK] test_coalesce_case_4_ghost_block\n");
	return 1;
}

/* 5. Sentinel 경계 갱신 누락 테스트 */
static int test_boundary_sentinel_update(void)
{
	allocator_init();
	int addr_last = allocator_malloc("aaaa", MAX_MEM);
	ASSERT_EQ(addr_last, 1, "Should allocate entire memory");

	allocator_free("aaaa");

	ASSERT_EQ(__alloc.pages[MAX_MEM + 1].prev_addr, 1, "Right sentinel prev_addr must be 1");

	fprintf(stdout, "  [OK] test_boundary_sentinel_update\n");
	return 1;
}

/* 6. 메모리 부족(OOM) 시 예외 처리 테스트 */
static int test_malloc_fail_handling(void)
{
	allocator_init();
	allocator_malloc("aaaa", 60000);

	int addr_fail = allocator_malloc("bbbb", 50000);
	ASSERT_EQ(addr_fail, 0, "Should fail to allocate 50000");
	ASSERT_EQ(allocator_query("bbbb"), 0, "Hash of failed alloc must be 0");

	// aaaa 덮어쓰기: 실패했을 때 aaaa도 0으로 날아가야 함
	int addr_override = allocator_malloc("aaaa", 50000);
	ASSERT_EQ(addr_override, 0, "Should overwrite 'aaaa' with 0 on failure");
	ASSERT_EQ(allocator_query("aaaa"), 0, "Hash of overwritten var must be 0");

	fprintf(stdout, "  [OK] test_malloc_fail_handling\n");
	return 1;
}

static void run_tests(void)
{
	fprintf(stdout, "[TEST] Starting all Allocator Tests\n");
	fprintf(stdout, "---------------------------------\n");

	int passed = 0;
	int total = 6;

	if (test_basic_allocation()) passed++;
	if (test_search_smallest_address()) passed++;
	if (test_coalesce_case_1_to_3()) passed++;
	if (test_coalesce_case_4_ghost_block()) passed++;
	if (test_boundary_sentinel_update()) passed++;
	if (test_malloc_fail_handling()) passed++;

	fprintf(stdout, "---------------------------------\n");
	if (passed == total)
		fprintf(stdout, "[RESULT] All %d tests passed successfully!\n", total);
	else
		fprintf(stdout, "[RESULT] %d/%d tests passed.\n", passed, total);
}

#endif /* TEST */
int main(void)
{
    FASTIO;
#if TEST
	run_tests();
#else
	allocator_init();
	parse_and_execute();
#endif
	return 0;
}