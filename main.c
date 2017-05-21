#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <sys\time.h>
#include <time.h>

int main(void)
{
	int i, n = 1, m = 0, max;

	FILE *book = fopen("book.txt", "r");

	while (!feof(book)) {
		if (fgetc(book) == '\n') {
			n++;
			max = m + 1;
			m = 0;
		} else {
			if (max < m) {
				max = m + 1;
			}
			m++;
		}
	}
	
	fclose(book);

	printf("%d %d", n, max);

	FILE *book2 = fopen("book.txt", "r");

	char mas[n][max];
	for(i = 0; i < n; i++) {
		fgets(mas[i], max, book2);
//		fscanf(book, "%s", mas[i]);
	}
	fclose(book2);
	
	FILE *book1 = fopen("1.txt", "w");
	for (i = 0; i < n; i++) {
		fputs(mas[i], book1);
	}
	
	fclose(book1);
	
//	system("pause");
	
	return 0;
}
