#include "bpt.h"

// MAIN

int main(int argc, char ** argv) {

	char * input_file;
	char *str;								// use as the name of the file to be opened;
	char *rec_str;
	char new_file[100];
	char record_value[120];
	FILE * fp;
	int file_d;
	node * root;
	int input, range2;
	char instruction;
	char license_part;

	root = NULL;												// ???
	verbose_output = false;										// ???

	if (argc > 1) {												// this is when error occurs
		order = atoi(argv[1]);									// ???. 
		if (order < MIN_ORDER || order > MAX_ORDER) {			// minorder and maxorder is defined in the bpt.h MIN == 3, MAX == 20. only available from 3 to 20
			fprintf(stderr, "Invalid order: %d .\n\n", order);
			usage_3();											// function usage3 defined in bpt.c
			exit(EXIT_FAILURE);
		}
	}

	license_notice();											// when first initiated, print out the following licence, usage1, usage2
	usage_1();
	usage_2();
	if (argc > 2) {								// when arguments are three, the first arg is order and the second arg is the pathname
		input_file = argv[2];									// it automatically read the tree and insert.
		fp = fopen(input_file, "r");
		if (fp == NULL) {
			perror("Failure1  open input file.");
			exit(EXIT_FAILURE);
		}
		while (!feof(fp)) {
			fscanf(fp, "%d\n", &input);
			root = insert(root, input, input);
		}
		fclose(fp);
		print_tree(root);										// read the tree and operate insertion, then print out the tree.
	}


	if (argc <= 1) {											// if the file name is not inserted, we should make new file
		printf("> ");
		for (;;) {
			scanf("%c", &instruction);
			if (instruction == 'o') {
				fgets(new_file , sizeof(new_file), stdin);
				new_file[strlen(new_file) - 1] = '\0';
				//				scanf("%s", &open_file);
				*str = new_file;
				if ((file_d=open(str, O_CREAT | O_RDWR | O_TRUNC, 755)) == 1) {
					perror("Failure2  open input file.\n");
					exit(EXIT_FAILURE);
				}
				if (close(file_d) == -1)
					printf("close error");
				else {
					fp = fopen(str, "rw");
					if (fp == NULL) {
						perror("Failure2  open open_file\n");
						exit(EXIT_FAILURE);
					}
					break;
				}
			}
			else {
				usage_4();
				printf("> ");
			}
		}
	}


	printf("> ");												// this part is operated after the file is opened
	while (scanf("%c", &instruction) != EOF) {
		switch (instruction) {
		case 'd':
			scanf("%d", &input);
			root = delete(root, input);
			print_tree(root);
			break;
		case 'i':												// MODIFY the insert function record, int + string
			scanf("%d", &input);
			fgets(record_value, sizeof(record_value), stdin);
			record_value[strlen(record_value) - 1] = '\0';
			//				scanf("%s", &open_file);
			*rec_str = record_value;
			root = insert(root, input, rec_str);
			print_tree(root);
			break;
		case 'f':
		case 'p':
			scanf("%d", &input);
			find_and_print(root, input, instruction == 'p');
			break;
		case 'r':
			scanf("%d %d", &input, &range2);
			if (input > range2) {
				int tmp = range2;
				range2 = input;
				input = tmp;
			}
			find_and_print_range(root, input, range2, instruction == 'p');
			break;
		case 'l':
			print_leaves(root);
			break;
		case 'q':
			while (getchar() != (int)'\n');
			return EXIT_SUCCESS;
			break;
		case 't':
			print_tree(root);
			break;
		case 'v':
			verbose_output = !verbose_output;
			break;
		case 'x':
			if (root)
				root = destroy_tree(root);
			print_tree(root);
			break;
		default:
			usage_2();
			break;
		}
		while (getchar() != (int)'\n');
		printf("> ");
	}
	printf("\n");

	return EXIT_SUCCESS;
}
