/**
 * reference: ecies.h
 */

#ifndef _IES_H_
#define _IES_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/stack.h>

#include <ruby.h>

typedef struct {
    const EVP_CIPHER *cipher;
    const EVP_MD *md;
    size_t KDF_digest_length;
    size_t envelope_key_length;
    const EC_KEY *user_key;
} ies_ctx_t;

typedef struct {
    struct {
	size_t key;
	size_t mac;
	size_t body;
    } length;
} cryptogram_head_t;

typedef unsigned char * cryptogram_t;

void cryptogram_free(cryptogram_t *cryptogram);
unsigned char * cryptogram_key_data(const cryptogram_t *cryptogram);
unsigned char * cryptogram_mac_data(const cryptogram_t *cryptogram);
unsigned char * cryptogram_body_data(const cryptogram_t *cryptogram);
size_t cryptogram_key_length(const cryptogram_t *cryptogram);
size_t cryptogram_mac_length(const cryptogram_t *cryptogram);
size_t cryptogram_body_length(const cryptogram_t *cryptogram);
size_t cryptogram_data_sum_length(const cryptogram_t *cryptogram);
size_t cryptogram_total_length(const cryptogram_t *cryptogram);
cryptogram_t * cryptogram_alloc(size_t key, size_t mac, size_t body);

cryptogram_t * ecies_encrypt(const ies_ctx_t *ctx, const unsigned char *data, size_t length, char *error);
unsigned char * ecies_decrypt(const ies_ctx_t *ctx, const cryptogram_t *cryptogram, size_t *length, char *error);

#endif /* _IES_H_ */
