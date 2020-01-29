// Compile with the following command...
// gcc sha3demo.c -o sha3demo.exe -I /home/Tim/openssl/include -L /home/Tim/openssl/lib/ -lssl -lcrypto

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

void digest_message(const unsigned char *message, size_t message_len,
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

char *get_hex(unsigned char *bin_md, unsigned char *hex_md, unsigned int md_len)
{
    memset(hex_md, 0, md_len);
    char *temp = malloc(2);
    for (int i = 0; i < md_len; i++) {
        sprintf(temp, "%02X", bin_md[i]);
        strncat(hex_md, temp, 2);
    }
    return hex_md;
}

int main(void)
{
    unsigned char *message = malloc(2048);
    unsigned int digest_length = 32;
    unsigned char *digest = malloc(digest_length);
    unsigned char *digest_hex = malloc(2 * digest_length + 1);
    printf("...enter a message to hash...\n");
    fgets(message, 2048, stdin);
    message[strcspn(message, "\n")] = 0;

    digest_message(message, strlen(message), &digest, &digest_length, EVP_sha256());
    printf("SHA-2 hash: %s\n", get_hex(digest, digest_hex, digest_length));

    digest_message(message, strlen(message), &digest, &digest_length, EVP_sha3_256());
    printf("SHA-3 hash: %s\n", get_hex(digest, digest_hex, digest_length));
}
