#ifndef PARSER_H
#define PARSER_H

#include <ctype.h>
#include <stdbool.h>
#define __USE_GNU
#include <search.h>

#include "regparser.h"

typedef struct {
    dict_t* dict;
    bool rules[NUM_RULES][NUM_RULES];
} parser_t;

/* パーザーの初期化 */
int parser_init(parser_t** p, const char* dict_path, const char* rules_path);

/* 文sentenceを形態素解析する */
/* TODO: 今は表示するだけだが、単語と品詞のペアを返すようにする */
int parser_parse(parser_t* p, const char* sentence);

/* パーザーが確保したメモリ開放 */
void parser_free(parser_t* p);

/* パースする文が有効かチェック */
bool is_sentence(const char* sentence);

/* 遷移規則を用いて、現在の状態(品詞)posと単語wordから次の状態を返す */
PartOfSpeech transit(parser_t* p, PartOfSpeech state, char* word);

#endif
