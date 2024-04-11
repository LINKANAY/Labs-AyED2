#ifndef FUNTION_H

void dump(char a[], unsigned int length);
unsigned int data_from_file(const char *path, unsigned int  indexes[], char letters[], unsigned int max_size);
char *parse_filepath(int argc, char *argv[]);
void arraySorted(unsigned int indexes[], char letters[], char sorterd[], unsigned int length);

#endif

