#include "pystr.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct pystr_node {
    char ch;
    struct pystr_node *next;
} pystr_node;

struct pystr {
    int length;
    pystr_node *head;
    pystr_node *tail; // End of the list (for O(1) appending)
};

static void pystr_reset_list(pystr *self) {
    pystr_node *current = self->head;
    pystr_node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    self->head = NULL;
    self->tail = NULL;
    self->length = 0;
}

// Constructor
pystr *pystr_new(void) {
    pystr *p = (pystr *)malloc(sizeof(*p));
    if (p == NULL) return NULL;

    p->length = 0;
    p->head = NULL;
    p->tail = NULL;

    return p;
}

// Destructor
void pystr_del(pystr *self) {
    if (self) {
        pystr_reset_list(self);
        free(self);
    }
}

// Append char: Primary modification method
int pystr_append(pystr *self, char ch) {
    if (!self) return -1;

    pystr_node *new_node = (pystr_node *)malloc(sizeof(pystr_node));
    if (new_node == NULL) return -1;

    new_node->ch = ch;
    new_node->next = NULL;

    if (self->head == NULL) {
        // List is empty
        self->head = new_node;
        self->tail = new_node;
    } else {
        // Append to the tail (O(1))
        self->tail->next = new_node;
        self->tail = new_node;
    }

    self->length++;
    return 0;
}

int pystr_appends(pystr *self, const char *str) {
    if (!self || !str) return -1;
    
    const char *ptr = str;
    while (*ptr != '\0') { 
        if (pystr_append(self, *ptr) != 0) {
            return -1;
        }
        ptr++;
    }
    return 0;
}

int pystr_assign(pystr *self, const char *str) {
    if (!self || !str) return -1;

    pystr_reset_list(self);

    return pystr_appends(self, str);
}

int pystr_len(const pystr *self) {
    if (!self) return 0;
    return self->length;
}

// String accessor: Builds a contiguous C-string
char *pystr_str(const pystr *self) {
    if (!self || self->length == 0) {
        char *empty_str = (char *)malloc(1);
        if (empty_str) empty_str[0] = '\0';
        return empty_str;
    }

    char *c_str = (char *)malloc(self->length + 1);
    if (c_str == NULL) return NULL;

    pystr_node *current = self->head;
    int i = 0;

    while (current != NULL) {
        c_str[i++] = current->ch;
        current = current->next;
    }

    c_str[i] = '\0'; 
    return c_str;
}

// Dump (Debugging)
void pystr_dump(const pystr *self) {
    if (!self) {
        printf("Object (NULL)\n");
        return;
    }
    
    char *data_str = pystr_str(self);

    if (data_str == NULL) {
        printf("Object length=%d data=(Memory Error)\n", self->length);
        return;
    }

    printf("Object length=%d data=%s\n", self->length, data_str);
    
    // Must free the string created by pystr_str
    free(data_str); 
}