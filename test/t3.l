/* Exemplo de Programa na linguagem L */

int n[10];
char nome[4096];
final MAXITER = 10;
char flag[10];
int k <- 500;
char t <- 'c';

/* Programa Principal */

   n[0] <- 9;
   n[1] <- n[0];


  write("Digite seu nome: ");
  readln(nome);
  for k <- 1 to MAXITER do begin
    writeln("Ola' ",nome);
  end