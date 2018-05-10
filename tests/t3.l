/* Exemplo de Programa na linguagem L */

char nome[10];
int k,i,n[3],max;
int t[10];
char c <- 'c';
char arr[100];

/* Programa Principal */

    for i<- 0 to 2 do begin
        readln(n[i]);
      end

      arr <- "Daniel Cardoso Leao - 512973; PUC Minas Ciencias da computacao. 07/04/2018 23:50 - Sabadao code and coffe hehe!";

      if n[0] > n[1] then begin
        if n[0] > n[2] then
            max <- n[0];
        else
            max<-n[2];
      end
      else
        if n[1] > n[2] then
            max<-n[1];
        else max<-n[2];

      writeln("O maior numero e' ",max);

/*
    readln(nome);

    k <- i;
    k <- t[10];
    c <- 't';
    c <- nome[0];
    nome[0] <- c;
    i <- 10;
    c <- 0DDh;

    writeln("123");
    writeln("iphone");
    writeln("asfdfas");
    writeln(nome);

    for i <- 0 to 10 do
        if( (i % 2) = 0 ) then
            writeln(i);

    if( "123" <> "Daniel" ) then
        writeln("ok");
    else
        writeln("not ok");

    for i <- 1 to 5 do begin
        if( "123" = "Daniel" ) then
            writeln("ok");
        else
            writeln("not ok");
    end

     nome <- "Daniel";

     for k <- 1 to 10 do
        writeln(k);

    writeln("asfdfas");
    writeln(nome);

    if( nome = "Daniel" ) then
        writeln(nome);

        */