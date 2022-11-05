# Inferno Nt/386
# Microsoft NMAKE

# Goal: minimalist system build
#  - build 'emu0.exe' - console, with no server code - minimalist
#  - build 'emu1.exe' - console; bootstrap rest of build
#  - use emu1 to build the rest of the system
#    - bootstrapping files required (limbo output)
#    - these are stored in the boot/ subdirectory

R=.

# Build outside the source tree
O=$R\obj\Nt
A=$O\lib

# Microsoft Visual C++
C=cl /nologo /Z7 /W3 /MT /std:c11 /D_WIN32_WINNT=0x0600 /Iinclude

# Control over modified sources
#USE_MODIFIED_SOURCE=1

!IF !EXIST($O)
!IF [mkdir $O]!=0
!ERROR Failed to create directory '$O'
!ENDIF
!ENDIF

all: emu1.exe

scrub:
    if exist $O rmdir /s/q $O
    if exist img0 rmdir /s/q img0
    if exist img1 rmdir /s/q img1
    del /q emu0.* emu1.*

## -------------------------- MINIMAL BUILD: IMG0 --------------------------
# Heavily stripped down emu build, removing most devices. Requires:
#  - devroot (foundation of namespace)
#  - devcons
#  - devfs   (use host filesystem)
#  - devenv  (process command line arguments; invoke dis from host)
#  - devprog (???)
#  - devmnt  (???)
#  - devcmd  (???)

SYSLIBS=netapi32.lib wsock32.lib user32.lib gdi32.lib advapi32.lib winmm.lib mpr.lib

# Libraries
#   - lib9 (strings, utf8, runes, error formatting, NT: locks, errors)
#   - libsec (des)
#   - libinterp
#   - libmath (mostly redundant; dtoa(), FP control)
#   - libdraw (redundant; process command line argument only)
EMU0_9OBJS=$O\lib9\convD2M.obj $O\lib9\convM2D.obj $O\lib9\convM2S.obj \
    $O\lib9\convS2M.obj $O\lib9\fcallfmt.obj $O\lib9\strtoll.obj \
    $O\lib9\rune.obj $O\lib9\cleanname.obj \
    $O\lib9\dofmt.obj $O\lib9\errfmt.obj $O\lib9\exits.obj \
    $O\lib9\fmt.obj $O\lib9\fmtfd.obj $O\lib9\fmtprint.obj \
    $O\lib9\fmtquote.obj $O\lib9\fmtstr.obj \
    $O\lib9\fprint.obj \
    $O\lib9\print.obj $O\lib9\rerrstr.obj \
    $O\lib9\seprint.obj $O\lib9\smprint.obj $O\lib9\snprint.obj \
    $O\lib9\sprint.obj $O\lib9\strdup.obj $O\lib9\strecpy.obj \
    $O\lib9\tokenize.obj \
    $O\lib9\utflen.obj $O\lib9\utfnlen.obj $O\lib9\utfrune.obj \
    $O\lib9\utfecpy.obj $O\lib9\vfprint.obj $O\lib9\vseprint.obj \
    $O\lib9\vsmprint.obj $O\lib9\vsnprint.obj \
    $O\lib9\errstr-Nt.obj $O\lib9\getwd-Nt.obj \
    $O\lib9\lock-Nt-386.obj
EMU0_SECOBJS=$O\libsec\des.obj $O\libsec\desmodes.obj \
    $O\libsec\genrandom.obj
# Dependence on pre-generated header files in boot\libinterp
EMU0_INTERPOBJS=$O\libinterp\alt.obj $O\libinterp\comp-386.obj $O\libinterp\conv.obj \
    $O\libinterp\dec.obj $O\libinterp\raise.obj \
    $O\libinterp\dlm-Nt.obj $O\libinterp\gc.obj $O\libinterp\heap.obj \
    $O\libinterp\link.obj $O\libinterp\load.obj $O\libinterp\loader.obj \
    $O\libinterp\readmod.obj $O\libinterp\runt.obj \
    $O\libinterp\sign.obj $O\libinterp\vstack.obj \
    $O\libinterp\xec.obj $O\libinterp\das-386.obj $O\libinterp\string.obj
EMU0_MATHOBJS=$O\libmath\dtoa.obj $O\libmath\FPcontrol-Nt.obj
EMU0_DRAWOBJS=$O\libdraw\chan.obj

# Removed discall.obj
EMU0_CORE_OBJS=\
    $O\emu\devroot.obj      $O\emu\devcons.obj      $O\emu\devenv.obj \
    $O\emu\devmnt.obj       $O\emu\devprog.obj      $O\emu\devfs.obj \
    $O\emu\devcmd.obj       $O\emu\cmd.obj          $O\emu\alloc.obj \
    $O\emu\cache.obj        $O\emu\chan.obj         $O\emu\dev.obj \
    $O\emu\devtab.obj       $O\emu\dial.obj         $O\emu\dis.obj \
    $O\emu\env.obj          $O\emu\error.obj \
    $O\emu\errstr.obj       $O\emu\exception.obj    $O\emu\exportfs.obj \
    $O\emu\inferno.obj      $O\emu\latin1.obj       $O\emu\main.obj \
    $O\emu\parse.obj        $O\emu\pgrp.obj         $O\emu\print.obj \
    $O\emu\proc.obj         $O\emu\qio.obj          $O\emu\random.obj \
    $O\emu\sysfile.obj      $O\emu\uqid.obj         $O\emu\os.obj \
    $O\emu\lock.obj         $O\emu\fp.obj           $O\emu\r16.obj \
    $O\emu\vlrt.obj
EMU0_OTHER_OBJS=\
    $O\emu\emu0.obj \
    $O\emu\nopointer.obj \
    $O\emu\nosrv.obj \
    $O\emu\nowin.obj

EMU0_ALLOBJS=$(EMU0_CORE_OBJS) $(EMU0_OTHER_OBJS) \
    $(EMU0_9OBJS) $(EMU0_SECOBJS) $(EMU0_INTERPOBJS) \
    $(EMU0_MATHOBJS) $(EMU0_DRAWOBJS)

_emu0-dirs:
!IF !EXIST($O\lib9)
    if not exist $O\lib9 mkdir $O\lib9
!ENDIF
!IF !EXIST($O\libdraw)
    if not exist $O\libdraw mkdir $O\libdraw
!ENDIF
!IF !EXIST($O\libinterp)
    if not exist $O\libinterp mkdir $O\libinterp
!ENDIF
!IF !EXIST($O\libmath)
    if not exist $O\libmath mkdir $O\libmath
!ENDIF
!IF !EXIST($O\libsec)
    if not exist $O\libsec mkdir $O\libsec
!ENDIF
!IF !EXIST($O\emu)
    if not exist $O\emu mkdir $O\emu
!ENDIF

emu0.exe: _emu0-dirs $(EMU0_ALLOBJS)
    link /nologo /debug:full /map /out:$@ /subsystem:console /entry:WinMainCRTStartup $(EMU0_ALLOBJS) $(SYSLIBS)

# img0\ is a minimal bootstrapping image that allows invocation of
# the command shell - proof-of-concept of minimal build
_img0-dirs:
!IF !EXIST(img0)
    if not exist img0 mkdir img0
!ENDIF
!IF !EXIST(img0\dis)
    if not exist img0\dis mkdir img0\dis
!ENDIF
!IF !EXIST(img0\dis\lib)
    if not exist img0\dis\lib mkdir img0\dis\lib
!ENDIF

build-img0: emu0.exe _img0-dirs \
    img0\dis\emuinit.dis \
    img0\dis\lib\arg.dis \
    img0\dis\lib\bufio.dis \
    img0\dis\lib\daytime.dis \
    img0\dis\lib\filepat.dis \
    img0\dis\lib\readdir.dis \
    img0\dis\lib\string.dis \
    img0\dis\lib\workdir.dis \
    img0\dis\cat.dis \
    img0\dis\cd.dis \
    img0\dis\echo.dis \
    img0\dis\ls.dis \
    img0\dis\pwd.dis \
    img0\dis\sh.dis

# XXX archive in boot?
img0\dis\emuinit.dis: $R\dis\$$(@F)
    copy $** $@
img0\dis\lib\arg.dis: $R\dis\lib\$$(@F)
    copy $** $@
img0\dis\lib\bufio.dis: $R\dis\lib\$$(@F)
    copy $** $@
img0\dis\lib\daytime.dis: $R\dis\lib\$$(@F)
    copy $** $@
img0\dis\lib\filepat.dis: $R\dis\lib\$$(@F)
    copy $** $@
img0\dis\lib\readdir.dis: $R\dis\lib\$$(@F)
    copy $** $@
img0\dis\lib\string.dis: $R\dis\lib\$$(@F)
    copy $** $@
img0\dis\lib\workdir.dis: $R\dis\lib\$$(@F)
    copy $** $@
img0\dis\cat.dis: $R\dis\$$(@F)
    copy $** $@
img0\dis\cd.dis: $R\dis\$$(@F)
    copy $** $@
img0\dis\echo.dis: $R\dis\$$(@F)
    copy $** $@
img0\dis\ls.dis: $R\dis\$$(@F)
    copy $** $@
img0\dis\pwd.dis: $R\dis\$$(@F)
    copy $** $@
img0\dis\sh.dis: $R\dis\$$(@F)
    copy $** $@

## --------------------------- LIMBO BUILD: IMG1 ---------------------------
# img0 is a proof-of-concept with a minimal runtime using precompiled dis
# files. img1 builds a different runtime sufficient to use limbo (required
# for continuing the bootstrapping process).
#
# The limbo compiler requires two built-in (C sources) modules: $Crypt $Math
# Sources for these modules are in libinterp/; the important entry points are:
#   mathmodinit()
#   cryptmodinit()  ->  ipintsmodinit()
# These are invoked from modinit() in emu.c (normally generated, but as part
# of the bootstrap we'll use a copy from boot/).
#
# Consequently, a new emu executable (emu1.exe) has to be built.

EMU1_CORE_OBJS=\
    $(EMU0_CORE_OBJS)

EMU1_OTHER_OBJS=\
    $O\emu\emu1.obj \
    $O\emu\nopointer.obj \
    $O\emu\nosrv.obj \
    $O\emu\nowin.obj

EMU1_9OBJS=\
    $(EMU0_9OBJS) \
    $O\lib9\u32.obj $O\lib9\u64.obj

EMU1_SECOBJS=\
    $(EMU0_SECOBJS) \
    $O\libsec\md4.obj \
    $O\libsec\md5.obj \
    $O\libsec\sha1.obj \
    $O\libsec\sha2.obj \
    $O\libsec\hmac.obj \
    $O\libsec\genprime.obj \
    $O\libsec\gensafeprime.obj \
    $O\libsec\genstrongprime.obj \
    $O\libsec\probably_prime.obj \
    $O\libsec\prng.obj \
    $O\libsec\md5block.obj \
    $O\libsec\sha1block.obj \
    $O\libsec\sha256block.obj \
    $O\libsec\sha512block.obj \
    $O\libsec\fastrand.obj \
    $O\libsec\smallprimetest.obj \
    $O\libsec\rsadecrypt.obj \
    $O\libsec\rsaencrypt.obj \
    $O\libsec\dsagen.obj \
    $O\libsec\dsaprimes.obj \
    $O\libsec\dsasign.obj \
    $O\libsec\dsaverify.obj \
    $O\libsec\rsagen.obj \
    $O\libsec\rsafill.obj \
    $O\libsec\eggen.obj \
    $O\libsec\egsign.obj \
    $O\libsec\egverify.obj \
    $O\libsec\rc4.obj \
    $O\libsec\egalloc.obj \
    $O\libsec\rsaalloc.obj \
    $O\libsec\aes.obj \
    $O\libsec\blowfish.obj \
    $O\libsec\dsaalloc.obj \
    $O\libsec\idea.obj

EMU1_INTERPOBJS=\
    $(EMU0_INTERPOBJS) \
    $O\libinterp\crypt.obj \
    $O\libinterp\math.obj \
    $O\libinterp\ipint.obj

EMU1_MATHOBJS=\
    $(EMU0_MATHOBJS) \
    $O\libmath\pow10.obj \
    $O\libmath\g_fmt.obj \
    $O\libmath\gfltconv.obj \
    $O\libmath\blas.obj \
    $O\libmath\gemm.obj \
    $O\libmath\e_acos.obj \
    $O\libmath\e_acosh.obj \
    $O\libmath\e_asin.obj \
    $O\libmath\e_atan2.obj \
    $O\libmath\e_atanh.obj \
    $O\libmath\e_cosh.obj \
    $O\libmath\e_exp.obj \
    $O\libmath\s_finite.obj \
    $O\libmath\e_fmod.obj \
    $O\libmath\e_hypot.obj \
    $O\libmath\e_j0.obj \
    $O\libmath\e_j1.obj \
    $O\libmath\e_jn.obj \
    $O\libmath\e_lgamma_r.obj \
    $O\libmath\e_log.obj \
    $O\libmath\e_log10.obj \
    $O\libmath\e_pow.obj \
    $O\libmath\e_remainder.obj \
    $O\libmath\e_sinh.obj \
    $O\libmath\e_sqrt.obj \
    $O\libmath\k_sin.obj \
    $O\libmath\k_cos.obj

# Multiple precision integers; req'd for crypt
EMU1_MPOBJS=\
    $O\libmp\mpaux.obj \
    $O\libmp\mpcmp.obj \
    $O\libmp\mprand.obj \
    $O\libmp\mpadd.obj \
    $O\libmp\mpleft.obj \
    $O\libmp\mpright.obj \
    $O\libmp\mpmod.obj \
    $O\libmp\mpexp.obj \
    $O\libmp\mpmul.obj \
    $O\libmp\mpdiv.obj \
    $O\libmp\mpfmt.obj \
    $O\libmp\mpdigdiv.obj \
    $O\libmp\mpsub.obj \
    $O\libmp\mpinvert.obj \
    $O\libmp\mpextendedgcd.obj \
    $O\libmp\mpvecadd.obj \
    $O\libmp\mpveccmp.obj \
    $O\libmp\mpvecsub.obj \
    $O\libmp\mpvecdigmuladd.obj \
    $O\libmp\mptobe.obj \
    $O\libmp\mptoi.obj \
    $O\libmp\mptoui.obj \
    $O\libmp\betomp.obj \
    $O\libmp\letomp.obj \
    $O\libmp\strtomp.obj

EMU1_INCLUDES=\
    $(EMU0_INCLUDES) \
    lib\math\fdlibm.h \
    lib\mp\dat.h \
    lib\mp\os.h

EMU1_ALLOBJS=$(EMU1_CORE_OBJS) $(EMU1_OTHER_OBJS) \
    $(EMU1_9OBJS) $(EMU1_SECOBJS) $(EMU1_INTERPOBJS) \
    $(EMU1_MATHOBJS) $(EMU0_DRAWOBJS) $(EMU1_MPOBJS)

_emu1-dirs: _emu0-dirs
!IF !EXIST($O\libmp)
    if not exist $O\libmp mkdir $O\libmp
!ENDIF

emu1.exe: _emu1-dirs $(EMU1_ALLOBJS)
    link /nologo /debug:full /map /out:$@ /subsystem:console /entry:WinMainCRTStartup $(EMU1_ALLOBJS) $(SYSLIBS)

_img1-dirs:
!IF !EXIST(img1)
    if not exist img1 mkdir img1
!ENDIF
!IF !EXIST(img1\dis)
    if not exist img1\dis mkdir img1\dis
!ENDIF
!IF !EXIST(img1\dis\lib)
    if not exist img1\dis\lib mkdir img1\dis\lib
!ENDIF
!IF !EXIST(img1\dis-boot)
    if not exist img1\dis-boot mkdir img1\dis-boot
!ENDIF
!IF !EXIST(img1\dis-tmp)
    if not exist img1\dis-tmp mkdir img1\dis-tmp
!ENDIF
!IF !EXIST(img1\appl)
    if not exist img1\appl mkdir img1\appl
!ENDIF
!IF !EXIST(img1\appl\cmd)
    if not exist img1\appl\cmd mkdir img1\appl\cmd
!ENDIF
!IF !EXIST(img1\appl\cmd\limbo)
    if not exist img1\appl\cmd\limbo mkdir img1\appl\cmd\limbo
!ENDIF
!IF !EXIST(img1\appl\cmd\sh)
    if not exist img1\appl\cmd\sh mkdir img1\appl\cmd\sh
!ENDIF
!IF !EXIST(img1\appl\lib)
    if not exist img1\appl\lib mkdir img1\appl\lib
!ENDIF
!IF !EXIST(img1\module)
    if not exist img1\module mkdir img1\module
!ENDIF
!IF !EXIST(img1\lib)
    if not exist img1\lib mkdir img1\lib
!ENDIF

# load Sys Sys->PATH      [$Sys]
# load Arg Arg->PATH      {emuinit.dis; needed for host invocation by emuinit.dis}
# load Crypt Crypt->PATH  [$Crypt]
# load Math Math->PATH    [$Math]
# load Bufio Bufio->PATH
# load String String->PATH
# load Workdir Workdir->PATH

# Limbo compiler sources; limbo.b regenerated from limbo.y
# Note that limbo.m appears to be manually written (not generated)
IMG1_LIMBO_SRCS=\
    img1\appl\cmd\limbo\arg.m \
    img1\appl\cmd\limbo\asm.b \
    img1\appl\cmd\limbo\com.b \
    img1\appl\cmd\limbo\decls.b \
    img1\appl\cmd\limbo\dis.b \
    img1\appl\cmd\limbo\disoptab.m \
    img1\appl\cmd\limbo\ecom.b \
    img1\appl\cmd\limbo\gen.b \
    img1\appl\cmd\limbo\isa.m \
    img1\appl\cmd\limbo\lex.b \
    img1\appl\cmd\limbo\limbo.m \
    img1\appl\cmd\limbo\limbo.y \
    img1\appl\cmd\limbo\nodes.b \
    img1\appl\cmd\limbo\opname.m \
    img1\appl\cmd\limbo\optim.b \
    img1\appl\cmd\limbo\sbl.b \
    img1\appl\cmd\limbo\stubs.b \
    img1\appl\cmd\limbo\typecheck.b \
    img1\appl\cmd\limbo\types.b
# Regenerate limbo.b from limbo.y
# Currently exclude shell built-ins
IMG1_OTHER_SRCS=img1\appl\cmd\yacc.b img1\lib\yaccpar \
    img1\appl\cmd\cd.b img1\appl\cmd\cmp.b img1\appl\cmd\echo.b \
    img1\appl\cmd\mkdir.b img1\appl\cmd\rm.b \
    img1\appl\cmd\emuinit.b \
#    img1\appl\cmd\sh\arg.b \
#    img1\appl\cmd\sh\csv.b \
#    img1\appl\cmd\sh\echo.b \
#    img1\appl\cmd\sh\expr.b \
    img1\appl\cmd\sh\mload.b \
#    img1\appl\cmd\sh\mpexpr.b \
#    img1\appl\cmd\sh\regex.b \
#    img1\appl\cmd\sh\sexprs.b \
    img1\appl\cmd\sh\sh.y \
#    img1\appl\cmd\sh\std.b \
#    img1\appl\cmd\sh\string.b \
#    img1\appl\cmd\sh\test.b \
#    img1\appl\cmd\sh\tk.b

# Note built-in modules (crypt draw ipints keyring math sys)
# Underlying libinterp/ support could be missing
IMG1_MODULE_SRCS=\
    img1\appl\lib\arg.b \
    img1\appl\lib\bufio.b \
    img1\appl\lib\filepat.b \
    img1\appl\lib\readdir.b \
    img1\appl\lib\string.b \
    img1\appl\lib\workdir.b
IMG1_MODULE_DEFS=\
    img1\module\arg.m \
    img1\module\bufio.m \
    img1\module\crypt.m \
    img1\module\draw.m \
    img1\module\filepat.m \
    img1\module\ipints.m \
    img1\module\keyring.m \
    img1\module\math.m \
    img1\module\readdir.m \
    img1\module\sh.m \
    img1\module\string.m \
    img1\module\sys.m \
    img1\module\workdir.m

# Note bootstrap compiler put into /dis-boot/
# Create script (/build) to bootstrap the limbo compiler (from within runtime)
build-img1-sources: emu1.exe _img1-dirs \
        img1\dis\emuinit.dis \
        img1\dis\lib\arg.dis \
        img1\dis\lib\bufio.dis \
        img1\dis\lib\filepat.dis \
        img1\dis\lib\string.dis \
        img1\dis\lib\workdir.dis \
        img1\dis\sh.dis \
        img1\dis-boot\limbo.dis \
        $(IMG1_LIMBO_SRCS) $(IMG1_OTHER_SRCS) \
        $(IMG1_MODULE_SRCS) $(IMG1_MODULE_DEFS)
    @rem <<img1\build
# Basic utilities used to build a new limbo compiler
/dis-boot/limbo.dis -o /dis-tmp/cd.dis /appl/cmd/cd.b
/dis-boot/limbo.dis -o /dis-tmp/yacc.dis /appl/cmd/yacc.b
/dis-tmp/cd.dis /appl/cmd/limbo
/dis-tmp/yacc.dis -o limbo.b limbo.y
# Build tmp compiler using bootstrap compiler
/dis-boot/limbo.dis -o /dis-tmp/limbo.dis /appl/cmd/limbo/limbo.b
/dis-tmp/cd.dis /
# Build tmp tools to create new directories, and remove tmp files
/dis-tmp/limbo.dis -o /dis-tmp/mkdir.dis /appl/cmd/mkdir.b
/dis-tmp/limbo.dis -o /dis-tmp/rm.dis /appl/cmd/rm.b
/dis-tmp/rm.dis /appl/cmd/limbo/limbo.b /dis-tmp/cd.dis /dis-tmp/yacc.dis
# Rebuild the tool chain using tmp compiler
/dis-tmp/limbo.dis -o /dis-tmp/cd.dis /appl/cmd/cd.b
/dis-tmp/limbo.dis -o /dis-tmp/yacc.dis /appl/cmd/yacc.b
/dis-tmp/cd.dis /appl/cmd/limbo
/dis-tmp/yacc.dis -o limbo.b limbo.y
# Build new compiler using tmp compiler
/dis-tmp/mkdir.dis -p /dis-new/lib
/dis-tmp/limbo.dis -o /dis-new/limbo.dis /appl/cmd/limbo/limbo.b
/dis-tmp/cd.dis /
# Rebuild tools using new compiler
/dis-new/limbo.dis -o /dis-new/cd.dis /appl/cmd/cd.b
/dis-new/limbo.dis -o /dis-new/mkdir.dis /appl/cmd/mkdir.b
/dis-new/limbo.dis -o /dis-new/rm.dis /appl/cmd/rm.b
/dis-new/limbo.dis -o /dis-new/yacc.dis /appl/cmd/yacc.b
# New tools - check that /dis-tmp/limbo & /dis-new/limbo match
/dis-new/limbo.dis -o /dis-new/cmp.dis /appl/cmd/cmp.b
/dis-new/limbo.dis -o /dis-new/echo.dis /appl/cmd/echo.b
/dis-new/echo.dis '** Validating limbo compiler build...'
/dis-new/cmp.dis /dis-tmp/limbo.dis /dis-new/limbo.dis
# no output when files match
/dis-new/echo.dis '** Rebuilding basic modules'
/dis-new/limbo.dis -o /dis-new/lib/arg.dis /appl/lib/arg.b
/dis-new/limbo.dis -o /dis-new/lib/bufio.dis /appl/lib/bufio.b
/dis-new/limbo.dis -o /dis-new/lib/filepat.dis /appl/lib/filepat.b
/dis-new/limbo.dis -o /dis-new/lib/workdir.dis /appl/lib/readdir.b
/dis-new/limbo.dis -o /dis-new/lib/string.dis /appl/lib/string.b
/dis-new/limbo.dis -o /dis-new/lib/workdir.dis /appl/lib/workdir.b
/dis-new/echo.dis '** Rebuilding emuint'
/dis-new/limbo.dis -o /dis-new/emuinit.dis /appl/cmd/emuinit.b
<<KEEP


# XXX archive in boot?
img1\dis\emuinit.dis: $R\dis\emuinit.dis
    copy $** $@
img1\dis\lib\arg.dis: $R\dis\lib\$$(@F)
    copy $** $@
img1\dis\lib\bufio.dis: $R\dis\lib\$$(@F)
    copy $** $@
img1\dis\lib\filepat.dis: $R\dis\lib\$$(@F)
    copy $** $@
img1\dis\lib\string.dis: $R\dis\lib\$$(@F)
    copy $** $@
img1\dis\lib\workdir.dis: $R\dis\lib\$$(@F)
    copy $** $@
img1\dis\sh.dis: $R\dis\$$(@F)
    copy $** $@
# Prebuilt libmo compiler (used to bootstrap)
img1\dis-boot\limbo.dis: $R\dis\$$(@F)
    copy $** $@

build-img1: build-img1-sources
    @echo "** Passing control to inferno..."
    .\emu1.exe -rimg1 sh.dis -x /build
    @echo "** ...control returning to host"

## ------------------------------ BUILD RULES ------------------------------
# Deliberately naive and verbose

E=emu
CFLAGS=/INt/386/include /Iemu/port /Iemu/Nt /DEMU /INt/386/boot

# emu.c is strictly generated during the normal build (as are srv.h srvm.h)
# Bootstrap using modified files
$O/$E/emu0.obj: Nt/386/boot/emu0.c
    $C $(CFLAGS) /Iemu /DKERNDATE=123 /c /Fo:$@ $**
$O/$E/emu1.obj: Nt/386/boot/emu1.c
    $C $(CFLAGS) /Iemu /DKERNDATE=123 /c /Fo:$@ $**

# Core files, some customised for Windows
# include/mathi.h include/interp.h include/isa.h include/mp.h include/libsec.h include/keyboard.h include/kernel.h include/raise.h include/draw.h include/memdraw.h include/memlayer.h
$O/$E/os.obj: emu/Nt/os.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/emu.root.obj: boot/emu/emu.root.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/lock.obj: emu/port/lock.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/fp.obj: emu/Nt/fp.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/r16.obj: emu/Nt/r16.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/vlrt.obj: emu/Nt/vlrt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/srv.obj: emu/port/srv.c
    $C $(CFLAGS) /c /Fo:$@ $**

# Devices
$O/$E/devroot.obj: emu/port/devroot.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devcons.obj: emu/port/devcons.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devenv.obj: emu/port/devenv.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devmnt.obj: emu/port/devmnt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devpipe.obj: emu/port/devpipe.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devprog.obj: emu/port/devprog.c
    $C $(CFLAGS) /I$O/libinterp /c /Fo:$@ $**
$O/$E/devprof.obj: emu/port/devprof.c
    $C $(CFLAGS) /I$O/libinterp /c /Fo:$@ $**
$O/$E/nosrv.obj: emu/port/nosrv.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devsrv.obj: emu/port/devsrv.c
    $C $(CFLAGS) /I$O/libinterp /c /Fo:$@ $**
$O/$E/devdup.obj: emu/port/devdup.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devssl.obj: emu/port/devssl.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devcap.obj: emu/port/devcap.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devfs.obj: emu/Nt/devfs.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devcmd.obj: emu/port/devcmd.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/cmd.obj: emu/Nt/cmd.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devindir.obj: emu/port/devindir.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devdraw.obj: emu/port/devdraw.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/win.obj: emu/Nt/win.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/nowin.obj: emu/port/nowin.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devip.obj: emu/port/devip.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/ipif.obj: emu/Nt/ipif.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/ipif6.obj: emu/Nt/ipif6.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/ipaux.obj: emu/port/ipaux.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/deveia.obj: emu/Nt/deveia.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devaudio.obj: emu/port/devaudio.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/audio.obj: emu/Nt/audio.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devmem.obj: emu/port/devmem.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devarch.obj: emu/Nt/devarch.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/nopointer.obj: emu/port/nopointer.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devpointer.obj: emu/port/devpointer.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devsnarf.obj: emu/port/devsnarf.c
    $C $(CFLAGS) /c /Fo:$@ $**

# Ports (core emulator code)
$O/$E/alloc.obj: emu/port/alloc.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/cache.obj: emu/port/cache.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/chan.obj: emu/port/chan.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/dev.obj: emu/port/dev.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/devtab.obj: emu/port/devtab.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/dial.obj: emu/port/dial.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/dis.obj: emu/port/dis.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/discall.obj: emu/port/discall.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/env.obj: emu/port/env.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/error.obj: emu/port/error.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/errstr.obj: emu/port/errstr.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/exception.obj: emu/port/exception.c
    $C $(CFLAGS) /I$O/libinterp /c /Fo:$@ $**
$O/$E/exportfs.obj: emu/port/exportfs.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/inferno.obj: emu/port/inferno.c
    $C $(CFLAGS) /I$O/libinterp /c /Fo:$@ $**
$O/$E/latin1.obj: emu/port/latin1.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/main.obj: emu/port/main.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/parse.obj: emu/port/parse.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/pgrp.obj: emu/port/pgrp.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/print.obj: emu/port/print.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/proc.obj: emu/port/proc.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/qio.obj: emu/port/qio.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/random.obj: emu/port/random.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/sysfile.obj: emu/port/sysfile.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$E/uqid.obj: emu/port/uqid.c
    $C $(CFLAGS) /c /Fo:$@ $**

## lib9
L=lib9
CFLAGS=/INt/386/include

$O/$L/convD2M.obj: lib9/convD2M.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/convM2D.obj: lib9/convM2D.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/convM2S.obj: lib9/convM2S.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/convS2M.obj: lib9/convS2M.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/fcallfmt.obj: lib9/fcallfmt.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/runestrchr.obj: lib9/runestrchr.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/runestrlen.obj: lib9/runestrlen.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/runetype.obj: lib9/runetype.c lib9/runetypebody-6.2.0.h
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/strtoll.obj: lib9/strtoll.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/strtoull.obj: lib9/strtoull.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rune.obj: lib9/rune.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/argv0.obj: lib9/argv0.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/charstod.obj: lib9/charstod.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/cistrcmp.obj: lib9/cistrcmp.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/cistrncmp.obj: lib9/cistrncmp.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/cistrstr.obj: lib9/cistrstr.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/cleanname.obj: lib9/cleanname.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/create.obj: lib9/create.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/dirwstat.obj: lib9/dirwstat.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/dofmt.obj: lib9/dofmt.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/dorfmt.obj: lib9/dorfmt.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/errfmt.obj: lib9/errfmt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/exits.obj: lib9/exits.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/fmt.obj: lib9/fmt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/fmtfd.obj: lib9/fmtfd.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/fmtlock.obj: lib9/fmtlock.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/fmtprint.obj: lib9/fmtprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/fmtquote.obj: lib9/fmtquote.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/fmtrune.obj: lib9/fmtrune.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/fmtstr.obj: lib9/fmtstr.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/fmtvprint.obj: lib9/fmtvprint.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/fprint.obj: lib9/fprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/getfields.obj: lib9/getfields.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/nulldir.obj: lib9/nulldir.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/pow10.obj: lib9/pow10.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/print.obj: lib9/print.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/qsort.obj: lib9/qsort.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/readn.obj: lib9/readn.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rerrstr.obj: lib9/rerrstr.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/runeseprint.obj: lib9/runeseprint.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/runesmprint.obj: lib9/runesmprint.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/runesnprint.obj: lib9/runesnprint.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/runevseprint.obj: lib9/runevseprint.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/seek.obj: lib9/seek.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/seprint.obj: lib9/seprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/smprint.obj: lib9/smprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/snprint.obj: lib9/snprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/sprint.obj: lib9/sprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/strdup.obj: lib9/strdup.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/strecpy.obj: lib9/strecpy.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/sysfatal.obj: lib9/sysfatal.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/tokenize.obj: lib9/tokenize.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/u16.obj: lib9/u16.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/u32.obj: lib9/u32.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/u64.obj: lib9/u64.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/utflen.obj: lib9/utflen.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/utfnlen.obj: lib9/utfnlen.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/utfrrune.obj: lib9/utfrrune.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/utfrune.obj: lib9/utfrune.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/utfecpy.obj: lib9/utfecpy.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/vfprint.obj: lib9/vfprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/vseprint.obj: lib9/vseprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/vsmprint.obj: lib9/vsmprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/vsnprint.obj: lib9/vsnprint.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/dirstat-Nt.obj: lib9/dirstat-Nt.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/errstr-Nt.obj: lib9/errstr-Nt.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/getuser-Nt.obj: lib9/getuser-Nt.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/getwd-Nt.obj: lib9/getwd-Nt.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/setbinmode-Nt.obj: lib9/setbinmode-Nt.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/lock-Nt-386.obj: lib9/lock-Nt-386.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/pread-Nt.obj: lib9/pread-Nt.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/isnan-posix.obj: lib9/isnan-posix.c
#    $C $(CFLAGS) /c /Fo:$@ $**

## libsec
L=libsec
CFLAGS=/INt/386/include

$O/$L/des.obj: libsec/port/des.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/desmodes.obj: libsec/port/desmodes.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/desECB.obj: libsec/port/desECB.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/desCBC.obj: libsec/port/desCBC.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/des3ECB.obj: libsec/port/des3ECB.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/des3CBC.obj: libsec/port/des3CBC.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/aes.obj: libsec/port/aes.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/blowfish.obj: libsec/port/blowfish.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/idea.obj: libsec/port/idea.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/hmac.obj: libsec/port/hmac.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/md5.obj: libsec/port/md5.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/md5block.obj: libsec/port/md5block.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/md4.obj: libsec/port/md4.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/sha1.obj: libsec/port/sha1.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/sha1block.obj: libsec/port/sha1block.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/sha2.obj: libsec/port/sha2.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/sha256block.obj: libsec/port/sha256block.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/sha512block.obj: libsec/port/sha512block.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/sha1pickle.obj: libsec/port/sha1pickle.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/md5pickle.obj: libsec/port/md5pickle.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rc4.obj: libsec/port/rc4.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/genrandom.obj: libsec/port/genrandom.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/prng.obj: libsec/port/prng.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/fastrand.obj: libsec/port/fastrand.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/nfastrand.obj: libsec/port/nfastrand.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/probably_prime.obj: libsec/port/probably_prime.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/smallprimetest.obj: libsec/port/smallprimetest.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/genprime.obj: libsec/port/genprime.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/dsaprimes.obj: libsec/port/dsaprimes.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/gensafeprime.obj: libsec/port/gensafeprime.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/genstrongprime.obj: libsec/port/genstrongprime.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rsagen.obj: libsec/port/rsagen.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rsafill.obj: libsec/port/rsafill.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rsaencrypt.obj: libsec/port/rsaencrypt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rsadecrypt.obj: libsec/port/rsadecrypt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rsaalloc.obj: libsec/port/rsaalloc.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/rsaprivtopub.obj: libsec/port/rsaprivtopub.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/eggen.obj: libsec/port/eggen.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/egencrypt.obj: libsec/port/egencrypt.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/egdecrypt.obj: libsec/port/egdecrypt.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/egalloc.obj: libsec/port/egalloc.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/egprivtopub.obj: libsec/port/egprivtopub.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/egsign.obj: libsec/port/egsign.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/egverify.obj: libsec/port/egverify.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/dsagen.obj: libsec/port/dsagen.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/dsaalloc.obj: libsec/port/dsaalloc.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/dsaprivtopub.obj: libsec/port/dsaprivtopub.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/dsasign.obj: libsec/port/dsasign.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/dsaverify.obj: libsec/port/dsaverify.c
    $C $(CFLAGS) /c /Fo:$@ $**

## libmath
L=libmath
CFLAGS=/INt/386/include

$O/$L/blas.obj: libmath/blas.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/dtoa.obj: libmath/dtoa.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/fdim.obj: libmath/fdim.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/FPcontrol-Nt.obj: libmath/FPcontrol-Nt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/gemm.obj: libmath/gemm.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/g_fmt.obj: libmath/g_fmt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/gfltconv.obj: libmath/gfltconv.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/pow10.obj: libmath/pow10.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_acos.obj: libmath/fdlibm/e_acos.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_acosh.obj: libmath/fdlibm/e_acosh.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_asin.obj: libmath/fdlibm/e_asin.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_atan2.obj: libmath/fdlibm/e_atan2.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_atanh.obj: libmath/fdlibm/e_atanh.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_cosh.obj: libmath/fdlibm/e_cosh.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_exp.obj: libmath/fdlibm/e_exp.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_fmod.obj: libmath/fdlibm/e_fmod.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_hypot.obj: libmath/fdlibm/e_hypot.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_j0.obj: libmath/fdlibm/e_j0.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_j1.obj: libmath/fdlibm/e_j1.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_jn.obj: libmath/fdlibm/e_jn.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_lgamma_r.obj: libmath/fdlibm/e_lgamma_r.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_log.obj: libmath/fdlibm/e_log.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_log10.obj: libmath/fdlibm/e_log10.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_pow.obj: libmath/fdlibm/e_pow.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/e_rem_pio2.obj: libmath/fdlibm/e_rem_pio2.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_remainder.obj: libmath/fdlibm/e_remainder.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_sinh.obj: libmath/fdlibm/e_sinh.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/e_sqrt.obj: libmath/fdlibm/e_sqrt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/k_cos.obj: libmath/fdlibm/k_cos.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/k_rem_pio2.obj: libmath/fdlibm/k_rem_pio2.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/k_sin.obj: libmath/fdlibm/k_sin.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/k_tan.obj: libmath/fdlibm/k_tan.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_asinh.obj: libmath/fdlibm/s_asinh.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_atan.obj: libmath/fdlibm/s_atan.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_cbrt.obj: libmath/fdlibm/s_cbrt.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_ceil.obj: libmath/fdlibm/s_ceil.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_copysign.obj: libmath/fdlibm/s_copysign.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_cos.obj: libmath/fdlibm/s_cos.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_erf.obj: libmath/fdlibm/s_erf.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_expm1.obj: libmath/fdlibm/s_expm1.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_fabs.obj: libmath/fdlibm/s_fabs.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/s_finite.obj: libmath/fdlibm/s_finite.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_floor.obj: libmath/fdlibm/s_floor.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_ilogb.obj: libmath/fdlibm/s_ilogb.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_log1p.obj: libmath/fdlibm/s_log1p.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_nextafter.obj: libmath/fdlibm/s_nextafter.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_rint.obj: libmath/fdlibm/s_rint.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_scalbn.obj: libmath/fdlibm/s_scalbn.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_sin.obj: libmath/fdlibm/s_sin.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_tan.obj: libmath/fdlibm/s_tan.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/s_tanh.obj: libmath/fdlibm/s_tanh.c
#    $C $(CFLAGS) /c /Fo:$@ $**

## libinterp (strictly requires limbo to generate header files)
# Bootstrap uses pregenerated header files (boot/libinterp)
# Note: native limbo.exe NOT built
L=libinterp
CFLAGS=/INt/386/include /INt/386/boot

# Generate header files from Limbo sources
#M=module
#$O/$L/runt.h: $M/runt.m
#    $B\limbo.exe -a -I$M $** > $@
#$O/$L/sysmod.h: $M/runt.m
#    $B\limbo.exe -t Sys -I$M $** > $@
#$O/$L/keyring.h: $L/keyringif.m
#    $B\limbo.exe -t Keyring -I$M $** > $@
#$O/$L/drawmod.h: $M/runt.m
#    $B\limbo.exe -t Draw -I$M $** > $@
#$O/$L/prefabmod.h: $M/runt.m
#    $B\limbo.exe -t Prefab -I$M $** > $@
#$O/$L/tkmod.h: $M/runt.m
#    $B\limbo.exe -t Tk -I$M $** > $@
#$O/$L/mathmod.h: $M/runt.m
#    $B\limbo.exe -t Math -I$M $** > $@
#$O/$L/loadermod.h: $M/runt.m
#    $B\limbo.exe -t Loader -I$M $** > $@
#$O/$L/freetypemod.h: $M/runt.m
#    $B\limbo.exe -t Freetype -I$M $** > $@
#$O/$L/ipintsmod.h: $M/ipints.m
#    $B\limbo.exe -t IPints -I$M $** > $@
#$O/$L/benchmod.h: $M/bench.m
#    $B\limbo.exe -t Bench -I$M $** > $@
#$O/$L/cryptmod.h: $M/runt.m
#    $B\limbo.exe -t Crypt -I$M $** > $@
#$O/$L/keyringif.h: $L/keyringif.m
#    $B\limbo.exe -a -I$M $** > $@
#$O/$L/bench.h: $M/bench.m
#    $B\limbo.exe -a -I$M $** > $@

$O/$L/alt.obj: libinterp/alt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/comp-386.obj: libinterp/comp-386.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/conv.obj: libinterp/conv.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/crypt.obj: libinterp/crypt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/dec.obj: libinterp/dec.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/dlm-Nt.obj: libinterp/dlm-Nt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/draw.obj: libinterp/draw.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/freetype.obj: libinterp/freetype.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/gc.obj: libinterp/gc.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/geom.obj: libinterp/geom.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/heap.obj: libinterp/heap.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/heapaudit.obj: libinterp/heapaudit.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/ipint.obj: libinterp/ipint.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/link.obj: libinterp/link.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/load.obj: libinterp/load.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/loader.obj: libinterp/loader.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/math.obj: libinterp/math.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/raise.obj: libinterp/raise.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/readmod.obj: libinterp/readmod.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/runt.obj: libinterp/runt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/sign.obj: libinterp/sign.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/vstack.obj: libinterp/stack.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/tk.obj: libinterp/tk.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/validstk.obj: libinterp/validstk.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/xec.obj: libinterp/xec.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/das-386.obj: libinterp/das-386.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/keyring.obj: libinterp/keyring.c
    $C $(CFLAGS) /Ilibkeyring /c /Fo:$@ $**
$O/$L/string.obj: libinterp/string.c
    $C $(CFLAGS) /c /Fo:$@ $**

## libkeyring
#L=libkeyring
#CFLAGS=/I$O/libkeyring /Iboot/libinterp

#$O/$L/dsaalg.obj: $L/dsaalg.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/egalg.obj: $L/egalg.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/rsaalg.obj: $L/rsaalg.c
#    $C $(CFLAGS) /c /Fo:$@ $**

## libdraw
L=libdraw
CFLAGS=/INt/386/include

$O/$L/alloc.obj: libdraw/alloc.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/allocimagemix.obj: libdraw/allocimagemix.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/arith.obj: libdraw/arith.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/bezier.obj: libdraw/bezier.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/border.obj: libdraw/border.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/buildfont.obj: libdraw/buildfont.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/bytesperline.obj: libdraw/bytesperline.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/chan.obj: libdraw/chan.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/cloadimage.obj: libdraw/cloadimage.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/computil.obj: libdraw/computil.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/creadimage.obj: libdraw/creadimage.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/defont.obj: libdraw/defont.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/draw.obj: libdraw/draw.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/drawrepl.obj: libdraw/drawrepl.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/ellipse.obj: libdraw/ellipse.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/font.obj: libdraw/font.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/freesubfont.obj: libdraw/freesubfont.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/getdefont.obj: libdraw/getdefont.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/getsubfont.obj: libdraw/getsubfont.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/init.obj: libdraw/init.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/line.obj: libdraw/line.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/mkfont.obj: libdraw/mkfont.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/openfont.obj: libdraw/openfont.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/poly.obj: libdraw/poly.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/loadimage.obj: libdraw/loadimage.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/readcolmap.obj: libdraw/readcolmap.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/readimage.obj: libdraw/readimage.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/readsubfont.obj: libdraw/readsubfont.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rectclip.obj: libdraw/rectclip.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/replclipr.obj: libdraw/replclipr.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/rgb.obj: libdraw/rgb.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/string.obj: libdraw/string.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/stringbg.obj: libdraw/stringbg.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/stringsubfont.obj: libdraw/stringsubfont.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/stringwidth.obj: libdraw/stringwidth.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/subfont.obj: libdraw/subfont.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/subfontcache.obj: libdraw/subfontcache.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/subfontname.obj: libdraw/subfontname.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/unloadimage.obj: libdraw/unloadimage.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/window.obj: libdraw/window.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/writecolmap.obj: libdraw/writecolmap.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/writeimage.obj: libdraw/writeimage.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/writesubfont.obj: libdraw/writesubfont.c
#    $C $(CFLAGS) /c /Fo:$@ $**

## libmp
L=libmp
CFLAGS=/INt/386/include /Ilibmp/port

$O/$L/mpaux.obj: libmp/port/mpaux.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpfmt.obj: libmp/port/mpfmt.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/strtomp.obj: libmp/port/strtomp.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mptobe.obj: libmp/port/mptobe.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/mptole.obj: libmp/port/mptole.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/betomp.obj: libmp/port/betomp.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/letomp.obj: libmp/port/letomp.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpadd.obj: libmp/port/mpadd.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpsub.obj: libmp/port/mpsub.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpcmp.obj: libmp/port/mpcmp.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/mpfactorial.obj: libmp/port/mpfactorial.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpmul.obj: libmp/port/mpmul.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpleft.obj: libmp/port/mpleft.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpright.obj: libmp/port/mpright.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpvecadd.obj: libmp/port/mpvecadd.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpvecsub.obj: libmp/port/mpvecsub.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpvecdigmuladd.obj: libmp/port/mpvecdigmuladd.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpveccmp.obj: libmp/port/mpveccmp.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpdigdiv.obj: libmp/port/mpdigdiv.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpdiv.obj: libmp/port/mpdiv.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpexp.obj: libmp/port/mpexp.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpmod.obj: libmp/port/mpmod.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpextendedgcd.obj: libmp/port/mpextendedgcd.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mpinvert.obj: libmp/port/mpinvert.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mprand.obj: libmp/port/mprand.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/crt.obj: libmp/port/crt.c
#    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mptoi.obj: libmp/port/mptoi.c
    $C $(CFLAGS) /c /Fo:$@ $**
$O/$L/mptoui.obj: libmp/port/mptoui.c
    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/mptov.obj: libmp/port/mptov.c
#    $C $(CFLAGS) /c /Fo:$@ $**
#$O/$L/mptouv.obj: libmp/port/mptouv.c
#    $C $(CFLAGS) /c /Fo:$@ $**


