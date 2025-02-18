typedef struct{char *name; long sig; void (*fn)(void*); int size; int np; uchar map[16];} Runtab;
Runtab Sysmodtab[]={
	"announce",0xb7c4ac0,Sys_announce,40,2,{0x0,0x80,},
	"aprint",0x77442d46,Sys_aprint,0,0,{0},
	"bind",0x66326d91,Sys_bind,48,2,{0x0,0xc0,},
	"byte2char",0x3d6094f9,Sys_byte2char,40,2,{0x0,0x80,},
	"char2byte",0x2ba5ab41,Sys_char2byte,48,2,{0x0,0x40,},
	"chdir",0xc6935858,Sys_chdir,40,2,{0x0,0x80,},
	"create",0x54db77d9,Sys_create,48,2,{0x0,0x80,},
	"dial",0x29e90174,Sys_dial,40,2,{0x0,0xc0,},
	"dirread",0x72210d71,Sys_dirread,40,2,{0x0,0x80,},
	"dup",0x6584767b,Sys_dup,40,0,{0},
	"export",0x6fc6dc03,Sys_export,48,2,{0x0,0xc0,},
	"fauth",0x20ccc34b,Sys_fauth,40,2,{0x0,0xc0,},
	"fd2path",0x749c6042,Sys_fd2path,40,2,{0x0,0x80,},
	"fildes",0x1478f993,Sys_fildes,40,0,{0},
	"file2chan",0x9f34d686,Sys_file2chan,40,2,{0x0,0xc0,},
	"fprint",0xf46486c8,Sys_fprint,0,0,{0},
	"fstat",0xda4499c2,Sys_fstat,40,2,{0x0,0x80,},
	"fversion",0xfe9c0a06,Sys_fversion,48,2,{0x0,0xa0,},
	"fwstat",0x50a6c7e0,Sys_fwstat,104,2,{0x0,0xbc,},
	"iounit",0x5583b730,Sys_iounit,40,2,{0x0,0x80,},
	"listen",0xb97416e0,Sys_listen,48,2,{0x0,0xe0,},
	"millisec",0x616977e8,Sys_millisec,32,0,{0},
	"mount",0x74c17b3a,Sys_mount,56,2,{0x0,0xe8,},
	"open",0x8f477f99,Sys_open,40,2,{0x0,0x80,},
	"pctl",0x5df27fb,Sys_pctl,40,2,{0x0,0x40,},
	"pipe",0x1f2c52ea,Sys_pipe,40,2,{0x0,0x80,},
	"pread",0x9d8aac6,Sys_pread,56,2,{0x0,0xc0,},
	"print",0xac849033,Sys_print,0,0,{0},
	"pwrite",0x9d8aac6,Sys_pwrite,56,2,{0x0,0xc0,},
	"read",0x7cfef557,Sys_read,48,2,{0x0,0xc0,},
	"readn",0x7cfef557,Sys_readn,48,2,{0x0,0xc0,},
	"remove",0xc6935858,Sys_remove,40,2,{0x0,0x80,},
	"seek",0xaeccaddb,Sys_seek,56,2,{0x0,0x80,},
	"sleep",0xe67bf126,Sys_sleep,40,0,{0},
	"sprint",0x4c0624b6,Sys_sprint,0,0,{0},
	"stat",0x319328dd,Sys_stat,40,2,{0x0,0x80,},
	"stream",0xb9e8f9ea,Sys_stream,48,2,{0x0,0xc0,},
	"tokenize",0x57338f20,Sys_tokenize,40,2,{0x0,0xc0,},
	"unmount",0x21e337e3,Sys_unmount,40,2,{0x0,0xc0,},
	"utfbytes",0x1d4a1f4,Sys_utfbytes,40,2,{0x0,0x80,},
	"werrstr",0xc6935858,Sys_werrstr,40,2,{0x0,0x80,},
	"write",0x7cfef557,Sys_write,48,2,{0x0,0xc0,},
	"wstat",0x56b02096,Sys_wstat,104,2,{0x0,0xbc,},
	0
};
#define Sysmodlen	43
