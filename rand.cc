#include <iostream>
#include <stdlib.h>

// re-implementation of rand() that produces the same
// numbers as the posix/gcc implementation in stdlib.h

int myrand(bool reseed=false, int seed=1)
{
  static int r[32];
  static int k;
  static bool inited=false;
  if (!inited || reseed)
    {
      //srand treats a seed 0 as 1 for some reason
      r[0]=(seed==0)?1:seed;

      for (int i=1; i<31; i++)
        {
          r[i] = (16807LL * r[i-1]) % 2147483647;
          if (r[i] < 0)
            r[i] += 2147483647;
        }
      k=31;
      for (int i=31; i<34; i++)
        {
          r[k%32] = r[(k+32-31)%32];
          k=(k+1)%32;
        }

      for (int i=34; i<344; i++)
        {
          r[k%32] = r[(k+32-31)%32] + r[(k+32-3)%32];
          k=(k+1)%32;
        }
      inited=true;
      if (reseed==true)
        return 0;// do not generate new no
    }

  r[k%32] = r[(k+32-31)%32] + r[(k+32-3)%32];
  int ret = r[k%32];
  k=(k+1)%32;
  return (unsigned int)ret >> 1;
}

void mysrand(int seed)
{
  myrand(true, seed);
}


int main()
{
  for (int i=0;i<3;++i)
    std::cout << myrand() << " = " << rand() << std::endl;
  std::cout << std::endl;
  
  mysrand(0);srand(0);
  
  for (int i=0;i<3;++i)
    std::cout << myrand() << " = " << rand() << std::endl;
  std::cout << std::endl;

  mysrand(1);srand(1);
  
  for (int i=0;i<3;++i)
    std::cout << myrand() << " = " << rand() << std::endl;
  std::cout << std::endl;

  mysrand(12345);srand(12345);
  for (int i=0;i<3;++i)
    std::cout << myrand() << " = " << rand() << std::endl;
  std::cout << std::endl;
}
