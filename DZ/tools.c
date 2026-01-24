static int ops_count = 0;

int add(int a, int b) { ops_count++; return a + b; }
int sub(int a, int b) { ops_count++; return a - b; }
int get_ops_count() { return ops_count; }