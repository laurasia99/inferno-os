#include "dat.h"
#include "fns.h"
#include "error.h"
#include "interp.h"


#include "emu.root.h"

ulong ndevs = 23;

extern Dev rootdevtab;
extern Dev consdevtab;
extern Dev envdevtab;
extern Dev mntdevtab;
//extern Dev pipedevtab;
extern Dev progdevtab;
//extern Dev srvdevtab;
//extern Dev dupdevtab;
extern Dev fsdevtab;
extern Dev cmddevtab;
//extern Dev drawdevtab;
//extern Dev ipdevtab;
//extern Dev memdevtab;
//extern Dev archdevtab;
//extern Dev pointerdevtab;
Dev* devtab[]={
	&rootdevtab,
	&consdevtab,
	&envdevtab,
	&mntdevtab,
//	&pipedevtab,
	&progdevtab,
//	&srvdevtab,
//	&dupdevtab,
	&fsdevtab,
	&cmddevtab,
//	&drawdevtab,
//	&ipdevtab,
//	&memdevtab,
//	&archdevtab,
//	&pointerdevtab,
	nil,nil,nil,nil,nil,nil,nil,nil,
	nil,
	nil,
	nil,
	nil,
	nil,
	nil,
	nil,
	nil,
	nil,
};

void links(void){
}

extern void sysmodinit(void);
extern void drawmodinit(void);
extern void mathmodinit(void);
extern void srvmodinit(void);
extern void keyringmodinit(void);
extern void cryptmodinit(void);
extern void ipintsmodinit(void);
extern void loadermodinit(void);
void modinit(void){
	sysmodinit();
//	drawmodinit();
	mathmodinit();
//	srvmodinit();
//	keyringmodinit();
	cryptmodinit();
//	ipintsmodinit();
	loadermodinit();
}

char* conffile = "emu";
ulong kerndate = KERNDATE;
