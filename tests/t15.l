int a;
char c <- 'a';
char name[10];
int b[2];
int d[10];
int i;
final MAX = 5;

name <- "Dani";

a <- 9999;

b[0] <- 5;
b[1] <- 15;

/* Programa Principal */

writeln(" *** Bubble Sort *** ");
writeln("");

for i <- 0 to MAX do begin
    readln( d[i] );
end

for i <- 0 to MAX do begin
    write( d[i], " " );
end

writeln("");

/*
for i <- 0 to 10 do
    if( (i % 2) = 0 ) then
        writeln(i);
*/
c <- 'b';

if( a > 10 ) then
    writeln(a);

for i <- 0 to 1 do
    writeln(b[i]);

if( name = "Dani") then
    write(name," is equal");

writeln("");
for i <- 0 to 3 do
    writeln(name[i]);


if( c = 'b' )then
    writeln(name);

c <- 'b';

name <- "Daniel C.L";
writeln(name);
writeln("e igual");
writeln(c);

