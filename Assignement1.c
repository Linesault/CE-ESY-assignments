#include <stdio.h>
#include <string.h>
#define CB_SIZE 32
#define CB_EMPTY '\0'  
struct CircularBuffer
{
    char buffer[CB_SIZE];
    unsigned int readposition;
    unsigned int writeposition;
};
struct CircularBuffer circ_buff;
void circ_buff_init(){.\Assignment1.exe
    circ_buff.readposition=0;
    circ_buff.writeposition=0;
}
int circ_buff_is_empty(void) {
    return circ_buff.readposition == circ_buff.writeposition;
}
int circ_buff_is_full(void) {
    return (circ_buff.writeposition - circ_buff.readposition) == (unsigned int)CB_SIZE;
}
char circ_buff_read(){
    if (circ_buff.readposition == circ_buff.writeposition) {
        printf("Underflow state ((nothing to read)).\n");
        return CB_EMPTY;
    }
    return circ_buff.buffer[circ_buff.readposition++ & (CB_SIZE - 1)];
}
void circ_buff_write(char c){
    if (circ_buff_is_full()) {
        printf("Overflow state of buffer ((full)) – oldest character '%c' discarded.\n",
               circ_buff.buffer[circ_buff.readposition & (CB_SIZE - 1)]);
        circ_buff.readposition++;
    } 
    circ_buff.buffer[circ_buff.writeposition++ & (CB_SIZE - 1)] = c;
}
int main(void) {
    char name[64];
    char namewithsuffix[128];
    int  i;
    circ_buff_init();
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    snprintf(full_name, sizeof(full_name), "%sCE-ESY", name);
    printf("Full string to buffer: \"%s\"\n", namewithsuffix);
    printf("Buffer size (CB_SIZE): %d\n\n", CB_SIZE);
    for (i = 0; namewithsuffix[i] != '\0'; i++) {
        circ_buff_write(namewithsuffix[i]);
    }
    printf("Output from buffer: ");
    while (!circ_buff_is_empty()) {
   
        putchar(circ_buff_read());
    }
    putchar('\n');
    if (circ_buff_is_empty()) {
        printf("\nBuffer is now empty. All characters were output successfully.\n");
    }
    return 0;
}
