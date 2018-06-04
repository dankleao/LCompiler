/* Exemplo de Programa na linguagem L */

/* Area de declaracoes */

    final EXIT = 0;
    final ASC = 1;
    final DESC = 2;
    final SIZE = 3;

    int i,j;
    int vector[3];
    int temp;
    int order;

/* Programa Principal */

    writeln("");
    writeln(" *** Bubble Sort *** ");
    writeln("");

    /* Le os valores para ordenacao */
    for i <- 0 to SIZE - 1 do
    begin
        write("value ", i," : ");
        readln(vector[i]);
    end

    /* Menu de opcoes */
    writeln("");
    writeln("-- Menu -- ");
    writeln(EXIT, " - exit");
    writeln(ASC," - ascending");
    writeln(DESC," - descending");
    writeln("");
    write("order by: ");
    readln(order);

    /* Ordena o vetor na ordem escolhida pelo usuario */

    if( (order > EXIT) and (order <= DESC) ) then begin

        writeln("");
        writeln(" Sorting...");
        writeln("");

        if( order = ASC ) then
            for i <- 0 to (SIZE - 1) do
            begin
                for j <- 0 to (SIZE - 1) do
                begin
                    if( vector[i] < vector[j] ) then
                    begin
                        temp <- vector[i];
                        vector[i] <- vector[j];
                        vector[j] <- temp;
                    end
                end
            end
        else
            for i <- 0 to (SIZE - 1) do
                begin
                    for j <- 0 to (SIZE - 1) do
                    begin
                        if( vector[i] > vector[j] ) then
                        begin
                            temp <- vector[i];
                            vector[i] <- vector[j];
                            vector[j] <- temp;
                        end
                    end
                end

        /* exibe vetor ordenado */
        for i <- 0 to SIZE - 1 do
            write(vector[i], " ");
    end