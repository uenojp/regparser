#include "regparser.h"

int dict_load(dict_t** dict, const char* path) {
    *dict = malloc(sizeof(dict_t));
    if (*dict == NULL) {
        perror("dict_load: malloc");
        return 1;
    }

    (*dict)->htab = malloc(sizeof(struct hsearch_data));
    if ((*dict)->htab == NULL) {
        perror("dict_load: malloc");
        return 1;
    }
    memset((*dict)->htab, 0, sizeof(*((*dict)->htab)));

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        perror("dict_load: fopen");
        return 1;
    }

    char pos_str[POS_LEN];
    PartOfSpeech pos;

    /* ハッシュテーブル:
     * char* poolは単語が"the", "child", "runs"のとき
     * [ the\0child\0runs ]となる
     * この各keyはハッシュテーブルが参照している
     */
    hcreate_r(NUM_WORDS_IN_DICT, (*dict)->htab);
    char* words_pool_tail = (*dict)->pool; /* このポインタ以降はkeyは登録されていない */
    ENTRY entry;                           /* key, valueの登録に使用 */
    ENTRY* found_;                         /* keyの検索に使用、dict_load()では登録の際、引数に渡すのみで使わない */

    int nscan;
    while ((nscan = fscanf(file, "%128s %16s\n", words_pool_tail, pos_str)) != EOF) {
        if (nscan != 2) {
            fprintf(stderr, "dict_load: incorrectly formatted input\n");
            return 1;
        }

        pos = to_enum(pos_str);
        if (pos == UNKNOWN) {
            fprintf(stderr, "dict_load: cannot identify part of speech of %s\n", words_pool_tail);
            return 1;
        }

        entry.key = words_pool_tail;
        entry.data = (void*)pos;
        words_pool_tail += strlen(words_pool_tail) + 1;

        /* entryに格納したkey, valueをハッシュテーブルに登録 */
        if (hsearch_r(entry, ENTER, &found_, (*dict)->htab) == 0) {
            perror("dict_load: hsearch_r");
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}

void dict_free(dict_t* dict) {
    free(dict->htab);
    free(dict);
}

PartOfSpeech get_part_of_speech(dict_t* dict, char* word) {
    if (!dict->htab->table) {
        fprintf(stderr, "haven't loaded dictionary");
        /* TODO: 単語が見つからなかったときのUNKNOWN(最下部のreturn)との区別を与える */
        return UNKNOWN;
    }

    ENTRY entry;
    ENTRY* found;
    entry.key = word;
    if (hsearch_r(entry, FIND, &found, dict->htab) != 0) {
        PartOfSpeech pos = (PartOfSpeech)found->data;
        return pos;
    }

    return UNKNOWN;
}
