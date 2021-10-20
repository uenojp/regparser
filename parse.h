#ifndef PARSE_H
#define PARSE_H

#include <ctype.h>
#include <stdbool.h>
#define __USE_GNU
#include <search.h>

#include "regparser.h"

/* 文sentenceを形態素解析する */
/* TODO: 今は表示するだけだが、単語と品詞のペアを返すようにする */
int parse(const char* sentence);

/* パースする文が有効かチェック */
bool is_sentence(const char* sentence);

/* 遷移規則を用いて、現在の状態(品詞)posと単語wordから次の状態を返す */
PartOfSpeech transit(const PartOfSpeech state, const char* word);

#endif
