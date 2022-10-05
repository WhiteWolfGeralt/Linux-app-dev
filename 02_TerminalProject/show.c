#include <ncurses.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* document[1024];

int get_document(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No filename in arguments\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File %s cannot be open\n", argv[1]);
        exit(errno);
    }

    int curr_c, i = 0, count_of_str = 0;
    char str[1024];
    while ((curr_c = getc(fp)) != EOF) {
        str[i++] = (char) curr_c;
        if (curr_c == '\n') {
            str[i++] = '\0';
            document[count_of_str] = malloc(i * sizeof (char));
            strcpy(document[count_of_str], str);
            i = 0;
            count_of_str++;
        }
    }
    fclose(fp);
    return count_of_str;
}

void init_scr(const char *file, int str) {
    initscr();
    noecho();
    cbreak();
    char s[100];
    sprintf(s, "File: %s; size: %d", file, str);
    printw(s);
    refresh();
}

int main(int argc, char *argv[]) {
    int str = get_document(argc, argv);
    init_scr(argv[1], str);

    WINDOW *box = newwin(LINES - 2, COLS - 2, 1, 2);
    box(box, 0, 0);
    wrefresh(box);
    WINDOW *win = newwin(LINES - 5, COLS - 6, 2, 4);
    keypad(win, TRUE);
    scrollok (win, TRUE);
    wmove(win, 1, 0);
    int offset = 0;
    while (1) {
        wrefresh(win);
        for (int i = 0 + offset; i < LINES - 6 + offset; ++i) {
            wprintw(win, "%3d: %s", i+1, document[i]);
        }

        int current_symbol = wgetch(win);
        if (current_symbol == 27) { //escape
            break;
        }
        if (current_symbol == 258 || current_symbol == 32) { //page down or space
            if (LINES - 6 + offset + 1 <= str) {
                offset++;
            }
        }
        if (current_symbol == 259) { //page up
            offset = offset - 1 >= 0 ? offset - 1 : 0; //max of (offset - 1) and 0
        }
    }
    endwin();
}
