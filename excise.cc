#include <iostream>
#include <cstdarg>
void myprintf(const char *fmt, ...) {
//int vasprintf(char **strp, const char *fmt, va_list ap);
char *res;
va_list al;
va_start(al, fmt);
int len = vasprintf(&res, fmt, al);
va_end(al);
std::cout << res << std::endl;
free(res);
}
int main()
{
myprintf("%s-%d", "⼩明", 18);
return 0;
}