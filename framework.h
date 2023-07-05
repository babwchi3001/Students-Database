//
// Created by Andi Kondi on 03.03.23.
// Do not make changes in the framework.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define YELLOW "\033[0;33m"
#define BLACK "\033[0;30m"
#define WHITE "\033[0;37m"
#define DEFAULT "\033[0m"
#define MAX_PTS_AMOUNT 20000
#define ARGS 3
#define FILE_NOT_FOUND 1
#define WRONG_PARAM_AMOUNT 2
#define MEMORY_PROBLEM 3
#define SUCCESS 0

#define SAVED_FILENAME "names_surnames_save.txt"

typedef struct _School_{
  int school_id;
  struct _Class_* class_1;
  struct _Class_* class_2;
  struct _Class_* class_3;

}School;


char* getInput(int* return_value)
{
  char* input = (char*)malloc(sizeof(char));
  if(!input)
  {
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;
  }
  char getchar_char = 0;
  int index = 0;
  while((getchar_char = (char)getchar()) != '\n')
  {
    input[index] = (char)getchar_char;
    input = realloc(input, index + sizeof(char) + 1);
    index++;
  }
  input[index] = '\0';
  return input;

}

int checkInput(char* curr_stud, School* actual_schools, int* return_value)
{
  int space_flag = 0;
  int upper_flag = 0;
  int check_numbers = 0;
  char* temp_string_for_strstr = malloc(100);
  if(!temp_string_for_strstr)
  {
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return MEMORY_PROBLEM;
  }
  int school_amount = 0;
  int stud_yob = 0;
  int stud_grade = 0;
  int some_flag = 1;

  char* temp_string_whatever = temp_string_for_strstr;
  strcpy(temp_string_for_strstr,curr_stud);
  temp_string_for_strstr = strstr(temp_string_for_strstr, "  ");
  if(temp_string_for_strstr == NULL)
  {
    printf("Invalid input, please check the format of the input!!!\n");
    free(temp_string_whatever);
    return 0;
  }
  temp_string_for_strstr += 2;

  for(int index = 0; actual_schools[index].school_id != 0xfff; index++)
    school_amount++;

  for(int index = 0; curr_stud[index] != '\0'; index++)
  {

    if(!(curr_stud[0] >= 65 && curr_stud[0] <= 90))
    {
      printf("Invalid input, student name must start with a capital letter!!!\n");
      free(temp_string_whatever);
      return 0;

    }
    if(space_flag == 5 && some_flag)
    {
      some_flag = 0;
      check_numbers = atoi(strtok(temp_string_for_strstr, " "));
      if(check_numbers > school_amount)
      {
        printf("Invalid school_id!!!\n");
        free(temp_string_whatever);
        return 0;
      }

      stud_yob = atoi(strtok(NULL, " "));
      if(stud_yob < 2000 || stud_yob > 2002)
      {
        printf("Invalid age!!!\n");
        free(temp_string_whatever);
        return 0;
      }
      stud_grade = atoi(strtok(NULL, " "));
      if(stud_grade > MAX_PTS_AMOUNT)
      {
        printf("Invalid student points!!!\n");
        free(temp_string_whatever);
        return 0;
      }
    }

    if(curr_stud[index] >= 65 && curr_stud[index] <= 90)
      upper_flag++;

    if(curr_stud[index] == ' ')
    {
      space_flag++;
    }

    if((curr_stud[index] == ' ' && !(curr_stud[index+1] >= 65 && curr_stud[index+1] <= 90))
       && space_flag == 1)
    {
      printf("Invalid input, student surname must start with a capital letter!!!\n");
      free(temp_string_whatever);
      return 0;
    }

    if((curr_stud[index] == ' ' && !(curr_stud[index+1] >= 48 && curr_stud[index+1] <= 57)) && space_flag >= 3)
    {
      printf("Invalid input, please check the format of the input!!!\n");
      free(temp_string_whatever);
      return 0;
    }
  }

  if(upper_flag != 2)
  {
    printf("Invalid input, please check the format of the input!!!\n");
    free(temp_string_whatever);
    return 0;
  }

  if(space_flag != 5)
  {
    printf("Invalid input, please check the format of the input!!!\n");
    free(temp_string_whatever);
    return 0;
  }
  free(temp_string_whatever);
  return 1;
}


/// This function is used to get the student name from the given input.

char* getName(char* student_info, int* return_value)
{
  char* temp_name = malloc(70);
  if(!temp_name)
  {
    *return_value = MEMORY_PROBLEM;
    printf("Memory could not be allocated!!!\n");
    return NULL;
  }
  int counter = 0;
  while(student_info[counter] != ' ' || student_info[counter + 1] != ' ')
  {
    temp_name[counter] = student_info[counter];
    counter++;
  }
  temp_name[counter] = '\0';
  return temp_name;
}
