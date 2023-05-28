#ifndef SYSCALL_H
#define SYSCALL_H

// extern int close  (int status);
// extern int _exit (int fd);
// extern int open(const char *name, int flags, int mode);
extern void *sys_sbrk (int irc);

//interProcessor
extern int sys_itpSct(int id);
extern void sys_itpCall(int pos,double arg1);
extern void sys_itpCall2(int pos,double arg1,double arg2);
extern double sys_itpRet(int pos);


extern void sys_wrbank1 (int id);



extern void sys_write( void *ptr ,double value);
extern double sys_read(void *ptr);























//math

extern double acos(double x) ;

extern double asin(double x) ;

extern double atan(double x) ;

extern double angle(double y, double x) ;
#define atan2 angle
extern double cos(double x) ;

extern double sin(double x) ;

extern double tan(double x) ;


// // 7.12.5 Hyperbolic functions
// // https://en.wikipedia.org/wiki/Hyperbolic_functions
// extern double acosh(double x) {
//     double tmp;
//     __asm__ (
//         "op mul %1 %2 %2\n"
//         "op sub %1 1\n"
//         "op sqrt %1 %1 0\n"
//         "op add %1 %1 %2\n"
//         "op log %0 %1 0\n"
//         : "=r" (__mlogev_function_return_value__), "=r" (tmp)
//         : "r" (x)
//     );
// }

// extern double asinh(double x) {
//     double tmp;
//     __asm__ (
//         "op mul %1 %2 %2\n"
//         "op add %1 1\n"
//         "op sqrt %1 %1 0\n"
//         "op add %1 %1 %2\n"
//         "op log %0 %1 0\n"
//         : "=r" (__mlogev_function_return_value__), "=r" (tmp)
//         : "r" (x)
//     );
// }

// extern double atanh(double x) {
//     double tmp1, tmp2;
//     __asm__ (
//         "op add %1 1 %3\n"
//         "op sub %2 1 %3\n"
//         "op div %1 %1 %2\n"
//         "op log %0 %1 0\n"
//         "op div %0 %0 2\n"
//         : "=r" (__mlogev_function_return_value__), "=r" (tmp1), "=r" (tmp2)
//         : "r" (x)
//     );
// }

// extern double cosh(double x) {
//     double tmp1, tmp2;
//     __asm__ (
//         "op pow %1 " __XSTR(M_E) " %3\n"
//         "op sub %2 0 %3\n"
//         "op pow %2 " __XSTR(M_E) " %2\n"
//         "op add %1 %1 %2\n"
//         "op div %0 %1 2\n"
//         : "=r" (__mlogev_function_return_value__), "=r" (tmp1), "=r" (tmp2)
//         : "r" (x)
//     );
// }

// extern double sinh(double x) {
//     double tmp1, tmp2;
//     __asm__ (
//         "op pow %1 " __XSTR(M_E) " %3\n"
//         "op sub %2 0 %3\n"
//         "op pow %2 " __XSTR(M_E) " %2\n"
//         "op sub %1 %1 %2\n"
//         "op div %0 %1 2\n"
//         : "=r" (__mlogev_function_return_value__), "=r" (tmp1), "=r" (tmp2)
//         : "r" (x)
//     );
// }

// extern double tanh(double x) {
//     double tmp;
//     __asm__ (
//         "op mul %1 %2 2\n"
//         "op pow %1 " __XSTR(M_E) " %1\n"
//         "op sub %0 %1 1\n"
//         "op add %1 %1 1\n"
//         "op div %0 %0 %1\n"
//         : "=r" (__mlogev_function_return_value__), "=r" (tmp)
//         : "r" (x)
//     );
// }

// 7.12.6 Exponential and logarithmic functions
extern double exp(double x ,double y) ;

// extern double exp2(double x) {
//     __asm__ (
//         "op pow %0 2.0 %1\n"
//         : "=r" (__mlogev_function_return_value__)
//         : "r" (x)
//     );
// }

// extern double expm1(double x) {
//     __asm__ (
//         "op pow %0 " __XSTR(M_E) " %1\n"
//         "op sub %0 %0 1\n"
//         : "=r" (__mlogev_function_return_value__)
//         : "r" (x)
//     );
// }
// TODO: ilogb, ldexp

extern double log(double x,double y );

extern double log10(double x) ;

// // TODO: For small magnitude x, log1p(x) is expected to be more accurate than log(1 + x)
// extern double log1p(double x) {
//     double x1 = x + 1;
//     __asm__ (
//         "op log %0 %1 0\n"
//         : "=r" (__mlogev_function_return_value__)
//         : "r" (x1)
//     );
// }

// extern double log2(double x) {
//     __asm__ (
//         "op log %0 %1 0\n"
//         "op div %0 %0 " __XSTR(M_LN2)
//         : "=r" (__mlogev_function_return_value__)
//         : "r" (x)
//     );
// }

// // TODO: logb, modf, scalbn, scalbln
// extern double cbrt(double x) {
//     __asm__ (
//         // TODO: more precise cbrt
//         "op pow %0 %1 0.3333333333333333\n"
//         : "=r" (__mlogev_function_return_value__)
//         : "r" (x)
//     );
// }

extern double abs(double x) ;

#define len hypot
extern double hypot(double x, double y) ;


extern double sqrt(double x) ;

// TODO: lgamma, tgamma
extern double ceil(double x) ;

extern double floor(double x) ;
// TODO: nearbyint, rint, lrint, round, lround, llround, trunc
// TODO: fmod, remainder, remquo
// TODO: 7.12.11 copysign, nan, nextafter, nexttoward

// 7.12.12 Maximum, minimum, and positive difference functions
// extern double fdim(double x, double y) {
//     __asm__ (
//         "op sub %0 %1 %2\n"
//         "op max %0 %0 0\n"
//         : "=r" (__mlogev_function_return_value__)
//         : "r" (x), "r" (y)
//     );
// }

// extern double fmax(double x, double y) {
//     __asm__ (
//         "op max %0 %1 %2\n"
//         : "=r" (__mlogev_function_return_value__)
//         : "r" (x), "r" (y)
//     );
// }

extern double min(double x, double y);

extern double max(double x, double y) ;


#endif