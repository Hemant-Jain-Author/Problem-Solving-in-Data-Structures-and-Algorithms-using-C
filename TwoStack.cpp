#include "stdafx.h"
//#include <stdlib.h>
//#include <stdio.h>
// 
//#define MAX_SIZE 50
//
//typedef struct stack{
//	int top1;
//	int top2;
//	int data[MAX_SIZE];
//}Stack;
//
//void StackInitialize(Stack* stk)
//{
//	stk->top1 = -1;
//	stk->top2 = MAX_SIZE;
//}
//
//void StackPush1 (Stack* stk, int data)
//{
//  if (stk->top1 < stk->top2 - 1)
//  {
//    stk->data[++stk->top1] = data;
//  }
//  else
//  {
//    printf ("Stack is Full!\n");
//  }
//}
//
//void StackPush2 (Stack* stk, int data)
//{
//  if (stk->top1 < stk->top2 - 1)
//  {
//    stk->data[--stk->top2] = data; 
//  }
//  else
//  {
//    printf ("Stack is Full!\n");
//  }
//}
// 
//int StackPop1 (Stack* stk)
//{
//  if (stk->top1 >= 0)
//  {
//    int value = stk->data[stk->top1--];
//    printf ("%d is being popped from Stack 1\n", value);
//	return value;
//  }
//  else
//  {
//    printf ("Stack Empty! Cannot Pop\n");
//  }
//  return INT_MIN;
//}
//int StackPop2 (Stack* stk)
//{
//  if (stk->top2 < MAX_SIZE)
//  {
//    int value = stk->data[stk->top2++];
//    printf ("%d is being popped from Stack 2\n", value);
//	return value;
//  }
//  else
//  {
//    printf ("Stack Empty! Cannot Pop\n");
//  }
//  return INT_MIN;
//}