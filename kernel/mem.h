#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct dynamic_mem_node
{
        uint32_t size;
        bool used;
        struct dynamic_mem_node *next;
        struct dynamic_mem_node *prev;
} dynamic_mem_node_t;

#define NULL_POINTER ((void*)0)
#define DYNAMIC_MEM_TOTAL_SIZE 4*1024 // 4KB of dynamic memory
#define DYNAMIC_MEM_NODE_SIZE sizeof(dynamic_mem_node_t)

static uint8_t dynamic_mem_area[DYNAMIC_MEM_TOTAL_SIZE];
static dynamic_mem_node_t *dynamic_mem_start;

void mem_free(void *p);
void *mem_alloc(size_t size);
