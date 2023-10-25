#include <stdlib.h>
#include <string.h>
#include "curses.h"

int gameflag = 0;

void menuscreen(){
    initscr();
    noecho();
    cbreak();
    
    // get screen size
    int yMax, xMax;
    getmaxyx (stdscr, yMax, xMax); // assigns max values of std screen to yMax and xMax

    // creates window in middle of screen with height 6 and width 48
    WINDOW * menu = newwin(6, 48, (yMax/2) - 3, (xMax/2) - 24);
    box(menu, 0, 0); // puts box around window

    refresh();
    wrefresh(menu);

    //enables arrow keys for window
    keypad(menu, true);

    // array holding menu options
    char choices[3][12] = {"Start Game", "Test", "Exit"};
    int choice;
    int highlight = 0;

    while(1)
    {
        for (int i=0; i<3; i++) //prints menu
        {
            if (i == highlight) //starts highlighting first menu option
                wattron   (menu, A_REVERSE); //enables A_REVERSE for menu window
                mvwprintw (menu, i+1, 1, choices[i]); //prints menu options inside top and left border of menu window
                wattroff  (menu, A_REVERSE); //disables A_REVERSE for window
        }
        choice = wgetch(menu); //assigns integer value of users keypress as int choice

        switch(choice) // processes result of pressing specific keys
        {
            case KEY_UP: //up arrow key pressed  
                highlight--;
                if (highlight == -1) //top of menu    
                    highlight = 0;
                break;
            case KEY_LEFT: //up arrow key pressed  
                highlight--;
                if (highlight == -1) //top of menu    
                    highlight = 0;
                break;

            case KEY_DOWN: //down arrow key pressed
                highlight++;
                if (highlight == 3) //bottom of menu  
                    highlight = 2;
                break;
            case KEY_RIGHT:
                highlight++;
                if (highlight == 3) //bottom of menu  
                    highlight = 2;
                break;

            default: //other key pressed
                break;
        }
        if (choice == 10) //if enter pressed
        {
            printw("Your choice was: %s", choices[highlight]);
            refresh();
            if (highlight == 2){
                endwin();
                return;
            }
            else if (highlight == 0){
                gameflag = 1;
                clear();
                refresh();
                break;
            }
        }
    }
}

void game(){
    if(gameflag == 1){
        
        initscr();
        noecho();
        cbreak();
        // get screen size
        int yMax, xMax;
        getmaxyx (stdscr, yMax, xMax); // assigns max values of std screen to yMax and xMax

        // creates window in middle of screen with height 6 and width 48
        WINDOW * menu = newwin(6, 48, (yMax/2) - 3, (xMax/2) - 24);
        box(menu, 0, 0); // puts box around window

        refresh();
        wrefresh(menu);

        //enables arrow keys for window
        keypad(menu, true);

        // array holding menu options
        char choices[3][12] = {"Start Game", "Test", "Exit"};
        int choice;
        int highlight = 0;
        getch();
    }
}

int main(int argc, char **argv)
{
    menuscreen();
    game();
    endwin();
    return 0;
}