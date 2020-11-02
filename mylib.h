#define BUFF_SIZE 1024
#define CHAR_FILLED_BY_P1 1
#define P2_COMPLETED 2
#define P3_COMPLETED 3

struct mem_seg {
	int status;
	char buff[BUFF_SIZE];
	int alphaNum;
	int specialChar;
};


