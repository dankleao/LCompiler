/* Exemplo de Programa na linguagem L */

    final TRUE = 1;
    final FALSE = 0;

    int i,j;
    char word[255];
    int isPalindrome;

/* Programa Principal */

    /* Le quantidade de caracteres da palavra */
    write("Word length: ");
    readln(i);

    /* Le palavra */
    write("Word: ");
    readln(word);

    isPalindrome <- TRUE;

    for j <- 0 to ( i / 2 - 1 ) do
    begin
        if( word[j] <> word[i - j - 1] ) then
        begin
                j <- i + 1; /* força a parada da repeticao */
                isPalindrome <- FALSE;
        end
    end

    writeln("analyzing...");

    if( isPalindrome ) then
        write(word," is a palindrome!");
    else
        write(word," is not a palindrome!");