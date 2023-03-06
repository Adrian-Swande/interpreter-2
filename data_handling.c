#include "data_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool DEBUG = false;
int MEMORY_BATCH = 10;


void allocate_memory(struct Data *data){
debug("allocating memory");

	if (data->allocated <= data->length)
		data->variableList = (struct Variable*)realloc(data->variableList, sizeof(struct Variable) * (data->length + MEMORY_BATCH)),
		data->allocated += MEMORY_BATCH;
	if (data->variableList == NULL)
		execution_error("realloc failed"),
		exit(0);
debug("end");}

int find_variable(char type, char *name, struct Data *data){
debug("searching for variable by name and type:");
debug(name);
if (type == INT) debug("integer");
else debug("string");

	int r = NONE;
	for (int i = data->length - 1; i >= 0; i--)
		if (!strcmp(data->variableList[i].name, name) &&
			data->variableList[i].type == type)
		{r = i; goto ret;}

ret: debug("end"); return r;}

void assign_integer_by_name(char *name, int integer, struct Data *data){
debug("assigning integer by name:");
debug(name);

	assign_integer_by_index(find_variable(INT, name, data), integer, data);

debug("end");}

void assign_string_by_name(char *name, char *string, struct Data *data){
debug("assigning string by name:");
debug(name);

	assign_string_by_index(find_variable(STR, name, data), string, data);

debug("end");}

void assign_integer_by_index(int index, int integer, struct Data *data){
debug("assigning integer by index:");
debug_int(index);

	if (index != NONE)
		data->variableList[index].integer = integer;
	else
		execution_error("tried to assign non-existing integer");

debug("end");}

void assign_string_by_index(int index, char *string, struct Data *data){
debug("assigning string by index:");
debug_int(index);
	
	if (index != NONE){
		char *temp = malloc(strlen(string) + 1);
		if (temp == NULL) execution_error("malloc failed"), exit(0);
		data->variableList[index].string = temp;

		strcpy(data->variableList[index].string, string);
	} else
		execution_error("tried to assign non-existing string");

debug("end");}


void declare_variable(char type, char *name, struct Data *data){
debug("declaring variable:");
debug(name);

	allocate_memory(data);
	
	data->variableList[data->length].type = type;
	
	char *temp = malloc(strlen(name) + 1);
	if (temp == NULL) execution_error("malloc failed"), exit(0);
	data->variableList[data->length].name = temp;
	
	strcpy(data->variableList[data->length].name, name);
	
	data->length++;
	
debug("end");}

int get_integer_by_name(char *name, struct Data *data){
debug("getting integer value by name:");
debug(name);

	int r = get_integer_by_index(find_variable(INT, name, data), data);

debug("end"); return r;}

char *get_string_by_name(char *name, struct Data *data){
debug("getting string value by name:");
debug(name);

	char *r = get_string_by_index(find_variable(STR, name, data), data);

debug("end"); return r;}

int get_integer_by_index(int index, struct Data *data){
debug("getting integer value by index:");
debug_int(index);

	int r = 0;
	if (index != NONE)
		r = data->variableList[index].integer;
	else
		execution_error("tried to get value from non-existing integer");

debug("end"); return r;}

char *get_string_by_index(int index, struct Data *data){
debug("getting string value by index:");
debug_int(index);

	char *r = NULL;
	if (index != NONE)
		r = data->variableList[index].string;
	else
		execution_error("tried to get value from non-existing string");

debug("end"); return r;}

int get_index_by_name_and_type(char type, char *name, struct Data *data){
debug("get index by name and type:");
debug(name);
if (type == INT) debug("integer");
else debug("string");

	int r = 0;
	int index = find_variable(type, name, data);
	if (index != NONE)
		r = index;
	else
		execution_error("tried to get index of non-existing variable");

debug("end"); return r;}

void free_variable_by_name_and_type(char type, char *name, struct Data *data){
debug("free variable by name and type:");
debug(name);
if (type == INT) debug("integer");
else debug("string");

	free_variable_by_index(find_variable(type, name, data), data);

debug("end");}
void free_variable_by_index(int index, struct Data *data){
debug("free variable by index:");
debug_int(index);

	if (index != NONE){
		free(data->variableList[index].name);
		free(data->variableList[index].string);
		for (int i = index; i < data->length; i++)
			data->variableList[i] = data->variableList[i + 1];
		free(data->variableList[data->length - 1].name);
		free(data->variableList[data->length - 1].string);
		data->length--;
	} else
		execution_error("tried to free non-existing variable");

debug("end");}

void execution_error(char *messsage){
	printf("\033[31mEXECUTION ERROR: '%s'\033[0m\n", messsage);
}

void print_all_variables_DEBUG(struct Data *data){
	printf("PRINTING OUT ALL VARIABLES (start)\n[allocated memory: %d, length: %d]\n", data->allocated, data->length);
	for (int i=0; i < data->length; i++){
		if (data->variableList[i].type == INT)
			printf("%d\ttype: int, name: '%s',\tvalue: %d;\n", i, data->variableList[i].name, data->variableList[i].integer);
		else
			printf("%d\ttype: str, name: '%s',\tvalue: '%s';\n", i, data->variableList[i].name, data->variableList[i].string);
	}
	printf("PRINTING OUT ALL VARIABLES (end)\n");
}

void toggle_debug(bool state){
	DEBUG = state;
}

void debug(char *message){
	if (DEBUG) printf("(\033[93m%s\033[0m)\n",message);
}

void debug_int(int integer){
	if (DEBUG) printf("(\033[93m%d\033[0m)\n",integer);
}

void set_memory_batch_size(unsigned int size){
	MEMORY_BATCH = size;
}
