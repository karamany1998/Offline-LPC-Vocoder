#ifndef LSFLPCUTILS_H__
#define LSFLPCUTILS_H__

int 
convertLpc2Lsf(const double *lpcs, double *lsf, int amountLsfs);

int 
convertLsf2Lpc(const double *lsf, double *lpcs, int amountLsfs);

#endif
