#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct video_games{
    char name[50], developer[50], publisher[50], genre[50];
    float price;
    int number_of_DLCs, year_of_launch;
}video_games;

void menu_list(){
    printf ("\n\t==============================================================");
    printf ("\n\t* Welcome to the list of videogames from a digital platform! *\n");
    printf ("\t==============================================================");
    printf ("\n\tThere are a few options to choose from:\n");
    printf ("\t1. Print the list !\n");
    printf ("\t2. Update the list with a new game\n");
    printf ("\t3. Delete a game from the list\n");
    printf ("\t4. Sort them by Name (alphabetically)\n");
    printf ("\t5. You can filter the games by searching a genre\n");

    printf ("\n\t*IMPORTANT* You should type the corresponding number in order for this to work: ");
}

void print_list(){
    int nr=0;
    printf("\n");
    char line[255];
    FILE * fpointer = fopen("input.txt", "r");
    while (fgets(line,sizeof(line),fpointer)) {
        if (nr==0){
        printf ("\t========================================================================\n");
        printf("\t| %s",line);
        printf ("\t========================================================================\n");
        }else{
        printf("\t(%d) %s",nr,line);
        }
        nr++;
    }
    printf("\n");
    fclose(fpointer);
}

void back_to_menu(int option){
    char user_input[30];
    if(option){
    printf("\n\t== To get back to the main menu or quit, type (Y or N) ==");
    printf("\n\tNOTE: Only capital Y and N are accepted as inputs !\n");
    printf("\n\t(Type here)-> ");
    }
    scanf("%s",&user_input);
    if(user_input[1]=='\0'){
    switch (user_input[0]){
    case 'Y':
        system("cls");
        menu_list();
        ask_input();
        break;
    case 'N':
        system("cls");
        printf("\n\t== You chose to close the program, Goodbye !==\n");
        break;
    default:
        system("cls");
        printf("\n\t== Sorry, wrong input, type again either (Y or N): ==\n");
        back_to_menu(0);
        break;
    }
    }else{
        system("cls");
        wrong_case(1);
    }
}

void delete_game(int option,int option_2){
    char user_input[30];
    if (option){
    printf("\n\t== What line would you like to remove completely ? ==");
    }
    if(option_2){
    FILE *fptr1, *fptr2;
    char file1[] ="input.txt";
    char file2[] ="input2.txt";
    char curr;
    int del, line_number = 0;
    printf("\n\t(Type the line number here)-> ");
    scanf("%d", &del);
    del++; //the input is incremented by one because the list header counts as a line inside the file
    fptr1 = fopen(file1,"r");
    fptr2 = fopen(file2, "w");
    curr = getc(fptr1);
    if(curr!=EOF) {line_number =1;}
    while(1){
      if(del != line_number)
        putc(curr, fptr2);
        curr = getc(fptr1);
        if(curr =='\n') line_number++;
        if(curr == EOF) break;
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(file1);
    rename(file2,file1);
    }
    //from here it repeats the delete procedure
    system("cls");
    print_list();
    printf("\n\t== Do you want to delete another one ? (Y/N) ==");
    printf("\n\t(Type here either 'Y' to delete one more or 'N' to go back to the main menu)-> ");
    scanf("%s", &user_input);
    if(user_input[1]=='\0'){
    switch (user_input[0]){
    case 'Y':
        system("cls");
        print_list();
        delete_game(0,1);
        break;
    case 'N':
        system("cls");
        menu_list();
        ask_input();
        break;
    default:
        delete_game(0,0);
        break;
    }
    }else{
        delete_game(0,0);
    }
}

void add_new_game(){
    char str[50],buf[50];
    int n=0;
    float x;
    struct video_games video_game1;
    FILE * fpointer = fopen("input.txt", "a");
    printf("\n\t*Type the game Title: ");
    scanf(" %[^\n]s",str);
    strcpy(video_game1.name,str);
    fprintf(fpointer,"\n%s, ",video_game1.name);

    system("cls");
    printf("\n\t*Type the name of the Development studio: ");
    scanf(" %[^\n]s",str);
    strcpy(video_game1.developer,str);
    fprintf(fpointer,"%s, ",video_game1.developer);

    system("cls");
    printf("\n\t*Type the name of the Publisher: ");
    scanf(" %[^\n]s",str);
    strcpy(video_game1.publisher,str);
    fprintf(fpointer,"%s, ",video_game1.publisher);

    system("cls");
    printf("\n\t* Type the game price (in EUR): ");
    scanf("%f",&x);
    gcvt(x, 6, buf);
    //the next comparison in the if condition is made in order to print "Free to play" for price 0
    if (!strcmp(buf,"0.")){
        fprintf(fpointer,"Free to play, ");
    }else{
        video_game1.price=x;
        fprintf(fpointer,"%.2f, ",video_game1.price);
    }

    system("cls");
    printf("\n\t* Type the game genre: ");
    scanf(" %[^\n]s",str);
    strcpy(video_game1.genre,str);
    fprintf(fpointer,"%s, ",video_game1.genre);

    system("cls");
    printf("\n\t* Type the number of DLCs: ");
    scanf("%d",&n);
    video_game1.number_of_DLCs=n;
    fprintf(fpointer,"%d, ",video_game1.number_of_DLCs);

    system("cls");
    printf("\n\t* Type the year of launch: ");
    scanf("%d",&n);
    video_game1.year_of_launch=n;
    fprintf(fpointer,"%d",video_game1.year_of_launch);

    fclose(fpointer);
}

void print_by_genre(int option){
    char user_input[30];
    int nr=1,is_substring=0;
    char line[255],line_2[255];
    char *ret;
    FILE *file=fopen("input.txt","r"),*temp=fopen("tempfile.txt","w"),*temp_read=fopen("tempfile.txt","r");

    if(option){printf("\n\t== You've chosen to filter all the games of specific genre ! ==\n");}

    printf("\n\t(Type here, any genre name starts with a capital letter)-> ");
    scanf("%s", &user_input);
    if(user_input[0] >= 'a' && user_input[0] <= 'z'){ system("cls"); print_by_genre(1);}
    system("cls");

    fgets(line,sizeof(line),file);
    strcpy(line_2,line);

    while (fgets(line,sizeof(line),file)){
    ret = strstr(line, user_input);
    if (ret){
        is_substring=1;
        fprintf(temp,"%s",line);
        }
    }
    fclose(file);
    if(!is_substring){
        printf("\n\t== Sorry, no result for '%s', maybe you typed it wrong ! ==\n",user_input);
        printf("\n\t * Try again mate ! * :D\n");
        print_by_genre(0);
    }
    printf("\n\t== Ok, here are all the %s video games ! ==\n\n",user_input);
    printf ("\t========================================================================\n");
    printf("\t| %s",line_2);
    printf ("\t========================================================================\n");
    fclose(temp);
    while (fgets(line,sizeof(line),temp_read)){
        printf("\t(%d) %s",nr,line);
        nr++;
    }
    fclose(temp_read);
    printf("\n");
    remove("tempfile.txt");
}

void sort_alphabetically(){
    printf("\n\t== You've picked the sorting by name (alphabetically) ! ==\n");
    char line[100][100];
	char temp[255];
    FILE *fptr = NULL;
    int i=0,j,nr=0,total=0;
    fptr = fopen("input.txt", "r");
    while(fgets(line[i], 100, fptr))
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    total = i;
    // here the sorting starts
    for(i=1;i<total-1;i++)
    {
        for(j=i+1;j<total;j++){
            if(strcmp(line[i],line[j])>0)
            {
                strcpy(temp,line[i]);
                strcpy(line[i],line[j]);
                strcpy(line[j],temp);
            }
        }
    }
    printf("\n");
    // after we get the total number of lines and the list is sorted, it simply prints all we've got 
    for(i = 0; i < total; ++i){
        if (!nr){
        printf ("\t========================================================================\n");
        printf("\t| %s\n",line);
        printf ("\t========================================================================\n");
        }else{
        printf("\t(%d) %s\n",nr,line[i]);
        }
        nr++;
    }
    fclose(fptr);
}

void ask_input(){
    char user_input[30];
    scanf("%s",&user_input);
    if(user_input[1]=='\0'){
    switch(user_input[0]){
    case '1'://Print list
        system("cls"); print_list();
        back_to_menu(1);
        break;
    case '2'://Update with a new game
        system("cls");
        add_new_game();
        system("cls");
        print_list();
        back_to_menu(1);
        break;
    case '3'://Delete a game
        system("cls");
        print_list();
        delete_game(1,1);
        print_list();
        back_to_menu(1);
        break;
    case '4'://Sort the list
        system("cls");
        sort_alphabetically();
        back_to_menu(1);
        break;
    case '5':// Print by genre
        system("cls");
        print_by_genre(1);
        back_to_menu(1);
        break;
    default: // Wrong input
        system("cls");
        menu_list();
        wrong_case(0);
        break;
    }
    }else{
        system("cls");
        menu_list();
        wrong_case(0);
    }
}

void wrong_case(int n){
        printf("\n\n\t== *Invalid input ! * Try retyping carefully: ==\n\n");
        if(n){printf("\t* Type again either (Y or N): *\n\n");}
        printf("\t(Type here)-> ");
        n ? back_to_menu(0): ask_input();
}

int main()
{
    menu_list();
    ask_input();
    return 0;
}
