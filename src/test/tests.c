#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../linked_list_map.h"

struct element {
  char value[10];
};

int cmp(void* c1, void* c2) {
  return strcmp(((struct element*)c1)->value, ((struct element*)c2)->value);
}

void del(void* c) {
  free(c);
}

void* new_element(char* c) {
  struct element* memory = (struct element*)malloc(sizeof(struct element));
  strcpy(memory->value, c);
  return memory;
}

void init_test() {
  struct linkedlist_map* map = linkedlist_map_new(&cmp, &del, &del);

  assert(map != NULL);

  linkedlist_map_destroy(map);
}

/* put one element into list*/
void put_get_simple_test1() {
  struct linkedlist_map* map = linkedlist_map_new(&cmp, &del, &del);

  struct element* key = new_element("a");
  linkedlist_map_put(map, key, new_element("a"));
  struct element* res = linkedlist_map_get(map, key);
  assert(strcmp(res->value, "a") == 0);

  linkedlist_map_destroy(map);
}

/* replcae head value*/
void replace_head_value_test() {
  struct linkedlist_map* map = linkedlist_map_new(&cmp, &del, &del);

  struct element* key1 = new_element("a");
  linkedlist_map_put(map, key1, new_element("a"));
  struct element* key2 = new_element("a");
  linkedlist_map_put(map, key2, new_element("b"));

  struct element* res = linkedlist_map_get(map, key2);
  assert(strcmp(res->value, "b") == 0);

  assert(linkedlist_map_size(map) == 1);

  linkedlist_map_destroy(map);
}

/* add two element into list second > first*/
void put_get_simple_test2() {
  struct linkedlist_map* map = linkedlist_map_new(&cmp, &del, &del);

  struct element* key1 = new_element("a");
  linkedlist_map_put(map, key1, new_element("a"));

  struct element* key2 = new_element("b");
  linkedlist_map_put(map, key2, new_element("b"));

  assert(linkedlist_map_size(map) == 2);

  struct element* res1 = linkedlist_map_get(map, key1);

  assert(strcmp(res1->value, "a") == 0);
  struct element* res2 = linkedlist_map_get(map, key2);
  assert(strcmp(res2->value, "b") == 0);
  linkedlist_map_destroy(map);
}

/* add two element into list, first>second*/
void put_get_simple_test3() {
  struct linkedlist_map* map = linkedlist_map_new(&cmp, &del, &del);

  // put first element
  // puts("add first");
  struct element* key1 = new_element("b");
  linkedlist_map_put(map, key1, new_element("b"));

  // put second element
  // puts("add second");
  struct element* key2 = new_element("a");
  linkedlist_map_put(map, key2, new_element("a"));

  assert(linkedlist_map_size(map) == 2);

  struct element* res1 = linkedlist_map_get(map, key1);
  assert(strcmp(res1->value, "b") == 0);
  struct element* res2 = linkedlist_map_get(map, key2);
  assert(strcmp(res2->value, "a") == 0);

  linkedlist_map_destroy(map);
}

void put_remove_get_test1() {
  struct linkedlist_map* map = linkedlist_map_new(&cmp, &del, &del);

  struct element* key = new_element("a");
  linkedlist_map_put(map, key, new_element("a"));

  assert(linkedlist_map_size(map) == 1);

  struct element* value = linkedlist_map_remove(map, key);
  assert(strcmp(value->value, "a") == 0);

  assert(linkedlist_map_size(map) == 0);
  del(value);
  
  linkedlist_map_destroy(map);
}

void put_remove_get_test2() {
  struct linkedlist_map* map = linkedlist_map_new(&cmp, &del, &del);

  struct element* key1 = new_element("a");
  linkedlist_map_put(map, key1, new_element("a"));

  struct element* key2 = new_element("b");
  linkedlist_map_put(map, key2, new_element("b"));

  assert(linkedlist_map_size(map) == 2);
  struct element* value2 = linkedlist_map_remove(map, key2);
  assert(cmp(value2->value, key2) == 0);
  del(value2);

  assert(linkedlist_map_size(map) == 1);

  struct element* value1 = linkedlist_map_remove(map, key1);
  assert(cmp(value1->value, key1) == 0);
  del(value1);

  assert(linkedlist_map_size(map) == 0);

  linkedlist_map_destroy(map);
}

void complex_test1() {
  struct linkedlist_map* map = linkedlist_map_new(&cmp, &del, &del);

  struct element* key2 = new_element("b");
  linkedlist_map_put(map, key2, new_element("b"));

  struct element* key1 = new_element("a");
  linkedlist_map_put(map, key1, new_element("a"));

  struct element* key3 = new_element("c");
  linkedlist_map_put(map, key3, new_element("c"));

  struct element* key4 = new_element("d");
  linkedlist_map_put(map, key4, new_element("d"));

  assert(linkedlist_map_size(map) == 4);

  struct element* res3 = linkedlist_map_get(map, key3);
  assert(strcmp(res3->value, "c") == 0);

  struct element* value3 = linkedlist_map_remove(map, key3);
  assert(strcmp(value3->value, "c") == 0);
  del(value3);
  assert(linkedlist_map_size(map) == 3);

  linkedlist_map_destroy(map);
}

void test_invalid_input1(){
  struct linkedlist_map* map = linkedlist_map_new(NULL, &del, &del);

  assert(map==NULL);
  map = linkedlist_map_new(&cmp, NULL, &del);
  assert(map==NULL);
  map = linkedlist_map_new(&cmp, &del, NULL);
  assert(map==NULL);

  linkedlist_map_destroy(map);
}

int main() {
  init_test();
  printf("%-30s %-10s\n","init_test", "complete");

  put_get_simple_test1();
  printf("%-30s %-10s\n","put_get_simple_test1", "complete");

  replace_head_value_test();
  printf("%-30s %-10s\n","replace_head_value_test", "complete");

  put_get_simple_test2();
  printf("%-30s %-10s\n","put_get_simple_test2", "complete");

  put_get_simple_test3();
  printf("%-30s %-10s\n","put_get_simple_test3", "complete");

  put_remove_get_test1();
  printf("%-30s %-10s\n","put_remove_get_test1", "complete");

  complex_test1();
  printf("%-30s %-10s\n","complex_test1", "complete");
  
  test_invalid_input1();
  printf("%-30s %-10s\n","test_invalid_input1", "complete");

}