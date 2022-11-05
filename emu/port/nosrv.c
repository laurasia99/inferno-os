/* Dummy */
#include "dat.h"
#include "interp.h"
#include "isa.h"
#include "runt.h"

/* Linked from devprog */
Type    *Trdchan;
Type    *Twrchan;

/* Called from Sys_file2chan */
int
srvf2c(char *dir, char *file, Sys_FileIO *io)
{
    return -1;
}


