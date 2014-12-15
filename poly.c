#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    WIN_PERSON,
    WIN_ADDRESS
} win_type_t;

typedef struct win_t {
    win_type_t type;
    char *label;
    int num;
} Win;

typedef struct win_person_t {
    Win super;
    char *fistname;
    char *secondname;
} WinPerson;

typedef struct win_address_t {
    Win super;
    char *address;
    char *town;
    char *country;
} WinAddress;

Win *
win_create_person(char *label, int num, char *firstname, char *secondname)
{
    WinPerson *new_win = malloc(sizeof(WinPerson));
    new_win->super.type = WIN_PERSON;
    new_win->super.label = strdup(label);
    new_win->super.num = num;
    new_win->fistname = strdup(firstname);
    new_win->secondname = strdup(secondname);

    return (Win*)new_win;
}

Win *
win_create_address(char *label, int num, char *address, char *town, char *country)
{
    WinAddress *new_win = malloc(sizeof(WinAddress));
    new_win->super.type = WIN_ADDRESS;
    new_win->super.label = strdup(label);
    new_win->super.num = num;
    new_win->address = strdup(address);
    new_win->town = strdup(town);
    new_win->country = strdup(country);

    return (Win*)new_win;
}

void
win_execute(Win *win)
{
    if (win->type == WIN_PERSON) {
        WinPerson *winperson = (WinPerson*)win;
        printf("Type WinPerson\n");
        printf("  Specific:\n");
        printf("    firstname: %s\n", winperson->fistname);
        printf("    secondname: %s\n", winperson->secondname);

    } else if (win->type == WIN_ADDRESS) {
        WinAddress *winaddress = (WinAddress*)win;
        printf("Type WinAddress\n");
        printf("  Specific:\n");
        printf("    address: %s\n", winaddress->address);
        printf("    town: %s\n", winaddress->town);
        printf("    country: %s\n", winaddress->country);
    }

    printf("  Common:\n");
    printf("    Label: %s\n", win->label);
    printf("    Num: %d\n", win->num);
    printf("\n");
}

int
main(void)
{
    GSList *wins = NULL;

    Win *win1 = win_create_person("TAG1", 1, "My", "Name");
    Win *win2 = win_create_address("TAG2", 2, "10 Some Road", "Town", "UK");

    wins = g_slist_append(wins, win1);
    wins = g_slist_append(wins, win2);

    GSList *curr = wins;
    while (curr) {
        Win *win = curr->data;
        win_execute(win);
        curr = g_slist_next(curr);
    }

    return 0;
}

