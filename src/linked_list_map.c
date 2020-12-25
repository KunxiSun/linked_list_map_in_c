#include "linked_list_map.h"
#include <stdio.h>
#include <stdlib.h>

struct linkedlist_map_entry {
  void* key;   
  void* value;

  struct linkedlist_map_entry* next;
};

struct linkedlist_map {
  struct linkedlist_map_entry* head;
  int (*cmp)(void*, void*);
  void (*keydel)(void*);
  void (*valdel)(void*);
};

struct linkedlist_map* linkedlist_map_new(int (*cmp)(void*, void*),
                                          void (*keydel)(void*),
                                          void (*valdel)(void*)) {

  if(cmp ==NULL || keydel ==NULL || valdel ==NULL){
    return NULL;
  }
  struct linkedlist_map* map =
      (struct linkedlist_map*)malloc(sizeof(struct linkedlist_map));
  map->cmp = cmp;
  map->keydel = keydel;
  map->valdel = valdel;
  map->head = NULL;

  return map;
}

struct linkedlist_map_entry* new_entry(void* key, void* value) {
  struct linkedlist_map_entry* entry =
      (struct linkedlist_map_entry*)malloc(sizeof(struct linkedlist_map_entry));
  entry->key = key;
  entry->value = value;
  entry->next = NULL;
  return entry;
}

void linkedlist_map_put(struct linkedlist_map* map, void* key, void* value) {
  /* check input*/
  if (map == NULL || key == NULL || value == NULL) {
    return;
  }

  /* check the head is NULL or not*/
  if (map->head == NULL) {
    struct linkedlist_map_entry* entry = new_entry(key, value);
    map->head = entry;
    return;
  }

  /* check special case, if head is bigger than the given*/
  if ((map->cmp(key, map->head->key)) < 0) {
    struct linkedlist_map_entry* entry = new_entry(key, value);
    entry->next = map->head;  
    map->head = entry;
    return;
  }

  struct linkedlist_map_entry* cur = map->head;
  struct linkedlist_map_entry* prev = NULL;
  while (cur != NULL) {
    int cmp = map->cmp(key, cur->key);
    if (cmp > 0) {
      /* if cmp>0, traverse to the next*/
      prev = cur;
      cur = cur->next;
      continue;
    } else if (cmp < 0) {
      /* if cmp<0, insert between cur and prev*/
      struct linkedlist_map_entry* entry = new_entry(key, value);
      prev->next = entry;
      entry->next = cur;
      return;
    } else {
      /* if cmp==0, replace the value*/
      map->valdel(cur->value);
      map->keydel(cur->key);
      cur->key = key;
      cur->value = value;
      return;
    }
  }

  /*if does not find a place to insert entry,
  add the entry at the end of the list*/
  struct linkedlist_map_entry* entry = new_entry(key, value);

  prev->next = entry;
}

void* linkedlist_map_get(struct linkedlist_map* map, void* key) {
  if (map == NULL || key == NULL) {
    return NULL;
  }

  struct linkedlist_map_entry* cur = map->head;
  while (cur != NULL) {
    int cmp = map->cmp(key, cur->key);
    if (cmp > 0) {
      cur = cur->next;
    } else if (cmp == 0) {
      return cur->value;
    } else {
      return NULL;
    }
  }
  return NULL;
}

void* linkedlist_map_remove(struct linkedlist_map* map, void* key) {
  if (map == NULL || key == NULL) {
    return NULL;
  }

  /* Check head*/
  if (map->cmp(key, map->head->key) == 0) {
    void* res = map->head->value;
    map->keydel(map->head->key);
    free(map->head);
    map->head = NULL;
    return res;
  }

  struct linkedlist_map_entry* cur = map->head;
  struct linkedlist_map_entry* prev = NULL;
  while (cur != NULL) {
    int cmp = map->cmp(key, cur->key);
    if (cmp > 0) {
      /* traverse to the next*/
      prev = cur;
      cur = cur->next;
    } else if (cmp < 0) {
      /* not find in list*/
      return NULL;
    } else {
      /* remove it from list*/
      void* res = cur->value;
      prev->next = cur->next;
      map->keydel(cur->key);
      free(cur);
      return res;
    }
  }
  return NULL;
}

size_t linkedlist_map_size(struct linkedlist_map* map) {
  if (map == NULL) {
    return 0;
  }

  size_t size = 0;
  struct linkedlist_map_entry* cur = map->head;
  while (cur != NULL) {
    size++;
    cur = cur->next;
  }
  return size;
}

/* helper function to do recursion*/
void destroy_helper(struct linkedlist_map* map,
                    struct linkedlist_map_entry* head) {
  if (head == NULL) {
    return;
  }

  destroy_helper(map, head->next);

  map->keydel(head->key);
  map->valdel(head->value);
  free(head);
}

void linkedlist_map_destroy(struct linkedlist_map* map) {
  if (map == NULL) {
    return;
  }

  destroy_helper(map, map->head);
  free(map);
}