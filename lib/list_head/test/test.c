#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "../debug.h"
#include "../../mem/debug.h"



void test_list_head_create()
{
    printf("\n\t%s\t\t", __func__);

    printf("\n\t\t%s 1\t\t", __func__);
    tag_t tag;
    tag = mem_tag_convert("test");
    list_head_p lh = mem_list_head_create(&tag, HD(1));
    assert(mem_list_head(lh, 1,
        tag, 1, HD(1)
    ));
    mem_list_head_free(&lh);

    printf("\n\t\t%s 2\t\t", __func__);
    tag = mem_tag_convert("");
    lh = mem_list_head_create(&tag, HD(1));
    assert(mem_list_head(lh, 1,
        tag, 1, HD(1)
    ));
    mem_list_head_free(&lh);

    printf("\n\t\t%s 3\t\t", __func__);
    tag = mem_tag_convert("abcdefghi abcdefghi abcdefghi abcdefghi abcdefghi");
    lh = mem_list_head_create(&tag, HD(1));
    assert(mem_list_head(lh, 1,
        tag, 1, HD(1)
    ));
    mem_list_head_free(&lh);

    assert(mem_mem_empty());
}

void test_list_head_pop()
{
    printf("\n\t%s\t\t", __func__);

    tag_t tag;
    tag = mem_tag_convert("test");

    list_head_p lh = mem_list_head_create(&tag, HD(1));
    free(lh->lb, list_body);

    lh->lh = LH(1);
    lh = mem_list_head_pop(lh);
    assert(lh == LH(1));

    assert(mem_mem_empty());
}

void test_list_head_insert()
{
    printf("\n\t%s\t\t", __func__);

    printf("\n\t\t%s 1\t\t", __func__);
    list_head_p lh = NULL;
    tag_t tag1 = mem_tag_convert("test 1");
    assert(mem_list_head_insert_test(&lh, HD(1), "test 1") == true);
    assert(mem_list_head(lh, 1,
        tag1, 1, HD(1)
    ));

    printf("\n\t\t%s 2\t\t", __func__);
    assert(mem_list_head_insert_test(&lh, HD(1), "test 1") == false);
    assert(mem_list_head(lh, 1,
        tag1, 1, HD(1)
    ));
    
    printf("\n\t\t%s 3\t\t", __func__);
    assert(mem_list_head_insert_test(&lh, HD(2), "test 1") == true);
    assert(mem_list_head(lh, 1,
        tag1, 2, HD(1), HD(2)
    ));

    printf("\n\t\t%s 4\t\t", __func__);
    tag_t tag2 = mem_tag_convert("test 2", NULL);
    assert(mem_list_head_insert_test(&lh, HD(3), "test 2") == true);
    assert(mem_list_head(lh, 2,
        tag1, 2, HD(1), HD(2),
        tag2, 1, HD(3)
    ));
    
    printf("\n\t\t%s 5\t\t", __func__);
    assert(mem_list_head_insert_test(&lh, HD(4), "test 1") == true);
    assert(mem_list_head(lh, 2,
        tag1, 3, HD(1), HD(2), HD(4),
        tag2, 1, HD(3)
    ));
    
    printf("\n\t\t%s 5\t\t", __func__);
    assert(mem_list_head_insert_test(&lh, HD(5), "test 2") == true);
    assert(mem_list_head(lh, 2,
        tag1, 3, HD(1), HD(2), HD(4),
        tag2, 2, HD(3), HD(5)
    ));

    mem_list_head_free(&lh);
    assert(mem_mem_empty());
}

void test_list_head_remove()
{
    printf("\n\t%s\t\t", __func__);

    tag_t tag1, tag2, tag3, tag4;
    tag1 = mem_tag_convert("test 1");
    tag2 = mem_tag_convert("test 2");
    tag3 = mem_tag_convert("test 3");
    tag4 = mem_tag_convert("test 4");

    list_head_p lh = NULL;
    mem_list_head_insert_test(&lh, HD(1), "test 1");
    mem_list_head_insert_test(&lh, HD(2), "test 1");
    mem_list_head_insert_test(&lh, HD(3), "test 2");
    mem_list_head_insert_test(&lh, HD(4), "test 2");
    mem_list_head_insert_test(&lh, HD(5), "test 3");
    mem_list_head_insert_test(&lh, HD(6), "test 4");
    assert(mem_list_head(lh, 4,
        tag1, 2, HD(1), HD(2),
        tag2, 2, HD(3), HD(4),
        tag3, 1, HD(5),
        tag4, 1, HD(6)
    ));

    printf("\n\t\t%s 1\t\t", __func__);
    assert(mem_list_head_remove(&lh, HD(7), NULL) == false);
    assert(mem_list_head(lh, 4,
        tag1, 2, HD(1), HD(2),
        tag2, 2, HD(3), HD(4),
        tag3, 1, HD(5),
        tag4, 1, HD(6)
    ));

    printf("\n\t\t%s 2\t\t", __func__);
    assert(mem_list_head_remove(&lh, HD(5), NULL) == true);
    assert(mem_list_head(lh, 3,
        tag1, 2, HD(1), HD(2),
        tag2, 2, HD(3), HD(4),
        tag4, 1, HD(6)
    ));

    printf("\n\t\t%s 3\t\t", __func__);
    assert(mem_list_head_remove(&lh, HD(6), NULL) == true);
    assert(mem_list_head(lh, 2,
        tag1, 2, HD(1), HD(2),
        tag2, 2, HD(3), HD(4)
    ));

    printf("\n\t\t%s 4\t\t", __func__);
    assert(mem_list_head_remove(&lh, HD(4), NULL) == true);
    assert(mem_list_head(lh, 2,
        tag1, 2, HD(1), HD(2),
        tag2, 1, HD(3)
    ));

    printf("\n\t\t%s 5\t\t", __func__);
    assert(mem_list_head_remove(&lh, HD(2), NULL) == true);
    assert(mem_list_head(lh, 2,
        tag1, 1, HD(1),
        tag2, 1, HD(3)
    ));

    printf("\n\t\t%s 6\t\t", __func__);
    assert(mem_list_head_remove(&lh, HD(1), NULL) == true);
    assert(mem_list_head(lh, 1,
        tag2, 1, HD(3)
    ));

    printf("\n\t\t%s 6\t\t", __func__);
    assert(mem_list_head_remove(&lh, HD(3), NULL) == true);
    assert(lh == NULL);

    assert(mem_mem_empty());
}



void test_list_head()
{
    printf("\n%s\t\t", __func__);

    test_list_head_create();
    test_list_head_pop();

    test_list_head_insert();
    test_list_head_remove();

    assert(mem_mem_empty());
}



int main() 
{
    setbuf(stdout, NULL);
    test_list_head();
    printf("\n\n\tTest successful\n\n");
    return 0;
}
