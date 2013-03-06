/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */
#include "tomcrypt.h"

/**
  @file crypt_sizes.c

  Provide various sizes to dynamic languages
  like Python - Larry Bugbee, February 2013
*/


typedef struct {
    const char *name;
    const long size;
} crypt_size;

crypt_size _crypt_sizes[] = {
    // hash state sizes
    {"hash_descriptor_struct_size",   sizeof(struct ltc_hash_descriptor)},
    {"hash_state_union_size",         sizeof(hash_state)},
    {"sha256_state_struct_size",      sizeof(struct sha256_state)},
    {"sha512_state_struct_size",      sizeof(struct sha512_state)},
    {"whirlpool_state_struct_size",   sizeof(struct whirlpool_state)},
    {"md2_state_struct_size",         sizeof(struct md2_state)},
    {"md4_state_struct_size",         sizeof(struct md4_state)},
    {"md5_state_struct_size",         sizeof(struct md5_state)},
    {"rmd128_state_struct_size",      sizeof(struct rmd128_state)},
    {"rmd160_state_struct_size",      sizeof(struct rmd160_state)},
    {"rmd256_state_struct_size",      sizeof(struct rmd256_state)},
    {"rmd320_state_struct_size",      sizeof(struct rmd320_state)},
    {"sha1_state_struct_size",        sizeof(struct sha1_state)},
    {"tiger_state_struct_size",       sizeof(struct tiger_state)},

    // block cipher key sizes
    {"cipher_descriptor_struct_size", sizeof(struct ltc_cipher_descriptor)},
    {"symmetric_key_union_size",      sizeof(symmetric_key)},
    {"anubis_key_struct_size",        sizeof(struct anubis_key)},
    {"blowfish_key_struct_size",      sizeof(struct blowfish_key)},
    {"cast5_key_struct_size",         sizeof(struct cast5_key)},
    {"des_key_struct_size",           sizeof(struct des_key)},
    {"des3_key_struct_size",          sizeof(struct des3_key)},
    {"kasumi_key_struct_size",        sizeof(struct kasumi_key)},
    {"khazad_key_struct_size",        sizeof(struct khazad_key)},
    {"kseed_key_struct_size",         sizeof(struct kseed_key)},
//    {"multi2_key_struct_size",        sizeof(struct multi2_key)},
    {"noekeon_key_struct_size",       sizeof(struct noekeon_key)},
    {"rc2_key_struct_size",           sizeof(struct rc2_key)},
    {"rc5_key_struct_size",           sizeof(struct rc5_key)},
    {"rc6_key_struct_size",           sizeof(struct rc6_key)},
    {"skipjack_key_struct_size",      sizeof(struct skipjack_key)},
    {"xtea_key_struct_size",          sizeof(struct xtea_key)},
    {"rijndael_key_struct_size",      sizeof(struct rijndael_key)},
    {"safer_key_struct_size",         sizeof(struct safer_key)},
    {"saferp_key_struct_size",        sizeof(struct saferp_key)},
    {"twofish_key_struct_size",       sizeof(struct twofish_key)},

    // mode sizes
    {"symmetric_CBC_struct_size",     sizeof(symmetric_CBC)},
    {"symmetric_CFB_struct_size",     sizeof(symmetric_CFB)},
    {"symmetric_CTR_struct_size",     sizeof(symmetric_CTR)},
    {"symmetric_ECB_struct_size",     sizeof(symmetric_ECB)},
    {"symmetric_F8_struct_size",      sizeof(symmetric_F8)},
    {"symmetric_LRW_struct_size",     sizeof(symmetric_LRW)},
    {"symmetric_OFB_struct_size",     sizeof(symmetric_OFB)},

    // MAC sizes
    // no states for ccm, lrw  ???
    {"chc_state_struct_size",         sizeof(struct chc_state)},
    {"f9_state_struct_size",          sizeof(f9_state)},
    {"hmac_state_struct_size",        sizeof(hmac_state)},
    {"omac_state_struct_size",        sizeof(omac_state)},
    {"pelican_state_struct_size",     sizeof(pelican_state)},
    {"pmac_state_struct_size",        sizeof(pmac_state)},
    {"xcbc_state_struct_size",        sizeof(xcbc_state)},
    {"ocb_state_struct_size",         sizeof(ocb_state)},
    {"gcm_state_struct_size",         sizeof(gcm_state)},
    {"eax_state_struct_size",         sizeof(eax_state)},

    // asymmetric keys
    {"rsa_key_struct_size",           sizeof(rsa_key)},
    {"dsa_key_struct_size",           sizeof(dsa_key)},
    {"ecc_set_struct_size",           sizeof(ltc_ecc_set_type)},
    {"ecc_key_struct_size",           sizeof(ecc_key)},
    {"ecc_point_struct_size",         sizeof(ecc_point)},
//    {"katja_key_struct_size",         sizeof(katja_key)},

    // prng state sizes
    {"prng_descriptor_struct_size",   sizeof(struct ltc_prng_descriptor)},
    {"prng_state_union_size",         sizeof(prng_state)},
    {"fortuna_prng_struct_size",      sizeof(struct fortuna_prng)},
    {"rc4_prng_struct_size",          sizeof(struct rc4_prng)},
    {"sober128_prng_struct_size",     sizeof(struct sober128_prng)},
    {"yarrow_prng_struct_size",       sizeof(struct yarrow_prng)},
    // sprng has no state as it uses other potentially available sources
    // like /dev/random.  See Developers Guide for more info.
};


int _crypt_add_up_sizes(int _crypt_sizes_len) {
    int i, total_len = 0;
    char number[10];
    for (i=0; i<_crypt_sizes_len; i++) {
        total_len += strlen(_crypt_sizes[i].name) + 1;
        // the +1 is for the commas
        sprintf(number,"%lu",_crypt_sizes[i].size);
        total_len += strlen(number) + 1;
        // the +1 is for newlines (and ending NULL)
    }
    return total_len;
};

int crypt_list_all_sizes(char *names_list, long *str_len) {
    int i;
    char number[10];
    int number_len;
    int _crypt_sizes_len = sizeof(_crypt_sizes) / sizeof(crypt_size);
    if (names_list == NULL) {
        *str_len = _crypt_add_up_sizes(_crypt_sizes_len);
    } else {
        if (*str_len < _crypt_add_up_sizes(_crypt_sizes_len)) {
            return 1;
        }
        char *ptr = names_list;
        for (i=0; i<_crypt_sizes_len; i++) {
            strcpy(ptr, _crypt_sizes[i].name);
            ptr += strlen(_crypt_sizes[i].name);
            strcpy(ptr, ",");
            ptr += 1;

            number_len = sprintf(number,"%lu",_crypt_sizes[i].size);
            strcpy(ptr, number);
            ptr += number_len;
            strcpy(ptr, "\n");
            ptr += 1;
        }
        ptr -= 1;       // to remove the trailing comma
        *ptr = 0;
    }
    return 0;
}

int crypt_get_size(const char* namein, long *sizeout) {
    int i;
    int _crypt_sizes_len = sizeof(_crypt_sizes) / sizeof(crypt_size);
    for (i=0; i<_crypt_sizes_len; i++) {
        if (strcmp(_crypt_sizes[i].name, namein) == 0) {
            *sizeout = _crypt_sizes[i].size;
            return 0;
        }
    }
    return 1;
}


/* $Source:  $ */
/* $Revision:  $ */
/* $Date:  $ */
