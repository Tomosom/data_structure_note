添加继承的类后，用Ubuntu10的编译器编译会告警 :
ubuntu10
g++  -o a.out offsetof.cpp
offsetof.cpp: In function ‘int main(int, char**)’:
offsetof.cpp:24: warning: invalid access to non-static data member ‘ST::i’  of NULL object
offsetof.cpp:24: warning: (perhaps the ‘offsetof’ macro was used incorrectly)
offsetof.cpp:25: warning: invalid access to non-static data member ‘ST::j’  of NULL object
offsetof.cpp:25: warning: (perhaps the ‘offsetof’ macro was used incorrectly)
offsetof.cpp:26: warning: invalid access to non-static data member ‘ST::c’  of NULL object
offsetof.cpp:26: warning: (perhaps the ‘offsetof’ macro was used incorrectly)

gcc version 7.4.0 (Ubuntu 7.4.0-1ubuntu1~18.04.1)
出现下面警告的原因：该版本的g++中自带了offset宏，使用我们自己定义的宏就不会有告警
offsetof.cpp:25:38: warning: offsetof within non-standard-layout type ‘ST’ is undefined [-Winvalid-offsetof]
  cout << "offsetof i : " << offsetof(struct ST, i) << endl;
                                      ^
offsetof.cpp:26:38: warning: offsetof within non-standard-layout type ‘ST’ is undefined [-Winvalid-offsetof]
  cout << "offsetof j : " << offsetof(struct ST, j) << endl;
                                      ^
offsetof.cpp:27:38: warning: offsetof within non-standard-layout type ‘ST’ is undefined [-Winvalid-offsetof]
  cout << "offsetof c : " << offsetof(struct ST, c) << endl;



referance blog
https://blog.csdn.net/albertsh/article/details/61415671?>

/* Define offsetof macro */
#ifdef __cplusplus

#ifdef  _WIN64
#define offsetof(s,m)   (size_t)( (ptrdiff_t)&reinterpret_cast<const volatile char&>((((s *)0)->m)) )
#else
//#define offsetof(s,m)   (size_t)&reinterpret_cast<const volatile char&>((((s *)0)->m))
#define offsetof(s,m)   (size_t)(&reinterpret_cast<const volatile char&>((((s*)0x11)->m)) - 0x11)
#endif

#else

#ifdef  _WIN64
#define offsetof(s,m)   (size_t)( (ptrdiff_t)&(((s *)0)->m) )
#else
#define offsetof(s,m)   (size_t)&(((s *)0)->m)
#endif

#endif  /* __cplusplus */


