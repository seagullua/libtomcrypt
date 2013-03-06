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
  @file crypt_constants.c

  Provide various constants to dynamic languages
  like Python - Larry Bugbee, February 2013
*/


typedef struct {
    const char *name;
    const long value;
} crypt_constant;

crypt_constant _crypt_constants[] = {
    {"CTR_COUNTER_LITTLE_ENDIAN", CTR_COUNTER_LITTLE_ENDIAN},
    {"CTR_COUNTER_BIG_ENDIAN",    CTR_COUNTER_BIG_ENDIAN},
    {"CTR_RFC3686",               LTC_CTR_RFC3686},

    {"PK_PUBLIC",                 PK_PUBLIC},
    {"PK_PRIVATE",                PK_PRIVATE},
    {"MIN_RSA_SIZE",              MIN_RSA_SIZE},
    {"MAX_RSA_SIZE",              MAX_RSA_SIZE},

    {"LTC_LTC_PKCS_1_OAEP",       LTC_LTC_PKCS_1_OAEP},
    {"LTC_LTC_PKCS_1_PSS",        LTC_LTC_PKCS_1_PSS},
    {"LTC_LTC_PKCS_1_V1_5",       LTC_LTC_PKCS_1_V1_5},
};


static int _crypt_add_up_constants(int _crypt_constants_len) {
    int i, total_len = 0;
    char number[10];
    for (i=0; i<_crypt_constants_len; i++) {
        total_len += strlen(_crypt_constants[i].name) + 1;
        // the +1 is for the commas
        sprintf(number,"%lu",_crypt_constants[i].value);
        total_len += strlen(number) + 1;
        // the +1 is for newlines (and ending NULL)
    }
    return total_len;
};

int crypt_list_all_constants(char *names_list, int *str_len) {
    int i;
    char number[10];
    int number_len;
    int _crypt_constants_len = sizeof(_crypt_constants) / sizeof(crypt_constant);
    if (names_list == NULL) {
        *str_len = _crypt_add_up_constants(_crypt_constants_len);
    } else {
        if (*str_len < _crypt_add_up_constants(_crypt_constants_len)) {
            return 1;
        }
        char *ptr = names_list;
        for (i=0; i<_crypt_constants_len; i++) {
            strcpy(ptr, _crypt_constants[i].name);
            ptr += strlen(_crypt_constants[i].name);
            strcpy(ptr, ",");
            ptr += 1;

            number_len = sprintf(number,"%lu",_crypt_constants[i].value);
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

int crypt_get_constant(const char* namein, int *valueout) {
    int i;
    int _crypt_constants_len = sizeof(_crypt_constants) / sizeof(crypt_constant);
    for (i=0; i<_crypt_constants_len; i++) {
        if (strcmp(_crypt_constants[i].name, namein) == 0) {
            *valueout = _crypt_constants[i].value;
            return 0;
        }
    }
    return 1;
}


/* $Source:  $ */
/* $Revision:  $ */
/* $Date:  $ */
