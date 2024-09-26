#include <stdio.h>


void printSlots(int slots[]){
    printf("\n");
    for(int i=0; i< 20; i++){
        printf("[%d]", slots[i]);
    }
    printf("\n");
}

int compileBF(char programkod[]){
    // Slot init
    int slots[32768];
    for(int i =0; i<32768; i++){
        slots[i] = 0;
    }
    // Pointer beállítása
    int pointer = 0;

    //Syntax ellenőrzéshez
    int loops_running = 0;
    int in_loop = 0;
    int i = 0;

    //Inputhoz
    char inp;
    //Outputhoz
    char out;
    //Program olvasásához
    char ins;


    while(programkod[i] != '\0'){
        ins = programkod[i];
        switch(ins){
            case '+':
                slots[pointer] = (slots[pointer] + 1 ) % 127; // ASCII túllépés elkerülése
                break;
            case '-':
                slots[pointer] = (slots[pointer] -  1 ) % 127;
                break;
            case '>':
                if(pointer < 32768) pointer = pointer + 1;
                else{
                    printf("\nRANGE_ERROR");
                    return 1;
                }
                break;
            case '<':
                if(pointer > 0) pointer -= 1;
                else{
                    printf("\nRANGE_ERROR");
                    return 1;
                }
                break;
            case '.':
                out = slots[pointer];
                printf("%c", out);
                break;
            case ',':
                scanf("%c", &inp);
                if(inp == EOF || inp == '\0' || inp == '\n') slots[pointer] = -1;
                else slots[pointer] = (int) inp;
                break;
            case '[':
                if(slots[pointer] <= 0){
                    in_loop = 1;
                    while(in_loop > 0){
                        i += 1;
                        if(programkod[i] == '['){ in_loop += 1;}
                        else if(programkod[i] == ']') in_loop -= 1;
                        else if(programkod[i] == '\0'){ 
                            printf("UNMATCHED '[' ");
                            return 1;
                        }  
                    }
                }else{
                    loops_running += 1;
                }
                break;
            case ']':
                
                if (loops_running == 0){
                    printf("UNMATCHED ']' ");
                    return 1;
                }
                if(slots[pointer] <= 0){ //Mivel tárol a program <0 értékeket, ezért szükséges, vagy végtelen loopba futhatunk -1-es pointer érték esetén
                    loops_running -= 1;
                    break;
                }
                in_loop = 1;
                while(in_loop > 0){
                    i -= 1;
                    if(programkod[i] == '[') {in_loop -= 1;}    
                    if(programkod[i] == ']') {in_loop += 1;}
                    if(programkod[i] == '\0'){
                        printf("\nUNMATCHED '[' ");
                        return 1;
                    }
                }
                break;
            default:
                break;
        }
        i += 1;
    }
    if(loops_running > 0){
        printf("\nSYNTAX ERROR");
        return 1;
    }
    printSlots(slots);

    return 0;

}

int main(){

    // Sierpinski-háromszög
    char programkod[] =  "[ThisprogramprintsSierpinskitriangleon80-columndisplay.]>++++[<++++++++>-]>++++++++[>++++<-]>>++>>>+>>>+<<<<<<<<<<[-[->+<]>[-<+>>>.<<]>>>[[->++++++++[>++++<-]>.<<[->+<]+>[->++++++++++<<+>]>.[-]>]]+<<<[-[->+<]+>[-<+>>>-[->+<]++>[-<->]<<<]<<<<]++++++++++.+++.[-]<]+++++*****Made*By:*NYYRIKKI*2002*****";
    // Reverse string
    char programkod2[] = ",.";//">,[>,]<[.<]";
    //compileBF(programkod);
    compileBF(programkod2);

    return 0;
}