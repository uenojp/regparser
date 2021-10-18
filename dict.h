#ifndef DICT_H
#define DICT_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <search.h>

#include "type.h"

#ifndef NUM_WORDS_IN_DICT
#define NUM_WORDS_IN_DICT 128
#endif

#ifndef NUM_RULES
#define NUM_RULES 128
#endif

#define WORD_SIZE 128
#define POS_SIZE 16

typedef struct {
    struct hsearch_data* htab;                /* 単語と品詞を保持するハッシュテーブル */
    char pool[NUM_RULES * NUM_WORDS_IN_DICT]; /* ハッシュテーブルのkeyをプールする */
} dict_t;

/* pathから単語と品詞のペアをhtabにロードする */
int dict_load(dict_t** dict, const char* path);

/* dict_loadで確保したメモリを解放する */
void dict_free(dict_t* dict);

PartOfSpeech get_part_of_speech(dict_t* dict, char* word);

#endif
