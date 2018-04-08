/* Exemplo de Programa na linguagem L */

int n[3], max, i;
char arr[100];

/* Programa Principal */

  for i<-0 to 2 do begin
    write("Digite um numero: ");
    readln(n);
  end

  arr <- "Daniel Cardoso Leao - 512973; PUC Minas Ciencias da computacao. 07/04/2018 23:50 - Sabadao code and coffe hehe!";

  if n[0] > n[1] then begin
    if n[0] > n[2] then
        max<-n[0];
    else max<-n[2];
  end
  else
    if n[1] > n[2] then
        max<-n[1];
    else max<-n[2];

  writeln("O maior numero e' ",max);
