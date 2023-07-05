#include "framework.h"


typedef struct _Class_{
  int class_year;
  struct _Class_* next_parallel;
  int max_stud_nr;
  int student_amount;
  struct _Student_* root_node;
}Class;

typedef struct _Student_{
  char* student_name;
  int year_of_birth;
  int student_points;
  int stud_school_id;
  struct _Student_* good_node;
  struct _Student_* bad_node;
}Student;

School* linkClasses(char** school_file_info, School* actual_schools, int* return_value);
char** readSchoolInfo(FILE* school_file, int* return_value);
char** readStudentInfo(FILE* student_file, int* return_value);
Student* linkStudents(char** student_file_info, Student* actual_students, int* return_value);
Student* insertIntoClass(Student* actual_students, Student* stud_node);
School* decideSchool(Student* actual_students, School* actual_schools, int* return_value);
int mainFunctionality(Student* actual_students, School* actual_schools, char** school_file_info, int* return_value);
void helpFunc();
void searchFunc(School* actual_schools, char* curr_stud, int* ret_val);
void searchInClass(Class* class, char* curr_stud, int* ret_val);
void searchStudent(Student* student, char* curr_stud, int* ret_val);
Student* addStudent(Student* actual_student, char* curr_stud, int* return_value);
Student* deleteNode(Student* root, int points, char* name, int* ret_val);
School* iterateSchools(School* actual_schools, Student student);
Student* findMinimumValueNode(Student* node);
void saveInFile(Student* actual_students, int* return_value);
School* loadFromFile(char** school_file_info, Student** actual_students, int* return_value);


///TODO: make a function to use instead of atoi. GetInt()!!!
int main(int argc, char* argv[])
{
  char* school_arg = argv[1];
  char* students_arg = argv[2];
  int return_value = SUCCESS;
  if(argc != ARGS)
  {
    printf("Wrong parameters!!!\n");
    return WRONG_PARAM_AMOUNT;
  }
  FILE* school_file = fopen(school_arg,"r");
  if(!school_file)
  {
    printf("File could not be opened!!!\n");
    return FILE_NOT_FOUND;
  }
  FILE* student_file = fopen(students_arg,"r");
  if(!student_file)
  {
    printf("File couldn't be opened!!!\n");
    return FILE_NOT_FOUND;
  }
  School* actual_schools = malloc(sizeof(School));
  if(!actual_schools)
  {
    printf("Memory could not be allocated!!!\n");
    return MEMORY_PROBLEM;
  }
  char** school_file_info = readSchoolInfo(school_file, &return_value);
  actual_schools = linkClasses(school_file_info, actual_schools, &return_value);
  char** student_file_info = readStudentInfo(student_file, &return_value);
  Student* actual_students = malloc(sizeof(Student));
  if(!actual_students)
  {
    free(actual_schools);
    printf("Memory could not be allocated!!!\n");
    return MEMORY_PROBLEM;
  }
  int index = 0;
  actual_students = linkStudents(student_file_info, actual_students, &return_value);
  actual_schools = decideSchool(actual_students, actual_schools, &return_value);

  if(return_value != SUCCESS)
  {
    printf("Error detected!!! Aborting ecxecution.\n");
    free(actual_schools);
    for(index = 0; actual_students[index].student_name != NULL; index++)
      free(actual_students[index].student_name);
    free(actual_students);
    return return_value;
  }

  return_value = mainFunctionality(actual_students, actual_schools, school_file_info, &return_value);

  for(index = 0; student_file_info[index] != NULL; index++)
  {
    free(student_file_info[index]);
  }
  free(student_file_info);

  for(index = 0; school_file_info[index] != NULL; index++)
  {
    free(school_file_info[index]);
  }
  free(school_file_info);
  fclose(student_file);
  fclose(school_file);
  return return_value;
}

/// This is the function that handles our inputs. In here we are asked for a specific type of prompt,
/// which does one of the following actions: SEARCH,ADD,REMOVE,SAVE,LOAD,HLP,EXIT. As well as the
/// student input (if needed).

int mainFunctionality(Student* actual_students, School* actual_schools, char** school_file_info, int* return_value)
{
  int load_flag = 0;
  School* new_actual_school = NULL;
  printf("                 WELCOME TO THE ESP-STUDENT-DATABASE\n");

  while(1)
  {
    load_flag = 0;
    if(*return_value != SUCCESS)
    {
      return *return_value;
    }
    printf("\n=============================================================================\n"
           "Please choose one of the following options:\nSEARCH\nADD\nREMOVE\nSAVE\nLOAD\nHELP\nEXIT\n"
           "=============================================================================\n");
    char* input = getInput(return_value);
    for(int i = 0; input[i] != '\0'; i++)
    {
      if((input[i] >= 65) && (input[i] <= 90))
        continue;
      input[i] -= 32;
    }

    if(!strcmp(input,"SEARCH"))
    {
      int ret_val = 0;
      printf("\nWhich student are you looking for???\n\n");
      char* curr_stud = getInput(return_value);
      searchFunc(actual_schools,curr_stud, &ret_val);
      printf(DEFAULT);
      if(!ret_val)
      {
        printf(RED"\nStudent %s has not been found!!!\n",curr_stud);
        printf(DEFAULT);
      }
      free(curr_stud);
      ///TODO: SEARCH function, make into a function;
    }
    else if(!strcmp(input,"ADD"))
    {
      printf("Please give the student information in this order: \"Name Surname  School_id Year_of_birth Points\"\n\n");
      char* curr_stud = getInput(return_value);
      int flag = checkInput(curr_stud, actual_schools, return_value);
      if(flag)
      {
        actual_students = addStudent(actual_students, curr_stud, return_value);
        int index = 0;
        for(index = 0; actual_students[index].student_name != NULL; index++);
        decideSchool(&actual_students[index-1],actual_schools,return_value);
        printf(GREEN"\nStudent %s has been successfully added to school %d\n",actual_students[index-1].student_name, actual_students[index-1].stud_school_id);
        printf(DEFAULT);
      }
      free(curr_stud);
      ///TODO: ADD function, make into a function;
    }
    else if(!strcmp(input,"REMOVE"))
    {
      ///TODO: REMOVE function, make into a function;

      printf("Please give the name and surname of the student you want to remove.\n\n");
      char* curr_stud = getInput(return_value);
      int flag = 0;
      int index = 0;
      for(index = 0; actual_students[index].student_name != NULL; index++)
      {
        flag = strcmp(actual_students[index].student_name,curr_stud);
        if(!flag && actual_students[index].student_points != 0xfffff)
        {
          if(actual_students[index].student_points == 0xfffff)
            flag = 1;
          break;
        }
      }
      if(!flag && actual_students[index].student_name != NULL)
      {
        iterateSchools(actual_schools,actual_students[index]);
        printf(GREEN"\nStudent %s has been successfully removed from school %d\n",actual_students[index].student_name, actual_students[index].stud_school_id);
        Student* temp_stud = actual_students+index;
        temp_stud->student_points = 0xfffff;
        printf(DEFAULT);
      }
      else
        printf(RED"\nStudent %s cannot be found!!!\n",curr_stud);
      printf(DEFAULT);

      free(curr_stud);
    }
    else if(!strcmp(input,"SAVE"))
    {
      saveInFile(actual_students, return_value);

      ///TODO: SAVE fucntion, make into a function;
    }
    else if(!strcmp(input,"LOAD"))
    {

      if(actual_students)
      {
        for(int index = 0; actual_students[index].student_name != NULL; index++)
          free(actual_students[index].student_name);
        free(actual_students);
      }
      int idx = 0;
      while (actual_schools[idx].school_id != 0xfff)
      {
        Class* class1_temp;
        while(actual_schools[idx].class_1 != NULL)
        {
          class1_temp = actual_schools[idx].class_1;
          actual_schools[idx].class_1 = actual_schools[idx].class_1->next_parallel;
          free(class1_temp);
        }

        Class* class2_temp;
        while(actual_schools[idx].class_2 != NULL)
        {
          class2_temp = actual_schools[idx].class_2;
          actual_schools[idx].class_2 = actual_schools[idx].class_2->next_parallel;
          free(class2_temp);
        }

        Class* class3_temp;
        while(actual_schools[idx].class_3 != NULL)
        {
          class3_temp = actual_schools[idx].class_3;
          actual_schools[idx].class_3 = actual_schools[idx].class_3->next_parallel;
          free(class3_temp);
        }
        idx++;
      }
      free(actual_schools);

      new_actual_school = loadFromFile(school_file_info,&actual_students, return_value);
      load_flag = 1;
      if(actual_schools == NULL)
        return FILE_NOT_FOUND;
      ///TODO: LOAD function, make into a function;
    }
    else if(!strcmp(input,"HELP"))
    {
      helpFunc();
    }
    else if(!strcmp(input,"EXIT"))
    {
      int index = 0;
      for(index = 0; actual_students[index].student_name != NULL; index++)
        free(actual_students[index].student_name);
      free(actual_students);

      int idx = 0;
      while (actual_schools[idx].school_id != 0xfff)
      {
        Class* class1_temp;
        while(actual_schools[idx].class_1 != NULL)
        {
          class1_temp = actual_schools[idx].class_1;
          actual_schools[idx].class_1 = actual_schools[idx].class_1->next_parallel;
          free(class1_temp);
        }

        Class* class2_temp;
        while(actual_schools[idx].class_2 != NULL)
        {
          class2_temp = actual_schools[idx].class_2;
          actual_schools[idx].class_2 = actual_schools[idx].class_2->next_parallel;
          free(class2_temp);
        }

        Class* class3_temp;
        while(actual_schools[idx].class_3 != NULL)
        {
          class3_temp = actual_schools[idx].class_3;
          actual_schools[idx].class_3 = actual_schools[idx].class_3->next_parallel;
          free(class3_temp);
        }
        idx++;
      }
      free(actual_schools);

      free(input);
      return SUCCESS;
    }
    free(input);
    if(load_flag)
      actual_schools = new_actual_school;
  }

}

/// This function iterated through all the schools and classes until it finds the student that we are looking for.
///
void searchFunc(School* actual_schools, char* curr_stud, int* ret_val)
{
  int outer_index = 0;
  School* temp_school = actual_schools;
  for(outer_index = 1; actual_schools->school_id != 0xfff; outer_index++)
  {

    searchInClass(actual_schools->class_1, curr_stud, ret_val);
    searchInClass(actual_schools->class_2, curr_stud, ret_val);
    searchInClass(actual_schools->class_3, curr_stud, ret_val);

    actual_schools += 1;
  }
  actual_schools = temp_school;
}

/// This function iterates through the linked list of classes until the student with is found.
///

void searchInClass(Class* class, char* curr_stud, int* ret_val)
{
  Class* temp_class = class;
  while((class != NULL))
  {
    searchStudent(class->root_node, curr_stud, ret_val);
    class = class->next_parallel;
  }
  class = temp_class;

}

/// This function searches recursively the BST until the student is found.

void searchStudent(Student* root, char* curr_stud, int* ret_val)
{
  if(root == NULL)
    return;
  if(strcmp(root->student_name, curr_stud) == 0 && root->student_points != 0xfffff)
  {
    printf(GREEN"\nStudent: %s has been found in school %d.\n",root->student_name,root->stud_school_id);
    printf(DEFAULT);
    *ret_val = 1;
  }
  searchStudent(root->bad_node, curr_stud, ret_val);
  searchStudent(root->good_node, curr_stud, ret_val);

}

/// This is the help function. Which displays a help menu.
///

void helpFunc()
{
  printf("++++++++++++++++++++++++++++++++++HELP MENU++++++++++++++++++++++++++++++++++++++++++\n"
         RED"SEARCH: Searches in the binary tree for a specified student.\n"
         BLUE"ADD: Searches for the correct school, class and node. After finding it it inserts the student on the correct position.\n"
         YELLOW"REMOVE: Searches for the correct school, class and node. After finding it it removes the student completely. The BST needs to be correctly formated after the student remove.\n"
         PURPLE"SAVE: Re-writes the files with the current student and school data.\n"
         GREEN"LOAD: Rerolls to the current version of the file without needing to restart the program. (BONUS)\n"
         WHITE"HELP: Displays the HELP menu.\n"
         BLACK"EXIT: Exits the program.\n"DEFAULT
         "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

/// This function reads the string format that we received from the file and parses it, to the student.
/// In here we also fill the element of the _Student_ struct.
///

Student* linkStudents(char** student_file_info, Student* actual_students, int* return_value)
{
  size_t outer_index = 0;
  size_t inner_index = 0;
  char *temp_stud_name = 0;
  int stud_school_id = 0;
  int stud_yob = 0;
  int stud_grade = 0;
  char *temp_string_for_strstr;
  for (outer_index = 0; student_file_info[outer_index] != NULL; outer_index++)
  {
    temp_stud_name = getName(student_file_info[outer_index],return_value);
    temp_string_for_strstr = strstr(student_file_info[outer_index], "  ");
    temp_string_for_strstr += 2;
    stud_school_id = atoi(strtok(temp_string_for_strstr, " "));
    stud_yob = atoi(strtok(NULL, " "));
    stud_grade = atoi(strtok(NULL, " "));
    if(outer_index)
    {
      actual_students = realloc(actual_students, sizeof(Student)*(outer_index + 2));
      if(!actual_students)
      {
        printf("Memory could not be allocated!!!\n");
        *return_value = MEMORY_PROBLEM;
        return NULL;
      }
      (actual_students+outer_index)->student_name = temp_stud_name;
      (actual_students+outer_index)->student_points = stud_grade;
      (actual_students+outer_index)->year_of_birth = stud_yob;
      (actual_students+outer_index)->stud_school_id = stud_school_id;
      (actual_students+outer_index)->bad_node = NULL;
      (actual_students+outer_index)->good_node = NULL;
    }
    else
    {
      (actual_students)->student_name = temp_stud_name;
      (actual_students)->student_points = stud_grade;
      (actual_students)->year_of_birth = stud_yob;
      (actual_students)->stud_school_id = stud_school_id;
      (actual_students)->bad_node = NULL;
      (actual_students)->good_node = NULL;
    }
  }
  (actual_students+outer_index)->student_name = NULL;
  return actual_students;
}


/// This function recursively inserts the student into the BST, based on their points, if the points are equal.
/// The node gets decided based of their name.

Student* insertIntoClass(Student* root, Student* stud_node)
{
  if (root == NULL) {
    return stud_node;
  }

  if (stud_node->student_points < root->student_points)
  {
    root->bad_node = insertIntoClass(root->bad_node, stud_node);
  }
  else if (stud_node->student_points > root->student_points)
  {
    root->good_node = insertIntoClass(root->good_node, stud_node);
  }
  else
  {
    if (strcmp(stud_node->student_name, root->student_name) <= 0)
    {
      root->bad_node = insertIntoClass(root->bad_node, stud_node);
    }
    else
    {
      root->good_node = insertIntoClass(root->good_node, stud_node);
    }
  }

  return root;
}
/*{
  if(root == NULL)
    return stud_node;

  if(stud_node->student_points < root->student_points)
  {
    root->bad_node = insertIntoClass(root->bad_node, stud_node);
  }
  else
  {
    root->good_node = insertIntoClass(root->good_node, stud_node);
  }

  return root;
}*/

/// This function is responsible for placing the students in the correct school and class. Based on their data.
/// In case a class reaches its maximum amount of students, a new class is generated which is linked at the end
/// of the linked list.

School* decideSchool(Student* actual_students, School* actual_schools, int* return_value)
{
  Student* temp_stud = actual_students;
  School* temp_school = actual_schools;


  int idx = 0;
  while (actual_schools[idx].school_id != 0xfff)
  {
    Class* class_1 = actual_schools[idx].class_1;
    Class* class_2 = actual_schools[idx].class_2;
    Class* class_3 = actual_schools[idx].class_3;
    actual_students = temp_stud;
    while(actual_students->student_name != NULL)
    {
      if(actual_students->stud_school_id == actual_schools[idx].school_id)
      {
        if(actual_students->year_of_birth == class_1->class_year)
        {
          if(class_1->student_amount == class_1->max_stud_nr)
          {
            if (class_1->next_parallel == NULL)
            {
              class_1->next_parallel  = (Class *) malloc(sizeof(Class));
              if(!class_1->next_parallel)
              {
                Class* tmp;
                while(class_1 != NULL)
                {
                  tmp = class_1;
                  class_1 = class_1->next_parallel;
                  free(tmp);
                }
                *return_value = MEMORY_PROBLEM;
                printf("Memory could not be allocated!!!\n");
                return NULL;

              }
              class_1->next_parallel->max_stud_nr = 30;
              class_1->next_parallel->student_amount = 0;
              class_1->next_parallel->class_year = 2002;
              class_1->next_parallel->root_node = NULL;
              class_1->next_parallel->next_parallel = NULL;
            }
            class_1 = class_1->next_parallel;
          }
          if(class_1->root_node == NULL)
          {
            class_1->root_node = actual_students;
            class_1->student_amount++;
          }
          else
          {
            insertIntoClass(class_1->root_node, actual_students);
            class_1->student_amount++;
          }
        }
        else if(actual_students->year_of_birth == class_2->class_year)
        {
          if(class_2->student_amount == class_2->max_stud_nr)
          {
            if(class_2->next_parallel == NULL)
            {
              class_2->next_parallel = (Class*)malloc(sizeof(Class));
              if(!class_2->next_parallel)
              {
                Class* tmp;
                while(class_2 != NULL)
                {
                  tmp = class_2;
                  class_2 = class_2->next_parallel;
                  free(tmp);
                }
                *return_value = MEMORY_PROBLEM;
                printf("Memory could not be allocated!!!\n");
                return NULL;

              }
              class_2->next_parallel->max_stud_nr = 30;
              class_2->next_parallel->student_amount = 0;
              class_2->next_parallel->class_year = 2001;
              class_2->next_parallel->root_node = NULL;
              class_2->next_parallel->next_parallel = NULL;
            }
            class_2 = class_2->next_parallel;
          }
          if(class_2->root_node == NULL)
          {
            class_2->root_node = actual_students;
            class_2->student_amount++;
          }
          else
          {
            insertIntoClass(class_2->root_node, actual_students);
            class_2->student_amount++;
          }
        }
        else if(actual_students->year_of_birth == class_3->class_year)
        {
          if(class_3->student_amount == class_3->max_stud_nr)
          {
            if(class_3->next_parallel == NULL)
            {
              class_3->next_parallel = (Class*)malloc(sizeof(Class));
              if(!class_3->next_parallel)
              {
                Class* tmp;
                while(class_3 != NULL)
                {
                  tmp = class_3;
                  class_3 = class_3->next_parallel;
                  free(tmp);
                }
                *return_value = MEMORY_PROBLEM;
                printf("Memory could not be allocated!!!\n");
                return NULL;

              }
              class_3->next_parallel->max_stud_nr = 30;
              class_3->next_parallel->student_amount = 0;
              class_3->next_parallel->class_year = 2000;
              class_3->next_parallel->root_node = NULL;
              class_3->next_parallel->next_parallel = NULL;
            }
            class_3 = class_3->next_parallel;
          }
          if(class_3->root_node == NULL)
          {
            class_3->root_node = actual_students;
            class_3->student_amount++;
          }
          else
          {
            insertIntoClass(class_3->root_node, actual_students);
            class_3->student_amount++;
          }
        }
      }
      actual_students++;
    }
    idx++;
  }

  actual_schools = temp_school;
  return actual_schools;
}

/// This function does the parsing of the string that we got from the schools file and it makes the linked lists for
/// all the classes of each school. It also initializes the variables in the structs _Class_ and _School_.
///

School* linkClasses(char** school_file_info, School* actual_schools, int* return_value)
{
  int inner_index = 0;
  int outer_index = 0;
  int classes_amount = 0;
  int class_counter = 0;
  actual_schools->class_1 = malloc(sizeof(Class));
  if(!actual_schools->class_1)
  {
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;

  }
  actual_schools->class_2 = malloc(sizeof(Class));
  if(!actual_schools->class_2)
  {
    free(actual_schools->class_1);
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;

  }
  actual_schools->class_3 = malloc(sizeof(Class));
  if(!actual_schools->class_3)
  {
    free(actual_schools->class_1);
    free(actual_schools->class_2);
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;

  }
  for(outer_index = 0; school_file_info[outer_index] != NULL; ++outer_index)
  {
    int class_flag = 0;
    if(outer_index)
    {
      //printf("%d-------",outer_index);
      actual_schools = realloc(actual_schools,sizeof(School) * (outer_index + 2));
      (actual_schools + outer_index)->class_1 = malloc(sizeof(Class));
      (actual_schools + outer_index)->class_2 = malloc(sizeof(Class));
      (actual_schools + outer_index)->class_3 = malloc(sizeof(Class));

    }
    actual_schools[outer_index+1].school_id = 0xfff;
    Class* head_1 = (actual_schools + outer_index)->class_1;
    Class* head_2 = (actual_schools + outer_index)->class_2;
    Class* head_3 = (actual_schools + outer_index)->class_3;

    actual_schools[outer_index].school_id = (int)outer_index + 1;

    for(inner_index = 0; school_file_info[outer_index][inner_index] != '\0'; inner_index++)
    {
      if((inner_index == 0) || school_file_info[outer_index][inner_index] == ' ')
        continue;
      else
        class_flag++;
      classes_amount = school_file_info[outer_index][inner_index] - 48;

      ///TODO: make into fuction until end of loop.
      while((class_counter != classes_amount) && (class_flag == 1))
      {
        actual_schools[outer_index].class_1->max_stud_nr = 30;
        actual_schools[outer_index].class_1->student_amount = 0;
        actual_schools[outer_index].class_1->class_year = 2002;
        actual_schools[outer_index].class_1->root_node = NULL;
        actual_schools[outer_index].class_1->next_parallel = malloc(sizeof(Class));
        actual_schools[outer_index].class_1 = actual_schools[outer_index].class_1->next_parallel;
        class_counter++;

        if(class_counter == classes_amount)
        {
          actual_schools[outer_index].class_1->max_stud_nr = 30;
          actual_schools[outer_index].class_1->student_amount = 0;
          actual_schools[outer_index].class_1->class_year = 2002;
          actual_schools[outer_index].class_1->root_node = NULL;
        }
      }
      actual_schools[outer_index].class_1->next_parallel = NULL;

      class_counter = 0;

      ///TODO: make into fuction until end of loop.
      while((class_counter != classes_amount) && (class_flag == 2))
      {
        actual_schools[outer_index].class_2->max_stud_nr = 30;
        actual_schools[outer_index].class_2->student_amount = 0;
        actual_schools[outer_index].class_2->class_year = 2001;
        actual_schools[outer_index].class_2->root_node = NULL;
        actual_schools[outer_index].class_2->next_parallel = malloc(sizeof(Class));
        if(!actual_schools[outer_index].class_2->next_parallel)
        {
          Class* tmp;
          while(actual_schools[outer_index].class_2 != NULL)
          {
            tmp = actual_schools[outer_index].class_2;
            actual_schools[outer_index].class_2 = actual_schools[outer_index].class_2->next_parallel;
            free(tmp);
          }
          free((actual_schools + outer_index)->class_1);
          free((actual_schools + outer_index)->class_2);
          free((actual_schools + outer_index)->class_3);
          *return_value = MEMORY_PROBLEM;
          printf("Memory could not be allocated!!!\n");
          return NULL;

        }
        actual_schools[outer_index].class_2 = actual_schools[outer_index].class_2->next_parallel;
        class_counter++;

        if(class_counter == classes_amount)
        {
          actual_schools[outer_index].class_2->max_stud_nr = 30;
          actual_schools[outer_index].class_2->student_amount = 0;
          actual_schools[outer_index].class_2->class_year = 2001;
          actual_schools[outer_index].class_2->root_node = NULL;
        }
      }
      actual_schools[outer_index].class_2->next_parallel = NULL;
      class_counter = 0;
      ///TODO: make into fuction until end of loop.
      while((class_counter != classes_amount) && (class_flag == 3))
      {
        actual_schools[outer_index].class_3->max_stud_nr = 30;
        actual_schools[outer_index].class_3->student_amount = 0;
        actual_schools[outer_index].class_3->class_year = 2000;
        actual_schools[outer_index].class_3->root_node = NULL;
        actual_schools[outer_index].class_3->next_parallel = malloc(sizeof(Class));
        if(!actual_schools[outer_index].class_3->next_parallel)
        {
          Class* tmp;
          while(actual_schools[outer_index].class_3 != NULL)
          {
            tmp = actual_schools[outer_index].class_3;
            actual_schools[outer_index].class_3 = actual_schools[outer_index].class_3->next_parallel;
            free(tmp);
          }
          free((actual_schools + outer_index)->class_1);
          free((actual_schools + outer_index)->class_2);
          free((actual_schools + outer_index)->class_3);
          *return_value = MEMORY_PROBLEM;
          printf("Memory could not be allocated!!!\n");
          return NULL;

        }
        actual_schools[outer_index].class_3 = actual_schools[outer_index].class_3->next_parallel;
        class_counter++;

        if(class_counter == classes_amount)
        {
          actual_schools[outer_index].class_3->max_stud_nr = 30;
          actual_schools[outer_index].class_3->student_amount = 0;
          actual_schools[outer_index].class_3->class_year = 2000;
          actual_schools[outer_index].class_3->root_node = NULL;
        }
      }
      actual_schools[outer_index].class_3->next_parallel = NULL;
      class_counter = 0;
    }

    (actual_schools + outer_index)->class_1 = head_1;
    (actual_schools + outer_index)->class_2 = head_2;
    (actual_schools + outer_index)->class_3 = head_3;
  }
  return actual_schools;
}

/// This function reads the data from the file and parses it into a string.
///

char** readSchoolInfo(FILE* school_file, int* return_value)
{
  char* school_info = (char*)malloc(sizeof(char) + 1);
  if(!school_info)
  {
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;

  }
  char** school_file_info = (char**) malloc(sizeof(char*));
  if(!school_file_info)
  {
    free(school_info);
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;

  }
  int counter = 1;

  size_t inner_index = 0;
  size_t outer_index = 0;
  while((school_info[inner_index] = (char)fgetc(school_file)) != EOF)
  {
    inner_index++;
    if(school_info[inner_index-1] == '\n' || school_info[inner_index-1] == EOF)
    {
      school_info[inner_index - 1] = '\0';
      school_file_info[outer_index] = school_info;
      school_info = malloc(sizeof(char) + 1);
      if(!school_info)
      {
        for(int i = 0; i != '\0'; i++)
          free(school_file_info[i]);
        free(school_file_info);
        *return_value = MEMORY_PROBLEM;
        printf("Memory could not be allocated!!!\n");
        return NULL;
      }
      outer_index++;
      school_file_info = (char**)realloc(school_file_info,sizeof(char*)*(outer_index + 2));
      if(!school_file_info)
      {
        for(int i = 0; i != '\0'; i++)
          free(school_file_info[i]);
        free(school_file_info);
        *return_value = MEMORY_PROBLEM;
        printf("Memory could not be allocated!!!\n");
        return NULL;
      }
      counter = 1;
      inner_index = 0;
    }
    counter++;
    school_info = realloc(school_info, counter);
  }
  free(school_info);
  return school_file_info;
}

/// This function reads the data from the file and parses it into a string.
///

char** readStudentInfo(FILE* student_file, int* return_value)
{
  char* student_info = (char*)malloc(sizeof(char) + 1);
  if(!student_info)
  {
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;

  }
  char** student_file_info = (char**) malloc(sizeof(char*));
  if(!student_file_info)
  {
    free(student_info);
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;

  }
  size_t inner_index= 0;
  size_t outer_index = 0;
  size_t counter = 2;

  while((student_info[inner_index] = (char)fgetc(student_file)) != EOF)
  {
    inner_index++;
    if(student_info[inner_index-1] == '\n' || student_info[inner_index-1] == EOF)
    {
      student_info[inner_index] = '\0';
      student_file_info[outer_index] = student_info;
      student_info = malloc(sizeof(char) + 1);
      if(!student_info)
      {
        for(int i = 0; i != '\0'; i++)
          free(student_file_info[i]);
        free(student_file_info);
        *return_value = MEMORY_PROBLEM;
        printf("Memory could not be allocated!!!\n");
        return NULL;
      }
      outer_index++;
      student_file_info = (char**)realloc(student_file_info,sizeof(char*)*(outer_index + 1));
      if(!student_info)
      {
        for(int i = 0; i != '\0'; i++)
          free(student_file_info[i]);
        free(student_file_info);
        *return_value = MEMORY_PROBLEM;
        printf("Memory could not be allocated!!!\n");
        return NULL;
      }
      student_file_info[outer_index] = NULL;
      counter = 1;
      inner_index = 0;
    }
    counter++;
    student_info = realloc(student_info, counter);
  }
  free(student_info);
  return student_file_info;
}

/// This function is responsible for handling user inputs.


///This function check if the format of our input is correct. This function is used for when we want to add a student.
///



/// This function is responsible for adding a student, in the _Student_ array.
///

Student* addStudent(Student* actual_students, char* curr_stud, int* return_value)
{
  int index = 0;
  char* temp_stud_name = 0;
  int stud_school_id = 0;
  int stud_yob = 0;
  int stud_grade = 0;
  char* temp_string_for_strstr;
  Student* temp_stud;
  for(index = 0; actual_students[index].student_name; index++);
  //printf("%s\n",(actual_students[index].student_name));
  temp_stud = realloc(actual_students, sizeof(Student) * (index + 2));
  if(!temp_stud)
  {
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;
  }
  actual_students = temp_stud;
  temp_stud_name = getName(curr_stud, return_value);
  temp_string_for_strstr = strstr(curr_stud, "  ");
  temp_string_for_strstr += 2;
  stud_school_id = atoi(strtok(temp_string_for_strstr, " "));
  stud_yob = atoi(strtok(NULL, " "));
  stud_grade = atoi(strtok(NULL, " "));

  actual_students[index].student_name = temp_stud_name;
  actual_students[index].student_points = stud_grade;
  actual_students[index].year_of_birth = stud_yob;
  actual_students[index].stud_school_id = stud_school_id;
  actual_students[index].bad_node = NULL;
  actual_students[index].good_node = NULL;

  actual_students[index+1].student_name = NULL;

  return actual_students;
}

/// This function is used to check the value of a node.
///

Student* findMinimumValueNode(Student* node)
{
  Student* current = node;
  while (current && current->bad_node != NULL)
    current = current->bad_node;

  return current;
}

/// This function is used to recursively remove a node from the BST

Student* deleteNode(Student* root, int points, char* name, int* ret_val)
{
  if (root == NULL)
    return root;

  if(!strcmp(root->student_name,name))
  {
    *ret_val = 1;
  }

  if (points < root->student_points)
    root->bad_node = deleteNode(root->bad_node, points, name, ret_val);

  else if (points > root->student_points)
    root->good_node = deleteNode(root->good_node, points, name, ret_val);

  else
  {
    if (strcmp(name, root->student_name) < 0)
      root->bad_node = deleteNode(root->bad_node, points, name, ret_val);

    else if (strcmp(name, root->student_name) > 0)
      root->good_node = deleteNode(root->good_node, points, name, ret_val);

    else
    {
      if (root->bad_node == NULL)
      {
        Student* temp = root->good_node;
        return temp;
      }
      else if (root->good_node == NULL)
      {
        Student* temp = root->bad_node;
        return temp;
      }
      else
      {
        Student* minimum_node = findMinimumValueNode(root->good_node);

        root->student_points = minimum_node->student_points;
        strcpy(root->student_name, minimum_node->student_name);

        root->good_node = deleteNode(root->good_node, minimum_node->student_points, minimum_node->student_name, ret_val);
      }
    }
  }

  return root;
}

/// This function iterated through the schools and classes until it find where the student to be removed is.
///

School* iterateSchools(School* actual_schools, Student student)
{
  School* temp_school = actual_schools;
  int idx = 0;
  int ret_val = 0;

  while (actual_schools[idx].school_id != 0xfff)
  {
    Class* class_1 = actual_schools[idx].class_1;
    Class* class_2 = actual_schools[idx].class_2;
    Class* class_3 = actual_schools[idx].class_3;
    while(class_1 != NULL)
    {
      if(!ret_val)
        break;
      deleteNode(class_1->root_node,student.student_points,student.student_name,&ret_val);
      class_1 = class_1->next_parallel;
    }
    while(class_2 != NULL)
    {
      if(!ret_val)
        break;
      deleteNode(class_2->root_node,student.student_points,student.student_name,&ret_val);
      class_2 = class_2->next_parallel;
    }
    while(class_3 != NULL)
    {
      if(!ret_val)
        break;
      deleteNode(class_3->root_node,student.student_points,student.student_name,&ret_val);
      class_3 = class_3->next_parallel;
    }
    idx++;
  }
  actual_schools = temp_school;
  return actual_schools;
}

/// This function does the save of the current state of the BST in a new file.
///

void saveInFile(Student* actual_students, int* return_value)
{
  FILE* existing_file = fopen(SAVED_FILENAME,"r");
  if(existing_file)
  {
    fclose(existing_file);
    remove(SAVED_FILENAME);
  }

  char* stud_school_id = NULL;
  char* stud_age = NULL;
  char* stud_points = NULL;
  char* full_string = NULL;

  FILE* file_to_save = fopen(SAVED_FILENAME,"w");
  if(!file_to_save)
  {
    printf("File could not be opened!!!\n");
    return;
  }
  int index = 0;
  for(index = 0;actual_students[index].student_name != NULL ; index++)
  {
    int inner_index = 0;
    while (actual_students[inner_index].student_name != NULL)
    {
      if(actual_students[inner_index].student_points == 0xfffff && (&actual_students[index]==&actual_students[inner_index]))
      {
        index++;
      }
      inner_index++;
    }

    if(actual_students[index].student_name == NULL)
      break;

    stud_points = malloc(10);
    if(!stud_points)
    {
      *return_value = MEMORY_PROBLEM;
      printf("Memory could not be allocated!!!\n");
      return;
    }
    memset(stud_points,0,10);
    stud_age = malloc(10);
    if(!stud_age)
    {
      free(stud_points);
      *return_value = MEMORY_PROBLEM;
      printf("Memory could not be allocated!!!\n");
      return;
    }
    memset(stud_age,0,10);
    stud_school_id = malloc(10);
    if(!stud_school_id)
    {
      free(stud_points);
      free(stud_age);
      *return_value = MEMORY_PROBLEM;
      printf("Memory could not be allocated!!!\n");
      return;
    }
    memset(stud_school_id,0,10);
    full_string = malloc(1000);
    if(!full_string)
    {
      free(stud_points);
      free(stud_age);
      free(stud_school_id);
      *return_value = MEMORY_PROBLEM;
      printf("Memory could not be allocated!!!\n");
      return;
    }
    memset(full_string,0,1000);

    strcat(full_string,actual_students[index].student_name);
    sprintf(stud_school_id,"  %d",actual_students[index].stud_school_id);
    strcat(full_string, stud_school_id);
    sprintf(stud_age," %d",actual_students[index].year_of_birth);
    strcat(full_string, stud_age);
    sprintf(stud_points," %d\n",actual_students[index].student_points);
    strcat(full_string, stud_points);
    fprintf(file_to_save, "%s%s%s%s",actual_students[index].student_name,stud_school_id,stud_age,stud_points);
    free(full_string);
    free(stud_points);
    free(stud_age);
    free(stud_school_id);
  }
  fclose(file_to_save);
}

/// This function is responsible for the load of the previously save file.
///

School* loadFromFile(char** school_file_info, Student** actual_students, int* return_value)
{
  School* actual_schools = NULL;
  FILE* student_file = fopen(SAVED_FILENAME,"r");
  if(!student_file)
  {
    printf("File could not be opened!!!\n");
    return actual_schools;
  }
  actual_schools = malloc(sizeof(School));
  if(!actual_schools)
  {
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;
  }
  actual_schools = linkClasses(school_file_info, actual_schools, return_value);
  char** student_file_info = readStudentInfo(student_file, return_value);

  *actual_students = malloc(sizeof(Student));
  if(!(actual_students))
  {
    free(actual_schools);
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;
  }
  *actual_students = linkStudents(student_file_info, *actual_students, return_value);

  for(int index = 0; student_file_info[index] != NULL; index++)
  {
    free(student_file_info[index]);
  }
  free(student_file_info);


  actual_schools = decideSchool(*actual_students, actual_schools, return_value);
  fclose(student_file);
  return actual_schools;
}

///TODO: Function to parse the inputs and filenames, for the framework.
