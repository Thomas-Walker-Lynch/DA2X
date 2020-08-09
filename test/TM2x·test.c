
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define TM2x·TEST
#include "TM2x.h"
#include "MallocCounter.h"
#include "Result.h"
#include "Conveyance.h"
#include "Inclusive.h"

int main(){

  #include "CLib·DataTypes.h"
  #include "Inclusive·DataTypes.h"
  #include "TM2x·DataTypes.h"
  union Conveyance·Data{
    #include "CLib·Data.h"
    #include "Inclusive·Data.h"
    #include "TM2x·Data.h"
  };
  union Conveyance·Data Conveyance·Data0 ,Conveyance·Data1;
  union {
    struct test_00{
      address_t malloc_cnt;
      address_t constructed_cnt;
      Result·Tallies results;
      bool f[256];
      uint i;
      TM2x *tape;
    } test_0;
  } Conveyance·Context0;

  #include "Conveyance·Text.h"
  #include "CLib·Text.h"
  #include "Inclusive·Text.h"
  #include "TM2x·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  continue_from test_0;

  test_0:{
    Conveyance nominal ,fail ,cleanup ,report;
    CX(test_0 ,0 ,0);
    cx->malloc_cnt = MallocCounter·count;
    cx->constructed_cnt = TM2x·constructed_count;
    cx->i = 0;

    //allocate
    AR(TM2x·alloc_heap ,0);
    ar->tape = &cx->tape;
    ar->nominal = &&nominal;
    ar->fail = &&fail;
    continue_from TM2x·alloc_heap;

    nominal:{
      Conveyance nominal;
      cx->f[cx->i++] = true;

      //construct
      AR(TM2x·construct_bytes ,0);
      ar->tape = cx->tape;
      ar->byte_n = 48;
      ar->nominal = &&nominal;
      ar->alloc_fail = &&fail;
      continue_from TM2x·construct_bytes;

      nominal:{
        cx->f[cx->i++] = Test·CLib·allocation_n == 63;
        continue_from cleanup;
        cend;
      }
      cend;
    }

    fail:{
      cx->f[cx->i++] = false;
      continue_from cleanup;
      cend;
    }

    cleanup:{
      // destruct and deallocate
      AR(TM2x·destruct_dealloc_heap ,0);
      ar->tape = cx->tape;
      ar->nominal = &&report;
      continue_from TM2x·destruct_dealloc_heap;
      cend;
    }

    report:{
      cx->f[cx->i++] = cx->malloc_cnt == MallocCounter·count;
      cx->f[cx->i++] = cx->constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_0" ,&cx->results ,cx->f ,cx->i);
      Result·Tallies·accumulate(accumulated_results_pt ,&cx->results);
      continue_from tests_finished;
      cend;
    }

    tests_finished:{
      Result·Tallies·print("Inclusive·test results" ,accumulated_results_pt);
      return accumulated_results.failed;
    }

    cend;
  }

  exit(0);

#if 0
  Result·Tallies r ,acc ,*accp; accp=&acc;
  Result·Tallies·init(accp);

  r = test_0(); Result·Tallies·accumulate(accp ,&r);
  r = test_1(); Result·Tallies·accumulate(accp ,&r);
  r = test_2(); Result·Tallies·accumulate(accp ,&r);

  Result·Tallies·print("TM2x·test results" ,accp);
  return acc.failed;
#endif



}

#if 0

Result·Tallies test_0(){
  address_t malloc_cnt = MallocCounter·count;
  address_t constructed_cnt = TM2x·constructed_count;
  bool f[5];
  uint i = 0;

  Result·Tallies r ,*rp; rp = &r;
  Result·Tallies·init(rp);

  TM2x·AllocStaticConstruct(a0p ,0 ,int32_t ,&&nominal ,&&fail);
  nominal:{
    f[i] = true;  
    continue_from end;
  }
  fail:{
    f[i] = false;
    continue_from end;
  }
  end:{
    cx->i++;
  }

  int32_t j = -5;
  int32_t k;

  f[cx->i++] = TM2x·byte_n(a0p) == 3;
  TM2x·Write(a0p ,0 ,j);
  TM2x·Read(a0p ,0 ,k);
  f[cx->i++] = k == -5;

  TM2x·destruct(a0p);
  f[cx->i++] = malloc_cnt == MallocCounter·count;
  f[cx->i++] = constructed_cnt == TM2x·constructed_count;
  Result·Tallies·tally("test_0" ,rp ,f ,i);
  return r;
}

Result·Tallies test_1(){
  address_t malloc_cnt = MallocCounter·count;
  address_t constructed_cnt = TM2x·constructed_count;
  Result·Tallies r ,*rp; rp = &r;
  Result·Tallies·init(rp);

  bool f[256];
  uint i = 0;

  TM2x a0,*a0p; a0p = &a0;
  continue_into TM2x·construct_elements(a0p ,1 ,byte_n_of(int32_t) ,&&construct_nominal ,&&construct_fail ,&&construct_fail);
  construct_fail:{
    f[i] = false;
    continue_from construct_end;
  }
  construct_nominal:{
    f[i] = true;
  }
  construct_end:{
    cx->i++;
  }
  f[cx->i++] = a0p->byte_n == 7;

  continue_into TM2x·resize_elements(a0p ,3 ,byte_n_of(int32_t) ,&&resize_nominal ,&&resize_fail ,&&resize_fail);
  resize_fail:{
    f[i] = false;
    continue_from resize_end;
  }
  resize_nominal:{
    f[i] = true;
  }
  resize_end:{
      cx->i++;
  }
  f[cx->i++] = a0p->byte_n == 15;

  // push 1 ,2 ,3 ,4
  //
    int32_t x;
    x = 1; TM2x·Write(a0p ,0 ,x);
    x = 2; TM2x·Write(a0p ,1 ,x);
    x = 3; TM2x·Write(a0p ,2 ,x);
    x = 4; TM2x·Write(a0p ,3 ,x);

  // pop 4 ,3 ,2 ,1
  //
    int32_t y;
    {
      continuations read_pop·nominal ,read_pop·pop_last ,read_pop·alloc_fail ,read_pop·end;
      uint j = 4;
      while( j > 1 ){
        continue_into TM2x·Read_Pop(a0p ,y ,&&read_pop·nominal ,&&read_pop·pop_last ,&&read_pop·alloc_fail);
        read_pop·nominal:{
          f[i] = true;
          continue_from read_pop·end;
        }
        read_pop·pop_last:{
          f[i] = false;
          continue_from read_pop·end;
        }
        read_pop·alloc_fail:{
          f[i] = false;
          continue_from read_pop·end;
        }
        read_pop·end:{
          cx->i++;
        }
        f[i] = y == j;
        cx->i++;
        --j;
      }
    }

    {
      continuations read_pop·nominal ,read_pop·pop_last ,read_pop·alloc_fail ,read_pop·end;
      continue_into TM2x·Read_Pop(a0p ,y ,&&read_pop·nominal ,&&read_pop·pop_last ,&&read_pop·alloc_fail);
      read_pop·nominal:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·pop_last:{
        f[i] = true;
        continue_from read_pop·end;
      }
      read_pop·alloc_fail:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·end:{
        cx->i++;
      }
      f[cx->i++] = y == 1;
    }
    f[cx->i++] = a0p->byte_n == 3;

  TM2x·destruct(a0p);
  f[cx->i++] =  malloc_cnt == MallocCounter·count;
  f[cx->i++] = constructed_cnt == TM2x·constructed_count;
  Result·Tallies·tally("test_1" ,rp ,f ,i);
  return r;
}

Result·Tallies test_2(){
  address_t malloc_cnt = MallocCounter·count;
  address_t constructed_cnt = TM2x·constructed_count;
  bool f[256];
  uint i = 0;

  Result·Tallies r ,*rp; rp = &r;
  Result·Tallies·init(rp);

  TM2x·AllocStaticConstruct(a0 ,0 ,int32_t ,&&nominal ,&&fail);
  nominal:{
    f[i] = true;  
    continue_from end;
  }
  fail:{
    f[i] = false;
  }
  end:{
    cx->i++;
  }
  f[cx->i++] = a0->byte_n == 3;

  int32_t x=1,y=0; 
  TM2x·Write(a0 ,0 ,x); 

  ++x;
  continue_into TM2x·Push(a0 ,x ,&&push_nominal_0 ,&&push_allocation_failed_0);
  push_allocation_failed_0:{
    f[i] = false;
    continue_from push_end_0;
  }
  push_nominal_0:{
    f[i] = true;
  }
  push_end_0:{
    cx->i++;
  }
  f[cx->i++] = TM2x·test_after_allocation_n == 7;
  TM2x·read(a0 ,1 ,&y ,3);
  f[cx->i++] = x==y;

  ++x; 
  continue_into TM2x·Push(a0 ,x ,&&push_nominal_1 ,&&push_allocation_failed_1);
  push_allocation_failed_1:{
    f[i] = false;
    continue_from push_end_1;
  }
  push_nominal_1:{
    f[i] = true;
  }
  push_end_1:{
    cx->i++;
  }
  f[cx->i++] = TM2x·test_after_allocation_n == 15;

  ++x; 
  continue_into TM2x·Push(a0 ,x ,&&push_nominal_2 ,&&push_allocation_failed_2);
  push_allocation_failed_2:{
    f[i] = false;
    continue_from push_end_2;
  }
  push_nominal_2:{
    f[i] = true;
  }  
  push_end_2:{
    cx->i++;
  }
  f[cx->i++] = TM2x·test_after_allocation_n == 15;

  ++x; 
  continue_into TM2x·Push(a0 ,x ,&&push_nominal_3 ,&&push_allocation_failed_3);
  push_allocation_failed_3:{
    f[i] = false;
    continue_from push_end_3;
  }
  push_nominal_3:{
    f[i] = true;
  }
  push_end_3:{
    cx->i++;
  }
  f[cx->i++] = TM2x·test_after_allocation_n == 31;

  y=111222;
    {
      continuations read_pop·nominal ,read_pop·pop_last ,read_pop·alloc_fail ,read_pop·end;
      continue_into TM2x·Read_Pop(a0 ,y ,&&read_pop·nominal ,&&read_pop·pop_last ,&&read_pop·alloc_fail);
      read_pop·nominal:{
        f[i] = true;
        continue_from read_pop·end;
      }
      read_pop·pop_last:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·alloc_fail:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·end:{
        cx->i++;
      }
    }
  f[cx->i++] = y == 5;
  f[cx->i++] = TM2x·test_after_allocation_n == 15;

    {
      continuations read_pop·nominal ,read_pop·pop_last ,read_pop·alloc_fail ,read_pop·end;
      continue_into TM2x·Read_Pop(a0 ,y ,&&read_pop·nominal ,&&read_pop·pop_last ,&&read_pop·alloc_fail);
      read_pop·nominal:{
        f[i] = true;
        continue_from read_pop·end;
      }
      read_pop·pop_last:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·alloc_fail:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·end:{
        cx->i++;
      }
    }
  f[cx->i++] = y == 4;
  f[cx->i++] = TM2x·test_after_allocation_n == 15;
    {
      continuations read_pop·nominal ,read_pop·pop_last ,read_pop·alloc_fail ,read_pop·end;
      continue_into TM2x·Read_Pop(a0 ,y ,&&read_pop·nominal ,&&read_pop·pop_last ,&&read_pop·alloc_fail);
      read_pop·nominal:{
        f[i] = true;
        continue_from read_pop·end;
      }
      read_pop·pop_last:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·alloc_fail:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·end:{
        cx->i++;
      }
    }
  f[cx->i++] = y == 3;
  f[cx->i++] = TM2x·test_after_allocation_n == 7;
  
    {
      continuations read_pop·nominal ,read_pop·pop_last ,read_pop·alloc_fail ,read_pop·end;
      continue_into TM2x·Read_Pop(a0 ,y ,&&read_pop·nominal ,&&read_pop·pop_last ,&&read_pop·alloc_fail);
      read_pop·nominal:{
        f[i] = true;
        continue_from read_pop·end;
      }
      read_pop·pop_last:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·alloc_fail:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·end:{
        cx->i++;
      }
    }
  f[cx->i++] = y == 2;
  f[cx->i++] = TM2x·test_after_allocation_n == 3;
  
    {
      continuations read_pop·nominal ,read_pop·pop_last ,read_pop·alloc_fail ,read_pop·end;
      continue_into TM2x·Read_Pop(a0 ,y ,&&read_pop·nominal ,&&read_pop·pop_last ,&&read_pop·alloc_fail);
      read_pop·nominal:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·pop_last:{
        f[i] = true;
        continue_from read_pop·end;
      }
      read_pop·alloc_fail:{
        f[i] = false;
        continue_from read_pop·end;
      }
      read_pop·end:{
        cx->i++;
      }
    }
  f[cx->i++] = y == 1;  
  f[cx->i++] = TM2x·test_after_allocation_n == 3;

  TM2x·destruct(a0);
  f[cx->i++] = malloc_cnt == MallocCounter·count;
  f[cx->i++] = constructed_cnt == TM2x·constructed_count;
  // printf("test_2 'i': %u" ,i);
  Result·Tallies·tally("test_2" ,rp ,f ,i);
  return r;
}
#endif
