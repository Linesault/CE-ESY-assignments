
عمل الطالب سامي هاني أدهم لمادة النظم المضمنة هندسة الحواسيب جامعة دمشق
#include <stdio.h>
#include <string.h>
تضمين المكاتب الخاصة بالدخل و الخرج القياسي و مكتبة سلسلة المحارف
#define CB_SIZE 32
#define CB_EMPTY '\0'  
تعريف حجم الbuffer
تعريف قيمة المحرف الصفري 
كلاهما ك macro
struct CircularBuffer
{
    char buffer[CB_SIZE];
    unsigned int readposition;
    unsigned int writeposition;
};
تعريف متحول من نوع sturct يحوي بداية الbuffer موضع القراءة و نهاية الbuffer موضع الكتابة  كمتحولات خاصة بالstruct بالاضافة لسلسة المحارف
struct CircularBuffer circ_buff;
تعريف غرض من نوع الstruct السابق
void circ_buff_init(){
    circ_buff.readposition=0;
    circ_buff.writeposition=0;
}
تابع تهيئة مؤشرات القراءة و الكتابة بقيم صفرية
int circ_buff_is_empty(void) {
    return circ_buff.readposition == circ_buff.writeposition;
}
تابع التحقق من ان الbuffer فارغ يعيد قيمة صحيحة
int circ_buff_is_full(void) {
    return (circ_buff.writeposition - circ_buff.readposition) == (unsigned int)CB_SIZE;}
    يتحقق من امتلاء الbuffer بحساب الفرق و يعمل casting للتأكد من ان القيمة ليس سالبة unsigned 
  char circ_buff_read(){
    if (circ_buff.readposition == circ_buff.writeposition) {
        printf("Underflow state ((nothing to read)).\n");
        return CB_EMPTY;
    }
    return circ_buff.buffer[circ_buff.readposition++ & (CB_SIZE - 1)];
}
تابع القراءة يضمن الا يكون المخزن فارغ يضمن ان لا يحصل اخطاء بشرط المخزن من اس
2
و يتحقق من حالة underflow
void circ_buff_write(char c){
    if (circ_buff_is_full()) {
        printf("Overflow state of buffer ((full)) – oldest character '%c' discarded.\n",
               circ_buff.buffer[circ_buff.readposition & (CB_SIZE - 1)]);
        circ_buff.readposition++;
    } 
    تابع الكتابة يتحقق اولا من امتلاء المخزن و من حالة overflow ثم يزيد موضع القراءة بمقدار 1 
    circ_buff.buffer[circ_buff.writeposition++ & (CB_SIZE - 1)] = c;
}
يكتب فقط بعدد المحارف حسب حجم البفر هنا 32 من الدخل القياسي
int main(void) {
    char name[64];
    char namewithsuffix[128];
    int  i;
    circ_buff_init();
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    snprintf(namewithsuffix, sizeof(namewithsuffix), "%sCE-ESY", name);
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
تابع الmain يحوي التعاريف و الاستدعاءات للازمة لتنفيذ المطلوب يطبع enter your name
و يظهر خطأ overflow في حال اكبر من حجم الbuffer
يطبع مصفوفة سلسلة محارف و يأخذ دخل من الكيبورد الاسم لاننا ضمننا مكتبة الدخل القياسية
