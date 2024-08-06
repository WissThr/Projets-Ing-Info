n = 0:100;
u_n = (n-3) ./ (n+3);
plot( n, u_n, 'Color', 'r' );
const = ones( size(u_n) );
hold on;
plot( n, const, 'Color', 'b', 'LineStyle', '--' );
ylim([-1.5 1.5]);
title('La suite u(n) converge vers 1');
xlabel('n');
ylabel('u(n)');
legend('u(n)', 'Valeur 1');

hold off;