#ifndef SYS
#define SYS
// extern int close  (int status);
// extern int _exit (int fd);
// extern int open(const char *name, int flags, int mode);
extern void *sys_sbrk(int irc);
// interProcessor
extern int sys_ipcSct(int id);
extern void sys_ipcCall(int pos, double arg1);
extern void sys_ipcCall2(int pos, double arg1, double arg2);
extern double sys_ipcRet(int pos);
extern void sys_wrbank1(int id);
extern void sys_wrbank2(int id);
extern void sys_write(void *ptr, double value);
extern double sys_read(void *ptr);

// math

extern double acos(double x);
extern double asin(double x);
extern double atan(double x);
extern double angle(double y, double x);
extern double cos(double x);
extern double sin(double x);
extern double tan(double x);
extern double exp(double x, double y);
extern double log(double x, double y);
extern double log10(double x);
extern double abs(double x);
extern double len(double x, double y);
extern double sqrt(double x);
extern double ceil(double x);
extern double floor(double x);
extern double min(double x, double y);
extern double max(double x, double y);
#endif