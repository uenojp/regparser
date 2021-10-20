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

#include "rule.h"
#include "type.h"

#ifndef NUM_WORDS_IN_DICT
#define NUM_WORDS_IN_DICT 128
#endif

/* pathから単語と品詞のペアを単語辞書にロードする */
int load_dict(const char* path);

PartOfSpeech get_part_of_speech(const char* word);

#endif
