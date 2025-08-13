#include <stdio.h>
#include <stdlib.h>
#include <r_socket.h>

int main(void) {
	R2Pipe *r = r2pipe_open (NULL); // "radare2 -N -q0 -");
	if (!r) {
		eprintf ("Failed to open r2pipe\n");
		return 1;
	}

	char *res = r2pipe_cmd (r, "?e hello world");
	if (res) {
		printf ("r2pipe reply: %s\n", res);
		free (res);
	} else {
		printf ("(no response)\n");
	}

	r2pipe_close (r);
	return 0;
}
