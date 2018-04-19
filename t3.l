/* Exemplo de Programa na linguagem L */

int n[10];
char nome[40];
final MAXITER=00001;
char flag[10];

/* Programa Principal */

  flag <- "";

  n[1] <- 10;

  write("Digite seu nome: ");
  readln(nome);
  for n<-1 to MAXITER do begin
    writeln("Ola' ",nome);
  end