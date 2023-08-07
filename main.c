

#include <ncurses.h>
/*
const char items[4][60] = {
    "Item1 fdrtwffwfw fgbbdv fgrssdgs",
    "Item2 fef dff  sdwwrw rsdfs fdfs rs",
    "Item3 sdsfs sww sdsd w ddfs w ddef",
    "Item4 sdwdd ds dwesdd sdws d sdcwsdc sd"
};
*/
#define LEN_ARAY_STRING 1024
#define LEN_ARAY_CHAR 8192

#define OFSET_X 1
#define OFSET_Y 1
int main()
{
    long len_string[LEN_ARAY_STRING];
    long number_string = 0;
    long aray_file[LEN_ARAY_CHAR];
    long count_char_in_string = 0;
    long count_char = 0;

    WINDOW * point_window;
    point_window = initscr();
    unsigned choice = 0;

    int x_coordinat = 0, y_coordinat = 0;
    long j;

    int max_row, max_col;
    


//    curs_set(0);
    keypad(stdscr, true);

    clear();
/*
    for ( unsigned i = 0; i < 4; i++ )
    {
        printw("%s\n", items[i]);
    }
*/

//    WINDOW *getwin(FILE *filep);
//  int open(const char *pathname, int flags);
    
    FILE * fp;
    if((fp=fopen("1.txt", "r+"))==NULL) {
        printw("Can't open file.\n");
        endwin();
        fclose(fp);
        return 1;
    }
/*
    long int begin_file;
    if((begin_file=ftell(fp)) == -1L)
    {
        printw("Error file processing.\n");
        endwin();
        fclose(fp);
        return 1;
    }
*/
    for(long i = 0; i < LEN_ARAY_STRING;++i){len_string[i] = 0;}
    for(long i = 0; i < LEN_ARAY_CHAR;++i){aray_file[i] = 0;}
    
    int c = 0;
    int mem = 0;
    while(mem == 0)
    {
        c=fgetc(fp);
        mem=feof(fp);
        if(mem==0)
        {
            aray_file[count_char] = c;
            ++count_char;
            if(LEN_ARAY_CHAR < count_char)
            {
                printw("Eror max char.\n");
                endwin();
                fclose(fp);
                return 1;
            }

            if('\n' == c)
            {
                len_string[number_string] = count_char_in_string;
                count_char_in_string = 0;
                ++number_string;
            }
            else
            {
                ++count_char_in_string;
                if(LEN_ARAY_STRING < count_char_in_string)
                {
                    printw("Eror max len string.\n");
                    endwin();
                    fclose(fp);
                    return 1;
                }
            }
            
            addch(c);
        }
    }
//    point_window = getwin(fp);
    
    

    move(0, 0);

    c = 0;

    while ( c != KEY_F(1) /*true*/ )
    {
//        getmaxyx(stdscr, max_row, max_col);
        
        c = getch();
        switch ( c )
        {
            case KEY_UP:
                if ( y_coordinat )
                {
                    y_coordinat--;
                    if ( x_coordinat > (len_string[y_coordinat] - OFSET_X) )
                        x_coordinat = len_string[y_coordinat] - OFSET_X;
                }
                move(y_coordinat, x_coordinat);
            break;
            case KEY_DOWN:
                if ( y_coordinat != (number_string - OFSET_Y) )
                {
                    y_coordinat++;
                    if ( x_coordinat > (len_string[y_coordinat] - OFSET_X) )
                        x_coordinat = len_string[y_coordinat] - OFSET_X;
                }
                move(y_coordinat, x_coordinat);
            break;
            case KEY_LEFT:
                if ( x_coordinat )
                    x_coordinat--;
                move(y_coordinat, x_coordinat);
            break;
            case KEY_RIGHT:
                if ( x_coordinat != (len_string[y_coordinat] - OFSET_X) )
                    x_coordinat++;
                move(y_coordinat, x_coordinat);
            break;
            default:
//                addch(c);
//                addch('A');
//                printw("Code of pressed key is %d\n", c);
                if(c != KEY_F(1))
                {
                    j = 0;
                    for(long i = 0; i < y_coordinat; ++i)
                    {
                        j = j + len_string[i] + 1; 
                    }
                    j = j + x_coordinat;
                    aray_file[j] = c;
                    if ( x_coordinat != (len_string[y_coordinat] - OFSET_X) )
                        x_coordinat++;
                    move(y_coordinat, x_coordinat);
                }
            break;
        }
    }
//    putwin(point_window, fp);

//    rewind(fp);


/*
/////////////////////////////////////////////////
      fpos_t file_loc;          ////////////
                                ////////
      fgetpos(fp, &file_loc);   //////
                                ////
      file_loc = begin_file;    ///////////
      fsetpos(fp, &file_loc);   /////////////////
////////////////////////////////////////////////
*/



/*
    FILE * fp_2;
    if((fp_2=fopen("2.txt", "r+"))==NULL) {
        printw("Can't open file.\n");
        endwin();
        fclose(fp_2);
        return 1;
    }
*/
    rewind(fp);
    for(long i = 0; i < LEN_ARAY_CHAR;++i)
    {
        if(0 == aray_file[i]){break;}
        fputc(aray_file[i], fp);
    }

    endwin();
    fclose(fp);
//    fclose(fp_2);
    return 0;
}
