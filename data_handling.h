#ifndef MEGUMIN_H
#define MEGUMIN_H

typedef unsigned char byte;
#define bool byte

#define true 1
#define false 0


#define INT 	-1
#define STR 	-2
#define NONE	-3


struct Variable
{
	char *name;
	char type;

	int integer;
	char *string;
};

struct Data
{
	bool DEBUG;
	struct Variable *variableList;
	unsigned int length;
	unsigned int allocated;
};


void allocate_memory(struct Data *data);

int find_variable(char type, char *name, struct Data *data);

void assign_integer_by_name(char *name, int integer, struct Data *data);
void assign_string_by_name(char *name, char *string, struct Data *data);

void assign_integer_by_index(int index, int integer, struct Data *data);
void assign_string_by_index(int index, char *string, struct Data *data);

void declare_variable(char type, char *name, struct Data *data);

int get_integer_by_name(char *name, struct Data *data);
char *get_string_by_name(char *name, struct Data *data);

int get_integer_by_index(int index, struct Data *data);
char *get_string_by_index(int index, struct Data *data);

int get_index_by_name_and_type(char type, char *name, struct Data *data);

void free_variable_by_name_and_type(char type, char *name, struct Data *data);
void free_variable_by_index(int index, struct Data *data);

void execution_error(char *messsage);
void print_all_variables_DEBUG(struct Data *data);
void toggle_debug(bool state);
void debug(char *message);
void debug_int(int integer);

void set_memory_batch_size(unsigned int size);

#endif
