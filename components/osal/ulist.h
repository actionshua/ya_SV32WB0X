/*
Copyright (c) 2007-2017, Troy D. Hanson   http://troydhanson.github.com/uthash/
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef UTLIST_H
#define UTLIST_H

#define UTLIST_VERSION 2.0.2

/*
 * This file contains macros to manipulate singly and doubly-linked lists.
 *
 * 1. LL_ macros:  singly-linked lists.
 * 2. DL_ macros:  doubly-linked lists.
 * 3. CDL_ macros: circular doubly-linked lists.
 *
 * To use singly-linked lists, your structure must have a "next" pointer.
 * To use doubly-linked lists, your structure must "prev" and "next" pointers.
 * Either way, the pointer to the head of the list must be initialized to NULL.
 *
 * ----------------.EXAMPLE -------------------------
 * struct item {
 *      int id;
 *      struct item *prev, *next;
 * }
 *
 * struct item *list = NULL:
 *
 * int main() {
 *      struct item *item;
 *      ... allocate and populate item ...
 *      DL_APPEND(list, item);
 * }
 * --------------------------------------------------
 *
 * For doubly-linked lists, the append and delete macros are O(1)
 * For singly-linked lists, append and delete are O(n) but prepend is O(1)
 * The sort macro is O(n log(n)) for all types of single/double/circular lists.
 */

/* These macros use decltype or the earlier __typeof GNU extension.
   As decltype is only available in newer compilers (VS2010 or gcc 4.3+
   when compiling c++ source) this code uses whatever method is needed
   or, for VS2008 where neither is available, uses casting workarounds. */
#if !defined(LDECLTYPE) && !defined(NO_DECLTYPE)
#if defined(_MSC_VER)   /* MS compiler */
#if _MSC_VER >= 1600 && defined(__cplusplus)  /* VS2010 or newer in C++ mode */
#define LDECLTYPE(x) decltype(x)
#else                   /* VS2008 or older (or VS2010 in C mode) */
#define NO_DECLTYPE
#endif
#elif defined(__BORLANDC__) || defined(__ICCARM__) || defined(__LCC__) || defined(__WATCOMC__)
#define NO_DECLTYPE
#else                   /* GNU, Sun and other compilers */
#define LDECLTYPE(x) __typeof(x)
#endif
#endif

/******************************************************************************
 * singly linked list macros (non-circular)                                   *
 *****************************************************************************/
#define LL_PREPEND(head,add)                                                                   \
    LL_PREPEND2(head,add,next)

#define LL_PREPEND2(head,add,next)                                                             \
do {                                                                                           \
  (add)->next = (head);                                                                        \
  (head) = (add);                                                                              \
} while (0)

#define LL_APPEND(head,add)                                                                    \
    LL_APPEND2(head,add,next)

#define LL_APPEND2(head,add,next)                                                              \
do {                                                                                           \
  LDECLTYPE(head) _tmp;                                                                        \
  (add)->next=NULL;                                                                            \
  if (head) {                                                                                  \
    _tmp = (head);                                                                             \
    while (_tmp->next) { _tmp = _tmp->next; }                                                  \
    _tmp->next=(add);                                                                          \
  } else {                                                                                     \
    (head)=(add);                                                                              \
  }                                                                                            \
} while (0)

#define LL_INSERT_INORDER(head,add,cmp)                                                        \
    LL_INSERT_INORDER2(head,add,cmp,next)

#define LL_INSERT_INORDER2(head,add,cmp,next)                                                  \
do {                                                                                           \
  LDECLTYPE(head) _tmp;                                                                        \
  if (head) {                                                                                  \
    LL_LOWER_BOUND(head, _tmp, add, cmp);                                                      \
    LL_APPEND_ELEM(head, _tmp, add);                                                           \
  } else {                                                                                     \
    (head) = (add);                                                                            \
    (head)->next = NULL;                                                                       \
  }                                                                                            \
} while (0)

#define LL_LOWER_BOUND(head,elt,like,cmp)                                                      \
    LL_LOWER_BOUND2(head,elt,like,cmp,next)

#define LL_LOWER_BOUND2(head,elt,like,cmp,next)                                                \
  do {                                                                                         \
    if ((head) == NULL || (cmp(head, like)) >= 0) {                                            \
      (elt) = NULL;                                                                            \
    } else {                                                                                   \
      for ((elt) = (head); (elt)->next != NULL; (elt) = (elt)->next) {                         \
        if (cmp((elt)->next, like) >= 0) {                                                     \
          break;                                                                               \
        }                                                                                      \
      }                                                                                        \
    }                                                                                          \
  } while (0)

#define LL_DELETE(head,del)                                                                    \
    LL_DELETE2(head,del,next)

#define LL_DELETE2(head,del,next)                                                              \
do {                                                                                           \
  LDECLTYPE(head) _tmp;                                                                        \
  if ((head) == (del)) {                                                                       \
    (head)=(head)->next;                                                                       \
  } else {                                                                                     \
    _tmp = (head);                                                                             \
    while (_tmp->next && (_tmp->next != (del))) {                                              \
      _tmp = _tmp->next;                                                                       \
    }                                                                                          \
    if (_tmp->next) {                                                                          \
      _tmp->next = (del)->next;                                                                \
    }                                                                                          \
  }                                                                                            \
} while (0)

#define LL_FOREACH(head,el)                                                                    \
    LL_FOREACH2(head,el,next)

#define LL_FOREACH2(head,el,next)                                                              \
    for ((el) = (head); el; (el) = (el)->next)

#define LL_APPEND_ELEM2(head, el, add, next)                                                   \
do {                                                                                           \
 if (el) {                                                                                     \
  (add)->next = (el)->next;                                                                    \
  (el)->next = (add);                                                                          \
 } else {                                                                                      \
  LL_PREPEND2(head, add, next);                                                                \
 }                                                                                             \
} while (0)                                                                                    \

#define LL_APPEND_ELEM(head, el, add)                                                          \
    LL_APPEND_ELEM2(head, el, add, next)

#ifdef NO_DECLTYPE
/* Here are VS2008 / NO_DECLTYPE replacements for a few functions */

#undef LL_CONCAT2
#define LL_CONCAT2(head1,head2,next)                                                           \
do {                                                                                           \
  char *_tmp;                                                                                  \
  if (head1) {                                                                                 \
    _tmp = (char*)(head1);                                                                     \
    while ((head1)->next) { (head1) = (head1)->next; }                                         \
    (head1)->next = (head2);                                                                   \
    UTLIST_RS(head1);                                                                          \
  } else {                                                                                     \
    (head1)=(head2);                                                                           \
  }                                                                                            \
} while (0)

#undef LL_APPEND2
#define LL_APPEND2(head,add,next)                                                              \
do {                                                                                           \
  if (head) {                                                                                  \
    (add)->next = head;     /* use add->next as a temp variable */                             \
    while ((add)->next->next) { (add)->next = (add)->next->next; }                             \
    (add)->next->next=(add);                                                                   \
  } else {                                                                                     \
    (head)=(add);                                                                              \
  }                                                                                            \
  (add)->next=NULL;                                                                            \
} while (0)

#undef LL_INSERT_INORDER2
#define LL_INSERT_INORDER2(head,add,cmp,next)                                                  \
do {                                                                                           \
  if ((head) == NULL || (cmp(head, add)) >= 0) {                                               \
    (add)->next = (head);                                                                      \
    (head) = (add);                                                                            \
  } else {                                                                                     \
    char *_tmp = (char*)(head);                                                                \
    while ((head)->next != NULL && (cmp((head)->next, add)) < 0) {                             \
      (head) = (head)->next;                                                                   \
    }                                                                                          \
    (add)->next = (head)->next;                                                                \
    (head)->next = (add);                                                                      \
    UTLIST_RS(head);                                                                           \
  }                                                                                            \
} while (0)

#undef LL_DELETE2
#define LL_DELETE2(head,del,next)                                                              \
do {                                                                                           \
  if ((head) == (del)) {                                                                       \
    (head)=(head)->next;                                                                       \
  } else {                                                                                     \
    char *_tmp = (char*)(head);                                                                \
    while ((head)->next && ((head)->next != (del))) {                                          \
      (head) = (head)->next;                                                                   \
    }                                                                                          \
    if ((head)->next) {                                                                        \
      (head)->next = ((del)->next);                                                            \
    }                                                                                          \
    UTLIST_RS(head);                                                                           \
  }                                                                                            \
} while (0)

#undef LL_REPLACE_ELEM2
#define LL_REPLACE_ELEM2(head, el, add, next)                                                  \
do {                                                                                           \
  if ((head) == (el)) {                                                                        \
    (head) = (add);                                                                            \
  } else {                                                                                     \
    (add)->next = head;                                                                        \
    while ((add)->next->next && ((add)->next->next != (el))) {                                 \
      (add)->next = (add)->next->next;                                                         \
    }                                                                                          \
    if ((add)->next->next) {                                                                   \
      (add)->next->next = (add);                                                               \
    }                                                                                          \
  }                                                                                            \
  (add)->next = (el)->next;                                                                    \
} while (0)

#undef LL_PREPEND_ELEM2
#define LL_PREPEND_ELEM2(head, el, add, next)                                                  \
do {                                                                                           \
  if (el) {                                                                                    \
    if ((head) == (el)) {                                                                      \
      (head) = (add);                                                                          \
    } else {                                                                                   \
      (add)->next = (head);                                                                    \
      while ((add)->next->next && ((add)->next->next != (el))) {                               \
        (add)->next = (add)->next->next;                                                       \
      }                                                                                        \
      if ((add)->next->next) {                                                                 \
        (add)->next->next = (add);                                                             \
      }                                                                                        \
    }                                                                                          \
    (add)->next = (el);                                                                        \
  } else {                                                                                     \
    LL_APPEND2(head, add, next);                                                               \
  }                                                                                            \
} while (0)                                                                                    \

#endif /* NO_DECLTYPE */

#endif /* UTLIST_H */
