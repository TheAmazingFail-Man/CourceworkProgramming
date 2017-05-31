#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>

void translater(char *word, int number_of_symbols, char keeper, int check_for_emptiness, char *text)
{
	int i;

	FILE *translated_text = fopen(text, "a");
	if (check_for_emptiness == 0) {
		for (i = 0; i < number_of_symbols; i++) {
			fprintf(translated_text, "%c", word[i]);
		}
	}
	fprintf(translated_text, "%c", keeper);
	fclose(translated_text);
}

int comparison(char **true_word, int word_number, int number_of_symbols, char *word)
{
	int i;

	for (i = 0; i < number_of_symbols; i++) {
		if (true_word[i][word_number] != word[i]) {
		
			return 0;
		}
	}
	
	return 1;
}

void word_search(char **word_for_translate, int word_number, int number_of_symbols_true_word, char **dictionary, int number_of_words, int selection, char keeper, int check_for_emptiness, char *text)
{
	int i, j, z, number_of_symbols_rus = 0, number_of_symbols_eng = 0, record_rus_word, record_eng_word, search_completed = 0, big_symbol, little_symbol;
	char *rus_word = (char*)malloc(20 * sizeof(char));
	char *eng_word = (char*)malloc(20 * sizeof(char));
	char *additional_word = (char*)malloc(20 * sizeof(char));
	
	for (i = 0; i < number_of_words && search_completed == 0; i++) {
		record_rus_word = 0;
		record_eng_word = 0;
		number_of_symbols_rus = 0;
		number_of_symbols_eng = 0;
		for (j = 0; record_rus_word == 0; j++) {
			if (dictionary[i][j] == ' ' && record_eng_word == 0) {
				j += 2;
				record_eng_word = 1;
			} else if (record_eng_word == 0) {
				eng_word[number_of_symbols_eng++] = dictionary[i][j];
			} else if (dictionary[i][j] == '\n') {
				if (selection == 1) {
					if (isupper(word_for_translate[0][word_number])) {
						rus_word[0] = toupper(rus_word[0]);
						big_symbol = 1;
					} else if (islower(word_for_translate[0][word_number])) {
						rus_word[0] = tolower(rus_word[0]);
						little_symbol = 1;
					}
					search_completed = comparison(word_for_translate, word_number, number_of_symbols_true_word, rus_word);
				} else if (selection == 2) {
					if (isupper(word_for_translate[0][word_number])) {
						eng_word[0] = toupper(eng_word[0]);
						big_symbol = 1;
					} else if (islower(word_for_translate[0][word_number])) {
						eng_word[0] = tolower(eng_word[0]);
						little_symbol = 1;
					}
					search_completed = comparison(word_for_translate, word_number, number_of_symbols_true_word, eng_word);
				}
				if (search_completed == 1) {
					if (selection == 1) {
						if (big_symbol == 1) {
							eng_word[0] = toupper(eng_word[0]);
						} else if (little_symbol == 1) {
							eng_word[0] = tolower(eng_word[0]);
						}
						translater(eng_word, number_of_symbols_eng, keeper, check_for_emptiness, text);
					} else if (selection == 2) {
						if (big_symbol == 1) {
							rus_word[0] = toupper(rus_word[0]);
						} else if (little_symbol == 1) {
							rus_word[0] = tolower(rus_word[0]);
						}
						translater(rus_word, number_of_symbols_rus, keeper, check_for_emptiness, text);
					}
				}
				record_rus_word = 1;
				free(eng_word);
				free(rus_word);
				eng_word = (char*)malloc(20 * sizeof(char));
				rus_word = (char*)malloc(20 * sizeof(char));
			} else if (record_eng_word == 1) {
				rus_word[number_of_symbols_rus++] = dictionary[i][j];
			}
		}
	}
	if (search_completed == 0) {
		for (j = 0; j < number_of_symbols_true_word; j++) {
			additional_word[j] = word_for_translate[j][word_number];
		}
		translater(additional_word, number_of_symbols_true_word, keeper, check_for_emptiness, text);
	}
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Rus");
	
	int i, j, n, word_number = 0, number_of_symbols_in_word = 0, number_of_symbols_in_text, number_of_words, check_for_emptiness, error = 0, selection;
	
	char symbol, keeper;
	char *name_begin_text = (char*)malloc(50 * sizeof(char));
	char *name_dictionary_text = (char*)malloc(50 * sizeof(char));
	char *name_end_text = (char*)malloc(50 * sizeof(char));
	char **word = (char**)malloc(100 * sizeof(char*));
	for (i = 0; i < 100; i++) {
		word[i] = (char*)malloc(20 * sizeof(char));
	}
	char *text = (char*)malloc(10000 * sizeof(char));
	char **dictionary = (char**)malloc(100 * sizeof(char*));
	for (i = 0; i < 100; i++) {
		dictionary[i] = (char*)malloc(100 * sizeof(char));
	}
	char *translated_text = (char*)malloc(10000 * sizeof(char));
	
	if (!argv[1]) {
		printf("\nВведите название исходного текста: ");
		gets(name_begin_text);
		FILE *book_one = fopen(name_begin_text, "r");
		if (!book_one) {
			free(book_one);
			printf("\nЗаданного файла не существует. Введите повторно название исходного текста: ");
			gets(name_begin_text);
			FILE *book_two = fopen(name_begin_text, "r");
			for (i = 0; !feof(book_two); i++) {
				text[i] = fgetc(book_two);
			}
			fclose(book_two);
		} else {
			for (i = 0; !feof(book_one); i++) {
				text[i] = fgetc(book_one);
			}
			fclose(book_one);
		}
		
		number_of_symbols_in_text = i;
		
		printf("\nВведите название словаря: ");
		gets(name_dictionary_text);
		FILE *book_dictionary_one = fopen(name_dictionary_text, "r");
		if (!book_dictionary_one) {
			free(book_dictionary_one);
			printf("\nЗаданного файла не существует. Введите повторно название словаря: ");
			gets(name_dictionary_text);
			FILE *book_dictionary_two = fopen(name_dictionary_text, "r");
			for (i = 0; !feof(book_dictionary_two); i++) {
				fgets(dictionary[i], 100, book_dictionary_two);
			}
			fclose(book_dictionary_two);
		} else {
			for (i = 0; !feof(book_dictionary_one); i++) {
				fgets(dictionary[i], 100, book_dictionary_one);
			}
			fclose(book_dictionary_one);
		}
		
		printf("\nВведите название файла с конечным результатом: ");
		gets(name_end_text);
		FILE *end_text = fopen(name_end_text, "w");
		fclose(end_text);
	} else {
		FILE *book = fopen(argv[1], "r");
		for (i = 0; !feof(book); i++) {
			text[i] = fgetc(book);
		}
		fclose(book);
		
		number_of_symbols_in_text = i;
		
		FILE *book_dictionary = fopen(argv[2], "r");
		for (i = 0; !feof(book_dictionary); i++) {
			fgets(dictionary[i], 100, book);
		}
		fclose(book_dictionary);
		
		FILE *end_text = fopen(argv[3], "w");
		fclose(end_text);
	}
	
	printf("\n\n\nВыбрать способ перевода текста:\n	1) Перевод с русского на английский.\n	2) Перевод с английского на русский.\n	Ответ: ");
	scanf("%d", &selection);
	while (selection != 1 && selection != 2) {
		printf("\n\n\nНеверная переменная.\n");
		printf("Выбрать способ перевода текста:\n	1) Перевод с русского на английский.\n	2) Перевод с английского на русский.\n	Ответ: ");
		scanf("%d", &selection);
	}
	
	number_of_words = i;

	for (i = 0; i < number_of_symbols_in_text; i++) {
		if (text[i] == ' ' || text[i] == '	' || text[i] == '\n' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == EOF) {
			
			keeper = text[i];

			if (word[0][word_number] == '\0') {
				check_for_emptiness = 1;
				if (!argv[1]) {
					translater(NULL, 0, keeper, check_for_emptiness, name_end_text);
				} else {
					translater(NULL, 0, keeper, check_for_emptiness, argv[3]);
				}
			} else {
				check_for_emptiness = 0;
				if (!argv[1]) {
					word_search(word, word_number, number_of_symbols_in_word, dictionary, number_of_words - 1, selection, keeper, check_for_emptiness, name_end_text);
				} else {
					word_search(word, word_number, number_of_symbols_in_word, dictionary, number_of_words - 1, selection, keeper, check_for_emptiness, argv[3]);
				}
			}
			word_number++;
			number_of_symbols_in_word = 0;
		} else {
			word[number_of_symbols_in_word++][word_number] = text[i];
		}
	}
	
	FILE *count_symbols = fopen(name_end_text, "r");
	for (n = 0; !feof(count_symbols); n++) {
		translated_text[n] = fgetc(count_symbols);
	}
	fclose(count_symbols);
	FILE *rewrite = fopen(name_end_text, "w");
	for (i = 0; i < n - 2; i++) {
		fprintf(rewrite, "%c", translated_text[i]);
	}
	fclose(rewrite);
	
	free(word);
	free(text);
	free(dictionary);
	free(translated_text);
}
