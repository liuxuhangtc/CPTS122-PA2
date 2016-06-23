/*******************************************************************************************
* Programmer: Xuhang Liu                                                                   *
* Class: Cpts 122, Summer 2016                                                             *
* PA #2                                                                                    *
* Date: June 20, 2016                                                                      *
* Description: Digital Music Manager					                                   *
*******************************************************************************************/


// Header

#ifndef DMM_H
#define DMM_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

//Structs
typedef struct song
{
	char* artist;
	char* album_title;
	char* song_title;
	char* genre;

	struct song_length
	{
		int min;
		int sec;

	} length;
	
	int counter;
	int rate;

}song;

typedef struct Node
{
	song *record;

	struct Node *next;
	struct Node *prev;
}Node;


Node* scan_field(Node *list);
Node* search_songTitle(Node *list);
Node* read();
Node* load();

//Functions
char* stringcopy(char* str);
int cnt_num(Node* list);
void display_info(song* record);
void show_records(Node* list);
void store_info(Node* list);
void del_list(Node* list);
void del_record(song* record);
void remove_record(Node** pList);
void sort_fun(Node** pList, Node* node, int option);
void sort_records(Node** pList, int option);
void rate(song* record);
void edit(song* record);


#endif