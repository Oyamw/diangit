#include <stdio.h>
#include <string.h>
#include "git_utils.c" // 确保包含你的工具函数

void display_menu() {
    printf("Git CLI\n");
    printf("1. Create Branch\n");
    printf("2. Create Tag\n");
    printf("3. List Branches\n");
    printf("4. List Tags\n");
    printf("5. Exit\n");
}

int main() {
    int choice;
    char name[256];

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter branch name: ");
            scanf("%s", name);
            create_branch(name);
            break;
        case 2:
            printf("Enter tag name: ");
            scanf("%s", name);
            create_tag(name);
            break;
        case 3:
            list_branches();
            break;
        case 4:
            list_tags();
            break;
        case 5:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
