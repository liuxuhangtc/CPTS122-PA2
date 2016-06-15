/*******************************************************************************************
* Programmer: Xuhang Liu                                                                   *
* Class: Cpts 122, Summer 2016                                                             *
* PA #2                                                                                    *
* Date: June 20, 2016                                                                      *
* Description: Digital Music Manager					                                   *
*******************************************************************************************/

#include"dmm.h"

int main()
{
	char menu = '1';
	Node* list = NULL;
	Node* result;


	int sort_option = 1;

	do
	{

		system("cls"); // Print menu
		printf("Welcome to the Digital Music Manager\n\n");
		printf("1. Load\n");
		printf("2. Store\n");
		printf("3. Display\n");
		printf("4. Insert\n");
		printf("5. Delete\n");
		printf("6. Edit\n");
		printf("7. Sort\n");
		printf("8. Rate\n");
		printf("9. Exit\n\n");

		printf("Please enter your choice(1-9): ");
		scanf("%c", &menu);

		fflush(stdin);
		system("cls");

		if (menu == '1')
		{
			del_list(list);
			list = load();
			if (list != NULL)
				printf("Loaded successfully.\n");
		}
		else if (menu == '2')
		{
			store_info(list);
			printf("Saved successfully\n");
		}
		else if (menu == '3')
		{
			show_records(list);
		}
		else if (menu == '4')
		{
			result = read();
			sort_fun(&list, result, sort_option);
			printf("A new record was added.\n");
		}
		else if (menu == '5')
		{
			remove_record(&list);
		}
		else if (menu == '6')
		{
			result = scan_field(list);
			if (result == NULL)
				printf("The record you want wasn't found!\n");
			else
				edit(result->record);
		}
		else if (menu == '7')
		{
			printf("Enter sort option( (1)Artist, (2)Genre, (3)Rating):");
			scanf("%d", &sort_option);
			sort_records(&list, sort_option);

			printf("The list was sorted as:\n\n");
		}
		else if (menu == '8')
		{
			result = scan_field(list);
			if (result == NULL)
				printf("No record found.\n");
			else
				rate(result->record);
		}
		else if (menu != '9')
		{
			printf("Please enter a valid number!\n");
		}


		if (menu != '9')
			system("PAUSE");

	} while (menu != '9');

	store_info(list);
	del_list(list);

	return 0;

}