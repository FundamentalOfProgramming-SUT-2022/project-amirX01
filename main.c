#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 100

int EXIT = 1;

char input[MAXN][MAXN], arman_val[MAXN];

void array_free(char to_be_free[]) {
	for (int i = 0; i < MAXN; i ++) 
		to_be_free[i] = '\0';
}

int strcomp(char s1[], char s2[]) {
	if (strlen(s1) != strlen(s2))
		return 0;
	else {
		for (int i = 0; i < strlen(s1); i ++) {
			if (s1[i] != s2[i])
				return 0;
		}
	}
	return 1;
}

char* strcomb(char* s, char* s1) {
    	int i, j;
	char *s3;
	printf("%s", s);
	for (i = 0; i < strlen(s); i ++)
		s3[i] = s[i];
	printf("%s", s1);
    	for (j = 0; strlen(s1); j++) {
        	s3[i + j] = s1[j];
    	} 
    	s3[i + j] = '\0'; 
	printf("%s", s3);
    	return s3;
}

void delay(int number_of_seconds) {
    	int milli_seconds = 1000 * number_of_seconds;
    	clock_t start_time = clock();
    	while (clock() < start_time + milli_seconds);
}

bool file_exists(char filename[]) {
    	FILE *fp = fopen(filename, "r");
    	bool is_exist = false;
    	if (fp != NULL) {
        	is_exist = true;
    		fclose(fp);
	}
    	return is_exist;
}

void backup(char path[]) {
	char filename[MAXN], addr[MAXN], command[MAXN] = "cp ", *final;
	int break_point = 0;
	array_free(filename);
	array_free(addr);
	for (int i = strlen(path) - 1; path[i] != '/'; i --)
		break_point = i;
	filename[0] = '.';
	for (int i = break_point; i < strlen(path); i ++)
		filename[i - break_point + 1] = path[i];
	for (int i = 0; i < break_point; i ++) 
		addr[i] = path[i];
	final = strcat(command, path);
	final = strcat(final, " ");
	final = strcat(final, addr);
	final = strcat(final, filename);
	printf("%d %s %s %s", break_point, final, filename, addr);
	system(final);
}

void putfileinstring(char path[]) {
	FILE *fptr;
    	char c;
    	fptr = fopen(path, "r");
    	if (fptr == NULL) {
        	printf("Cannot open the file.\n");
        	return;
    	}
    	c = fgetc(fptr);
	arman_val[0] = c;
    	for (int i = 1; c != EOF; i ++) {
        	c = fgetc(fptr);
		arman_val[i] = c;
    	}
    	fclose(fptr);
    	return;	
}

void get_input();

void createfile(char filename[], char path[]) {
	char mkdir[1000000] = "mkdir -p ", touch[1000000] = "touch ";
	if (filename[0] == 34) {
		filename[0] = 39, filename[strlen(filename) - 1] = 39;
		path[0] = 39, path[strlen(path) - 1] = 39;
	}	
	printf("%s %s\n", filename, path);
	if (file_exists(filename))
		printf("the given file name is exists.\n");
	else {
		system(strcat(mkdir, path));
		system(strcat(touch, filename));
		printf("file created sucsesfully.\n");
	}
	return;
}

void insertstr(char path[], char str[], int line_no, int line_pos) {
	FILE *fp;
	long Fin, lSize;
	int position = 0, line_num = 0;
	char c;
	printf("%s %s", path,  str);
	fp = fopen(path, "r+");
	if (fp == NULL) {
		printf("Cannot openthe file.\n");
		return;
	}
	backup(path);
	while (line_num < line_no - 1 && c != EOF) {
		if (c == EOF || line_num >= line_no - 1)
			break;
		c = fgetc(fp);
		position ++;
		if (c == '\n')
			line_num ++;
	}
	for (int i = 0; i < line_pos; i ++) {
		c = fgetc(fp);
		position ++;
	}
	printf("%d", position);
	fseek(fp, 0L, SEEK_END);
	Fin = ftell(fp);
	fseek(fp, position, SEEK_SET);
	char *buffer;
	lSize = Fin - position;
	buffer = (char*) malloc(sizeof(char) * lSize);
	size_t result = fread(buffer, 1, lSize, fp);
	fseek(fp, position, SEEK_SET);
	fputs(str, fp);
	fputs(buffer, fp);
	fclose(fp);
	return;
}

void cat(char path[]) {
	FILE *fptr;
    	char c;
    	fptr = fopen(path, "r");
    	if (fptr == NULL) {
        	printf("Cannot open the file.\n");
        	return;
    	}
    	c = fgetc(fptr);
	arman_val[0] = c;
    	for (int i = 1; c != EOF; i ++) {
        	printf ("%c", c);
        	c = fgetc(fptr);
		arman_val[i] = c;
    	}
    	fclose(fptr);
    	return;	
}

void removestr(char path[], int line_no, int start, int count) {
	FILE *fp;
	char c;
	int position = 0, line_num = 0;
	long Fin, lSize;
	fp = fopen(path, "r+");
	if (fp == NULL) {
		printf("Cannot open the file.\n");
		return;
	}
	backup(path);
	printf ("%s %d %d %d\n", path, line_no, start, count);
	while (line_num < line_no - 1 && c != EOF) { 
		if (c == EOF || line_num >= line_no - 1)
			break;
		c = fgetc(fp);
		position ++;
		if (c == '\n')
			line_num ++;
	}
	printf ("heyyy2222\n");
	for (int i = 0; i < start; i ++) {
		c = fgetc(fp);
		position ++;
	}
	printf("heyyyyyyy3\n");
	fseek(fp, 0L, SEEK_END);
	Fin = ftell(fp);
	if (count < 0)
		fseek(fp, position + count, SEEK_SET);
	else 
		fseek(fp, position, SEEK_SET);
	char *buffer;
	lSize = Fin - position;
	buffer = (char*) malloc(sizeof(char) * lSize);
	size_t result = fread(buffer, 1, lSize, fp);
	if (count > 0)
		fseek(fp, position, SEEK_SET);
	else 
		fseek(fp, position + count, SEEK_SET);
	fputs(buffer, fp);
	fputc(EOF, fp);
	fclose(fp);
	return;
	
}

void copystr(char path[], int line_no, int start, int count) {
	FILE *fp, *fptr;
	char c;
	int position, line_num;
	fp = fopen(path, "r+");
	if (fp == NULL) {
		printf("Cannot open the file.\n");
	}
	printf ("%s %d %d %d\n", path, line_no, start, count);
	while (line_num < line_no - 1 && c != EOF) { 
		if (c == EOF || line_num >= line_no - 1) 
			break;
		c = fgetc(fp);
		position ++;

		if (c == '\n')
			line_num ++;
	}
	printf ("heyyybro\n");
	for (int i = 0; i < start; i ++) {
		c = fgetc(fp);
		position ++;
	}
	printf("heyyyyyyybro3\n");
	if (count < 0)
		fseek(fp, position + count, SEEK_SET);
	else 
		fseek(fp, position, SEEK_SET);
	printf("111");
	char *buffer;
	buffer = (char*) malloc(sizeof(char) * count);
	size_t result = fread(buffer, 1, count, fp);
	fclose(fp);
	//printf("insert it pelease");
	fptr = fopen("system/clipboard.txt", "w+");
	fputs(buffer, fptr);
	fclose(fptr);
	return;
}

void cutstr(char path[], int line_no, int start, int count) {
	backup(path);
	copystr(path, line_no, start, count);
	removestr(path, line_no, start, count);
	return;
}

void pastestr(char path[], int line_no, int line_pos) {
	FILE *fp, *fptr;
	char c;
	long FIN;
	backup(path);
	fptr = fopen("system/clipboard.txt", "r");
	fseek(fptr, 0L, SEEK_END);
	FIN = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	char *buffer;
	buffer = (char*) malloc(sizeof(char) * FIN);
	size_t result = fread(buffer, 1, FIN, fptr);
	fclose(fptr);
	insertstr(path, buffer, line_no, line_pos);
}

void findstr(char str[], char path[]);
//void replacestr(char str[], char replace[], char path[]);
void grep() {
	char commandv1[MAXN] = "grep -i ", commandv2[MAXN] = "grep -l ", commandv3[MAXN] = "grep -c ", command2[MAXN] = " > grepoutput.txt", *finalv;
	if (strcomp(input[1], "-l")) {
		finalv = strcat(commandv2, input[3]);
		for (int i = 5; input[i][0] != '\0'; i ++) {
			finalv = strcat(finalv, " ");
			finalv = strcat(finalv, input[i]);
		}
		finalv = strcat(finalv, command2);
		system(finalv);
	}
	else if (strcomp(input[1], "-c")) {
		finalv = strcat(commandv3, input[3]);
		for (int i = 5; input[i][0] != '\0'; i ++) {
			finalv = strcat(finalv, " ");
			finalv = strcat(finalv, input[i]);
		}
		finalv = strcat(finalv, command2);
		system(finalv);
	}
	else {
		finalv = strcat(commandv1, input[2]);
		for (int i = 4; input[i][0] != '\0'; i ++) {
			finalv = strcat(finalv, " ");
			finalv = strcat(finalv, input[i]);
		}
		finalv = strcat(finalv, command2);
		system(finalv);
	}
	putfileinstring(grepoutput.txt);
}

void auto_indent(char path[]) {
	FILE *fp;
	int indent_count = 0, position = 0;
	char c;
	fp = fopen(path, "+r");
	if (fp == NULL) {
		printf("Cannot open the file.\n");
		return;
	}
	printf("im in");
	while (c != EOF) {
		c = fgetc(fp);
		position ++;
		if (c == '{') {
			indent_count ++;
			fputc('\n', fp);
			for (int i = 0; i < indent_count * 4; i ++)
				fputc(' ', fp);
		}
		else if (c == '}') {
			indent_count --;
			fseek(fp, position - 1, SEEK_SET);
			fputc('\n', fp);
			for (int i = 0; i < indent_count * 4; i ++)
				fputc(' ', fp);
			fseek(fp, position, SEEK_SET);
			fputc('\n', fp);
			for (int i = 0; i < indent_count * 4; i ++);
		}
	}
	fclose(fp);
	char command[MAXN] = "indent -linux ";
	system(strcat(command, path));
}

void compare(char path1[], char path2[]) {
	FILE *fp1, *fp2;
	char line1[MAXN], line2[MAXN], backup[MAXN][MAXN];
	int br = 1, i = 1, j = 1;
	fp1 = fopen(path1, "r+");
	fp2 = fopen(path2, "r+");
	for (i = 1; i < 5; i ++){
		array_free(line1);
		array_free(line2);
		fgets(line1, MAXN, fp1);
		fgets(line2, MAXN, fp2);
		if (!strcomp(line1, line2)) {
			if (line1 != '\0' && line2 != '\0')
				printf("============ #%d ============\n%s\n%s\n", i, line1, line2);
			else if (line1 != NULL || line2 != NULL) {
				for (j = 1; line1 == NULL && line2 == NULL; j ++) {
					if(line1 != NULL)
						fgets(backup[i], MAXN, fp1);
					else
						fgets(backup[i], MAXN, fp2);
				}
				printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n", i, i + j);
				for (int k = k; k < j; k ++)
					printf("%s\n", backup[k]);
			}
			else
				br = 0;
		}
		
	}
}
void tree(char depth[]) {
	char command[MAXN] = "tree -L ", command2[MAXN] = " > treeoutput.txt", *final;
	if (!strcmp(depth, "-1")) {
		system("tree");
		return;
	}
	final = strcat(command, depth);
	printf("%s", final);
	final = strcat(final, command2);
	printf("%s", final);
	system(final);
	putfileinstring("treeoutput.txt");
	return;
}

void arman(int i) {
	if (strcomp(input[i + 1], "insertstr")) {
		//insertstr(input[i + 3], arman_val, )
	}

}

void get_input() {
	//printf("%s", strcomb(input[0], input[1]));
	for (int i = 0; i < MAXN; i ++)
		array_free(input[i]);
	int valid_command = 1, len, len2, count_space = 0, count_word = 0;
	char c;
	do {
		scanf("%c", &c);
		if (c == '\n')
			break;
		else if (c == 34) {
			do {
				if (c == '\n')
					break;
				scanf("%c", c);
				input[count_space][count_word] = c;

			} while (c != 34);
		}
		else if (c == ' ') {
			//printf("%s ", input[count_space]);
			count_space ++;
			count_word = 0;
		}
		else {
			input[count_space][count_word] = c;
			count_word ++;
		}
	} while (c != '\n');
	//printf("%s", input[7]);	
	for (int i = 0; i < MAXN; i ++) {
		if (strcomp(input[i], "=D")) {
			arman(i);
			return;
		}
	}
	if (strcomp(input[0], "createfile")) {
		char path[MAXN];
		int path_end;
		for (int i = strlen(input[2]); input[2][i] != '/'; i --)
			path_end = i;
		for (int i = 0; i < path_end; i ++) 
			path[i] = input[2][i];
		createfile(input[2], path);
	}
	else if (strcomp(input[0], "cat")) {
		printf("%s\n", input[2]);
		cat(input[2]);
	}
	else if (strcomp(input[0], "tree"))
		tree(input[2]);
	else if (strcomp(input[0], "insertstr")) {
		int line_no = 0, line_pos = 0, i = 0;
		for (i = 0; input[6][i] != ':'; i++)
			line_no = 10 * line_no + input[6][i] - '0';
		for (++ i; i < strlen(input[6]); i ++)
			line_pos = 10 * line_pos + input[6][i] - '0';
		insertstr(input[2], input[4], line_no, line_pos);
	}
	else if (strcomp(input[0], "removestr") || strcomp(input[0], "copystr") || strcomp(input[0], "cutstr")) {
		int line_no = 0, i = 0, line_pos = 0, count = 0;
		for (i = 0; input[4][i] != ':'; i ++)
			line_no = line_no * 10 + (input[4][i] - '0');
		for (++ i; i < strlen(input[4]); i ++)
			line_pos = line_pos * 10 + (input[4][i] - '0');
		for (i = 0; i < strlen(input[6]); i ++)
			count = count * 10 + (input[6][i] - '0');
		printf("%d", count);
		if (input[7][1] == 'b') {
			printf("yes");
			count *= -1;
		}
		if (strcomp(input[0], "removestr"))
			removestr(input[2], line_no, line_pos, count);
		else if (strcomp(input[0], "copystr"))
			copystr(input[2], line_no, line_pos, count);
		else
			cutstr(input[2], line_no, line_pos, count);
	}
	else if (strcomp(input[0], "pastestr")) {
		int line_no = 0, i = 0, line_pos = 0;
		for (i = 0; input[4][i] != ':'; i ++)
			line_no = line_no * 10 + input[4][i] - '0';
		for (++ i; i < strlen(input[4]); i ++)
			line_pos = line_pos * 10 + input[4][i] - '0';
		pastestr(input[2], line_no, line_pos);
	}
	else if (strcomp(input[0], "compare"))
		compare(input[1], input[2]);
	else if (strcomp(input[0], "auto_indent"))
		auto_indent(input[1]);
	else if (strcomp(input[0], "grep")) {
		grep();
	}
	else
		printf("invalid command\n");
	//printf("testing");
	//backup("root/test.txt");
	return;
}

int main() {
	while(EXIT == 1) { 
		get_input();
	}	
}
