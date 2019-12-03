// Compile with the following command...
// gcc lists7.c -I /home/Tim/openssl/include -L /home/Tim/openssl/lib/ -lssl -lcrypto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <openssl/evp.h>
#include "liblists.h"

void generate_lists(struct node *ap, struct node *bp)
{
    unsigned char buffer[4];
    FILE *fp = fopen("/dev/urandom", "r");

    // randomly generate first list
    fgets(buffer, 4, fp);
    int len_a = (((int) *buffer) % 10) + 5;
    for (int i = 0; i < len_a; i++) {
        fgets(buffer, 4, fp);
        prepend(ap, ((int) *buffer) % 10);
    }

    // randomly generate intersecting list
    fgets(buffer, 4, fp);
    int len_b = (((int) *buffer) % 5) + 1;
    for (int i = 0; i < len_b; i++) {
        fgets(buffer, 4, fp);
        prepend(bp, ((int) *buffer) % 10);
    }
    print_list(bp);
    printf("\n");
    struct node *b_tail = bp;
    for (int i = 0; i < len_b; i++) {
        b_tail = b_tail->next;
    }
    fgets(buffer, 4, fp);
    int intersection =  (((int) *buffer) % (len_a - 1)) + 1;
    struct node *intersection_pointer = ap;
    for (int i = 0; i < intersection; i++) {
        intersection_pointer = intersection_pointer->next;
    }
    b_tail->next = intersection_pointer;
}

/*
void hash(const unsigned char *message, size_t message_len,
                    unsigned char **digest, unsigned int *digest_len,
                    const EVP_MD *type)
{
    EVP_MD_CTX *mdctx;
    mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, type, NULL);
    EVP_DigestUpdate(mdctx, message, message_len);
    *digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(type));
    EVP_DigestFinal_ex(mdctx, *digest, digest_len);
    EVP_MD_CTX_destroy(mdctx);
}
*/

int main(void)
{
    struct node a;
    a.next = NULL;
    struct node *ap = &a;
    struct node b;
    b.next = NULL;
    struct node *bp = &b;
    generate_lists(ap, bp);
    print_list(ap);
    printf("\n");
    print_list(bp);
    printf("\n");

    // initialize hash table for memory addresses: O(1) space with large constant vs. O(n) tree
    int hash_table[1024];

    // scan first list and add entries to hash table: O(1) time per entry, O(n) time total
    //unsigned int digest_length = 10;
    //unsigned char *digest = malloc(digest_length);
    struct node *iter = ap;
    while (iter->next != NULL) {
        // hash(iter->next, 4, &digest, &digest_length, EVP_sha256());
        printf("%d : %d\n", ((int) iter->next % 1024), (int) iter->next);
        hash_table[(int) iter->next % 1024] = (int) iter->next;
        iter = iter->next;
    }
    printf("\n");

    // scan second list and check existing hash table entries for an intersection: O(n) time total
    // on average but worst case is O(n^2) if hash table is poorly constructed and all entries collide
    // in which case using a tree for O(n log n) average and worst case total time
    iter = bp;
    while (iter->next != NULL) {
        // hash(iter->next, 4, &digest, &digest_length, EVP_sha256());
        printf("%d : %d\n", ((int) iter->next % 1024), (int) iter->next);
        if (hash_table[(int) iter->next % 1024] == (int) iter->next) {
             printf("Intersection found at %d\n", iter->next);
             return 0;
        }
        iter = iter->next;
    }
    printf("no intersection found\n");

}

