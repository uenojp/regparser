#include "regparser.h"

static struct hsearch_data dictionary;          /* 単語と品詞を保持するハッシュテーブル */
static char pool[WORD_LEN * NUM_WORDS_IN_DICT]; /* ハッシュテーブルのkeyをプールする */
static bool loaded = false;                     /*辞書がファイルから読み込まれたらtrueへ*/

int load_dict(const char* path) {
    memset(&dictionary, 0, sizeof(dictionary));

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        perror("load_dict: fopen");
        return 1;
    }

    char pos_str[POS_LEN];
    PartOfSpeech pos;

    /* ハッシュテーブル:
     * char* poolは単語が"the", "child", "runs"のとき
     * [ the\0child\0runs ]となる
     * この各keyはハッシュテーブルが参照している
     */
    hcreate_r(NUM_WORDS_IN_DICT, &dictionary);
    char* words_pool_tail = pool; /* このポインタ以降はkeyは登録されていない */
    ENTRY entry;                  /* key, valueの登録に使用 */
    ENTRY* found_;                /* keyの検索に使用、dict_load()では登録の際、引数に渡すのみで使わない */

    while (fscanf(file, "%128s %16s\n", words_pool_tail, pos_str) != EOF) {
        pos = to_enum(pos_str);
        if (pos == UNKNOWN) {
            fprintf(stderr, "%s in %s is an invalid part of speech\n", words_pool_tail, path);
            fclose(file);
            return 1;
        }

        entry.key = words_pool_tail;
        entry.data = (void*)pos;
        words_pool_tail += strlen(words_pool_tail) + 1;

        /* entryに格納したkey, valueをハッシュテーブルに登録 */
        if (hsearch_r(entry, ENTER, &found_, &dictionary) == 0) {
            perror("load_dict: hsearch_r");
            fclose(file);
            return 1;
        }
    }

    if (fclose(file) != 0) {
        perror("load_dict: fclose");
        return 1;
    }

    loaded = true;

    return 0;
}

PartOfSpeech get_part_of_speech(const char* word) {
    if (!loaded)
        return UNKNOWN;

    ENTRY entry;
    ENTRY* found;

/* 再代入によるconst侵害の警告を抑制 */
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
    entry.key = word;
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"

    if (hsearch_r(entry, FIND, &found, &dictionary) != 0) {
        PartOfSpeech pos = (PartOfSpeech)found->data;
        return pos;
    }

    return UNKNOWN;
}
