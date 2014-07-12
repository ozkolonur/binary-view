#include <stdio.h>
#include <malloc.h>
#include <string.h>

char *itob(int value);
int btoi(char *value);
void print_usage(void);

int main(int argc, char* argv[])
{
    unsigned int val;
    if (argc < 2)
    {
	print_usage();
	return 0;
    }
    if(strncmp(argv[1], "0b", 2) == 0)
    {
    	printf("%s:\t0x%08x\n", itob(btoi(argv[1])), btoi(argv[1]));
	printf("        |       |       |       \n");
	printf("        23      15      7       \n");
    }
    else if(strncmp(argv[1], "0x", 2) == 0)
    {
	val = strtol(argv[1], (char**)NULL, 16);
	printf("0x%08x:\t%s", val, itob(val)); 	 /* wrong usage: creates memory leak*/
	printf("\n\t\t        |       |       |       \n");
	printf("\t\t        23      15      7       \n");
    }
    else
	print_usage();

    return 0;
}

void print_usage(void)
{
    printf("Views hex or binary representation of any value.\n");
    printf("Usage:\n\tbview <0b...>\n\tbview <0x...>\n");
}

/*
 * @brief	gets binary representation of an integer (like 0xa5 = 0b10100101)
 *
 * @param	value, integer expression which we need to get its binary form. 
 * 
 * @returns	returns pointer to char array which includes binary form. 
 *		creates array using malloc, it can be freed later.
 */
char *itob(int value)
{
    char *result = malloc(33 * sizeof(char));
    char *tmp = result;
    int bitnum = sizeof(int) * 8 - 1;
    int i;
    
    for(i=0; i< bitnum + 1; i++, tmp++)
    {
	if (value & (1 << (bitnum - i)))
	    *tmp = '1';
	else
	    *tmp = '0';
    }
    *tmp = '\0';
    return result;
}    

/*
 * @brief	gets binary representation of an integer (like 0b10100101 = 0xa5)
 *
 * @param	value, char array of 1s and 0s, which we need to get its hex form. 
 * 
 * @returns	returns integer expression computed from input.
 */
int btoi(char *value)
{
    int bitnum = sizeof(int) * 8 - 1;
    int i, len, result = 0;
    char *tmp= value;  
    
    /* Remove first two bytes if they are 0b.... */
    if(strstr(value, "0b") == tmp)
	tmp += 2;

    len = strlen(tmp);
    tmp += len - 1; /* Seek end */
    for(i=0; i < len; i++, tmp--)
    {
	if(*tmp == '1')
	    result |= (1<<i);
    }
    return result;
}    

