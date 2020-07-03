#ifndef DA2XHD_LIB_H
#define DA2XHD_LIB_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "TM2x.h"

/*
  element_pt is always element aligned and pointing to the base of an element.

  operand order:
    context just before pred or function
    element_byte_n  just after hd, and if not hd, just after tape
 
*/


//#define TM2xHd_F_PREFIX
//#define TM2xHd_F_PREFIX extern inline
#define TM2xHd_F_PREFIX static inline


//--------------------------------------------------------------------------------
// dyanamic array iterator
//
  typedef struct {
    char *element_pt;
  } TM2xHd;

  #define TM2xHd_Mount(tape ,hd) TM2xHd TM2xHd_ ## hd ,*hd; hd = &TM2xHd_ ## hd; TM2xHd_rewind(tape ,hd);

  TM2xHd_F_PREFIX bool TM2xHd_is_on_tape(TM2x *tape ,TM2xHd *hd){
    return hd->element_pt <= TM2x_byte_n_pt(tape) && hd->element_pt >= TM2x_byte_0_pt(tape);
  }

  TM2xHd_F_PREFIX void TM2xHd_rewind(TM2x *tape ,TM2xHd *hd){
    hd->element_pt = TM2x_byte_0_pt(tape);
  }

  TM2xHd_F_PREFIX bool TM2xHd_step(TM2x *tape ,TM2xHd *hd ,address_t element_byte_n){
    if( hd->element_pt >= (char *)TM2x_element_n_pt(tape ,element_byte_n) ) return false;
    hd->element_pt += element_byte_n + 1;
    return true;
  }
  
  TM2xHd_F_PREFIX void *TM2xHd_pt(TM2xHd *hd){
    return hd->element_pt;
  }

  TM2xHd_F_PREFIX void TM2xHd_read(TM2xHd *hd ,address_t element_byte_n ,void *dst_pt){
    memcpyn(dst_pt, hd->element_pt, element_byte_n);
  }
  #define TM2xHd_Read(hd ,item) TM2xHd_read(hd ,byte_no_of(type_of(item)) ,&item)
  #define TM2xHd_Read_Expr(hd ,type) *((type *)hd->element_pt)

  TM2xHd_F_PREFIX void TM2xHd_write(TM2xHd *hd ,address_t element_byte_n ,void *src_element_pt){
    memcpyn(hd->element_pt ,src_element_pt ,element_byte_n);
  }
  #define TM2xHd_Write(hd ,item) *((typeof(item) *)hd->element_pt) = item
  #define TM2xHd_Write_Lval(hd ,item) *((typeof(item) *)hd->element_pt)


//--------------------------------------------------------------------------------
// quantifiers
//

  // nah .. better to implement this with memcpyn, see TM2x_init_copy
  // shallow copy tape_src elements to the end of tape_acc
  TM2xHd_F_PREFIX void TM2x_cat
  (
   TM2x *tape_acc
   ,TM2x *tape_src
   ,address_t element_byte_n
   ){
    TM2xHd_Mount(tape_src, hd_src);
    do{
      TM2x_push_write(tape_acc ,TM2xHd_pt(hd_src) ,element_byte_n);
    }while( TM2xHd_step(tape_src ,hd_src ,element_byte_n) );
  }

  // applies f to each element, in order starting at the current hd position, until reaching the end of the tape
  TM2xHd_F_PREFIX void TM2xHd_apply_to_each
  (
   TM2x *tape
   ,TM2xHd *hd
   ,address_t element_byte_n
   ,void *context
   ,void f(void *context ,void *el ,address_t element_byte_n)
   ){
    do{
      f(context ,TM2xHd_pt(hd) ,element_byte_n);
    }while( TM2xHd_step(tape ,hd ,element_byte_n) );
  }

  // applies pred to each element until either pred is not true, or reaching the end of the tape
  TM2xHd_F_PREFIX bool TM2xHd_all
  (
   TM2x *tape
   ,TM2xHd *hd
   ,address_t element_byte_n
   ,void *context
   ,bool pred(void *context ,void *el ,address_t element_byte_n)
   ){
    do{
      if( !pred(context ,TM2xHd_pt(hd) ,element_byte_n) ) return false;
    }while( TM2xHd_step(tape ,hd ,element_byte_n) );
    return true;
  }

  TM2xHd_F_PREFIX bool TM2xHd_exists
  (
   TM2x *tape
   ,TM2xHd *hd
   ,address_t element_byte_n
   ,void *context
   ,bool pred(void *context ,void *el ,address_t element_byte_n)
   ){
    do{
      if( pred(context ,TM2xHd_pt(hd) ,element_byte_n) ) return true;
    }while( TM2xHd_step(tape ,hd ,element_byte_n) );
    return false;
  }

//--------------------------------------------------------------------------------
// set
//
  // push_write src_elmeent on array if pred not exists over tape
  // when pred is a comparison can be used to force order
  // when pred is equality can be used for set behavior
  TM2xHd_F_PREFIX bool TM2xHd_push_write_if
  (
   TM2x *tape_dst
   ,void *src_element_pt 
   ,address_t element_byte_n
   ,void *context
   ,bool pred(void *context ,void *el ,address_t element_byte_n)
   ){
    TM2xHd_Mount(tape_dst ,hd);
    if( !TM2xHd_exists(tape_dst ,hd ,element_byte_n ,context ,pred) ){
      TM2x_push_write(tape_dst ,src_element_pt ,element_byte_n);
      return true;
    }
    return false;
  }

  // -accumulates copies of elements from set_src into set_acc
  // -returns whether the set_src was a subset of set_acc before the union
  // -context given to the pred is a pointer to the src element
  TM2xHd_F_PREFIX bool TM2xHd_accumulate_union
  (
   TM2x *set_acc
   ,TM2x *set_src
   ,address_t element_byte_n
   ,bool pred(void *context ,void *el ,address_t element_byte_n)
   ){
    bool subset = true;
    TM2xHd_Mount(set_acc ,hd_acc);
    TM2xHd_Mount(set_src ,hd_src);
    do{
      void *src_element_pt = TM2xHd_pt(hd_src);
      if( !TM2xHd_exists(set_acc ,hd_acc ,element_byte_n ,src_element_pt ,pred) ){
        TM2x_push_write(set_acc ,src_element_pt ,element_byte_n);      
        subset = false;
      }
      TM2xHd_rewind(set_acc ,hd_acc);
    }while( TM2xHd_step(set_src ,hd_src ,element_byte_n) );
    return subset;
  }

  // -initialize set_c with the intersection of sets a and b
  // -returns whether the sets set_a and set_b were not found to be distinct, i.e. if initialization occurred
  // -context given to the pred is a_element, the pred src element is the b_element
  TM2xHd_F_PREFIX bool TM2xHd_init_intersection
  (
   TM2x *set_c
   ,TM2x *set_a
   ,TM2x *set_b
   ,address_t element_byte_n
   ,bool pred(void *context ,void *el ,address_t element_byte_n)
   ){
    TM2xHd_Mount(set_a ,hd_a);
    TM2xHd_Mount(set_b ,hd_b);
    bool found_first = false;
    // search for first, nested extension
    do{
      void *a_element_pt = TM2xHd_pt(hd_a);
      found_first = TM2xHd_exists(set_b ,hd_b ,element_byte_n ,a_element_pt ,pred);
      if( found_first ){
        TM2x_init_write(set_c ,a_element_pt ,element_byte_n);      
        // extend
        while(TM2xHd_step(set_a ,hd_a ,element_byte_n)){
          if(TM2xHd_exists(set_b ,hd_b ,element_byte_n ,a_element_pt ,pred)){
            TM2x_push_write(set_c ,a_element_pt ,element_byte_n);      
          }
        }
        break;
      }
      if( !TM2xHd_step(set_a ,hd_a ,element_byte_n) )
        break;
      TM2xHd_rewind(set_b ,hd_b);
    }while(true);
    return found_first;
  }

//--------------------------------------------------------------------------------
// some useful predicates
//
  TM2xHd_F_PREFIX bool TM2xHd_pred_bytes_eq(void *context ,void *a_e0 ,address_t element_byte_n){
    char *e0 = a_e0;
    char *e1 = context;
    return memcmpn(e0 ,e1 ,element_byte_n) == 0;
  }
  TM2xHd_F_PREFIX bool TM2xHd_pred_cstring_eq(void *context ,void *a_e0 ,address_t element_byte_n){
    char *e0 = a_e0;
    char *e1 = context;
    return strncmpn(e0 ,e1 ,element_byte_n) == 0;
  }

//--------------------------------------------------------------------------------
// some utility functions typically be used with apply_to_each
//
  // each element is a pointer to dynamic memory, and that memory is to be freed:
  TM2xHd_F_PREFIX void TM2xHd_f_free(void *context ,void *element_pt ,address_t element_byte_n){
    free(element_pt);
  }

  // elements are integers to be printed
  // could improve this by getting the integer size from element_byte_n
  TM2xHd_F_PREFIX void TM2xHd_f_print_int(void *context ,void *element_pt ,address_t element_byte_n){
    fprintf(stderr ,"%s%d" ,(char *)context ,*(int *)element_pt);
  }

  // elements are char *
  TM2xHd_F_PREFIX void TM2xHd_f_print_cstring(void *context ,void *element_pt ,address_t element_byte_n){
    fprintf(stderr ,"%s%s" ,(char *)context ,(char *)element_pt);
  }


#endif
