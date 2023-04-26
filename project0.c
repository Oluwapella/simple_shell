#include <unistd.h>
/**
 * main - programm that print greetings
 *
 * Return: alwaayws return (0);
 */


int main(void)
{
	char *users = "you are wlc to the page of alx student\n";
	int c = 67;
	{
	write(STDOUT_FILENO, users, c);
	}
return (0);
}
