/* Exemplo de Programa na linguagem L */

/* Area de declaracoes */

    final EXIT = 0;
    final SUM = 1;
    final MULT = 2;
    final TRANSPOSE = 3;
    final MTX_LEN = 3;

    int i,j,k;
    int mtxA[9];
    int mtxB[9];
    int mtxC[9];
    int sum;
    int operation;

/* Programa Principal */

    writeln("");
	writeln(" *** Matrix Operations *** ");
	writeln("");

    writeln(" -- Menu --");
    writeln(EXIT," - exit");
    writeln(SUM," - mtxA + mtxB ");
    writeln(MULT," - mtxA * mtxB ");
    writeln(TRANSPOSE," - transpose mtxA");
    writeln("");
    write("Choose operation: ");
    readln(operation);
    writeln("");

    if( ( operation > EXIT ) and ( operation <= TRANSPOSE ) ) then begin

        /* Preenche matriz A */
        writeln("Fill Matrix A");
        writeln("");
        for i <- 0 to MTX_LEN - 1 do
            for j <- 0 to MTX_LEN - 1 do
            begin
                write("(",i,",",j,")"," = ");
                readln( mtxA[(i*MTX_LEN)+j] );
            end

        /* Zera matriz C */
         for i <- 0 to MTX_LEN - 1 do
            for j <- 0 to MTX_LEN - 1 do
            begin
                mtxC[(i*MTX_LEN)+j] <- 0;
            end

        if( not ( operation = TRANSPOSE ) ) then begin

            /* Preenche matriz B */
            writeln("Fill Matrix B");
            writeln("");
            for i <- 0 to MTX_LEN - 1 do
                for j <- 0 to MTX_LEN - 1 do
                begin
                    write("(",i,",",j,")"," = ");
                    readln( mtxB[(i*MTX_LEN)+j] );
                end

            for i <- 0 to MTX_LEN - 1 do begin
                for j <- 0 to MTX_LEN - 1 do begin
                    if( operation = SUM ) then begin
                        mtxC[(i*MTX_LEN)+j] <- mtxA[(i*MTX_LEN)+j] + mtxB[(i*MTX_LEN)+j];
                    end
                    else begin
                        sum <- 0;
                        for k <- 0 to MTX_LEN - 1 do begin
                            sum <- sum + mtxA[(i*MTX_LEN)+k] * mtxB[(k*MTX_LEN)+j];
                        end
                    mtxC[(i*MTX_LEN)+j] <- sum;
                    end
                end
            end

        end
        else begin
            for i <- 0 to MTX_LEN - 1 do begin
                for j <- 0 to MTX_LEN - 1 do
                    mtxC[j*MTX_LEN+i] <- mtxA[i*MTX_LEN+j];
                writeln("");
            end

        end

        writeln("calculating...");
        writeln("");

        /* Exibe matrizA */
        writeln("");
        writeln("Show Matrix A");
        writeln("");
        for i <- 0 to MTX_LEN - 1 do begin
            for j <- 0 to MTX_LEN - 1 do
                write(mtxA[(i*MTX_LEN)+j]," ");
            writeln("");
        end

        /* Exibe matrizB */
        writeln("");
        writeln("Show Matrix B");
        writeln("");
        for i <- 0 to MTX_LEN - 1 do begin
            for j <- 0 to MTX_LEN - 1 do
                write(mtxB[(i*MTX_LEN)+j]," ");
            writeln("");
        end

         /* Exibe matrizC*/
        writeln("");
        writeln("Show Matrix C");
        writeln("");
        for i <- 0 to MTX_LEN - 1 do begin
            for j <- 0 to MTX_LEN - 1 do
                write(mtxC[(i*MTX_LEN)+j]," ");
            writeln("");
        end

    end