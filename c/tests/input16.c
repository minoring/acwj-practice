int   d, f;
int  *e;

void ford() {
    int minho;
    minho = 3;
    printint(minho);
}

int main() {
  int a, b, c;
  b= 3; c= 5; a= b + c * 10;
  printint(a);

  d= 12; printint(d);
  e= &d; f= *e; printint(f);
  ford(5);
  return(0);
}
