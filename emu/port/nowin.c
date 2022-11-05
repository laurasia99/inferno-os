/* Dummy */
#include	<windows.h>

static	HINSTANCE	inst;
static	HINSTANCE	previnst;
static	int		cmdshow;

char	*argv0 = "inferno";
int WINAPI
WinMain(HINSTANCE winst, HINSTANCE wprevinst, LPSTR cmdline, int wcmdshow)
{
	inst = winst;
	previnst = wprevinst;
	cmdshow = wcmdshow;

	/* cmdline passed into WinMain does not contain name of executable.
	 * The globals __argc and __argv to include this info - like UNIX
	 */
	main(__argc, __argv);
	return 0;
}

