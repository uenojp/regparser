#include <getopt.h>
#include <unistd.h>

#include "regparser.h"

void print_help_message() {
    const char* help_message =
        "Usage: cmd [OPTION]... [STRING]\n"
        "Option:\n"
        "  -h, --help         print usage\n"
        "  -d, --dict FILE    load word dictionary\n"
        "  -r, --rule FILE    load grammer rules\n";
    printf("%s", help_message);
}

int main(int argc, char** argv) {
    /* デフォルトの単語辞書と文法規則 */
    char* dict = "./asset/dictionary";
    char* rule = "./asset/rules";

    struct option options[] = {
        {"help", no_argument, NULL, 'h'},
        {"dict", required_argument, NULL, 'd'},
        {"rule", required_argument, NULL, 'r'},
        {0, 0, 0, 0},
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "hd:r:", options, NULL)) != -1) {
        switch (opt) {
            case 'h': print_help_message(); return 0; break;
            case 'd': dict = optarg; break;
            case 'r': rule = optarg; break;
            default: break;
        }
    }

    if (optind == argc) {
        fprintf(stderr, "no input sentence\n");
        return 1;
    }

    if (load_dict(dict) != 0)
        return 1;
    if (load_rule(rule) != 0)
        return 1;

    for (int i = optind; i < argc; i++) {
        if (parse(argv[i]) != 0)
            return 1;
    }

    return 0;
}
