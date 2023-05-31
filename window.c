#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <time.h>
#include "Game_mechanics/game.h"
#include "test_function/testFunction.h"

#include "Game_mechanics/movePiece.h"
#include "Game_mechanics/minMax.h"
char *recupiece(struct piece *p, char* res);
static gboolean button_pressed (GtkWidget *ebox, GdkEventButton *event, GtkLabel *labelBoard[][8]);
int drawBoard(GtkLabel *labels[][8], struct piece **board);
GdkColor prevColor;
static gboolean button_pressed (GtkWidget*, GdkEventButton*, GtkLabel *[][8]);
int clicks = 0;
int player = 1;
GtkWidget *table, *prevEventbox, *hpane, *infogrid, *textview, *scroll_win;
GtkTextBuffer *buffer;
GtkTextIter txtiter;
GtkLabel *currentPlayer, *row_label, *col_label;
struct piece **tab;

struct Move {
    int currRow;
    int currCol;
    int nextRow;
    int nextCol;
};
struct Move mov;
char note[5];
char mnum[12]; // max int size is 11 chars (if you inlude the - sign) long + 0 char
int board[8][8];
int movecnt = 0;
int main(int argc, char *argv[])
{
    tab = newBoard();
    /*fill the board array with pieces*/
    GtkWidget *window, *eventbox;
    GtkLabel *label;
    gtk_init (&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW (window), "CHESSGPT");
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);
    gtk_widget_set_size_request(window, 680,350);
    table = gtk_grid_new ();
    GtkStyleContext *context;
    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path (provider,
            "style/chessGUI.css", NULL);
    context = gtk_widget_get_style_context (table);
    gtk_style_context_add_provider (context,
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_USER);

    /*container for the labels of the gui board*/
    GtkLabel *labelBoard[8][8];
    /*one is larger to make the squares wider*/	
    char *pieces[64] = { "♜", "♞", "♝","♛","♚","♝","♞","♜",
        "♟", "♟", "♟","♟","♟","♟","♟","♟",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "♙", "♙", "♙","♙","♙","♙","♙","♙",
        "♖", "♘", "♗","♕","♔","♗","♘","♖"};
    int i,j;
    int p = 0;
    int oddCol = 1;
    int oddRow = 1;
    for (i = 0; i < 8; i ++) {
        for (j = 0; j < 8; j++) {
            label = (GtkLabel *) gtk_label_new(pieces[p]);
            /* set the size of the label to avoid that they are resized when there is no piece in the row */
            gtk_widget_set_size_request((GtkWidget *) label, 56, 56);
            /*put the label into the container for easy access when mocing pieces*/
            labelBoard[i][j]=label;
            eventbox = gtk_event_box_new();
            context = gtk_widget_get_style_context (eventbox);
            gtk_style_context_add_provider (context,
                    GTK_STYLE_PROVIDER(provider),
                    GTK_STYLE_PROVIDER_PRIORITY_USER);
            if (oddRow) {
                if (oddCol) {
                    gtk_widget_set_name (eventbox, "lightbrown");
                    oddCol = 0;
                } else {
                    gtk_widget_set_name (eventbox, "darkbrown");
                    oddCol = 1;
                }
            } else {
                if (oddCol) {
                    gtk_widget_set_name (eventbox, "darkbrown");
                    oddCol = 0;
                } else {
                    gtk_widget_set_name (eventbox, "lightbrown");
                    oddCol = 1;
                }
            }

            gtk_event_box_set_above_child(GTK_EVENT_BOX(eventbox),FALSE);
            /*put label into eventbox*/
            gtk_container_add(GTK_CONTAINER (eventbox), (GtkWidget *) label);
            /*put eventbox into table*/
            gtk_grid_attach((GtkGrid *) table, eventbox,j+1,i,1,1);


            g_signal_connect(G_OBJECT (eventbox), "button_press_event",
                    G_CALLBACK (button_pressed), (gpointer) labelBoard);

            gtk_widget_set_events(eventbox, GDK_BUTTON_PRESS_MASK);
            /*Dont need widget_realize
             * connect to a signal that will be called 
             * after the widget is realized automatically
             * in g_signal_connect(window)
             gtk_widget_realize(eventbox);*/

            p++;
        }
        oddRow = !oddRow;
    }
    /* add square row names */
    sprintf(mnum,"%s","`");
    for (i = 1; i < 9; i++) {
        mnum[0]++; // mnums first char becomes 'a', then 'b', then 'c' etc.
        label = (GtkLabel *) gtk_label_new(mnum);
        gtk_widget_set_size_request((GtkWidget *) label, 0, 30);
        gtk_grid_attach((GtkGrid *) table,(GtkWidget *) label,i,9,1,1);
    }
    i = 8;
    for (j = 0; j < 8; j++) {
        sprintf(mnum,"%d",i--);
        label = (GtkLabel *) gtk_label_new(mnum);
        gtk_widget_set_size_request((GtkWidget *) label, 30, 0);
        gtk_grid_attach((GtkGrid *) table,(GtkWidget *) label,0,j,1,1);
    }

    /*make a horizontal pane*/
    //hpane = gtk_grid_new(1,2,TRUE);
    hpane = gtk_grid_new();
    /*add the table to the horizontal pane*/
    gtk_grid_attach((GtkGrid *) hpane, table, 0, 0, 1,1);

    /* create a vertical grid containing game info.
     * the first  widget is shows the current player
     * and the second widget is a textview showing last moves
     */
    infogrid = gtk_grid_new();
    textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textview), FALSE);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview), GTK_WRAP_WORD);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
    gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textview), 10);
    gtk_text_view_set_right_margin (GTK_TEXT_VIEW (textview), 10);

    /*add game info textview to the scroll window 
     * and the scroll window and current player label to infogrid.
     * Finally add the info grid to the hpane, right of the chess board.*/
    scroll_win = gtk_scrolled_window_new (NULL, NULL);
    gtk_widget_set_size_request(scroll_win, 250,415);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll_win),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER (scroll_win), textview);
    gtk_grid_attach((GtkGrid *) infogrid, (GtkWidget *) scroll_win,0,1,1,1);
    currentPlayer = (GtkLabel *) gtk_label_new("Current player: White");
    gtk_grid_attach((GtkGrid *) infogrid, (GtkWidget *) currentPlayer,0,0,1,1);
    gtk_grid_attach((GtkGrid *) hpane, (GtkWidget *) infogrid, 1,0,1,1);



    /*add table to window*/
    gtk_container_add (GTK_CONTAINER (window), hpane);
    gtk_widget_show_all (window);
    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
    freeBoard(tab);
    return 0;
}


            
            
char *recupiece(struct piece *p, char* res)
{ 
    if(p == NULL)
    {
        strcpy(res," ");
    }
    else
    {
    	if (!(p->isWhite))
    	{
            size_t len = strlen(p->name);
            if(strncmp(p->name, "pawn", len) == 0)
                strcpy(res,"♙") ;
            else if (strncmp(p->name, "knight", len) == 0)
            	strcpy(res,"♘");
            else if (strncmp(p->name, "bishop", len) == 0)
               strcpy(res,"♗");
            else if (strncmp(p->name, "rook", len) == 0)
                strcpy(res,"♖");
            else if (strncmp(p->name, "queen", len) == 0)
                strcpy(res,"♕");
            else if(strncmp(p->name, "king", len) == 0)
                strcpy(res,"♔");
    	}
    	else
    	{
            size_t len = strlen(p->name);
            if(strncmp(p->name, "pawn", len) == 0)
                strcpy(res,"♟");
            else if (strncmp(p->name, "knight", len) == 0)
            	strcpy(res,"♞");
            else if (strncmp(p->name, "bishop", len) == 0)
                strcpy(res,"♝");
            else if (strncmp(p->name, "rook", len) == 0)
               strcpy(res,"♜");
            else if (strncmp(p->name, "queen", len) == 0)
                strcpy(res,"♛");
            else if(strncmp(p->name, "king", len) == 0)
                strcpy(res,"♚");
    	}
    }
    return res;
}

int drawBoard(GtkLabel *labels[][8], struct piece **board)
{
    char *res = malloc(2);
    for(size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            char *piece = recupiece(board[i * 8 + j], res);
            gtk_label_set_text(labels[i][j],piece);
        }
    }
    free(res);
}   

static gboolean button_pressed (GtkWidget *ebox, GdkEventButton *event,
			GtkLabel *labelBoard[][8])
{
    // prevEventbox = eventbox;// Just set the prevEventbox to avoid nullpointer exception
    unsigned left, top, width, height;

    if (event->type == GDK_BUTTON_PRESS)
    {
        if (!clicks) {
            gtk_widget_set_name (ebox, "selected");
            /*get coordinates of eventbox*/
            gtk_container_child_get(GTK_CONTAINER(table), ebox,
                    "left-attach", &left,
                    "top-attach",&top,
                    "width",&width,
                    "height",&height,
                    NULL);
            
                /*save label*/
                prevEventbox = ebox;
                /*save the current coordinates*/
            //store the position you move from. It will be used to move the pieces in the board array
            // subtract 1 from left because the row numbers are part of the label table
            mov.currCol = (int)left-1;
            mov.currRow = (int)top;
            clicks = 1;
            if (tab[8*top+left-1] != NULL)
            {
                 mov.currCol = (int)left-1;
                mov.currRow = (int)top;
                clicks = 1;
            }
        } else {
            /*make move*/
            gtk_container_child_get(GTK_CONTAINER(table), ebox,
                    "left-attach",  &left,
                    "top-attach",   &top,
                    "width", &width,
                    "height",&height,
                    NULL);
            //store the position you move to. It will be used to move the pieces in the board array
            // subtract 1 from left because the row numbers are part of the label table
            mov.nextCol = (int)left-1;
            mov.nextRow = (int)top;
            /*color back to normal*/
            if ((mov.currCol+mov.currRow)&1)
            {
                /*odd square, darkbrown color*/
                //gtk_widget_override_background_color(prevEventbox, GTK_STATE_NORMAL, &dbrown);
                gtk_widget_set_name (prevEventbox, "darkbrown"); 
            } else 
            {
                /*even square, lightbrown color*/
                gtk_widget_set_name (prevEventbox, "lightbrown"); 
            }
            int u = 0;
            u = movePiece(tab,mov.currRow*8+mov.currCol, mov.nextRow*8+mov.nextCol);
            if (u) 
            {
                /* Update the GUI board */
                drawBoard(labelBoard, tab);
                /* Update the game info */
                player = !player; 
                if (!player){
                    gtk_label_set_text(currentPlayer, "Current player: Black");
                } else {
                    gtk_label_set_text(currentPlayer, "Current player: White");
                }
            }
            clicks = 0;
        }
    }
    return FALSE;
}


