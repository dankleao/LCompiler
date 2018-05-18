/* Exemplo de Programa na linguagem L */

/* Area de declaracoes */
int i,j;
final SIZE = 5;
int vector[5];
int element;

/* Programa Principal */

	writeln(" *** Binary Search *** ");
	writeln("");

	for i <- 0 to SIZE - 1 do begin
		write("num ",i, " : ");
		readln(vector[i]);
	end

	writeln("");
	write("element: ");
	readln(element);

	writeln("");
	writeln("Searching...");
	writeln("");

	for i <- 0 to SIZE - 1 do begin
		writeln(vector[i]);
	end

	writeln(element);