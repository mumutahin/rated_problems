#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int option = 0;
int i = 0;
int n = 0;
int j = 0;
float present = 75.00;
char money = 'p';
float tdays = 1;

struct student {
    char name[20];
    int rno;
    char fees;
    float days;
    float attend;
    int sClass;
} s[50];

void execute();
void printStudents(struct student s[]);
void deleteRecord(struct student s[]);
void add(struct student s[50]);
void eligibleStudents(struct student s[]);
void saveData(struct student s[]);
void loadData(struct student s[]);

void clearScreen() {
    system("cls");
}

void execute() {
    printf("\n\n Enter the serial number to select the option \n\n");
    printf(" 1. To show Eligible candidates \n");
    printf(" 2. To delete the student record \n");
    printf(" 3. To change the eligibility criteria \n");
    printf(" 4. Reset the eligibility criteria \n");
    printf(" 5. Print the list of all the student \n");
    printf(" 6. Add a new student record \n"); 
    printf(" Enter 0 to exit \n Enter a number:");

    scanf("%d", &option);

    switch (option) {
    case 1:
        eligibleStudents(s);
        execute();
        break;

    case 2:
        deleteRecord(s);
        execute();
        break;

    case 3:
        printf("Old Attendance required = %.2f%%", present);
        printf("\n Enter the updated attendance required ");
        scanf("%f", &present);
        printf("fees status required was %c \n", money);
        printf("Enter the new fees status 'p' for paid 'n' for not paid and 'b' for both :");
        scanf(" %c", &money);
        printf("Eligibility Criteria updated \n");
        execute();
        break;

    case 4:
        present = 75.00;
        money = 'p';
        printf("Eligibility criteria reset \n");
        execute();
        break;

    case 5:
        printStudents(s);
        execute();
        break;

    case 6:
        add(s);
        execute();
        break;

    case 0:
        saveData(s);
        exit(0);

    default:
        printf("Enter number only from 0-6 \n");
        execute();
    }
}

void printStudents(struct student s[]) {
    clearScreen();
    int classNumber;
    printf("Enter the class number to print the students list: ");
    scanf("%d", &classNumber);

    FILE *fp;
    char filename[50];
    sprintf(filename, "class_%d_students.txt", classNumber);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Students in class %d:\n", classNumber);
    while (fscanf(fp, "%s %d %c %f %f %d\n", s[i].name, &s[i].rno, &s[i].fees, &s[i].days, &s[i].attend, &s[i].sClass) == 6) {
        if (s[i].sClass == classNumber) {
            printf("Name: %s\n", s[i].name);
            printf("Roll number: %d\n", s[i].rno);
            printf("Fees: %c\n", s[i].fees);
            printf("Days present: %.2f\n", s[i].days);
            printf("Attendance: %.2f%%\n", s[i].attend);
            printf("Class: %d\n\n", s[i].sClass);
        }
        i++;
    }

    fclose(fp);
    execute();
}

void deleteRecord(struct student s[]) {
    clearScreen();
    int classNumber;
    printf("Enter the class number to search for student: ");
    scanf("%d", &classNumber);

    int rollNumber;
    printf("Enter the roll number of the student to delete: ");
    scanf("%d", &rollNumber);

    FILE *fp;
    char filename[50];
    sprintf(filename, "class_%d_students.txt", classNumber);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE *tempFile;
    char tempFilename[] = "temp_students.txt";
    tempFile = fopen(tempFilename, "w");

    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    int found = 0;
    while (fscanf(fp, "%s %d %c %f %f %d\n",
    
     s[i].name, &s[i].rno, &s[i].fees, &s[i].days,
      &s[i].attend, &s[i].sClass) == 6) 
      {
        if (s[i].sClass == classNumber && s[i].rno == rollNumber) {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%s %d %c %.2f %.2f %d\n", s[i].name, s[i].rno, s[i].fees, s[i].days, s[i].attend, s[i].sClass);
    }

    fclose(fp);
    fclose(tempFile);

    if (!found) {
        printf("Student with roll number %d in class %d not found.\n", rollNumber, classNumber);
    } else {
        remove(filename);
        rename(tempFilename, filename);
        printf("Student Record deleted\n");
    }
}

void eligibleStudents(struct student s[]) {
    clearScreen();
    int classNumber;
    printf("Enter the class number to show eligible students: ");
    scanf("%d", &classNumber);

    FILE *fp;
    char filename[50];
    sprintf(filename, "class_%d_students.txt", classNumber);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int eligibleFound = 0;

    printf("Qualified students in class %d are:\n", classNumber);
    while (fscanf(fp, "%s %d %c %f %f %d\n", s[i].name, &s[i].rno, &s[i].fees, &s[i].days, &s[i].attend, &s[i].sClass) == 6) {
        if (s[i].sClass == classNumber) {
            if (s[i].fees == money || money == 'b') {
                if (s[i].attend >= present) {
                    printf("Student name: %s \n", s[i].name);
                    printf("Student roll no.: %d \n", s[i].rno);
                    printf("Student fees status: %c \n", s[i].fees);
                    printf("Student attendance: %.2f%% \n", s[i].attend);
                    printf("Class: %d\n", s[i].sClass);
                    printf("____________________________________________________________ \n");
                    eligibleFound = 1;
                }
            }
        }
    }

    fclose(fp);

    if (!eligibleFound) {
        printf("No eligible students found in class %d.\n", classNumber);
    }
}

void add(struct student s[50]) {
    clearScreen();
    printf("Enter the total number of working days: ");
    scanf("%f", &tdays);

    int classNumber;
    printf("Enter class: ");
    scanf("%d", &classNumber);

    printf("Enter the number of students :");
    scanf("%d", &n);

    FILE *fp;
    char filename[50];
    sprintf(filename, "class_%d_students.txt", classNumber);

    fp = fopen(filename, "a+");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    rewind(fp);
    int existingStudents = 0;
    while (fscanf(fp, "%s %d %c %f %f %d\n", s[existingStudents].name, &s[existingStudents].rno, &s[existingStudents].fees, &s[existingStudents].days, &s[existingStudents].attend, &s[existingStudents].sClass) == 6) {
        if (s[existingStudents].sClass == classNumber) {
            existingStudents++;
        }
    }

    for (i = existingStudents; i < n + existingStudents; i++) {
        printf("\nStudent number %d \n", (i + 1));

        printf("Enter the name of the student: ");
        scanf("%s", s[i].name);

        printf("Enter the roll number: ");
        scanf("%d", &s[i].rno);

        int duplicateFound = 0;
        for (j = 0; j < existingStudents; j++) {
            if (s[j].sClass == classNumber && s[j].rno == s[i].rno) {
                printf("Student with the same roll number already exists in class %d.\n", classNumber);
                duplicateFound = 1;
                break;
            }
        }

        if (duplicateFound) {
            i--;
            continue;
        }

        printf("Enter the fee status of the student 'p' for paid , 'n' for not paid: ");
        scanf(" %c", &s[i].fees);

        printf("Enter the number of days the student was present: ");
        scanf("%f", &s[i].days);

        s[i].attend = (s[i].days / tdays) * 100;
        s[i].sClass = classNumber;

        printf("student attendance = %.2f%% \n", s[i].attend);

        fprintf(fp, "%s %d %c %.2f %.2f %d\n", s[i].name, s[i].rno, s[i].fees, s[i].days, s[i].attend, s[i].sClass);
    }

    fclose(fp);
    execute();
}

void saveData(struct student s[]) {
    FILE *fp;
    fp = fopen("student_data.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%d\n", n);

    for (i = 0; i < n; i++) {
        fprintf(fp, "%s %d %c %.2f %.2f %d\n", s[i].name, s[i].rno, s[i].fees, s[i].days, s[i].attend, s[i].sClass);
    }

    fclose(fp);
}

void loadData(struct student s[]) {
    FILE *fp;
    fp = fopen("student_data.txt", "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fscanf(fp, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(fp, "%s %d %c %f %f %d\n", s[i].name, &s[i].rno, &s[i].fees, &s[i].days, &s[i].attend, &s[i].sClass);
    }

    fclose(fp);
}

int main() {
    printf("Welcome to Student database registration \nAnd Examination eligibility checker \n\n");

    printf("Enter 0 to exit \n");
    printf("Enter 1 to add student record \n");
    printf("Enter 2 to print the list of all the student \n\nEnter a number: ");

    scanf("%d", &option);

    switch (option) {
    case 0:
        saveData(s);
        exit(0);

    case 1:
        loadData(s);
        add(s);
        break;

    case 2:
        loadData(s);
        printStudents(s);
        execute();
        break;

    default:
        printf("Only enter 0 or 1\n");
        execute();
    }

    return 0;
}
