#include "data_handling.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
struct Data data;
data.length=0;
data.allocated=0;
data.variableList=NULL;


	toggle_debug(true);
	set_memory_batch_size(25);

	declare_variable(STR, "a", &data);
	declare_variable(INT, "b", &data);
	declare_variable(INT, "c", &data);
	declare_variable(INT, "d", &data);
	declare_variable(INT, "e", &data);

	assign_integer_by_name("b", 45, &data);
	assign_string_by_name("a", "Hejsan!", &data);

	print_all_variables_DEBUG(&data);

	printf("'a' = '%s'\n", get_string_by_name("a", &data));
	printf("'b' = %d\n", get_integer_by_name("b", &data));

	assign_integer_by_index(get_index_by_name_and_type(INT, "b", &data), 566, &data);
	assign_string_by_index(get_index_by_name_and_type(STR, "a", &data), "MEGUMIN!!", &data);

	print_all_variables_DEBUG(&data);

	free_variable_by_name_and_type(STR, "c", &data);
	free_variable_by_name_and_type(INT, "c", &data);

	print_all_variables_DEBUG(&data);


free(data.variableList);
data.variableList=NULL;
return 0;}
