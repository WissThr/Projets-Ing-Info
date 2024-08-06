n = 0:100;
m = 4:100;
u_n = (n-3) ./ (n+3);
plot( n, u_n, 'Color', 'r' );
const = ones( size(u_n) );
hold on;
plot( n, const, 'Color', 'b', 'LineStyle', '--' );


v_n = (m+3) ./ (m-3);
plot( m, v_n, 'Color', 'g' );
const = ones( size(v_n) );
ylim([-1.5 6.5]);

title('La suite u(n) et v(n) convergent vers 1');
xlabel('n');
ylabel('u(n) et v(n)');
legend('u(n)', 'Valeur 1','v(n)');

hold off;