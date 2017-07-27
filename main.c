#include <stdio.h>
#include "tree.h"

int main (int argc, char* argv[]) {
	if (argc != 2) {
		printf("Incorrect input! Enter './a.out (file.txt)'\n");
		return 0;
	}

	FILE* fp = fopen(argv[1], "r");

	if (!fp) {
		printf("Attempt to open non-existing file: %s\n", argv[1]);
		return 0;
	}

	if (feof(fp)) {
		printf("File is empty.\n");
		fclose(fp);
		return 0;
	}

	char ch = 0;
	unsigned int value = 0;

	while (ch != '+') {
		int num = fscanf(fp, "%c%u\n", &ch, &value);

		if ((num != 2) || ((ch != '+') && (ch != '-') && (ch != '?'))) {
			printf("Incorrect file!\n");
			fclose(fp);
			return 0;
		}
		
		if (ch == '-')
			printf("There is no elements in the tree. It's impossible to remove '%u'\n", value);

		if (ch == '?')
			printf("There is no elements in the tree. Node '%u' is not found\n", value);
					
	}

	node* root = insert(NULL, value);
	if (error_glob == -2) {
		fclose(fp);
		printf("Bad allocation!\n");
		return 0;
	}

	printf("Node with key '%u' is successfully added to the tree\n", value);

	while (fscanf(fp, "%c%u\n", &ch, &value) == 2) {
		if ((ch != '+') && (ch != '-') && (ch != '?')) {
			printf("Incorrect file!\n");

			fclose(fp);
			destruct_tree(root);

			return 0;
		}

		if (ch == '+') {
			root = insert(root, value);
			if (error_glob == -2) {
				printf("Bad allocation\n");

				fclose(fp);
				destruct_tree(root);

				return 0;
			}

			if (error_glob != -1)
				printf("Node with key '%u' is successfully added to the tree\n", value);
			error_glob = 0;
		}

		if (ch == '-') {
			root = remove_node(root, value);
			if (error_glob != -1)
				printf("Node with key '%u' is successfully removed from the tree\n", value);
			error_glob = 0;
		}
		if (ch == '?')
			printf(find_key(root, value) ? "Node with key '%u' is found\n" : "Node with key '%u' is not found\n", value);
	}

	if (!feof(fp))
		printf("Incorrect file!\n");

	fclose(fp);

	print_tree(root);
	destruct_tree(root);
	return 0;
}
