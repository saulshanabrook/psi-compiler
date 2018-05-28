#include <stdio.h>
#include <stdlib.h>

#include "sys.e"
#include "types.h"
#include "parser.h"
#include "symbtab.h"

/* free_id_entry recursively frees entries in the entry chain */
void free_id_entry (id_entry *entry)
{
  if (entry != NULL) {
    free_id_entry (entry->next);
    free (entry);
  }
}

long compute_hashkey (string name)
{
  int len_name, i, hashkey = 1;

  /* hashkey = (c1 * c2 * ... * cn) mod MAXTABLE */
  len_name = strlen (name);
  for (i = 0; i < len_name; i++) {
    hashkey *= (int) name[i];
  }
  return (hashkey % MAXTABLE);
}
 
/* create_symbtab creates and initialized a symbol table */
symbtab *create_symbtab (void)
{
  symbtab *new;
  int i;

  new = (symbtab *) get_mem (sizeof (symbtab));
  for (i = 0; i < MAXTABLE; i++)
    new->htable[i]=NULL;      /* set all entries to NULL, just in case */
  new->curr_scope = 1;        /* current scope starts at 1 (global scope) */
  return (new);
}

void inc_scope (symbtab *tab)
{
  tab->curr_scope++;
}
   
void dec_scope (symbtab *tab)
{
  tab->curr_scope--;
}
   
/* destroy_symbtab destroys a symbol tables (frees memory) */
void destroy_symbtab (symbtab *table)
{
  int i;

  for (i = 0; i < MAXTABLE; i++) {
    free_id_entry (table->htable[i]);     /* free all the entries */
  }
  free (table);
}

/* find_symbtab searches for name in the symbol table;  
 * entry is a reference to the symbol table entry corresponding to name,
 * and present indicates if the name was already present in the current
 * scope.  entry is NULL if name was not present.
 */
id_entry *find_symbtab (symbtab *table, string name, boolean *present)
{
  long hashkey;
  boolean exit;
  id_entry *curr_entry;

  *present = false;
  hashkey = compute_hashkey (name);
  curr_entry = table->htable[hashkey];
  exit = false;
  while ((!exit) & (curr_entry != NULL)) {
    if (curr_entry->scope < table->curr_scope) {  /* outside of scope */
      exit = true;
    } else { /* first entries in chain are always <= table->curr_scope so */
      /* just compare the strings.  */
      if (strncmp (curr_entry->name, name, MAXSTRING) == 0) {
        *present = true;
        exit = true;
      } else { /* keep on searching */
        curr_entry = curr_entry->next;
      }
    }
  }
  return ((*present==true) ? curr_entry : NULL);
}

/* enter_symbtab enters a name in the table if not already present.
 * entry is a reference to the symbol table entry corresponding to name,
 * and present indicates if the name was already present in the current
 * scope.
 */
id_entry *enter_symbtab (symbtab *table, string name, boolean *present)
{
  long hashkey;
  id_entry *temp, *entry;

  entry = find_symbtab (table, name, present);
  if (!(*present)) { /* not present, so create new entry, and insert it */
    entry = (id_entry *) get_mem (sizeof(id_entry));
    strncpy (entry->name, name, MAXSTRING);
    entry->scope = table->curr_scope;
    hashkey = compute_hashkey (name);
    temp = table->htable[hashkey];
    entry->next = temp;
    table->htable[hashkey] = entry;
  }
  return (entry);
}

void copy_attribs (entry_attr *dest, entry_attr *src)
{
  dest->class = src->class;
  dest->type  = src->type;
  dest->loc   = src->loc;
}

void set_attributes (id_entry *entry, entry_attr *new_attribs)
{
  if (entry->attribs == NULL) {
    entry->attribs = (entry_attr *) get_mem (sizeof (entry_attr));
  }
  copy_attribs (entry->attribs, new_attribs);
}

entry_attr *get_attributes (id_entry *entry)
{
  entry_attr *attr;

  attr = (entry_attr *) get_mem (sizeof (entry_attr));
  copy_attribs (attr, entry->attribs);
  return (attr);
}

