#ifndef PARSER_H
#define PARSER_H

#include "type.h"

/* 単語の品詞を返す */
PartOfSpeech dictionary(const char* word);

/* 現在の状態(品詞)から、次の状態(品詞)へ遷移 */
PartOfSpeech transit(PartOfSpeech state, const char* word);

#endif
