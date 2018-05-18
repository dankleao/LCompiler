/* Exemplo de Programa na linguagem L */

/* Declarações de constantes e variáveis */

int n[3];
int max <- 0,
    i;
char msg[100];
char character <- 0DDh;

/* Programa Principal */

    msg <- "My first program in L";

    writeln(msg);

    for i <- 0 to 2 do
    begin
        write("Digite um numero: ");
        readln(n[i]);
    end

    if n[0] > n[1] then
    begin
        if n[0] > n[2] then
            max <- n[0];
        else
            max<-n[2];
    end
    else
        if n[1] > n[2] then
            max<-n[1];
        else max<-n[2];

  write("O maior numero e: ", max);


/* Fim do programa principal */