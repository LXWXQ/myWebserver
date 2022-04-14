extern void error_exit(const char *s)
{
	perror(s);
	exit(-1);
}