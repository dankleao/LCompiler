/* Exemplo de Programa na linguagem L */

int n[3], max, i;

/* Programa Principal */

  for i<-0 to 2 do begin
    write("Digite um numero: ");
    readln(n);
  end

    max <- ( 8*9/10-10+300 );
    max <- not ( 'c' <> 0AAh );
    max <- id[(10%id[0])];

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
