#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_EMAIL_LENGTH 50
#define MAX_QUESTIONS 100
#define MAX_QUESTION_LENGTH 200
#define MAX_CHOICES 4
#define MAX_TEST_PARTICIPANTS 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int num_tests_taken;
} User;

typedef struct {
    char question[MAX_QUESTION_LENGTH];
    int question_type;  // 1: short question, 2: multiple choice, 3: both
    char choices[MAX_CHOICES][MAX_QUESTION_LENGTH];
    int num_choices;
    int correct_choice; // Index of correct choice in choices array (1-based)
} Question;

User admins[MAX_USERS];
User students[MAX_USERS];
Question questions[MAX_QUESTIONS];
int num_admins = 0;
int num_students = 0;
int num_questions = 0;

// Function prototypes
void clearScreen();
void displayAdminPanel(User *admin);
void displayStudentPanel(User *student);
void login(User *user, User *users, int *num_users, const char *user_type);
void registerUser(User *users, int *num_users, const char *user_type);
void profileSettings(User *user);
void createQuestions();
void viewQuestions();
void editQuestions();
void deleteQuestions();
void takeTest(User *student);
void viewTestResults();

int main() {
    int choice;
    User currentUser;

    while (1) {
        clearScreen();
        printf("Welcome to the Online Test Management System\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character left in buffer

        switch (choice) {
            case 1:
                clearScreen();
                printf("Login as:\n");
                printf("1. Admin\n");
                printf("2. Student\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                getchar();  // Consume newline character left in buffer
                switch (choice) {
                    case 1:
                        login(&currentUser, admins, &num_admins, "Admin");
                        if (strlen(currentUser.username) > 0) {
                            displayAdminPanel(&currentUser);
                        }
                        break;
                    case 2:
                        login(&currentUser, students, &num_students, "Student");
                        if (strlen(currentUser.username) > 0) {
                            displayStudentPanel(&currentUser);
                        }
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                break;
            case 2:
                clearScreen();
                printf("Register as:\n");
                printf("1. Admin\n");
                printf("2. Student\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                getchar();  // Consume newline character left in buffer
                switch (choice) {
                    case 1:
                        registerUser(admins, &num_admins, "Admin");
                        break;
                    case 2:
                        registerUser(students, &num_students, "Student");
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                break;
            case 3:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}

void clearScreen() {
    system("cls");
}

void login(User *user, User *users, int *num_users, const char *user_type) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    bool loggedIn = false;

    printf("Enter username: ");
    scanf("%s", username);
    getchar();  // Consume newline character left in buffer
    printf("Enter password: ");
    scanf("%s", password);
    getchar();  // Consume newline character left in buffer

    for (int i = 0; i < *num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            *user = users[i];
            loggedIn = true;
            break;
        }
    }

    if (!loggedIn) {
        printf("Invalid username or password.\n");
        printf("Press Enter to go back.\n");
        getchar();  // Wait for user input to go back
        return;
    }

    printf("Welcome, %s!\n", user->username);
    printf("Press Enter to continue.\n");
    getchar();  // Wait for user input to continue
}

void registerUser(User *users, int *num_users, const char *user_type) {
    char username[MAX_USERNAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    printf("Register as %s:\n", user_type);
    printf("Enter username: ");
    scanf("%s", username);
    getchar();  // Consume newline character left in buffer

    // Check if username already exists
    for (int i = 0; i < *num_users; ++i) {
        if (strcmp(username, users[i].username) == 0) {
            printf("Username already exists. Please choose a different username.\n");
            printf("Press Enter to go back.\n");
            getchar();  // Wait for user input to go back
            return;
        }
    }

    printf("Enter email: ");
    scanf("%s", email);
    getchar();  // Consume newline character left in buffer

    printf("Enter password: ");
    scanf("%s", password);
    getchar();  // Consume newline character left in buffer

    printf("Confirm password: ");
    scanf("%s", confirm_password);
    getchar();  // Consume newline character left in buffer

    if (strcmp(password, confirm_password) != 0) {
        printf("Passwords do not match. Registration failed.\n");
        printf("Press Enter to go back.\n");
        getchar();  // Wait for user input to go back
        return;
    }

    // Add user to users array
    strcpy(users[*num_users].username, username);
    strcpy(users[*num_users].email, email);
    strcpy(users[*num_users].password, password);
    ++*num_users;

    printf("Registration successful!\n");
    printf("Press Enter to continue.\n");
    getchar();  // Wait for user input to continue
}

void displayAdminPanel(User *admin) {
    int choice;

    while (1) {
        clearScreen();
        printf("Welcome, %s (Admin)\n", admin->username);
        printf("1. Profile Settings\n");
        printf("2. Create Questions\n");
        printf("3. View/Edit/Delete Questions\n");
        printf("4. Take Test\n");
        printf("5. View Test Results\n");
        printf("6. Logout\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character left in buffer

        switch (choice) {
            case 1:
                profileSettings(admin);
                break;
            case 2:
                createQuestions();
                break;
            case 3:
                viewQuestions();
                editQuestions();
                deleteQuestions();
                break;
            case 4:
                takeTest(admin);
                break;
            case 5:
                viewTestResults();
                break;
            case 6:
                printf("Logging out.\n");
                admin->username[0] = '\0';  // Clear current user info
                return;
            case 7:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

void profileSettings(User *user) {
    int choice;

    while (1) {
        clearScreen();
        printf("Profile Settings\n");
        printf("1. View Account Info\n");
        printf("2. Change Username\n");
        printf("3. Change Email\n");
        printf("4. Change Password\n");
        printf("5. Delete Account\n");
        printf("6. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character left in buffer

        switch (choice) {
            case 1:
                clearScreen();
                printf("Account Info\n");
                printf("Username: %s\n", user->username);
                printf("Email: %s\n", user->email);
                printf("Number of Tests Taken: %d\n", user->num_tests_taken);
                printf("Press Enter to go back.\n");
                getchar();  // Wait for user input to go back
                break;
            case 2:
                clearScreen();
                printf("Change Username\n");
                printf("Enter new username: ");
                scanf("%s", user->username);
                getchar();  // Consume newline character left in buffer
                printf("Username changed successfully.\n");
                printf("Press Enter to go back.\n");
                getchar();  // Wait for user input to go back
                break;
            case 3:
                clearScreen();
                printf("Change Email\n");
                printf("Enter new email: ");
                scanf("%s", user->email);
                getchar();  // Consume newline character left in buffer
                printf("Email changed successfully.\n");
                printf("Press Enter to go back.\n");
                getchar();  // Wait for user input to go back
                break;
            case 4:
                clearScreen();
                printf("Change Password\n");
                char current_password[MAX_PASSWORD_LENGTH];
                char new_password[MAX_PASSWORD_LENGTH];
                char confirm_new_password[MAX_PASSWORD_LENGTH];
                printf("Enter current password: ");
                scanf("%s", current_password);
                getchar();  // Consume newline character left in buffer

                if (strcmp(current_password, user->password) != 0) {
                    printf("Incorrect password. Password change failed.\n");
                    printf("Press Enter to go back.\n");
                    getchar();  // Wait for user input to go back
                    break;
                }

                printf("Enter new password: ");
                scanf("%s", new_password);
                getchar();  // Consume newline character left in buffer

                printf("Confirm new password: ");
                scanf("%s", confirm_new_password);
                getchar();  // Consume newline character left in buffer

                if (strcmp(new_password, confirm_new_password) != 0) {
                    printf("Passwords do not match. Password change failed.\n");
                    printf("Press Enter to go back.\n");
                    getchar();  // Wait for user input to go back
                    break;
                }

                strcpy(user->password, new_password);
                printf("Password changed successfully.\n");
                printf("Press Enter to go back.\n");
                getchar();  // Wait for user input to go back
                break;
            case 5:
                clearScreen();
                printf("Delete Account\n");
                printf("Are you sure you want to delete your account? (Y/N): ");
                char confirm_delete;
                scanf(" %c", &confirm_delete);
                getchar();  // Consume newline character left in buffer

                if (confirm_delete == 'Y' || confirm_delete == 'y') {
                    // Implement account deletion logic here if needed
                    user->username[0] = '\0';  // Clear current user info
                    printf("Account deleted successfully.\n");
                    printf("Press Enter to go back.\n");
                } else {
                    printf("Account deletion cancelled.\n");
                    printf("Press Enter to go back.\n");
                }
                getchar();  // Wait for user input to go back
                break;
            case 6:
                return;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

void createQuestions() {
    int choice;

    while (1) {
        clearScreen();
        printf("Create Questions\n");
        printf("1. Short Answer Question\n");
        printf("2. Multiple Choice Question\n");
        printf("3. Both\n");
        printf("4. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character left in buffer

        switch (choice) {
            case 1: {
                clearScreen();
                printf("Short Answer Question\n");
                if (num_questions >= MAX_QUESTIONS) {
                    printf("Question limit reached. Cannot add more questions.\n");
                    printf("Press Enter to go back.\n");
                    getchar();  // Wait for user input to go back
                    break;
                }
                printf("Enter the question: ");
                fgets(questions[num_questions].question, MAX_QUESTION_LENGTH, stdin);
                strtok(questions[num_questions].question, "\n");  // Remove trailing newline
                questions[num_questions].question_type = 1;
                ++num_questions;
                printf("Question added successfully.\n");
                printf("Press Enter to go back.\n");
                getchar();  // Wait for user input to go back
                break;
            }
            case 2: {
                clearScreen();
                printf("Multiple Choice Question\n");
                if (num_questions >= MAX_QUESTIONS) {
                    printf("Question limit reached. Cannot add more questions.\n");
                    printf("Press Enter to go back.\n");
                    getchar();  // Wait for user input to go back
                    break;
                }
                printf("Enter the question: ");
                fgets(questions[num_questions].question, MAX_QUESTION_LENGTH, stdin);
                strtok(questions[num_questions].question, "\n");  // Remove trailing newline
                printf("Enter the number of choices (max %d): ", MAX_CHOICES);
                scanf("%d", &questions[num_questions].num_choices);
                getchar();  // Consume newline character left in buffer
                printf("Enter the choices (one per line):\n");
                for (int i = 0; i < questions[num_questions].num_choices; ++i) {
                    printf("Choice %d: ", i + 1);
                    fgets(questions[num_questions].choices[i], MAX_QUESTION_LENGTH, stdin);
                    strtok(questions[num_questions].choices[i], "\n");  // Remove trailing newline
                }
                printf("Enter the index of the correct choice (1-%d): ", questions[num_questions].num_choices);
                scanf("%d", &questions[num_questions].correct_choice);
                getchar();  // Consume newline character left in buffer
                questions[num_questions].question_type = 2;
                ++num_questions;
                printf("Question added successfully.\n");
                printf("Press Enter to go back.\n");
                getchar();  // Wait for user input to go back
                break;
            }
            case 3: {
                clearScreen();
                printf("Both Short Answer and Multiple Choice Question\n");
                if (num_questions >= MAX_QUESTIONS) {
                    printf("Question limit reached. Cannot add more questions.\n");
                    printf("Press Enter to go back.\n");
                    getchar();  // Wait for user input to go back
                    break;
                }
                printf("Enter the question: ");
                fgets(questions[num_questions].question, MAX_QUESTION_LENGTH, stdin);
                strtok(questions[num_questions].question, "\n");  // Remove trailing newline
                printf("Enter the number of choices (max %d): ", MAX_CHOICES);
                scanf("%d", &questions[num_questions].num_choices);
                getchar();  // Consume newline character left in buffer
                printf("Enter the choices (one per line):\n");
                for (int i = 0; i < questions[num_questions].num_choices; ++i) {
                    printf("Choice %d: ", i + 1);
                    fgets(questions[num_questions].choices[i], MAX_QUESTION_LENGTH, stdin);
                    strtok(questions[num_questions].choices[i], "\n");  // Remove trailing newline
                }
                printf("Enter the index of the correct choice (1-%d): ", questions[num_questions].num_choices);
                scanf("%d", &questions[num_questions].correct_choice);
                getchar();  // Consume newline character left in buffer
                questions[num_questions].question_type = 3;
                ++num_questions;
                printf("Question added successfully.\n");
                printf("Press Enter to go back.\n");
                getchar();  // Wait for user input to go back
                break;
            }
            case 4:
                return;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

void viewQuestions() {
    clearScreen();
    printf("View Questions\n");

    if (num_questions == 0) {
        printf("No questions available.\n");
    } else {
        for (int i = 0; i < num_questions; ++i) {
            printf("Question %d:\n", i + 1);
            printf("Question: %s\n", questions[i].question);
            if (questions[i].question_type == 2 || questions[i].question_type == 3) {
                printf("Choices:\n");
                for (int j = 0; j < questions[i].num_choices; ++j) {
                    printf("%d. %s\n", j + 1, questions[i].choices[j]);
                }
                printf("Correct choice: %d\n", questions[i].correct_choice);
            }
            printf("\n");
        }
    }

    printf("Press Enter to go back.\n");
    getchar();  // Wait for user input to go back
}

void editQuestions() {
    int choice;
    int edit_index;

    while (1) {
        clearScreen();
        printf("Edit Questions\n");
        printf("Enter the question number to edit (1-%d) or 0 to go back: ", num_questions);
        scanf("%d", &edit_index);
        getchar();  // Consume newline character left in buffer

        if (edit_index == 0) {
            return;
        }

        if (edit_index < 1 || edit_index > num_questions) {
            printf("Invalid question number.\n");
            printf("Press Enter to go back.\n");
            getchar();  // Wait for user input to go back
            continue;
        }

        --edit_index;  // Adjust to zero-based index

        printf("Editing question %d:\n", edit_index + 1);
        printf("Question: %s\n", questions[edit_index].question);
        if (questions[edit_index].question_type == 2 || questions[edit_index].question_type == 3) {
            printf("Choices:\n");
            for (int j = 0; j < questions[edit_index].num_choices; ++j) {
                printf("%d. %s\n", j + 1, questions[edit_index].choices[j]);
            }
            printf("Correct choice: %d\n", questions[edit_index].correct_choice);
        }

        printf("1. Edit Question\n");
        printf("2. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character left in buffer

        switch (choice) {
            case 1:
                clearScreen();
                printf("Editing question %d:\n", edit_index + 1);
                printf("Enter new question: ");
                fgets(questions[edit_index].question, MAX_QUESTION_LENGTH, stdin);
                strtok(questions[edit_index].question, "\n");  // Remove trailing newline
                if (questions[edit_index].question_type == 2 || questions[edit_index].question_type == 3) {
                    printf("Enter the number of choices (max %d): ", MAX_CHOICES);
                    scanf("%d", &questions[edit_index].num_choices);
                    getchar();  // Consume newline character left in buffer
                    printf("Enter the choices (one per line):\n");
                    for (int i = 0; i < questions[edit_index].num_choices; ++i) {
                        printf("Choice %d: ", i + 1);
                        fgets(questions[edit_index].choices[i], MAX_QUESTION_LENGTH, stdin);
                        strtok(questions[edit_index].choices[i], "\n");  // Remove trailing newline
                    }
                    printf("Enter the index of the correct choice (1-%d): ", questions[edit_index].num_choices);
                    scanf("%d", &questions[edit_index].correct_choice);
                    getchar();  // Consume newline character left in buffer
                }
                printf("Question edited successfully.\n");
                printf("Press Enter to go back.\n");
                getchar();  // Wait for user input to go back
                break;
            case 2:
                // Go back
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

void deleteQuestions() {
    int delete_index;

    while (1) {
        clearScreen();
        printf("Delete Questions\n");
        printf("Enter the question number to delete (1-%d) or 0 to go back: ", num_questions);
        scanf("%d", &delete_index);
        getchar();  // Consume newline character left in buffer

        if (delete_index == 0) {
            return;
        }

        if (delete_index < 1 || delete_index > num_questions) {
            printf("Invalid question number.\n");
            printf("Press Enter to go back.\n");
            getchar();  // Wait for user input to go back
            continue;
        }

        --delete_index;  // Adjust to zero-based index

        // Shift questions array to delete the question
        for (int i = delete_index; i < num_questions - 1; ++i) {
            strcpy(questions[i].question, questions[i + 1].question);
            questions[i].question_type = questions[i + 1].question_type;
            for (int j = 0; j < MAX_CHOICES; ++j) {
                strcpy(questions[i].choices[j], questions[i + 1].choices[j]);
            }
            questions[i].num_choices = questions[i + 1].num_choices;
            questions[i].correct_choice = questions[i + 1].correct_choice;
        }

        --num_questions;  // Decrease the number of questions

        printf("Question deleted successfully.\n");
        printf("Press Enter to go back.\n");
        getchar();  // Wait for user input to go back
    }
}

void takeTest(User *student) {
    printf("Take Test\n");
    printf("Sorry, this feature is currently under development.\n");
    printf("Press Enter to go back.\n");
    getchar();  // Wait for user input to go back
}

void viewTestResults() {
    printf("View Test Results\n");
    printf("Sorry, this feature is currently under development.\n");
    printf("Press Enter to go back.\n");
    getchar();  // Wait for user input to go back
}

void displayStudentPanel(User *student) {
    int choice;

    while (1) {
        clearScreen();
        printf("Welcome, %s (Student)\n", student->username);
        printf("1. Profile Settings\n");
        printf("2. Take Test\n");
        printf("3. View Test Results\n");
        printf("4. Logout\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character left in buffer

        switch (choice) {
            case 1:
                profileSettings(student);
                break;
            case 2:
                takeTest(student);
                break;
            case 3:
                viewTestResults();
                break;
            case 4:
                printf("Logging out.\n");
                student->username[0] = '\0';  // Clear current user info
                return;
            case 5:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}
