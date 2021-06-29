#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct btns {
    int num;
    char operation;
} button[16];
gpointer entryp;
char operation;
unsigned long long int num1, num2, result;
int isNum1=0;

void calculate(GtkWidget *widget, gpointer data) {
    char buffer[101];
    if(isNum1==1) {
        const char *entry_text=gtk_entry_get_text(GTK_ENTRY(entryp));
        num2=atoi(entry_text);
    }
    if(result) {
        num1=result;
        num2=atoi(gtk_entry_get_text(GTK_ENTRY(entryp)));
    }
#ifdef DEBUG
    printf("[STATUS] operation: %c\nnum1: %lld\nnum2: %lld\n", operation, num1, num2);
#endif
    if(num1&&num2&&operation) {
        if(operation=='+') {
            result=num1+num2;
        } else if(operation=='-') {
            result=num1-num2;
        } else if(operation=='*') {
            result=num1*num2;
        } else if(operation=='/') {
            result=num1/num2;
        }
        sprintf(buffer, "%lld", result);
#ifdef DEBUG
        printf("[RESULT] %lld %c %lld = %lld\n", num1, operation, num2, result);
        printf("buffer: %s\n---------------------------\n\n", buffer);
#endif
        gtk_entry_set_text(GTK_ENTRY(entryp), buffer);
        isNum1=0;
    }
}

void on_num_btn_click(GtkWidget *widget, gpointer data) {
    int btn=(int)data;
    char buffer[10];
    const char *entry_text=gtk_entry_get_text(GTK_ENTRY(entryp));
    sprintf(buffer, "%s%d", entry_text, button[btn].num);
#ifdef DEBUG
    printf("[INFO] button no. %d with value %d clicked\n", btn, button[btn].num);
#endif
    gtk_entry_set_text(GTK_ENTRY(entryp), buffer);
}

void on_operation_btn_click(GtkWidget *widget, gpointer data) {
    int btn=(int)data;
    operation=button[btn].operation;
    const char *entry_text=gtk_entry_get_text(GTK_ENTRY(entryp));
    num1=atoi(entry_text);
    isNum1=1;
#ifdef DEBUG
    printf("[INFO] button no. %d with operation '%c' clicked\n", btn, button[btn].operation);
    printf("isNum1: %d\n", isNum1);
#endif
    gtk_entry_set_text(GTK_ENTRY(entryp), "");
}

void on_AC_btn_click(GtkWidget *widget, gpointer data) {
    num1=0;
    num2=0;
    result=0;
    isNum1=0;
    operation=0;
    gtk_entry_set_text(GTK_ENTRY(entryp), "");
#ifdef DEBUG
    printf("[STATUS] AC button clicked\n");
    printf("reset everything\n");
#endif
}

#ifdef DEBUG
void DEBUG_on_window_destroy(GtkWidget *widget, gpointer data) {
    printf("[STATUS] window destroyed, exiting\n");
    gtk_main_quit();
}
#endif

int main(int argc, char **argv) {
#ifdef DEBUG
    printf("[STATUS] starting\n");
#endif
    GObject *window, *btnAC, *btnadd, *btnsub, *btndiv, *btnmul, *btneq, *btn0, *btn1, *btn2, *btn3, *btn4, *btn5, *btn6, *btn7, *btn8, *btn9, *entry;
    GtkBuilder *builder;
    GError *error=NULL;
#ifdef DEBUG
    printf("[INIT] getting UI file location\n");
#endif
    char *ui_path="../res/calc.ui";

#ifdef DEBUG
    printf("[INIT] initializing GTK\n");
#endif
    gtk_init(&argc, &argv);

#ifdef DEBUG
    printf("[INIT] loading UI file\n");
#endif
    builder=gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, ui_path, &error)) {
        g_printerr("\e[1;31mError loading UI file:\e[0;31m %s\e[0m\n", error->message);
        g_clear_error(&error);
        return 1;
    }
#ifdef DEBUG
    printf("[INIT] loading UI objects\n");
#endif
    window=gtk_builder_get_object(builder, "window");
    btn0=gtk_builder_get_object(builder, "btn0");
    btn1=gtk_builder_get_object(builder, "btn1");
    btn2=gtk_builder_get_object(builder, "btn2");
    btn3=gtk_builder_get_object(builder, "btn3");
    btn4=gtk_builder_get_object(builder, "btn4");
    btn5=gtk_builder_get_object(builder, "btn5");
    btn6=gtk_builder_get_object(builder, "btn6");
    btn7=gtk_builder_get_object(builder, "btn7");
    btn8=gtk_builder_get_object(builder, "btn8");
    btn9=gtk_builder_get_object(builder, "btn9");
    btnadd=gtk_builder_get_object(builder, "btnadd");
    btnsub=gtk_builder_get_object(builder, "btnsub");
    btnmul=gtk_builder_get_object(builder, "btnmul");
    btndiv=gtk_builder_get_object(builder, "btndiv");
    btneq=gtk_builder_get_object(builder, "btneq");
    btnAC=gtk_builder_get_object(builder, "btnAC");
    entry=gtk_builder_get_object(builder, "entry");

    entryp=entry;
    for(int i=0; i<=10; i++) {
        button[i].num=i;
#ifdef DEBUG
        printf("[INIT] button[%d].num: %d\n", i, i);
#endif
    }
    button[11].num=11;
    button[11].operation='+';
    button[12].num=12;
    button[12].operation='-';
    button[13].num=13;
    button[13].operation='/';
    button[14].num=14;
    button[14].operation='*';
    button[15].num=15;
    button[15].operation='=';
#ifdef DEBUG
    for(int i=11; i<=15; i++) {
        printf("[INIT] button[%d].operation: %c\n", button[i].num, button[i].operation);
    }
#endif
#ifdef DEBUG
    g_signal_connect(window, "destroy", G_CALLBACK(DEBUG_on_window_destroy), NULL);
#else
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
#endif
    g_signal_connect(btn0, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[0].num);
    g_signal_connect(btn1, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[1].num);
    g_signal_connect(btn2, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[2].num);
    g_signal_connect(btn3, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[3].num);
    g_signal_connect(btn4, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[4].num);
    g_signal_connect(btn5, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[5].num);
    g_signal_connect(btn6, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[6].num);
    g_signal_connect(btn7, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[7].num);
    g_signal_connect(btn8, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[8].num);
    g_signal_connect(btn9, "clicked", G_CALLBACK(on_num_btn_click), (gpointer)button[9].num);
    g_signal_connect(btnadd, "clicked", G_CALLBACK(on_operation_btn_click), (gpointer)button[11].num);
    g_signal_connect(btnsub, "clicked", G_CALLBACK(on_operation_btn_click), (gpointer)button[12].num);
    g_signal_connect(btndiv, "clicked", G_CALLBACK(on_operation_btn_click), (gpointer)button[13].num);
    g_signal_connect(btnmul, "clicked", G_CALLBACK(on_operation_btn_click), (gpointer)button[14].num);
    g_signal_connect(btneq, "clicked", G_CALLBACK(calculate), (gpointer)button[15].num);
    g_signal_connect(btnAC, "clicked", G_CALLBACK(on_AC_btn_click), NULL);

    gtk_widget_show_all(GTK_WIDGET(window));
#ifdef DEBUG
    printf("[STATUS] loaded\n================\n\n");
#endif
    gtk_main();
}
