long plus(long, long);
	void sumstore(long x, long y,
		long *dest) {
	long t = plus(x, y);
	*dest = t;
}
