/*
   Copyright (C) 2000-2002 MySQL AB
    All rights reserved. Use is subject to license terms.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

/*
  Rename a table
*/

#include "heapdef.h"

int heap_rename(const char *old_name, const char *new_name)
{
  reg1 HP_SHARE *info;
  char *name_buff;
  DBUG_ENTER("heap_rename");

  pthread_mutex_lock(&THR_LOCK_heap);
  if ((info = hp_find_named_heap(old_name)))
  {
    if (!(name_buff=(char*) my_strdup(new_name,MYF(MY_WME))))
    {
      pthread_mutex_unlock(&THR_LOCK_heap);
      DBUG_RETURN(my_errno);
    }
    my_free(info->name,MYF(0));
    info->name=name_buff;
  }
  pthread_mutex_unlock(&THR_LOCK_heap);
  DBUG_RETURN(0);
}
