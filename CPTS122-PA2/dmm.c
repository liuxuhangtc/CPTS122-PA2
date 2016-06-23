//PA2---XUHANG LIU

#include"dmm.h"

// string copy
char* stringcopy(char* str)
{
	int i;
	char* result;
	int len = strlen(str);

	result = (char*)malloc(len + 1);
	strcpy(result, str);

	for (i = 0; result[i]; i++) {
		if (result[i] == '\n' || result[i] == '\r')
			result[i] = 0;
	}
	return result;
}

//Count number
int cnt_num(Node* list)
{
	int cnt = 0;
	Node* temp = list;
	if (list == NULL)
		return 0;
	list->prev->next = NULL;

	while (temp != NULL)
	{
		cnt++;
		temp = temp->next;
	}

	list->prev->next = list;

	return cnt;
}

//Show the records
void show_records(Node* list)
{
	char type;
	Node* temp;

	printf("Enter 1 to display all options or enter 2 to search: ");
	scanf("%c", &type);

	if (type == '1')
	{
		if (list == NULL)
			printf("The list is empty.\n");
		else
		{
			list->prev->next = NULL;
			for (temp = list; temp != NULL; temp = temp->next)
			{
				display_info(temp->record);
			}
			list->prev->next = list;
		}
	}
	else
	{
		temp = scan_field(list);
		if (temp == NULL)
			printf("No record found!\n");
		else
			display_info(temp->record);
	}
}

//Display
void display_info(song* record)
{
	if (record != NULL)
	{
		printf("Artist: %s\n", record->artist);
		printf("Album title: %s\n", record->album_title);
		printf("Song title: %s\n", record->song_title);
		printf("Genre: %s\n", record->genre);
		printf("Length:  %d:%02d\n", record->length.min,
			record->length.sec);
		printf("Rating: %d\t # of times played: %d\n\n", record->rate,
			record->counter);
	}
}

//Load from file
Node* load()
{
	FILE* fp = fopen("data.txt", "r");

	int cnt = 0;

	Node* list = NULL;
	Node* temp;

	char line[128];
	char ch;

	if (fp == NULL)
	{
		printf("Failed to open the file\n");
		return NULL;
	}

	fscanf(fp, "%d", &cnt);
	ch = fgetc(fp);

	while (ch != '\n' && !feof(fp))
		ch = fgetc(fp);

	for (; cnt > 0; cnt--)
	{
		temp = (Node*)malloc(sizeof(Node));
		temp->record = (song*)malloc(sizeof(song));

		fgets(line, sizeof(line), fp);
		temp->record->artist = stringcopy(line);

		fgets(line, sizeof(line), fp);
		temp->record->album_title = stringcopy(line);

		fgets(line, sizeof(line), fp);
		temp->record->song_title = stringcopy(line);

		fgets(line, sizeof(line), fp);
		temp->record->genre = stringcopy(line);

		fscanf(fp, "%d %d %d %d", &(temp->record->length.min),
			&(temp->record->length.sec),
			&(temp->record->counter), &(temp->record->rate));

		ch = fgetc(fp);

		while (ch != '\n' && !feof(fp))
			ch = fgetc(fp);


		if (list == NULL)
		{
			temp->prev = temp;
			temp->next = temp;
			list = temp;
		}
		else
		{
			temp->next = list;
			temp->prev = list->prev;
			temp->prev->next = temp;
			list->prev = temp;
		}
	}

	fclose(fp);

	return list;
}

//Store to the file
void store_info(Node* list)
{
	Node* curr = list;
	FILE* fp = fopen("data.txt", "w");
	fprintf(fp, "%d\n", cnt_num(list));

	while (curr != NULL)
	{

		fprintf(fp, "%s\n", curr->record->artist);
		fprintf(fp, "%s\n", curr->record->album_title);
		fprintf(fp, "%s\n", curr->record->song_title);
		fprintf(fp, "%s\n", curr->record->genre);
		fprintf(fp, "%d %d %d %d\n", curr->record->length.min,
			curr->record->length.sec,
			curr->record->counter,
			curr->record->rate);

		curr = curr->next;

		if (curr == list)
			curr = NULL;
	}

	fclose(fp);
}

//Delete method
void del_list(Node* list)
{
	Node* temp;

	if (list == NULL)
		return;


	list->prev->next = NULL;

	while (list != NULL)
	{
		temp = list;
		list = list->next;

		del_record(temp->record);
		free(temp);
	}
}

//Delete
void del_record(song* record)
{
	if (record == NULL)
		return;


	free(record->artist);
	free(record->album_title);
	free(record->song_title);
	free(record->genre);

	free(record);
}

//Remove
void remove_record(Node** pList)
{
	Node* temp = search_songTitle(*pList);

	if (temp == NULL)
		printf("No record was found.\n");
	else
	{
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;

		if (temp->next == temp)
			*pList = NULL;
		else if (temp == (*pList))
			(*pList) = temp->next;

		del_record(temp->record);
		free(temp);

		printf("Record deleted successfully!\n");
	}
}

//Ask info to insert
Node* read()
{
	char line[128];
	Node* result = (Node*)malloc(sizeof(Node));
	song* record = (song*)malloc(sizeof(song));
	result->record = record;

	fflush(stdin);
	printf("Please answer few questions for the music and your answer should not include spaces and enter. Thank you!\n");
	printf("Who's the artist: ");
	gets(line);
	record->artist = stringcopy(line);

	printf("What's the name of the album: ");
	gets(line);
	record->album_title = stringcopy(line);

	printf("What's the name of the song: ");
	gets(line);
	record->song_title = stringcopy(line);

	printf("What's the genre: ");
	gets(line);
	record->genre = stringcopy(line);

	printf("How many minutes and seconds is the song respectively:(Format like 3 30)  ");
	scanf("%d %d", &(record->length.min), &(record->length.sec));

	printf("How many times have you played the song: ");
	scanf("%d", &(record->counter));

	printf("What would you rate the song out of 5: ");
	scanf("%d", &(record->rate));

	return result;
}

//Sorting
void sort_fun(Node** pList, Node* node, int option)
{
	Node* start = *pList;
	Node* temp = start;
	int cmp;

	if (start != NULL)
		start->prev->next = NULL;


	while (temp != NULL)
	{
		if (option == 1)
			cmp = strcmp(temp->record->artist, node->record->artist);
		else if (option == 2)
			cmp = strcmp(temp->record->genre, node->record->genre);
		else
			cmp = temp->record->rate - node->record->rate;

		if (cmp >= 0)
			break;

		temp = temp->next;
	}

	if (start == NULL)
	{
		node->prev = node->next = node;
		*pList = node;
	}
	else if (temp == NULL)
	{

		node->next = start;
		node->prev = start->prev;
		start->prev->next = node;
		start->prev = node;
	}
	else
	{

		start->prev->next = start;


		node->next = temp;
		node->prev = temp->prev;
		node->prev->next = node;
		temp->prev = node;

		if (temp == start)
			*pList = node;
	}
}

//Sorts
void sort_records(Node** pList, int option)
{
	Node* temp = *pList;
	Node* node;

	if (temp == NULL)
		return;

	temp->prev->next = NULL;
	*pList = NULL;

	while (temp != NULL)
	{
		node = temp->next;

		sort_fun(pList, temp, option);

		temp = node;
	}
}

//Rate
void rate(song* record)
{
	display_info(record);
	printf("Enter its rating out of 5: ");
	scanf("%d", &(record->rate));
}

//Edit
void edit(song* record)
{
	char line[128];
	int val = 0;

	fflush(stdin);
	printf("Current artist: %s\n", record->artist);
	printf("You can enter a new value or press ENTER to skip: ");
	gets(line);
	if (strlen(line) > 0)
	{
		free(record->artist);
		record->artist = stringcopy(line);
	}

	printf("Current album title: %s\n", record->album_title);
	printf("You can enter a new album title or ENTER to continue: ");
	gets(line);
	if (strlen(line) > 0)
	{
		free(record->album_title);
		record->album_title = stringcopy(line);
	}

	printf("Current song title: %s\n", record->song_title);
	printf("You can enter a new song title or ENTER to continue: ");
	gets(line);
	if (strlen(line) > 0)
	{
		free(record->song_title);
		record->song_title = stringcopy(line);
	}

	printf("Current genre: %s\n", record->genre);
	printf("You can enter a new genre or ENTER to continue: ");
	gets(line);
	if (strlen(line) > 0)
	{
		free(record->genre);
		record->genre = stringcopy(line);
	}

	printf("Current minutes value: %d\n", record->length.min);
	printf("You can enter new minutes value or enter -1 to skip: ");
	scanf("%d", &val);
	if (val >= 0)
		record->length.min = val;

	printf("Current seconds value: %d\n", record->length.sec);
	printf("You can enter a new seconds value or enter -1 to skip: ");
	scanf("%d", &val);
	if (val >= 0)
		record->length.sec = val;

	printf("Current number of times played: %d\n", record->counter);
	printf("Enter new value or enter -1 to skip: ");
	scanf("%d", &val);
	if (val >= 0)
		record->counter = val;

	printf("Current rating: %d\n", record->rate);
	printf("Enter new value or enter -1 to skip: ");
	scanf("%d", &val);
	if (val >= 0)
		record->rate = val;

}

//Scan and to display
Node* scan_field(Node *list)
{
	int field;
	char key[128];
	int key_value = 0;
	int cnt = cnt_num(list);
	int i;

	printf("Fields:\n\n");
	printf("1) Artist\n");
	printf("2) Album title\n");
	printf("3) Song title\n");
	printf("4) Genre\n");
	printf("5) Minutes\n");
	printf("6) Seconds\n");
	printf("7) Number of times played\n");
	printf("8) Rating\n\n");
	printf("Enter your selection(1 - 8): ");
	scanf("%d", &field);
	fflush(stdin);
	printf("Enter search key: ");
	if (field >= 5 && field <= 8)
		scanf("%d", &key_value);
	else
		gets(key);

	for (i = 0; i < cnt; i++)
	{
		if ((field == 1 && strcmp(key, list->record->artist) == 0) ||
			(field == 2 && strcmp(key, list->record->album_title) == 0) ||
			(field == 3 && strcmp(key, list->record->song_title) == 0) ||
			(field == 4 && strcmp(key, list->record->genre) == 0) ||
			(field == 5 && key_value == list->record->length.min) ||
			(field == 6 && key_value == list->record->length.sec) ||
			(field == 7 && key_value == list->record->counter) ||
			(field == 8 && key_value == list->record->rate))

			return list;

		list = list->next;
	}
	return NULL;
}

//Search from the title
Node* search_songTitle(Node *list)
{
	char title[128];

	Node* temp = list;

	fflush(stdin);
	printf("Enter the song title: ");
	gets(title);

	while (temp != NULL)
	{
		if (strcmp(temp->record->song_title, title) == 0)
			return temp;
		temp = temp->next;

		if (temp == list)
			temp = NULL;
	}

	return NULL;
}