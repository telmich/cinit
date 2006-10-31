/***********************************************************************
 * 
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    List handling: Add a new item to a (non-)empty list
 */

/*
 * list: pointer to the list
 * new:  pointer to data to insert (already filled up)
 */
int list_entry_add(void *list, void *new)
{
   if( list == NULL ) {       /* new list          */
      list        = new;
      list->prev  = list;
      list->next  = list;
   } else {                   /* already existing  */
      new->next         = list;           /* new-> first    */
      new->prev         = list->prev;     /* last <- new    */
      list->prev->next  = new;            /* last -> new    */
      list->prev        = new;            /* new <- first   */
   }

   return 1;
}
