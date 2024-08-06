x=input("Entrez une valeur entière positive:");
if x>1
  i=2;
  while mod(x,i)!=0 && i<x
    ++i;
  endwhile
  if i==x
    disp("premier");
  else
    disp("pas premier");
  endif
end
disp("fin");
