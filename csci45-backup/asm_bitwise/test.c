#include <unistd.h>
#include <string.h>

int main() {
	char *str = "Hello Wordsgfdshgdj!\n";
	//printf("Hello World!");
	//0 is stdin, 1 is stdout, 2 is stderr
	write(1, str, strlen(str));
}
